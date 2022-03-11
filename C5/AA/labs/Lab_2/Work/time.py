from algos import *
import time

iter = 1
test_sizes = [10, 25, 50, 75, 100, 125, 150]

t_class = []
t_vin = []
t_vin_opt = []

for test in test_sizes:
    time_classic = 0
    time_vinograd = 0
    time_vinograd_opt = 0
    a, b, res = matrix_gen_val(test, test, test, 5)
    for i in range(0, iter):
        t_start = time.process_time()
        vinograd_mat_optimized(res, a, b, test, test, test)
        time_vinograd_opt += time.process_time() - t_start

        t_start = time.process_time()
        vinograd_mat_mult(res, a, b, test, test, test)
        time_vinograd += time.process_time() - t_start

        t_start = time.process_time()
        classic_mat_mult(res, a, b, test, test, test)
        time_classic += time.process_time() - t_start
        
    time_classic = time_classic / iter
    time_vinograd = time_vinograd / iter
    time_vinograd_opt = time_vinograd_opt / iter
    t_class.append(time_classic)
    t_vin.append(time_vinograd)
    t_vin_opt.append(time_vinograd_opt)

print(t_class, t_vin, t_vin_opt)