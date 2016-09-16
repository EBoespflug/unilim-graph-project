#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <set>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>



namespace graph {

	inline namespace traversal {

		/* Effectue un parcours en profondeur sur le graphe pass� en param�tre � partir de "firstVertex". A chaque sommet, applique la fonction pass�e en param�tre. */
		template<typename GraphModel>
		void depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function = {});

		/* Effectue un parcours en largeur sur le graphe pass� en param�tre � partir de "firstVertex". A chaque sommet, applique la fonction pass�e en param�tre.*/
		template<typename GraphModel>
		void breadthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function = {});

		namespace internal_ {

			template<class GraphModel>
			void depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t v, std::set<typename GraphModel::vertex_t>& exploredVertices, std::function<void(typename GraphModel::vertex_t&)>&& function);
		}
	}

	inline namespace neighbourhood {

		/* Retourne un std::set contenant tous les successeurs (de profondeur inf�rieure ou �gale � "depth") au sommet "v" du graphe "graph". Si le graphe est non-orient�, calcule les voisins.*/
		template<class GraphModel>
		std::set<typename GraphModel::vertex_t> successors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth = 1);

		/* Retourne un std::set contenant tous les predecesseurs (de profondeur inf�rieure ou �gale � "depth") au sommet "v" du graphe "graph". Si le graphe est non-orient�, calcule les voisins.*/
		template<class GraphModel>
		std::set<typename GraphModel::vertex_t> predecessors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth = 1);

		namespace internal_ {
			template<class GraphModel>
			void successors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth, std::set<typename GraphModel::vertex_t>& set);

			template<class GraphModel>
			void predecessors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth, std::set<typename GraphModel::vertex_t>& set);
		}
	}

	inline namespace connected_component {

		/*Retourne true si "graph" est fortement connexe (connexe pour les graphe non orient�s).*/
		template<typename GraphModel>
		inline bool isStronglyConnected(const GraphModel& graph) { return stronglyConnectedComponents(graph).size() <= (size_t)1u; }

		/*Retourne un std::set contenant la liste des sommets contenus dans la m�me composante fortement connexe (connece pour les graphe orient�s) que "v" pour le graphe "graph".*/
		template<typename GraphModel>
		std::set<typename GraphModel::vertex_t> stronglyConnectedComponent(typename GraphModel::vertex_t v, const GraphModel& graph);

		/*Retourne la liste de toutes les composantes fortement connexes (connexes pour les graphes orient�s).*/
		template<typename GraphModel>
		std::vector<std::set<typename GraphModel::vertex_t>> stronglyConnectedComponents(const GraphModel& graph);
	}

	// Minimum Covering Tree.

	/* Applique l'algorithme de Kruskal au graphe connexe et pond�r� "graph" et retourne la paire : (un arbre couvrant minimum, pond�ration totale de l'arbre convrant minimum) */
	template<typename EdgeData, typename GraphModel>
	static std::pair<GraphModel, EdgeData> kruskal(const  graph::Graph<EdgeData, GraphModel>& graph);

	/* Applique l'algorithme de Prim au graphe connexe et pond�r� "graph" et retourne la paire : (un arbre couvrant minimum, pond�ration totale de l'arbre couvrant minimum)*/
	template<typename EdgeData, typename GraphModel>
	static std::pair<GraphModel, EdgeData> prim(const graph::Graph<EdgeData, GraphModel>& graph);

	// Shortest path

	/* Applique l'algorithme de Djikstra afin de trouver le plus cours chemin entre le sommets pass� en param�tres et chaque sommet d'un graphe d'entr�e positivement valu� (orient� ou non).
	* Si le graphe est pond�r� par des valeurs n�gatives, le comportement est ind�fini.
	*/
	template<typename EdgeData, typename GraphModel>
	static std::map<typename GraphModel::vertex_t, std::pair<EdgeData, typename GraphModel::vertex_t>> djikstra(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start);

	/* Applique l'algorithme de Bellman-Ford sur un graphe valu� (orient� ou non) afin de trouver le plus cours chemin entre le sommets pass� en param�tres et chaque sommet d'un graphe d'entr�e positivement valu� (orient� ou non).
	* Retourne (<tableau d'ex�cution>, true) si le graphe comporte un cycle d'absorpsion.
	*/
	template<typename EdgeData, typename GraphModel>
	static std::pair<std::vector<std::map<typename GraphModel::vertex_t, EdgeData>>, bool> bellmanFord(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start);

	// Coloration.

	/* Retourne un vecteur contenant la couleur de chaque sommet d'un graphe non-orient� calcul�e � l'aide de l'algorithme Welsh-Powell.
	* Notez que cette coloration peut ne pas �tre optimale.
	*/
	template <typename GraphModel>
	static std::vector<unsigned> welsh_powell(const GraphModel& graph);
}

#include "GraphAlgorithms.tpp"
#include "GraphBasicsAlgorithms.tpp"

#endif