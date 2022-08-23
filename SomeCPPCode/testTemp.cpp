#include <iostream>
#include <type_traits>


//meta function
template <typename U, typename V>
struct is_same
{
	static const bool value = false;
};

template<typename U>
struct is_same<U, U>
{
	static const bool value = true;
};

template <typename T>
struct remove_const
{
	using type = T;
};

template <typename T>
struct remove_const<const T>
{
	using type = T;
};


//Basic type traits.

template <typename U, typename V>
void f(U x, V y)
{
	typename remove_const<U>::type a;
	remove_const_t<U> a1;
	//
	//
	//

	if (is_same<U, V>::value)
	{

	}
	else
	{

	}
}

template <typename T>
class C
{
	C() = delete;

};

//since c++ 14
template <typename T>
using remove_const_t = typename remove_const<T>::type;

//since c++ 17
template <typename U, typename V>
const bool is_same_v = is_same<U, V>::value;

//variadic templates (since c++ 11)

template <typename First, typename Second, typename... Types>
struct is_homogeneous
{
	static const bool value = std::is_same_v<First, Second> && is_homogeneous<Second, Types...>::value;
};

template <typename First, typename Second>
struct is_homogeneous<First, Second>
{
	static const bool value = std::is_same_v<First, Second>;
};

template <typename... Args>
const bool is_homogeneous_v = is_homogeneous<Args...>::value;

void print() {}

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail)
{
	//std::cout << head << '\n';
	std::cout << sizeof...(tail) << '\n';
	print(tail...);
}


int main()
{
	//print(1, 2, "some", 5.0f);
	std::cout << is_homogeneous_v<int, int, int> << '\n';
	
	
	return 0;
}