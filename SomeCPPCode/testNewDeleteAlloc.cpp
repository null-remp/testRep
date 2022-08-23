#include <iostream>
#include <vector>

//NEW\DELETE overloading, Allocators
//Standart new/delete overloading

struct S
{
private:

	friend void* operator new(size_t, S*);
	friend int main();
	S() 
	{
		std::cout << "Constructor" << std::endl;
	}
	~S() 
	{
		std::cout << "Destructor" << std::endl;
	}

public:
	int x = 1;
	double d = 0.5;

	/*static void* operator new(size_t n)
	{
		std::cout << "S new " << n << " bytes allocated\n";

		void* p = malloc(n);

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

	static void operator delete(void* p)
	{
		std::cout << "S delete. Memory has been deallocated\n";
		free(p);
	}*/
};

void* operator new(size_t n)
{
	std::cout << n << " bytes allocated\n";
	
	void* p = malloc(n);

	if (!p)
	{
		throw std::bad_alloc();
	}

	return p;
}

void* operator new[](size_t n)
{
	std::cout << "Array of " << n << " bytes allocated\n";

	void* p = malloc(n);

	if (!p)
	{
		throw std::bad_alloc();
	}

	return p;

}

void operator delete(void* p)
{
	std::cout << "Memory has been deallocated\n";
	free(p);
}

void operator delete[](void* p)
{
	std::cout << "Array memory has been deallocated\n";
	free(p);
}

//placement new
void* operator new(size_t, S* p)
{
	return p;
}

struct MyStruct
{

};

MyStruct mystruct;

void* operator new(size_t n, MyStruct)
{
	std::cout << "Custom operator new called" << std::endl;
	return malloc(n);
}


void operator delete (void* p, MyStruct)
{
	std::cout << "Custom operator delete called" << std::endl;

	free(p);
}

int main()
{
	//S* p = new S(); //new-expression
	//delete p;

	//S* p_arr = new S[10];
	//delete[] p_arr;
	//S* p = reinterpret_cast<S*> (operator new(sizeof(S)));
	//new(p) S();
	//delete(p);

	S* p = new(mystruct) S();

	p->~S();
	operator delete(p, mystruct);
	
	return 0;
}