#pragma once
#include <vector>
#include "TypeList.h"
#include "Helpers.h"


template<typename ...T>
struct Nodes {};

template<typename ...T>
struct Nodes<TypeList<T...>> {
	using Type = typename TypeList<T...>::Head;

	std::unique_ptr<Type> current;
	Nodes<typename TypeList<T...>::Tail> next;

	Nodes() {
		//std::cout << "New Node Created" << std::endl;
	}

};

template<typename ...T>
struct Edges {};

template<typename ...T>
struct Edges<TypeList<T...>> {
	using Type = typename TypeList<T...>::Head;

	std::unique_ptr<Type> current;
	Edges<typename TypeList<T...>::Tail> next;

	Edges() {
		//std::cout << "New Edges Created" << std::endl;
	}

};

template<>
struct Edges<EmptyTypeList> {};


template<typename VertexTypeList, typename EdgeTypeList, bool isOrient>
class Graph {};

template<typename ...VertexTypeList, typename ...EdgeTypeList, bool isOrient>
class Graph<TypeList<VertexTypeList...>, TypeList<EdgeTypeList...>, isOrient> {
public:
	using VertexesTypes = typename TypeList<VertexTypeList...>;
	using EdgesTypes = typename TypeList<EdgeTypeList...>;

	bool isOriented;
	Nodes<VertexesTypes> vertexes;
	Edges<EdgesTypes> edges;

	// Валидация
	static_assert(Size<VertexesTypes>::res > 0, "ERROR while creating Graph. Vertex count should be more than 0");
	static_assert(Size<EdgesTypes>::res == Size<VertexesTypes>::res * Size<VertexesTypes>::res, "ERROR while creating Graph. Invalid Edges");
	

	Graph() {
		isOriented = isOrient;
		//std::cout << "Graph constructor" << std::endl;
	}

	template<typename D>
	void dispatch(D d)
	{
		VertexExecuteHelper<0, Size<VertexesTypes>::res>::Dispatch(this, d);
	}

	template<int index, typename T>
	void AddVertex(T vertex) {
		static_assert(Conversion<T, TypeAt<index, VertexesTypes>::res>::equal && index <= Size<VertexesTypes>::res, "ERROR while adding vertex. Incorrect type or index");
		// добавляет вершину T с номером index 
		//std::cout << "Add vertex " << index << " " << isOriented << std::endl;
		VertexHelper<index>::SetVertex(vertexes, vertex);
	}

	template<int index>
	decltype(auto) GetVertex() {
		static_assert(index <= Size<VertexesTypes>::res , "ERROR while getting vertex. Incorrect index");
		// Возвращает вершину графа под индексом index
		//std::cout << "Get vertex " << index << std::endl;
		return VertexHelper<index>::GetVertex(vertexes);
	}

	template<int index1, int index2, typename T>
	void AddEdge(T edge) {
		static_assert(index1 <= Size<VertexesTypes>::res && index2 <= Size<VertexesTypes>::res, "ERROR while adding edge. Incorrect index");
		static_assert(Conversion<T, TypeAt< (index1 * Size<VertexesTypes>::res) + index2, EdgesTypes>::res>::equal, "ERROR while adding edge. Incorrect type");
		// добавляет ребро T между вершинами под индексами index1 и index2 
		//std::cout << "Add edge " << index1 << " " << index2 << std::endl;
		EdgeHelper<(index1 * Size<VertexesTypes>::res) + index2>::SetEdge(edges, edge);
		if (!isOrient && index1 != index2) {
			EdgeHelper<(index2 * Size<VertexesTypes>::res) + index1>::SetEdge(edges, edge);
		}
	};

	template<int index1, int index2>
	decltype(auto) GetEdge() {
		static_assert(index1 <= Size<VertexesTypes>::res && index2 <= Size<VertexesTypes>::res, "ERROR while getting edge. Incorrect index");
		// Возвращает ребро между index1 и index2 вершинами графа 
		return EdgeHelper<(index1 * Size<VertexesTypes>::res) + index2>::GetEdge(edges);
	}

private:

};