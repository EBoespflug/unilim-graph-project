#include <cassert>

#include "Graph.h"


template<typename EdgeData, typename GraphModel>
void graph::Graph<EdgeData, GraphModel>::show() const
{
	std::cout << "Node count : " << GraphModel::vertexCount() << std::endl;

	for (auto i{ begin() }; i < end(); ++i)
		for (auto j{ begin() }; j < end(); ++j)
			if (existEdge(edge(i, j)))
				std::cout << i << "==>" << j << " : " << _edgeData.at(edge(i, j)) << std::endl;
}

template<typename EdgeData, typename GraphModel>
void graph::Graph<EdgeData, GraphModel>::addEdge(typename GraphModel::edge_t e, EdgeData&& data)
{
	GraphModel::addEdge(e);
	_edgeData[e] = std::forward<edge_data_t>(data);
}

template<typename EdgeData, typename GraphModel>
EdgeData graph::Graph<EdgeData, GraphModel>::edgeData(typename GraphModel::edge_t e) const
{
	assert(existEdge(e) && "The edge have to exist.");
	return _edgeData.at(e);
}

template<typename EdgeData, typename GraphModel>
bool graph::Graph<EdgeData, GraphModel>::isDirected() const
{
	// Optimize, don't check all
	for (auto i{ begin() }; i < end(); ++i)
		for (auto j{ begin() }; j < end(); ++j)
		{
			auto ij{ existEdge(edge(i, j)) };
			bool ji{ existEdge(edge(j, i)) };
			if ( ij != ji || (ij && ji && (_edgeData.at(edge(i, j)) != _edgeData.at(edge(j, i)))))
				return true;
		}
	return false;
}

template<typename EdgeData, typename GraphModel>
void graph::Graph<EdgeData, GraphModel>::removeEdge(typename GraphModel::edge_t e)
{
	GraphModel::removeEdge(e);
	_edgeData.erase(e);
}