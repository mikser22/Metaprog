#include <iostream>
#include <vector>

#include "TypeList.h"
#include "Functor.h"
#include "Graph.h"

struct Cat {};
struct Dog {};
struct CatDog {};


struct DispatchFunctions
{
	void vertexFunction(int index, const std::unique_ptr<Cat>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "MEOW \n";
		};
		std::cout << std::endl;
	}

	void vertexFunction(int index, const std::unique_ptr<Dog>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "BARK \n";
		};
		std::cout << std::endl;
	}

	void vertexFunction(int index, const std::unique_ptr<CatDog>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "MEOW or BARK\n";
		};
		std::cout << std::endl;
	}
};


int main()
{
	Graph<
		TypeList<
			Cat, Dog, CatDog // Типы вершин
		>,
		TypeList< // Типы ребер
			int, int, char,    // (0, 0) (0, 1) (0, 2)
			int, int, float,   // (1, 0) (1, 1) (1, 2)
			double, short, int // (2, 0) (2, 1) (2, 2)
		>,
		false> graph;

	Cat cat;
	Dog dog;
	CatDog cd;
	graph.AddVertex<1>(dog);
	graph.AddVertex<0>(cat);
	graph.AddVertex<2>(cd);
 
	graph.dispatch(DispatchFunctions());
}

