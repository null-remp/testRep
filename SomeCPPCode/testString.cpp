#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <utility>

class String
{
private:
	size_t size = 0;
	char* str = nullptr;

public:
	String() = default;

	String(size_t size, char letter = '\0') : size(size), str(new char[size])
	{
		memset(str, letter, this->size);
	}

	//delegating constructors (since c++11)
	//COPY CONSTRUCTOR (1)
	String(const String& s) : String(s.size, '\0')
	{
		/*size = s.size;
		str = new char[size];
		*/
		std::cout << "called String(const String& s) : String(s.size, '\0')" << std::endl;
		memcpy(str, s.str, size);

	}

	void print() const
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << str[i];
		}
	}

	//DESTRUCTOR (2)
	~String()
	{
		delete[] str;
	}

	//copy-and-swap idioma
	//OPERATOR COPYING (3)
	String& operator=(const String& s)
	{

		String copy = s; // copy constructor will be
	/*if (str)
	{
	delete[] str;
	}

	size = s.size;
	str = new char[size];
	memcpy(str, s.str, size * sizeof(char));

	return *this;*/

		swap(copy);
		return *this;
	}

	//move-constructor (since C++11) (4)
	String(String&& s) noexcept : str(s.str), size(s.size)
	{
		std::cout << "Move constructor has called" << std::endl;
		s.str = nullptr;
		s.size = 0;
	}

	//operator move copying (5)
	String& operator=(String&& s) noexcept
	{
		std::cout << "Called move operator=" << std::endl;
		String new_s = std::move(s); //called move constuctor
		swap(new_s);
		return *this;
	}

	void swap(String& s)
	{
		std::swap(size, s.size);
		std::swap(str, s.str);
	}

	size_t s_size() const
	{
		return size;
	}

	const char& operator[](size_t index) const
	{
		return str[index];
	}

	char& operator[](size_t index)
	{
		
		return str[index];
	}
};

std::ostream& operator << (std::ostream& out, const String& s)
{
	for (size_t i = 0; i < s.s_size(); ++i)
	{
		out << s[i];
	}
	return out;
}

//std::istream& operator >> (std::istream& in, String& s)
//{
//
//}

struct Complex
{
	double re = 0.0;
	double im = 0.0;

	Complex(double x = 0.0, double y = 0.0) : re(x), im(y) {}

	Complex& operator+=(const Complex& c)
	{
		re += c.re;
		im += c.im;

		return *this;
	}

	Complex& operator++()
	{
		this->re += 1;
		this->im += 1;


		return *this;
	}

	Complex operator++(int)
	{
		Complex copy = *this;
		++(*this);
		return copy;
	}

	void print()
	{
		std::cout << "Re: " << re << " and " << " Im: " << im << '\n';
	}
};

bool operator<(const Complex& a, const Complex& b)
{
	return a.re * a.re + a.im * a.im < b.re* b.re + b.im + b.im;
}

bool operator>(const Complex& a, const Complex& b)
{
	return b < a;
}

Complex operator+(const Complex& a, const Complex& b)
{
	Complex copy = a;
	
	return copy += b;
}

void f(int x)
{
	String s(10, 'A');
	s.size = 0;

	std::cout << s.s_size() << '\n';
}

//Functional class, functors
//Callable
struct GreaterThenZero
{
	bool operator()(int x)
	{
		return x > 0;
	}
};

struct MyCompare
{
	bool operator()(int x, int y)
	{
		return abs(x) < abs(y);
	}
};

class Object
{
public:
	int x, y;

	Object()
	{

	}

	Object(int x, int y) : x(x), y(y) {}

	Object(const Object& obj)
	{
		x = obj.x;
		y = obj.y;

		std::cout << "The copy constructor" << std::endl;
	}

	Object& operator=(const Object& obj)
	{
		Object copy = obj;
		x = copy.x;
		y = copy.y;

		std::cout << "Operator of copy" << std::endl;

		return *this;
	}
};

int main()
{
	{
		/*Object obj1(8, 8);
		Object obj2;

		obj2 = obj1;*/
	}

	{
		//std::vector<int> v{ -1, -3, 43, 2, 5 };

		////std::cout << *std::find_if(v.begin(), v.end(), GreaterThenZero());

		// 
		//std::sort(v.begin(), v.end(), MyCompare());

		//std::set<int, std::less<int>> s;
		//s.insert(0);
		//s.insert(-1);
		//s.insert(2);
		
		/*
		for (int x : s)
		{
			std::cout << x << '\n';
		}*/
	}

	{
		//String s(5, 'A');

		//std::cout << s << std::endl;
	}

	{
	/*	Complex x(1.0, 1.0);

		Complex y(2.0, 2.0);
*/

		//copy elision, since (c++11)
		//Complex sum = x + y;
	}

	{
	/*	String str(4, 'A');
		String c_str;
		String cc_str;

		const String const_str(5, 'A');
		String ss(5, 'a');

		ss[0] = 'b';*/

		//const_str.print();
		
	}

	{
		String s(5, 'A');
		String ss = std::move(s);
		std::cout << ss.s_size() << std::endl;
	} 
	
	return 0;
}