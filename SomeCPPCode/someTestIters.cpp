#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>

// Iterators

//Categories of iterators
// 
// Input Iterator
//		|
// Forward Iterator ++
//		|
// Bidirectional Iterator -- and ++
//		|
// Random Access Iterator += n, -= n, it1 - it2, <, >, ++, --

// std::advance, std::distance functions 
template <typename Iter, typename IterCategory>
void n_advance_helper(Iter& iter, int n, IterCategory)
{
	for (int i = 0; i < n; ++i, ++iter);
}

template <typename Iter>
void n_advance_helper(Iter& iter, int n, std::random_access_iterator_tag)
{
	iter += n;
}

template <typename Iter>
void n_advance(Iter& iter, int n)
{
	n_advance_helper(iter, n, typename std::iterator_traits<Iter>::iterator_category());
}

template <typename Iter, typename IterCategory>
size_t n_distance_helper(Iter& iter_1, Iter& iter_2, IterCategory)
{
	size_t distance = 0;

	//for (; iter_1 != iter_2; ++distance, ++iter_1)

	while (iter_1 != iter_2)
	{
		++distance;
		++iter_1;
	}

	return distance;
}

template <typename Iter>
size_t n_distance_helper(Iter& iter_1, Iter& iter_2, std::random_access_iterator_tag)
{
	return iter_2 - iter_1;
}

template <typename Iter>
size_t n_distance(Iter& iter_1, Iter& iter_2)
{
	return n_distance_helper(iter_1, iter_2, typename std::iterator_traits<Iter>::iterator_category());
}

//std::conditional
template <bool B, typename T, typename F>
struct n_conditional
{
	using type = F;
};

template <typename T, typename F>
struct n_conditional<true, T, F>
{
	using type = T;
};

template <bool B, typename T, typename F>
using n_conditional_t = typename n_conditional<B, T, F>::type;

//reverse iterator
template <typename Iterator>
struct reverse_iterator
{
private:
	Iterator iter;

public:
	reverse_iterator(const Iterator& iter) : iter(iter) {}

	reverse_iterator<Iterator>& operator++()
	{
		--iter;
		return *this;
	}

	Iterator base() const
	{
		return iter;
	}
};

//const-iterator
template <typename T>
class Vector
{
private:
	T* arr;
	size_t size;

public:
	template <bool IsConst>
	class common_iterator
	{
	private:
		n_conditional_t<IsConst, const T*, T*> ptr;
		
	public:
		common_iterator(T* ptr) : ptr(ptr) {}

		using iterator = common_iterator<true>;
		using const_iterator = common_iterator<false>;

		n_conditional_t<IsConst, const T&, T&> operator*()
		{
			return *ptr;
		}

		n_conditional_t<IsConst, const T*, T*> operator->()
		{
			return ptr;
		}

		n_conditional_t<IsConst, iterator&, const_iterator&> operator++()
		{
			++ptr;
			return *this;
		}
	};

	using iterator = common_iterator<true>;
	using const_iterator = common_iterator<false>;



	iterator begin() const
	{
		return iterator(arr);
	}

	iterator end() const
	{
		return iterator(arr + size);
	}

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	reverse_iterator rbegin() const
	{
		return reverse_iterator(arr + size - 1);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(arr - 1);
	}
};

//output iterators

struct IsEven
{
	bool operator()(int x) const
	{
		return x % 2 == 0;
	}
};

//template <typename Container>
//class back_insert_iterator
//{
//	Container& container;
//
//public:
//	back_insert_iterator(Container& container) : container(container) {}
//
//	back_insert_iterator<Container>& operator++()
//	{
//		return *this;
//	}
//
//	back_insert_iterator<Container>& operator*()
//	{
//		return *this;
//	}
//
//	back_insert_iterator<Container>& operator=(const typename Container::value_type& value)
//	{
//		container.push_back(value);
//		return *this;
//	}
//};
//
//template <typename Container>
//back_insert_iterator<Container> back_inserter(Container& container)
//{
//	return back_insert_iterator<Container>(container);
//}

//Stream iterators
template <typename T>
class istream_iterator
{
	std::istream& in;
	T value;

public:
	istream_iterator(std::istream& in) : in(in) 
	{
		in >> value;
	}

	istream_iterator<T>& operator++()
	{
		in >> value;
	}

	T& operator*()
	{
		return value;
	}

};



int main()
{
	std::vector<int> v;

	std::istream_iterator<int> it(std::cin);

	for (size_t i = 0; i < 5; ++i, ++it)
	{
		v.push_back(*it);
	}

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	/*std::list<int> l = { 1, 2, 3, 4, 5 };

	std::vector<int> v;

	std::copy_if(l.begin(), l.end(), std::back_inserter(v), IsEven());
	*/
	
	/*std::list<int> l = { 1, 2, 3, 4, 5 };
	
	for (std::list<int>::reverse_iterator rit = l.rbegin(); rit != l.rend(); ++rit)
	{
		std::cout << *rit;
	}

	std::list<int>::iterator it;
	reverse_iterator<std::list<int>::iterator> res(it);
	res++;*/

	/*
	std::list<int> l = { 10, 20, 30, 40, 50 };

	std::list<int>::const_iterator it = l.cbegin();*/

	//std::cout << *it << '\n';
	//*it = 2;
	//std::cout << *it << '\n';

	/*
	std::list<int> v = { 1, 2, 3, 4, 5 };

	for (int x : v)
	{
		std::cout << x << '\n';
	}

	for (std::list<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << '\n';
	}*/

	/*std::map<int, int> m;

	m[3] = 30;
	m[5] = 50;

	m[9] = 90;

	std::map<int, int>::iterator it = m.find(3);
	std::map<int, int>::iterator it2 = m.find(5);*/

	/*std::list<int> l = { 10, 20, 30, 40, 50 };
	
	std::list<int>::iterator it = l.begin();
	std::list<int>::iterator it2 = l.end();
	
	std::cout << n_distance(it, it2);*/

	return 0;
}