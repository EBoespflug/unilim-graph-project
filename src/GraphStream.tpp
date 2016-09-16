#include <fstream>

#include <functional>

// LOAD 

template<typename EdgeData, typename GraphModel>
graph::Graph<EdgeData, GraphModel> graph::GraphStream<EdgeData, GraphModel>::readGraph(const std::string& path)
{
	std::ifstream file{ path };
	if (!file)
		throw std::runtime_error("Can't open the specified file : " + path);

	size_t size;
	file >> size;
	Graph<EdgeData, GraphModel> graph{ size };

	while (!file.eof())
	{
		typename GraphModel::vertex_t origin, des;
		EdgeData data;

		file >> origin;
		file >> des;
		file >> data;

		if (!graph.existVertex(origin) || !graph.existVertex(des))
			throw std::runtime_error("Corrupted file : " + path);
		graph.addEdge(graph.edge(origin, des), std::move(data));
	}

	return graph;
}

template<typename GraphModel>
graph::Graph<void, GraphModel> graph::GraphStream<void, GraphModel>::readGraph(const std::string& path)
{
	std::ifstream file{ path };
	if (!file)
		throw std::runtime_error("Can't open the specified file : " + path);

	size_t size;
	file >> size;
	Graph<void, GraphModel> graph{ size };

	while (!file.eof())
	{
		typename GraphModel::vertex_t origin, des;

		file >> origin;
		file >> des;

		if (!graph.existVertex(origin) || !graph.existVertex(des))
			throw std::runtime_error("Corrupted file : " + path);
		graph.addEdge(graph.edge(origin, des));
	}

	return graph;
}

// SAVE

template<typename EdgeData, typename GraphModel>
void graph::GraphStream<EdgeData, GraphModel>::saveGraph(const Graph<EdgeData, GraphModel>& graph, const std::string& path)
{
	std::ofstream file(path, std::ios::trunc);
	if (!file)
		throw std::runtime_error("Can't open the specified file : " + path);

	file << graph.vertexCount() << std::endl;

	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		for (auto j{ graph.begin() }; j < graph.end(); ++j)
			if (graph.existEdge(graph.edge(i, j)))
				file << i << " " << j << " " << /* edgeData */ std::endl;
}

template<typename GraphModel>
void graph::GraphStream<void, GraphModel>::saveGraph(const Graph<void, GraphModel>& graph, const std::string& path)
{
	std::ofstream file(path, std::ios::trunc);
	if (!file)
		throw std::runtime_error("Can't open the specified file : " + path);

	file << graph.vertexCount() << std::endl;

	for (auto i{ graph.begin() }; i < graph.end(); ++i)
		for (auto j{ graph.begin() }; j < graph.end(); ++j)
			if (graph.existEdge(graph.edge(i, j)))
				file << i << " " << j << " " << std::endl;
}


