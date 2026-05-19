#include <iostream>

#define LOG(x) std::cout << x << std::endl;

#include <cstring>
namespace pointer
{
	void main()
	{
		int var = 8;
		// int* ptr = &var;
		// double* q = (double*)&var;
		//*ptr = 10;
		// LOG(var);

		char *buffer = new char[8]; // buffer is a pointer pointing to a block of memory of 8 bytes, which is enough to hold 8 chars
		memset(buffer, 0, 8);		// fill the memory block with 0s, or '\0' in the case of char

		char **ptr = &buffer;

		delete[] buffer;
		std::cin.get();
	}
}

namespace reference
{
	void Increment(int value)
	{
		value++;
	}

	void Increment_ptr(int *value)
	{
		(*value)++;
	}

	void Increment_ref(int &value)
	{
		value++;
	}

	void main()
	{
		int a = 5;
		Increment(a);
		Increment_ptr(&a);
		Increment_ref(a);

		int b = 8;
		int &ref = a;
		ref = b; // a = b; => a=8,b=8,ref=8.

		// int* b = &a;
		// int& ref = a; // create an alias for a, ref is another name for a, it refers to the same memory location as a
		// ref = 2;

		LOG(a);

		std::cin.get();
	}

}

int main()
{
	// pointer::main();
	reference::main();
}