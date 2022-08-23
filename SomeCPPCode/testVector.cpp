#include <iostream>
#include <vector>
#include <deque>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>


//Vector implementation
template <typename T, typename Alloc = std::allocator<T>>
//вторая проблема этого вектора, он небезопасен с точки зрения исключений
class qvector
{
private:
	T* arr;
	size_t size;
	size_t capacity;
	Alloc alloc;

	using Alloc_traits = std::allocator_traits<Alloc>;

public:
	qvector<T, Alloc>& operator=(const qvector<T, Alloc>& another)
	{
		if (this == &another)
		{
			return *this;
		}

		for (size_t i = 0; i < size; i++)
		{
			Alloc_traits::destroy(alloc, arr + i);
			//pop_back();
		}

		Alloc_traits::deallocate(arr, capacity);

		if (Alloc_traits::propagate_on_container_copy_assignment::value
			&& alloc != another.alloc)
		{
			alloc = another.alloc;
		}

		size = another.size;
		capacity = another.capacity;

		Alloc_traits::allocate(alloc, capacity);

		for (size_t i = 0; i < size; i++)
		{
			push_back(another[i]);
		}

		return *this;
	}

	qvector(size_t n, T& value = T(), const Alloc& alloc = Alloc())
	{
		arr = Alloc_traits::allocate(alloc, n);

		size_t i = 0;
		for (; i < n; ++i)
		{
			Alloc_traits::constract(alloc, arr + i, value);
		}
	}

	~qvector()
	{
		for (size_t i = 0; i < size; i++)
		{
			Alloc_traits::destroy(alloc, arr + i);
		}

		Alloc_traits::deallocate(arr, capacity);
	}

	T& operator[](size_t i)
	{
		return arr[i];
	}

	T& at(size_t i)
	{
		if (i >= size)
		{ 
			throw std::out_of_range(".....");
		}
		
		return arr[i];
	}

	const T& operator[](size_t i) const
	{
		return arr[i];
	}

	const T& at(size_t i) const
	{
		if (i >= size)
		{
			throw std::out_of_range(".....");
		}

		return arr[i];
	}

	size_t qsize() const
	{
		return size;
	}

	void resize(size_t n, const T& value = T())
	{
		if (n < capacity)
		{
			reserve(capacity);
		}

		for (size_t i = size; i < n; i++){}
	}

	size_t qcapacity() const
	{
		return capacity;
	}

	void reserve(size_t n)
	{
		if (n <= capacity)
		{
			return;
		}

		//T* new_arr = new T[n];
		//T* new_arr = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]);
		//T* new_arr = alloc.allocate(n);
		T* new_arr = Alloc_traits::allocate(alloc, n);

		/*try
		{
			std::uninitialized_copy(arr, arr + size, new_arr);
		}
		catch (...)
		{
			//delete[] reinterpret_cast<int8_t*>(arr);
			
			Alloc_traits::deallocate(new_arr, n);
			throw;
		}*/
		
		size_t i = 0
		try
		{
			for (; i < size; ++i)
			{
				Alloc_traits::construct(alloc, new_arr + i, std::move(a rr[i]));
				//Alloc_traits::construct(alloc, new_arr + i, arr[i]);
				//new(new_arr + i) T(arr[i]);
				//new_arr[i] = arr[i];
			}	
		}
		catch (...)
		{
			for (size_t j = 0; j < i; j++)
			{
				//(new_arr + i)->~T();
				Alloc_traits::destroy(alloc, new_arr + j);
			}

			//delete[] reinterpret_cast<int8_t*>(arr);
			Alloc_traits::deallocate(new_arr, n);
			throw;
		}
		
		for (size_t i = 0; i < size; ++i)
		{
			//(arr + i)->~T();
			Alloc_traits::destroy(alloc, new_arr + i);

		}
		//delete[] reinterpret_cast<int8_t*>(arr);
		Alloc_traits::deallocate(new_arr, n);

		arr = new_arr;
	}


	//push_back(std::string("some str"));
	void push_back(const T& value) // 1 copy
	{
		if (size == capacity)
		{
			reserve(2 * capacity);
		}

		Alloc_traits::constract(alloc, arr + size, value);
		
		//new(arr + size) std::string(std::string("some str")))
		//new(arr + size) T(value); // 2 copy
		++size;
	}

	//move push_back
	void push_back(T&& value) 
	{
		if (size == capacity)
		{
			reserve(2 * capacity);
		}

		Alloc_traits::constract(alloc, arr + size, std::move(value));
		++size;
	}

	template<typename... Args>
	void emplace_back(const Args&... args)
	{
		if (size == capacity)
		{
			reserve(2 * capacity);
		}

		Alloc_traits::constract(alloc, arr + size, args...);
		
		++size;
	}

	void pop_back()
	{
		//(arr + size - 1)->~T();
		Alloc_traits::destroy(alloc, arr + size - 1);
		--size;
	}
};

//BOOL Vector
template<>
class qvector<bool>
{
	int8_t* arr;
	size_t size;
	size_t capacity;

	struct BitReference
	{
		int8_t* cell;
		uint8_t num;

		BitReference& operator=(bool b )
		{
			 
		}
	};

public:

	BitReference operator[](size_t i)
	{

	}
};

struct Object
{
	Object()
	{
	 	std::cout << "Object()" << std::endl;
	}

	Object(int)
	{
		std::cout << "Object() int" << std::endl;
	}


	void show()
	{
		std::cout << "show()" << std::endl;
	}

	~Object()
	{
		std::cout << "~Object()" << std::endl;
	}
};

//stack, queue, priority_queue

template <typename T, typename Container = std::deque<T>>
class Stack
{
private:
	Container container;

public:
	void push(const T& value)
	{
		container.push_back(value);
	}

	void pop()
	{
		container.pop_back();
	}

	T& top()
	{
		return container.back();
	}
};

int main()
{

	
	/*
	//Object* ptr = new Object[10];
	Object* ptr = reinterpret_cast<Object*>(new int8_t[10 * sizeof(Object)]);

	for (size_t i = 0; i < 10; i++)
	{
		new (ptr + i) Object(); //вызов конструктора по данному адрессу
	}

	for (size_t i = 0; i < 10; i++)
	{
		(ptr + i)->~Object();
	}

	delete[] reinterpret_cast<int8_t*>(ptr);
	*/

	/*std::vector<int> v;

	
	for (size_t i = 0; i < 25; ++i)
	{
		v.push_back(i);

		std::cout << v.size() << " and " << v.capacity() << std::endl;
	}

	std::cout << "!" << std::endl;

	for (size_t i = 0; i < 25; ++i)
	{
		v.pop_back();

		std::cout << v.size() << " and " << v.capacity() << std::endl;
	}

	v.clear();

	std::cout << v.capacity() << std::endl;*/

	return 0;
}