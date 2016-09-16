#include "AdjacencyListModel.h"

#include <cassert>

namespace graph {


	std::pair<AdjacencyListModel::vertex_t, AdjacencyListModel::vertex_t> AdjacencyListModel::_verticesFromEdge(edge_t edge) const
	{
		assert(edge < (_vertices.size() * _vertices.size()) && "Internal precondition's assertion failed : edge have to be a legal edge.");
		
		vertex_t vd{ edge % _vertices.size() };
		vertex_t vo{ (edge - vd) / _vertices.size() };
		return std::make_pair(vo, vd);
	}
	
	AdjacencyListModel::edge_t AdjacencyListModel::edge(vertex_t origin, vertex_t destination) const
	{
		assert(existVertex(origin) && existVertex(destination) && "Precondition's assertion failed : origin and destination have to be existing vertices.");
		return origin* _vertices.size() + destination;
	}

	bool AdjacencyListModel::existVertex(vertex_t v) const
	{
		return v < _vertices.size();
	}

	bool AdjacencyListModel::existEdge(edge_t edge) const
	{
		assert(edge < (_vertices.size() * _vertices.size()) && "Precondition's assertion failed : edge have to be a legal edge.");

		auto v{ _verticesFromEdge(edge) };
		vertex_t vo{ v.first };
		vertex_t vd{ v.second };

		unsigned start{ _vertices[vo] };
		unsigned end;
		if (vo == _vertices.size() - 1u) // Last
			end = (unsigned)_edges.size();
		else
			end = _vertices[vo + 1u];

		for (auto i{ start }; i < end; ++i)
			if (_edges[i] == vd)
				return true;
		return false;
	}

	void AdjacencyListModel::addEdge(edge_t edge)
	{
		assert(edge < (_vertices.size() * _vertices.size()) && "Precondition's assertion failed : edge have to be a legal edge.");

		if (existEdge(edge))
			return;

		auto v{ _verticesFromEdge(edge) };
		vertex_t vo{ v.first };
		vertex_t vd{ v.second };



		_edges.insert(_edges.begin() + _vertices[vo], (unsigned)vd); // Insert Edge.
		for (auto i{ vo + 1u }; i < _vertices.size(); ++i) // Correct indexes.
			_vertices[i]++;
	}

	void AdjacencyListModel::removeEdge(edge_t edge)
	{
		assert(edge < (_vertices.size() * _vertices.size()) && "Precondition's assertion failed : edge have to be a legal edge.");

		auto v{ _verticesFromEdge(edge) };
		vertex_t vo{ v.first };
		vertex_t vd{ v.second };

		unsigned start{ _vertices[vo] };
		unsigned end;
		if (vo == _vertices.size() - 1u) // Last
			end = (unsigned)_edges.size();
		else
			end = _vertices[vo + 1u];

		bool removed{ false };
		for (auto i{ start }; i < end; ++i)
			if (_edges[i] == vd)
			{
				_edges.erase(_edges.begin() + i); // Remove Edge.
				removed = true;				
			}

		if (!removed)
			return;

		for (auto i{ vo + 1u }; i < _vertices.size(); ++i) // Correct indexes.
			_vertices[i]--;
	}

	void AdjacencyListModel::show() const
	{
		std::cout << "Node count : " << _vertices.size() << std::endl;

		for (auto i{ 0u }; i < _vertices.size(); ++i)
			for (auto j{ 0u }; j < _vertices.size(); ++j)
				if (existEdge(edge(i, j)))
					std::cout << i << "==>" << j << std::endl;
	}

	bool AdjacencyListModel::isDirected() const
	{
		// Optimize, don't check all
		for (auto i{ begin() }; i < end(); ++i)
			for (auto j{ begin() }; j < end(); ++j)
				if (existEdge(edge(i, j)) != existEdge(edge(j, i)))
					return true;
		return false;
	}
}