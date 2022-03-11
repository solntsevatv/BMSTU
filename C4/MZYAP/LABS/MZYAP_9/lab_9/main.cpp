#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

#define DELTA(start, end) (duration_cast<microseconds>(end - start)).count()

void get_time_float(float a, float b)
{
	float c = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c *= a * b;
	auto end = high_resolution_clock::now();
	cout << "Float mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c += a + b;
	end = high_resolution_clock::now();
	cout << "Float sum: " << DELTA(start, end) << endl;
}

void get_time_double(double a, double b)
{
	double c = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c *= a * b;
	auto end = high_resolution_clock::now();
	cout << "Double mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c += a + b;
	end = high_resolution_clock::now();
	cout << "Double sum: " << DELTA(start, end) << endl;
}

void get_time_long_double(long double a, long double b)
{
	long double c = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c *= a * b;
	auto end = high_resolution_clock::now();
	cout << "Long double mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
		c += a + b;
	end = high_resolution_clock::now();
	cout << "Long double sum: " << DELTA(start, end) << endl;
}

void get_asm_time_float(float a, float b)
{
	float c = 0;
	auto start = high_resolution_clock::now();
	_asm {
		finit
		fld dword ptr [c]
		mov ecx, 100000	
		cycle_add:
			fadd dword ptr [a]
			fadd dword ptr [b]
			loop cycle_add
		fstp dword ptr [c]
	}
	auto end = high_resolution_clock::now();
	cout << "Float asm mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	_asm {
		finit
		fld dword ptr[c]
		mov ecx, 100000
		cycle_mult:
			fmul dword ptr[a]
			fmul dword ptr[b]
			loop cycle_mult
		fstp dword ptr[c]
	}
	end = high_resolution_clock::now();
	cout << "Float asm sum: " << DELTA(start, end) << endl;
}

void get_asm_time_double(double a, double b)
{
	double c = 0;
	auto start = high_resolution_clock::now();
	_asm {
		finit
		fld qword ptr[c]
		mov ecx, 100000
		cycle_add:
		fadd qword ptr[a]
			fadd qword ptr[b]
			loop cycle_add
			fstp qword ptr[c]
	}
	auto end = high_resolution_clock::now();
	cout << "Double asm mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	_asm {
		finit
		fld qword ptr[c]
		mov ecx, 100000
		cycle_mult:
		fmul qword ptr[a]
			fmul qword ptr[b]
			loop cycle_mult
			fstp qword ptr[c]
	}
	end = high_resolution_clock::now();
	cout << "Double asm sum: " << DELTA(start, end) << endl;
}

void get_asm_time_long_double(long double a, long double b)
{
	long double c = 0;
	auto start = high_resolution_clock::now();
	_asm {
		finit
		fld tbyte ptr[c]
		mov ecx, 100000
		cycle_add:
		fadd tbyte ptr[a]
			fadd tbyte ptr[b]
			loop cycle_add
			fstp tbyte ptr[c]
	}
	auto end = high_resolution_clock::now();
	cout << "Long double asm mult: " << DELTA(start, end) << endl;

	c = 0;
	start = high_resolution_clock::now();
	_asm {
		finit
		fld tbyte ptr[c]
		mov ecx, 100000
		cycle_mult:
		fmul tbyte ptr[a]
			fmul tbyte ptr[b]
			loop cycle_mult
			fstp tbyte ptr[c]
	}
	end = high_resolution_clock::now();
	cout << "Long double asm sum: " << DELTA(start, end) << endl;
}

void get_sin(double pi)
{
	cout << "sin pi: " << sin(pi) << endl;
	cout << "sin pi/2: " << sin(pi / 2) << endl;
}

void get_asm_sin()
{
	long double result;
	_asm {
		finit
		fldpi
		fsin 
		fstp tbyte ptr[result]
	}

	cout << "sin pi: " << result << endl;
	int	del = 2;
	_asm {
		finit
		fldpi
		fld dword ptr[del]
		fdiv st(1), st(0)
		fsin
		fstp tbyte ptr[result]
	}

	cout << "sin pi/2: " << result << endl;
}

int main(void)
{
	long double a = 8.121987498379;
	long double b = 2.114231312312;

	get_time_float(float(a), float(b));
	get_time_double(double(a), double(b));
	get_time_long_double(a, b);
	
	cout << endl;

	get_asm_time_float(float(a), float(b));
	get_asm_time_double(double(a), double(b));
	get_asm_time_long_double(a, b);

	cout << endl;

	cout << "Pi = 3.14" << endl;
	get_sin(3.14);
	cout << "Pi = 3.141596" << endl;
	get_sin(3.141596);
	cout << endl;
	get_asm_sin();
	return 0;
}