#include <iostream>

using namespace std;

extern "C" void str_move(const char *src, char *dst, int len);


int str_len(const char* string)
{
	__asm {
	xor eax, eax
	mov ecx, -1
	mov edi, string
	repne scasb
	not ecx
	mov eax, ecx
	}
}


int main()
{
	const char* str = "testing";
	cout << "String: " << str << endl;
	cout << "Strlen: " << str_len(str) << endl;
	
	char new_str[256] = { ' ' };
	str_move(str, new_str, str_len(str));

	cout << "Copied str: " << new_str << endl;

	return 0;
}
