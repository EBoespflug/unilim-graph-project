#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <list>
#include <map>

#include "AdjacencyMatrixModel.h"
#include "AdjacencyListModel.h"

namespace graph {

	/*Structure de donn�e permettant de stocker des graphes pond�r�s (orient�s ou non).
	 * S'appuie sur un mod�le de graphe basique et d�fini un type de pond�ration. Si ce type est void_t, le graphe est non pond�r�.*/
	template<typename EdgeData = void, typename GraphModel = AdjacencyMatrixModel>
	class Graph : private GraphModel
	{
	public:
		using GraphModel::vertex_t;
		using GraphModel::edge_t;
		using edge_data_t = EdgeData;

		using GraphModel::edge;
		using GraphModel::existVertex;
		using GraphModel::existEdge;
		using GraphModel::vertexCount;
		using GraphModel::edgeCount;
		using GraphModel::size;
		using GraphModel::begin;
		using GraphModel::cbegin;
		using GraphModel::end;
		using GraphModel::cend;

		template<typename ...Ts>
		Graph(Ts && ...args) : GraphModel( std::forward<Ts>(args)... ) {}

		/* Ajoute un arc avec la pond�ration pr�cis�e.*/
		void addEdge(typename GraphModel::edge_t e, EdgeData&& data);
		/* Supprime l'arc sp�cifi�. */
		void removeEdge(typename GraphModel::edge_t e);
		/* Retourne la pond�ration de l'arc sp�cifi�. */
		EdgeData edgeData(typename GraphModel::edge_t e) const;
		/* Retourne vrai si le graphe est orient�. */
		bool isDirected() const;

		/* Affiche le graphe sur la sortie standard. */
		void show() const;

	private:
		std::map<typename GraphModel::edge_t, EdgeData> _edgeData;
	};

	template<typename GraphModel>
	class Graph<void, GraphModel> : private GraphModel
	{
	public:
		using GraphModel::vertex_t;
		using GraphModel::edge_t;
		using edge_data_t = void;

		using GraphModel::edge;
		using GraphModel::existVertex;
		using GraphModel::existEdge;
		using GraphModel::vertexCount;
		using GraphModel::edgeCount;
		using GraphModel::size;
		using GraphModel::begin;
		using GraphModel::cbegin;
		using GraphModel::show;
		using GraphModel::end;
		using GraphModel::cend;
		using GraphModel::addEdge;
		using GraphModel::removeEdge;
		using GraphModel::isDirected;

		/* Construit un graphe avec un nombre de sommets fix�. */
		Graph(size_t vertexCount) : GraphModel(vertexCount) { }
	};
}

#include "Graph.tpp"

#endif