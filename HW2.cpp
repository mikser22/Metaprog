// Задание - https://docs.google.com/document/d/1VA7jwpNpQPGwxwCy05yhw6193TuWwyQXyS4XCU_pnv4/edit

#include <iostream>

 class BaseUnit {};
 class Type1 {};
 class Type2 {};
 class Type3 {};
 class Type4 {};
 class Type5 {};
 class Type6 {};
 class Type7 {};
 class Type8 {};
 class Type9 {};
 class Type10 {};
 class Type11 {};
 class Type12 {};
 class Type13 {};
 class Type14 {};
 class Type15 {};
 class Type16 {};

// Количество элементов на текущем уровне
template <size_t level>
struct LevelSize
{
	static const size_t size = 3 * LevelSize<level - 2>::size;
};

template <>
struct LevelSize<1>
{
	static const size_t size = 3;
};

template <>
struct LevelSize<0>
{
	static const size_t size = 1;
};

// Индекс начального и конечного элемента на уровне
template <size_t level>
struct StartEndLevelIndexes
{
	static const size_t startIndex = StartEndLevelIndexes<level - 1>::endIndex + 1;
	static const size_t endIndex = startIndex + LevelSize<level>::size - 1;
};

template <>
struct StartEndLevelIndexes<1>
{
	static const size_t startIndex = 1;
	static const size_t endIndex = 3;
};

// Индекс следующего элемента после линейного шага
template <size_t currentLevel, size_t currentIndex>
struct NextLinearIndex
{
	static const size_t index = StartEndLevelIndexes<currentLevel + 1>::startIndex + (currentIndex - StartEndLevelIndexes<currentLevel>::startIndex);
};

// Индекс следующего элемента после не линейного шага (самого левого)
template <size_t currentLevel, size_t currentIndex>
struct NextNonLinearIndex
{
	static const size_t index = 3 * (currentIndex - StartEndLevelIndexes<currentLevel>::startIndex) + StartEndLevelIndexes<currentLevel + 1>::startIndex;
};

template <typename T>
struct Holder
{
	T value;
};

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

//LevelX1 - уровень иерархии на который пришли линейным шагом
template <typename T, class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX1;

template <class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX1<Nulltype, TypeList, level, index, Unit>
{
};

//LevelX3 - уровень иерархии на который пришли не линейным шагом
template <typename T, class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX3;

template <class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX3<Nulltype, TypeList, level, index, Unit>
{
};

template <typename T, class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX1 : public LevelX3<typename TypeAt<NextNonLinearIndex<level, index>::index, TypeList>::res, TypeList, NextNonLinearIndex<level, index>::index, level + 1, Unit>,
								 public LevelX3<typename TypeAt<NextNonLinearIndex<level, index>::index + 1, TypeList>::res, TypeList, NextNonLinearIndex<level, index>::index + 1, level + 1, Unit>,
								 public LevelX3<typename TypeAt<NextNonLinearIndex<level, index>::index + 2, TypeList>::res, TypeList, NextNonLinearIndex<level, index>::index + 2, level + 1, Unit>
{
	Unit<T> unit;
};

template <typename T, class TypeList, int index, int level, template <typename> typename Unit>
struct LevelX3 : public LevelX1<typename TypeAt<NextLinearIndex<level, index>::index, TypeList>::res, TypeList, NextLinearIndex<level, index>::index, level + 1, Unit>
{
	Unit<T> unit;
};

template <class TypeList, template <typename> typename Unit>
struct GenCustomHierarchy : public LevelX3<typename TypeAt<1, TypeList>::res, TypeList, 1, 1, Unit>,
														public LevelX3<typename TypeAt<2, TypeList>::res, TypeList, 2, 1, Unit>,
														public LevelX3<typename TypeAt<3, TypeList>::res, TypeList, 3, 1, Unit>
{
	Unit<typename TypeAt<0, TypeList>::res> unit;
};

int main()
{
	//std::cout << LevelSize<2>::size << " " << LevelSize<3>::size << " " << LevelSize<4>::size << std::endl;

	//std::cout << StartEndLevelIndexes<2>::startIndex << " " << StartEndLevelIndexes<2>::endIndex << std::endl;
	//std::cout << StartEndLevelIndexes<3>::startIndex << " " << StartEndLevelIndexes<3>::endIndex << std::endl;

	//std::cout << NextLinearIndex<1, 2>::index << " " << NextLinearIndex<3, 8>::index << " " << NextLinearIndex<3, 11>::index << std::endl;

	//std::cout << NextNonLinearIndex<2, 4>::index << " " << NextNonLinearIndex<2, 6>::index << " " << NextNonLinearIndex<4, 16>::index << std::endl;

	GenCustomHierarchy<
			TypeList<BaseUnit, Type1, Type2, Type3, Type4, Type5, Type6, Type7, Type8, Type9, Type10, Type11, Type12, Type13, Type14, Type15, Type16>,
			Holder>
			x;
}