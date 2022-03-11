#include <iostream>
#include <chrono>
#include <immintrin.h>

using namespace std;
using namespace std::chrono;

#define DELTA(start, end) (duration_cast<nanoseconds>(end - start)).count()

struct vector
{
	float x;
	float y;
	float z;
	float w;
};

void scalar_vector_mult(vector a, vector b)
{
	float c = 0;
	auto start = high_resolution_clock::now();
	c = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	auto end = high_resolution_clock::now();
	cout << "C++ result: " << c << endl;
	cout << " Time (ms): " << DELTA(start, end) << endl;
}

void scalar_vector_mult_asm(vector a, vector b)
{
	float res = 0;
	auto start = high_resolution_clock::now();
	_asm {
		movups xmm0, [a] // load a
		movups xmm1, [b] // load b
		mulps xmm0, xmm1 // mult a * b, res to a (xmm0) [x1*x2, y1*y2, z1*z2, w1*w2]
		movhlps xmm1, xmm0 // move z1*z2, w1*w2 to xmm2
		addps xmm0, xmm1 // add x1*x2 + z1*z2, y1*y2 + z1*z2
		shufps xmm0, xmm0, 11011000b // reconfigure floats displacement in order to sum
		addps xmm0, xmm0 // sum x1*x2 + z1*z2 + y1*y2 + z1*z2
		movss [res], xmm0
	}
	auto end = high_resolution_clock::now();
	cout << "ASM result: " << res << endl;
	cout << " Time (ms): " << DELTA(start, end) << endl;
}



int main(void)
{
	vector a = { 1.0, 2.0, 3.0, 4.0 };
	vector b = { 4.0, 3.0, 2.0, 1.0 };
	float c_1 = 0;
	float c_2 = 0;
	
	scalar_vector_mult(a, b);
	scalar_vector_mult_asm(a, b);
	return 0;
}