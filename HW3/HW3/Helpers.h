#pragma once
#include <vector>

template<int index>
struct VertexHelper;

template<int index>
struct VertexHelper {
	template<typename T, typename Nodes>
	static void SetVertex(Nodes& nodes, T&& vertex)
	{
		VertexHelper<index - 1>::SetVertex(nodes.next, vertex);
	}

	template<typename Nodes>
	static decltype(auto) GetVertex(Nodes& nodes)
	{
		return VertexHelper<index - 1>::GetVertex(nodes.next);
	}
};

template<>
struct VertexHelper<0> {
	template<typename T, typename Nodes>
	static void SetVertex(Nodes& nodes, T&& vertex)
	{
		nodes.current = std::make_unique<typename Nodes::Type>(vertex);
	}

	template<typename Nodes>
	static std::unique_ptr<typename Nodes::Type>& GetVertex(Nodes& nodes)
	{
		return nodes.current;
	}
};


template<int index>
struct EdgeHelper {
	template<typename T, typename Edges>
	static void SetEdge(Edges& edges, T&& edge)
	{
		EdgeHelper<index - 1>::SetEdge(edges.next, edge);
	}

	template<typename Edges>
	static decltype(auto) GetEdge(Edges& edges)
	{
		return EdgeHelper<index - 1>::GetEdge(edges.next);
	}

};

template<>
struct EdgeHelper<0> {
	template<typename T, typename Edges>
	static void SetEdge(Edges& edges, T&& edge)
	{
		edges.current = std::make_unique<typename Edges::Type>(edge);
	}

	template<typename Edges>
	static std::unique_ptr<typename Edges::Type>& GetEdge(Edges& edges)
	{
		return edges.current;
	}
};


// VertexExecuteHelper - помощник для обхода всех вершин графа и выполнения некоторого действия 
template<int index, int size>
struct VertexExecuteHelper
{
	template<typename G, typename D>
	static void Dispatch(G* g, D d)
	{
		d.vertexFunction(index, g->GetVertex<index>());
		VertexExecuteHelper<index + 1, size>::Dispatch(g, d);
	}

};

template<int size>
struct VertexExecuteHelper<size, size>
{
	template<typename G, typename D>
	static void Dispatch(G g, D d)
	{}
};

