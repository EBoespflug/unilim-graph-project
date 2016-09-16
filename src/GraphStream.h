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
		/* Lis un graphe à partir du fichier situé au chemin "path".
		 * Le type EdgeData doit surcharger l'opérateur >> pour les flux std::ifstream. 
		 */
		static graph::Graph<EdgeData, GraphModel> readGraph(const std::string& path);

		/*Sauvegarde un graphe sous la forme d'un fichier texte situé au chemin "path".
		 * Le type EdgeData doit surcharger l'opérateur << pour les flux std::ofstream. 
		 */
		static void saveGraph(const Graph<EdgeData, GraphModel>& graph, const std::string& path);
	};

	template<typename GraphModel>
	struct GraphStream<void, GraphModel> {
		/*Lis un graphe non pondéré à partir du fichier situé au chemin "path".*/
		static graph::Graph<void, GraphModel> readGraph(const std::string& path);

		/*Sauvegarde un graphe non pondéré sous la forme d'un fichier texte situé au chemin "path".*/
		static void saveGraph(const graph::Graph<void, GraphModel>& graph, const std::string& path);
	};
}

#include "GraphStream.tpp"

#endif