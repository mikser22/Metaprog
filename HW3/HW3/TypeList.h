#pragma once

class Nulltype
{
};

template <typename... Args>
struct TypeList
{
	using Head = Nulltype;
	using Tail = Nulltype;
};

template <typename H, typename... T>
struct TypeList<H, T...>
{
	using Head = H;
	using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyTypeList;

template <typename H>
struct TypeList<H>
{
	using Head = H;
	using Tail = EmptyTypeList;
};

template <size_t ind, typename... T>
struct TypeAt
{
	using res = Nulltype;
};

template <size_t ind, typename... T>
struct TypeAt<ind, TypeList<T...>>
{
	using res = typename TypeAt<ind - 1, typename TypeList<T...>::Tail>::res;
};

template <size_t ind>
struct TypeAt<ind, Nulltype>
{
	using res = Nulltype;
};

template <typename... T>
struct TypeAt<0, TypeList<T...>>
{
	using res = typename TypeList<T...>::Head;
};

template<typename T>
struct Size
{
	static constexpr int res = 1;
};

template<>
struct Size<TypeList<>>
{
	static constexpr int res = 0;
};

template<>
struct Size<Nulltype>
{
	static constexpr int res = 0;
};

template<typename ...Args>
struct Size<TypeList<Args...>>
{
	static constexpr int res = 1 + Size<typename TypeList<Args...>::Tail>::res;
};
