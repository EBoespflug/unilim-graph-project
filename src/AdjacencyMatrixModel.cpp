#include "AdjacencyMatrixModel.h"

#include <cassert>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace graph {

	AdjacencyMatrixModel::edge_t AdjacencyMatrixModel::edge(vertex_t origin, vertex_t destination) const
	{
		//std::cout << "or :" << origin << "des" << destination << std::endl;
		assert(existVertex(origin) && existVertex(destination) && "Precondition's assertion failed : origin and destination have to be existing vertices.");
		return origin* _vertexCount + destination;
	}

	bool AdjacencyMatrixModel::existVertex(vertex_t v) const
	{
		return v < _vertexCount;
	}

	bool AdjacencyMatrixModel::existEdge(edge_t edge) const
	{
		assert(edge < (_vertexCount * _vertexCount) && "Precondition's assertion failed : edge have to be a legal edge.");
		return _data.at(edge) == true;
	}

	void AdjacencyMatrixModel::addEdge(edge_t edge)
	{
		assert(edge < (_vertexCount * _vertexCount) && "Precondition's assertion failed : edge have to be a legal edge.");
		_data.at(edge) = true;
	}

	void AdjacencyMatrixModel::removeEdge(edge_t edge)
	{
		assert(edge < (_vertexCount * _vertexCount) && "Precondition's assertion failed : edge have to be a legal edge.");
		_data.at(edge) = false;
	}

	size_t AdjacencyMatrixModel::edgeCount() const
	{
		size_t count{};
		for (auto i{ begin() }; i < end(); ++i)
			for (auto j{ begin() }; j < end(); ++j)
				if (existEdge(edge(i, j)))
					++count;
		return count;
	}

	void AdjacencyMatrixModel::show() const
	{
		std::cout << "Node count : " << _vertexCount << std::endl;

		for (auto i{ 0u }; i < _vertexCount; ++i)
			for (auto j{ 0u }; j < _vertexCount; ++j)
				if (_data.at(i * _vertexCount + j))
					std::cout << i << "==>" << j << std::endl;
	}

	bool AdjacencyMatrixModel::isDirected() const
	{
		// Optimize, don't check all
		for (auto i{ begin() }; i < end(); ++i)
			for (auto j{ begin() }; j < end(); ++j)
				if (existEdge(edge(i, j)) != existEdge(edge(j, i)))
					return true;
		return false;
	}
}