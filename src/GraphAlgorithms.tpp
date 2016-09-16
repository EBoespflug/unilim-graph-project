
#include <map>
// MINIMUM COVERING TREE

template<typename EdgeData, typename GraphModel>
std::pair<GraphModel, EdgeData> graph::kruskal(const graph::Graph<EdgeData, GraphModel>& graph)
{
	assert(!graph.isDirected() && "Precondition's assertion failed : graph can't be directed.");
	assert(graph::isStronglyConnected(graph) && "Precondition's assertion failed : graph have to be connected.");

	using vecType_t = std::pair<std::pair<typename GraphModel::vertex_t, typename GraphModel::vertex_t>, EdgeData>;
	std::vector<vecType_t> data;

	// Filling vector
	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		for (auto j{ i + 1 }; j < graph.end(); ++j)
			if (graph.existEdge(graph.edge(i, j)))
			{
				data.push_back(std::make_pair(std::make_pair(i, j), graph.edgeData(graph.edge(i, j))));
			}

	// Sorting edges.
	std::sort(data.begin(), data.end(), [](const vecType_t& i1, const vecType_t& i2) { return i1.second < i2.second; });

	// Creating tree.
	GraphModel tree{ graph.vertexCount() };
	EdgeData total{};

	auto addCycle{ [&tree](typename GraphModel::vertex_t v1, typename GraphModel::vertex_t v2) {
		auto cc{ graph::stronglyConnectedComponents(tree) };

		for (auto set : cc)
			if (std::find(set.begin(), set.end(), v1) != set.end()
				&& std::find(set.begin(), set.end(), v2) != set.end())
				return true;

		return false;
	} };

	unsigned i{};
	do
	{
		// If it don't make Cycle
		if (!addCycle(data[i].first.first, data[i].first.second))
		{
			// Add
			tree.addEdge(tree.edge(data[i].first.first, data[i].first.second));
			tree.addEdge(tree.edge(data[i].first.second, data[i].first.first));
			total += data[i].second;
		}
		else
			++i;
	} while (i < data.size() && graph::stronglyConnectedComponents(tree).size() > 1u);

	return std::make_pair(tree, total);
}

template<typename EdgeData, typename GraphModel>
std::pair<GraphModel, EdgeData> graph::prim(const graph::Graph<EdgeData, GraphModel>& graph)
{
	assert(!graph.isDirected() && "Precondition's assertion failed : graph can't be directed.");
	assert(graph::isStronglyConnected(graph) && "Precondition's assertion failed : graph have to be connected.");
	if (graph.vertexCount() == 0)
		return std::make_pair(GraphModel{}, EdgeData{});

	GraphModel tree(graph.vertexCount());
	std::vector<bool> addedVertices(graph.vertexCount(), false); // addedVertices[i] = true if the vertex i has been added in the tree.

	using vecType_t = std::pair<std::pair<typename GraphModel::vertex_t, typename GraphModel::vertex_t>, EdgeData>;
	std::vector<vecType_t> data;

	// Filling vector
	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		for (auto j{ i + 1 }; j < graph.end(); ++j)
			if (graph.existEdge(graph.edge(i, j)))
			{
				data.push_back(std::make_pair(std::make_pair(i, j), graph.edgeData(graph.edge(i, j))));
			}


	// Sorting edges.
	std::sort(data.begin(), data.end(), [](const vecType_t& i1, const vecType_t& i2) { return i1.second < i2.second; });

	// Adding one vertex.
	addedVertices[0u] = true;
	EdgeData total{};

	bool ended;// true if no vertex can be added.
	do
	{
		ended = true;

		for (auto vt : data) // For each edge.
		{

			typename GraphModel::vertex_t v1{ vt.first.first };
			typename GraphModel::vertex_t v2{ vt.first.second };

			// Assert that this edge connect one added vertex to a non-added vertex.
			if (addedVertices[v1] != addedVertices[v2])
			{
				typename GraphModel::vertex_t toAdd{ (addedVertices[v1] == false) ? v1 : v2 }; // Picking the not added vertex.
				addedVertices[toAdd] = true; // Add.
											 // Add edges.
				tree.addEdge(tree.edge(v1, v2));
				tree.addEdge(tree.edge(v2, v1));

				total += vt.second;

				ended = false;
				break; // Retart the loop.
			}
		}
	} while (!ended);

	return std::make_pair(tree, total);
}

/* SHORTEST PATH */


template<typename EdgeData, typename GraphModel>
std::map<typename GraphModel::vertex_t, std::pair<EdgeData, typename GraphModel::vertex_t>> graph::djikstra(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start)
{
	
	assert(graph.existVertex(start) && "Precondition's assertion failed : start have to be an existing vertex.");
	
	std::set<typename GraphModel::vertex_t> unsettledVertices;
	std::set<typename GraphModel::vertex_t> settledVertices;
	unsettledVertices.insert(start);
	
	std::map<typename GraphModel::vertex_t, std::pair<EdgeData, typename GraphModel::vertex_t>> distances; // Distance of each vertex and predecessor for the shortest path.
																										   
	distances.insert(std::make_pair(start, std::make_pair(EdgeData{}, graph.begin()))); // Adding start vertex with the value of start.
																					   
	auto lowestDistanceVertex{ [&]() {
		assert(unsettledVertices.size() != 0u && "Lambda precondition's assertion failed : can't be called with an empty set of unsettled vertices.");
		
		auto f{ unsettledVertices.begin() };
		std::pair<EdgeData, typename GraphModel::vertex_t> min{ std::make_pair(distances[*f].first, *f) };

		for (auto& v : unsettledVertices)
			if (distances.count(v) != 0)
			{
				EdgeData d{ distances[v].first };
				if (d < min.first)
					min = std::make_pair(d, v);
			}
		return min.second;
		
	} };
	
	while (!unsettledVertices.empty())
	{
		typename GraphModel::vertex_t current{ lowestDistanceVertex() };
		unsettledVertices.erase(unsettledVertices.find(current));
		settledVertices.insert(current);

		// Test neighboors.
		for (auto i{ graph.begin() }; i < graph.end(); ++i)
			if (settledVertices.find(i) == settledVertices.end()) // Unsettled.
				if (graph.existEdge(graph.edge(current, i)))
				{
					EdgeData d{ distances[current].first + graph.edgeData(graph.edge(current, i)) };

					if (distances.count(i) == 0 || distances[i].first > d) // If d[i] == inf || d[i] > d.
					{
						distances[i].first = d;
						distances[i].second = current;
						unsettledVertices.insert(i);
					}
				}
	}

	return distances;
}


template<typename EdgeData, typename GraphModel>
std::pair<std::vector<std::map<typename GraphModel::vertex_t, EdgeData>>, bool>  graph::bellmanFord(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start)
{
	assert(graph.existVertex(start) && "Precondition's assertion failed : start have to be an existing vertex.");

	std::vector<std::map<typename GraphModel::vertex_t, EdgeData>> distances(graph.vertexCount());
	distances[0u].insert(std::make_pair(start, EdgeData{}));

	for (auto k{ 1u }; k < distances.size(); ++k)
		for (auto i{ graph.begin() }; i < graph.end(); ++i)
		{

			if (distances[k - 1].count(i) != 0) // d[k - 1, i] != inf.
				distances[k].insert(std::make_pair(i, distances[k - 1][i])); // d[k, i] = d[k - 1, i].
			for (auto j{ graph.begin() }; j < graph.end(); ++j)
				if (graph.existEdge(graph.edge(j, i))) // for each edge.
					if (distances[k - 1].count(j) != 0) // d[k - 1, j] != inf.
					{
						EdgeData d{ distances[k - 1][j] + graph.edgeData(graph.edge(j, i)) };
						if (distances[k].count(i) == 0 || distances[k][i] > d) // d[k][i] = inf || d[k][i] > d.
							distances[k][i] = d;
					}
		}

	// Check for negative-weight cycles.
	const auto n{ graph.vertexCount() - 1 };
	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		for (auto j{ graph.begin() }; j < graph.end(); ++j)
			if (graph.existEdge(graph.edge(j, i))) // for each edge.
				if (distances[n].count(j) != 0) // d[|graph| - 1, j] != inf.
					if (distances[n].count(i) == 0 || distances[n][i] >(distances[n][j] + graph.edgeData(graph.edge(j, i)))) // d[k][i] = inf || d[k][i] > d.
						return std::make_pair<std::vector<std::map<typename GraphModel::vertex_t, EdgeData>>, bool>({}, true);

	return std::make_pair(distances, false);
}

/* COLORATION */

template<typename GraphModel>
std::vector<unsigned> graph::welsh_powell(const GraphModel& graph)
{
	assert(!graph.isDirected() && "Precondition's assertion failed : graph can't be directed.");

	if (graph.vertexCount() == 0u)
		return{};
	std::vector<unsigned> result(graph.vertexCount(), 0u); // 0u = unknown color.
	std::vector<typename GraphModel::vertex_t> vertices;

	// Filling vector.
	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		vertices.push_back(i);


	// Sorting vertices by degree.
	auto degree{ [&](typename GraphModel::vertex_t v) { // Could use graph::successors or graph::predecessors here (but'll be slower).
		unsigned count{}; 
		for (auto i{ graph.begin() }; i < graph.end(); ++i)
			if (graph.existEdge(graph.edge(i, v))) // Directed
				++count;
		return count;
	} };

	std::sort(vertices.begin(), vertices.end(), [&](typename GraphModel::vertex_t v1, typename GraphModel::vertex_t v2) { return degree(v1) > /* decreasing */ degree(v2); });


	// Computing
	typename GraphModel::vertex_t current{ graph.begin() };

	unsigned currentColor{ 1u };

	for (auto i{ 0u }; i < vertices.size(); ++i)
	{
		typename GraphModel::vertex_t currentVertex{ vertices[i] };
		if (result[currentVertex] == 0u) // Don't compute for colored vertices.
		{
			result[currentVertex] = currentColor; // Apply color.
												  // Other vertices.
			for (auto j{ i + 1 }; j < vertices.size(); ++j)
				if (result[vertices[j]] == 0u) // Only non colored vertices.
				{
					bool add{ true }; // Determine if the color will be applied.
					for (auto v{ graph.begin() }; v < graph.end(); ++v)
						if (result[v] == currentColor) // vertices with the same color.
							if (graph.existEdge(graph.edge(vertices[j], v))) // Neightboor.
								add = false;
					if (add)
						result[vertices[j]] = currentColor;
				}
			currentColor++;
		}
	}

	return result;
}