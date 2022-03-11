#include "xcl2.hpp"
#include <algorithm>
#include <cstdio>
#include <random>
#include <vector>

using std::default_random_engine;
using std::generate;
using std::uniform_int_distribution;
using std::vector;

const int DATA_SIZE = 1 << 10;

// ------------------------------------------------------------------------------------

// Генератор случайных чисел для создания массивов

// ------------------------------------------------------------------------------------

 int gen_random() {
 static default_random_engine e;
 static uniform_int_distribution<int> dist(0, 100);

 return dist(e);
}

// ------------------------------------------------------------------------------------

// Функция для проверки  корректности работы ускорителя

// ------------------------------------------------------------------------------------

void var002_no_prragmas(int* c, const int* a, const int* b, const int len) {
    for (int i = 0; i < len; i+=2) {
          if (b[i] > a[i]) {
               c[i] = b[i];
          } else {
               c[i]= a[i];
          }
    }
    for (int i = 1; i < len; i+=2) {
          if (b[i] < a[i]) {
               c[i] = b[i];
          } else {
               c[i]= a[i];
          }
    }
}

// ------------------------------------------------------------------------------------

// Проверка результатов работы ускорителя

// ------------------------------------------------------------------------------------

void verify(const vector<int, aligned_allocator<int> >& gold, const vector<int, aligned_allocator<int> >& out) {
 if (!equal(begin(gold), end(gold), begin(out))) {
 printf("TEST FAILED\n");
 exit(EXIT_FAILURE);
 }
}

int main(int argc, char** argv) {
 if (argc != 2) {
 std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
 return EXIT_FAILURE;
 }

 std::string binaryFile = argv[1];

 // Вычисление размера массива
 size_t size_in_bytes = DATA_SIZE * sizeof(int);
 cl_int err;
 cl::CommandQueue q;
 cl::Context context;
 cl::Program program;

 // Объявление и инициализация исходных массивов размерности DATA_SIZE
 vector<int, aligned_allocator<int> > source_a(DATA_SIZE);
 vector<int, aligned_allocator<int> > source_b(DATA_SIZE);
 vector<int, aligned_allocator<int> > source_results(DATA_SIZE);
 generate(begin(source_a), end(source_a), gen_random);
 generate(begin(source_b), end(source_b), gen_random);

 // Получение списка устройств и инициализация контекста
 auto devices = xcl::get_xil_devices();
 auto fileBuf = xcl::read_binary_file(binaryFile);
 cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
 bool valid_device = false;
 for (unsigned int i = 0; i < devices.size(); i++) {
 auto device = devices[i];
 // Зоздание контекста и очередей команд к устройствам (если их несколько)
 OCL_CHECK(err, context = cl::Context(device, nullptr, nullptr, nullptr, &err));
 OCL_CHECK(err, q = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err));

 std::cout << "Trying to program device[" << i << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
 program = cl::Program(context, {device}, bins, nullptr, &err);
 if (err != CL_SUCCESS) {
 std::cout << "Failed to program device[" << i << "] with xclbin file!\n";
 } else {
 std::cout << "Device[" << i << "]: program successful!\n";
 valid_device = true;
 break; 
 }
 }
 if (!valid_device) {
 std::cout << "Failed to program any device found, exit!\n";
 exit(EXIT_FAILURE);
 }

 // Выделение памяти под буферы устрйства 
 OCL_CHECK(err, cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, source_a.data(),
 &err));
 OCL_CHECK(err, cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, size_in_bytes, source_b.data(),
 &err));
 OCL_CHECK(err, cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, size_in_bytes,
 source_results.data(), &err));

 // Вектор для проверки результатов работы ускорителя 
 vector<int, aligned_allocator<int> > gold(DATA_SIZE);
 var002_no_prragmas(gold.data(), source_a.data(), source_b.data(), DATA_SIZE);

 printf(
 "|-------------------------+-------------------------|\n"
 "| Kernel                  |    Wall-Clock Time (ns) |\n"
 "|-------------------------+-------------------------|\n");

// ------------------------------------------------------------------------------------

 // Тест ускорителя без использования оптимизации (no_pragmas)

// ------------------------------------------------------------------------------------

 OCL_CHECK(err, cl::Kernel kernel_var002_no_prragmas(program, "var002_no_prragmas", &err));

// Устанавливаем необходимые нам значения

 OCL_CHECK(err, err = kernel_var002_no_prragmas.setArg(0, buffer_result));
 OCL_CHECK(err, err = kernel_var002_no_prragmas.setArg(1, buffer_a));
 OCL_CHECK(err, err = kernel_var002_no_prragmas.setArg(2, buffer_b));
 OCL_CHECK(err, err = kernel_var002_no_prragmas.setArg(3, DATA_SIZE));

 // Копируем содержимое буферов в DDR память ускорительной карты
 OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_a, buffer_b}, 0 /* 0 means from host*/));

 cl::Event event;
 uint64_t nstimestart, nstimeend;
 // Запускаем задачу на исполнение и ждем готовности по прерыванию
 OCL_CHECK(err, err = q.enqueueTask(kernel_var002_no_prragmas, nullptr, &event));
 q.finish();

 //Читаем метки времени исполнения задачи
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_START, &nstimestart));
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_END, &nstimeend));
 auto no_pragmas_time = nstimeend - nstimestart;

 printf("| %-22s  | %23lu |\n", "var002_no_prragmas", no_pragmas_time);
 printf("|-------------------------+-------------------------|\n");

 // Читаем обратно данные из DDR памяти устройства в буфер результатов
 OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
 q.finish();
 verify(gold, source_results);

// ------------------------------------------------------------------------------------

 // Тест ускорителя с развертыванием циклов (untolled)

// ------------------------------------------------------------------------------------

 OCL_CHECK(err, cl::Kernel kernel_var002_unrolled(program, "var002_unrolled", &err));

// Устанавливаем необходимые нам значения

 OCL_CHECK(err, err = kernel_var002_unrolled.setArg(0, buffer_result));
 OCL_CHECK(err, err = kernel_var002_unrolled.setArg(1, buffer_a));
 OCL_CHECK(err, err = kernel_var002_unrolled.setArg(2, buffer_b));
 OCL_CHECK(err, err = kernel_var002_unrolled.setArg(3, DATA_SIZE));

 // Второй раз копировать память не требуется: DDR память используется всеми ускорителями
 // Запускаем задачу на исполнение и ждем готовности по прерыванию
 OCL_CHECK(err, err = q.enqueueTask(kernel_var002_unrolled, nullptr, &event));
 q.finish();

 //Читаем метки времени исполнения задачи
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_START, &nstimestart));
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_END, &nstimeend));
 auto unrolled_time = nstimeend - nstimestart;

 printf("| %-22s  | %23lu |\n", "var002_unrolled", unrolled_time);
 printf("|-------------------------+-------------------------|\n");

 // Читаем обратно данные из DDR памяти устройства в буфер результатов
 OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
 q.finish();
 verify(gold, source_results);

// ------------------------------------------------------------------------------------

   // Тест ускорителя с конвейеризацией (pipelined)

// ------------------------------------------------------------------------------------

 OCL_CHECK(err, cl::Kernel kernel_var002_pipelined(program, "var002_pipelined", &err));

// Устанавливаем необходимые нам значения

 OCL_CHECK(err, err = kernel_var002_pipelined.setArg(0, buffer_result));
 OCL_CHECK(err, err = kernel_var002_pipelined.setArg(1, buffer_a));
 OCL_CHECK(err, err = kernel_var002_pipelined.setArg(2, buffer_b));
 OCL_CHECK(err, err = kernel_var002_pipelined.setArg(3, DATA_SIZE));

 // Второй раз копировать память не требуется: DDR память используется всеми ускорителями
 // Запускаем задачу на исполнение и ждем готовности по прерыванию
 OCL_CHECK(err, err = q.enqueueTask(kernel_var002_pipelined, nullptr, &event));
 q.finish();

 //Читаем метки времени исполнения задачи
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_START, &nstimestart));
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_END, &nstimeend));
 auto pipelined_time = nstimeend - nstimestart;

 printf("| %-22s  | %23lu |\n", "var002_pipelined", pipelined_time);
 printf("|-------------------------+-------------------------|\n");

 // Читаем обратно данные из DDR памяти устройства в буфер результатов
 OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
 q.finish();
 verify(gold, source_results);

 // -------------------------------------------------------------------------------------------------
 // Тест ускорителя с развертыванием цикла и конвейеризацией (pipe_unroll)
 // -------------------------------------------------------------------------------------------------

 OCL_CHECK(err, cl::Kernel kernel_var002_pipe_unroll(program, "var002_pipe_unroll", &err));

// Устанавливаем необходимые нам значения

 OCL_CHECK(err, err = kernel_var002_pipe_unroll.setArg(0, buffer_result));
 OCL_CHECK(err, err = kernel_var002_pipe_unroll.setArg(1, buffer_a));
 OCL_CHECK(err, err = kernel_var002_pipe_unroll.setArg(2, buffer_b));
 OCL_CHECK(err, err = kernel_var002_pipe_unroll.setArg(3, DATA_SIZE));

 // Второй раз копировать память не требуется: DDR память используется всеми ускорителями
 // Запускаем задачу на исполнение и ждем готовности по прерыванию
 OCL_CHECK(err, err = q.enqueueTask(kernel_var002_pipe_unroll, nullptr, &event));
 q.finish();

 //Читаем метки времени исполнения задачи
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_START, &nstimestart));
 OCL_CHECK(err, err = event.getProfilingInfo<uint64_t>(CL_PROFILING_COMMAND_END, &nstimeend));
 auto pipe_unroll_time = nstimeend - nstimestart;

 printf("| %-22s  | %23lu |\n", "var002_pipe_unroll", pipe_unroll_time);
 printf("|-------------------------+-------------------------|\n");
 printf(
 "Note: Wall Clock Time is meaningful for real hardware execution "
 "only, not for emulation.\n");
 printf(
 "Please refer to profile summary for kernel execution time for "
 "hardware emulation.\n");

 // Читаем обратно данные из DDR памяти устройства в буфер результатов
 OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_result}, CL_MIGRATE_MEM_OBJECT_HOST));
 q.finish();
 verify(gold, source_results);

 printf("TEST PASSED.\n");
 return EXIT_SUCCESS;
}