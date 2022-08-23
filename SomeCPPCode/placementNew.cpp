#include <iostream>
#include <new>

struct MyStruct
{
	int x;

	MyStruct()
	{
		x = 1;
		std::cout << "MyStruct()" << std::endl;
	}

	MyStruct(MyStruct&)
	{
		std::cout << "MyStruct() Copy" << std::endl;
		x = 2;
	}

	MyStruct(const int val) : x(val) 
	{
		std::cout << "MyStruct with parms" << std::endl;
	}

	MyStruct& operator=(const MyStruct&) = delete;

	void print_x()
	{
		std::cout << "X is " << x << std::endl;
	}

	~MyStruct()
	{
		std::cout << "~MyStruct()" << std::endl;
	}
};

int main()
{
	/*
	const int N = 10;
	const int BUF_SIZE = N * sizeof(double);
	
	std::cout << "BUF_SIZE is " << BUF_SIZE << std::endl;
	std::cout << "sizeof(int) is " << sizeof(int) << std::endl;
	int8_t buffer[BUF_SIZE];
		
	int* ptr = nullptr;
	ptr = new(buffer) int[N * 2];

	double val = 3;

	for (size_t i = 0; i < N * 2; i++)
	{
		ptr[i] = val;
		val += 3;
	}

	for (size_t i = 0; i < N * 2; i++)
	{
		std::cout << ptr[i] << std::endl;
	}
	*/

	{
	/*	MyStruct* p = (MyStruct*)operator new(sizeof(MyStruct));
		new(p) MyStruct();

		p->~MyStruct();

		operator delete(p);*/
	}

	//int a = int(10); //functional notation
	//std::cout << a;

	{
		/*int a;
		new(&a) int(10);

		std::cout << "a: " << a << std::endl;
		std::cout << std::endl;

		int* ptr = new int;
		ptr = (int*)operator new(sizeof(int));
		new(ptr) int(33);

		delete operator();
		delete(ptr);*/
	}

	{
		/*int a[10];
		new(a) int[10]{ 1,2,3,5,6,7,8,9,1,1 };

		for (size_t i = 0; i < 10; i++)
		{
			std::cout << a[i] << std::endl;
		}*/
	}

	/*{
		MyStruct* ptr = (MyStruct*) operator new(sizeof(MyStruct));
		new (ptr) MyStruct(10);
		delete(ptr);

	}
	{

		MyStruct* ptr = (MyStruct*) operator new(sizeof(MyStruct));
		new (ptr) MyStruct(10);

		ptr->~MyStruct();
		operator delete(ptr);
	}*/

	{
		//int a;
		//new (&a) int(10);     
		//std::cout << a;

		//std::cout << '\n';
		//int* ptr = new int;
		//ptr = (int*)operator new(sizeof(int));
		//ptr = new (ptr) int(33);   
		//std::cout << *ptr << '\n'; 
		//operator delete(ptr);      
		//delete ptr;                

	}
	return 0;
}