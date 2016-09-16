#ifndef GRAPH_STREAM_H
#define GRAPH_STREAM_H

#include "Graph.h"
#include <string>

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <list>

#include "AdjacencyMatrixModel.h"

namespace graph {
	template<typename EdgeData = void, typename GraphModel = AdjacencyMatrixModel>
	struct GraphStream {
		/* Lis un graphe � partir du fichier situ� au chemin "path".
		 * Le type EdgeData doit surcharger l'op�rateur >> pour les flux std::ifstream. 
		 */
		static graph::Graph<EdgeData, GraphModel> readGraph(const std::string& path);

		/*Sauvegarde un graphe sous la forme d'un fichier texte situ� au chemin "path".
		 * Le type EdgeData doit surcharger l'op�rateur << pour les flux std::ofstream. 
		 */
		static void saveGraph(const Graph<EdgeData, GraphModel>& graph, const std::string& path);
	};

	template<typename GraphModel>
	struct GraphStream<void, GraphModel> {
		/*Lis un graphe non pond�r� � partir du fichier situ� au chemin "path".*/
		static graph::Graph<void, GraphModel> readGraph(const std::string& path);

		/*Sauvegarde un graphe non pond�r� sous la forme d'un fichier texte situ� au chemin "path".*/
		static void saveGraph(const graph::Graph<void, GraphModel>& graph, const std::string& path);
	};
}

#include "GraphStream.tpp"

#endif