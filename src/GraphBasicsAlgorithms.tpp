#include <queue>
#include <cassert>
#include <iterator>
#include <algorithm>

/* TRAVERSAL */

template<typename GraphModel>
void graph::traversal::depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function)
{
	assert(graph.existVertex(firstVertex) && "Precondition assertion failed : firstVertex have to be an existing vertex.");
	std::set<typename GraphModel::vertex_t> exploredVertices;

	internal_::depthFirstTraversal(graph, firstVertex, exploredVertices, std::move(function));
}

template<typename GraphModel>
void graph::traversal::breadthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function)
{
	assert(graph.existVertex(firstVertex) && "Precondition assertion failed : firstVertex have to be an existing vertex.");
	std::queue<typename GraphModel::vertex_t> queue;
	std::set<typename GraphModel::vertex_t> exploredVertices;

	queue.push(firstVertex);
	exploredVertices.insert(firstVertex);

 while (!queue.empty())
	{
		typename GraphModel::vertex_t vertex = queue.front();
		queue.pop();

		if(function)
			function(vertex);

		for (const auto& item : graph::neighbourhood::successors(graph, vertex))
			if (std::find(exploredVertices.begin(), exploredVertices.end(), item) == exploredVertices.end())
			{
				exploredVertices.insert(item);
				queue.push(item);
			}
	}
}


// internal_

template<class GraphModel>
void graph::traversal::internal_::depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t v, std::set<typename GraphModel::vertex_t>& exploredVertices, std::function<void(typename GraphModel::vertex_t&)>&& function)
{
	assert(graph.existVertex(v) && "Precondition assertion failed : v have to be an existing vertex.");
	if (std::find(exploredVertices.begin(), exploredVertices.end(), v) == exploredVertices.end())
	{
		if (function)
			function(v);
		exploredVertices.insert(v);

		for (const auto& item : graph::neighbourhood::successors(graph, v))
			depthFirstTraversal(graph, item, exploredVertices, std::move(function));
	}
}

/* CONNECTED_COMPONENT */

template<typename GraphModel>
std::set<typename GraphModel::vertex_t> graph::connected_component::stronglyConnectedComponent(typename GraphModel::vertex_t v, const GraphModel& graph)
{
	assert(graph.existVertex(v) && "Precondition assertion failed : v have to be an existing vertex.");

	auto succ{ graph::neighbourhood::successors(graph, v, graph.vertexCount()) };
	auto pred{ graph::neighbourhood::predecessors(graph, v, graph.vertexCount()) };

	decltype(succ) intersect;
	std::set_intersection(succ.begin(), succ.end(), pred.begin(), pred.end(), std::inserter(intersect, intersect.begin()));

	intersect.insert(v);
	return intersect;
}

template<typename GraphModel>
std::vector<std::set<typename GraphModel::vertex_t>> graph::connected_component::stronglyConnectedComponents(const GraphModel& graph)
{
	std::vector<std::set<typename GraphModel::vertex_t>> ret;

	auto unexploredVertices{ [&graph](const decltype(ret)& ret) {
		if (ret.empty())
			return std::make_pair(graph.begin(), true);
		for (typename GraphModel::vertex_t i = graph.begin(); i < graph.end(); ++i)
		{
			bool found = false;		
			for (const auto& set : ret)
				if (std::find(set.begin(), set.end(), i) != set.end())
					found = true;
			if (!found)
				return std::make_pair(i, true);
		}
		return std::make_pair(typename GraphModel::vertex_t{}, false);
	} };

	auto unexplored{ unexploredVertices(ret) };
	while (unexplored.second)
	{
		ret.push_back(stronglyConnectedComponent(unexplored.first, graph));
		unexplored = unexploredVertices(ret);	// Checking unexploredVertexes.
	}

	return ret;
}

/* NEIGHBOURHOOD */

template<class GraphModel>
std::set<typename GraphModel::vertex_t> graph::neighbourhood::successors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth)
{
	if (depth > graph.vertexCount()) // Restrict lookup depth.
		depth = graph.vertexCount();

	std::set<typename GraphModel::vertex_t> ret;

	internal_::successors(graph, v, depth, ret);
	return ret;
}

template<class GraphModel>
std::set<typename GraphModel::vertex_t> graph::neighbourhood::predecessors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth)
{
	if (depth > graph.vertexCount()) // Restrict lookup depth.
		depth = graph.vertexCount();

	std::set<typename GraphModel::vertex_t> ret;

	internal_::predecessors(graph, v, depth, ret);
	return ret;
}

// internal_

template<class GraphModel>
void graph::neighbourhood::internal_::successors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth, std::set<typename GraphModel::vertex_t>& set)
{
	assert(graph.existVertex(v) && "Private precondition assertion failed : v have to be an existing vertex.");

	if (depth != 0u)
		for (auto i{ graph.begin()}; i < graph.end(); ++i)
			if(graph.existEdge(graph.edge(v, i)))
				if (std::find(set.begin(), set.end(), i) == set.end())
				{
					set.insert(i);
					successors(graph, i, depth - 1, set);
				}
}

template<class GraphModel>
void graph::neighbourhood::internal_::predecessors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth, std::set<typename GraphModel::vertex_t>& set)
{
	assert(graph.existVertex(v) && "Private precondition assertion failed : v have to be an existing vertex.");

	if (depth != 0u)
		for (auto i{ graph.begin() }; i < graph.end(); ++i)
			if (graph.existEdge(graph.edge(i, v)))
				if (std::find(set.begin(), set.end(), i) == set.end())
				{
					set.insert(i);
					predecessors(graph, i, depth - 1, set);
				}
}
