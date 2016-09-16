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

		/* Effectue un parcours en profondeur sur le graphe passé en paramètre à partir de "firstVertex". A chaque sommet, applique la fonction passée en paramètre. */
		template<typename GraphModel>
		void depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function = {});

		/* Effectue un parcours en largeur sur le graphe passé en paramètre à partir de "firstVertex". A chaque sommet, applique la fonction passée en paramètre.*/
		template<typename GraphModel>
		void breadthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t firstVertex, std::function<void(typename GraphModel::vertex_t&)>&& function = {});

		namespace internal_ {

			template<class GraphModel>
			void depthFirstTraversal(GraphModel& graph, typename GraphModel::vertex_t v, std::set<typename GraphModel::vertex_t>& exploredVertices, std::function<void(typename GraphModel::vertex_t&)>&& function);
		}
	}

	inline namespace neighbourhood {

		/* Retourne un std::set contenant tous les successeurs (de profondeur inférieure ou égale à "depth") au sommet "v" du graphe "graph". Si le graphe est non-orienté, calcule les voisins.*/
		template<class GraphModel>
		std::set<typename GraphModel::vertex_t> successors(const GraphModel& graph, typename GraphModel::vertex_t v, size_t depth = 1);

		/* Retourne un std::set contenant tous les predecesseurs (de profondeur inférieure ou égale à "depth") au sommet "v" du graphe "graph". Si le graphe est non-orienté, calcule les voisins.*/
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

		/*Retourne true si "graph" est fortement connexe (connexe pour les graphe non orientés).*/
		template<typename GraphModel>
		inline bool isStronglyConnected(const GraphModel& graph) { return stronglyConnectedComponents(graph).size() <= (size_t)1u; }

		/*Retourne un std::set contenant la liste des sommets contenus dans la même composante fortement connexe (connece pour les graphe orientés) que "v" pour le graphe "graph".*/
		template<typename GraphModel>
		std::set<typename GraphModel::vertex_t> stronglyConnectedComponent(typename GraphModel::vertex_t v, const GraphModel& graph);

		/*Retourne la liste de toutes les composantes fortement connexes (connexes pour les graphes orientés).*/
		template<typename GraphModel>
		std::vector<std::set<typename GraphModel::vertex_t>> stronglyConnectedComponents(const GraphModel& graph);
	}

	// Minimum Covering Tree.

	/* Applique l'algorithme de Kruskal au graphe connexe et pondéré "graph" et retourne la paire : (un arbre couvrant minimum, pondération totale de l'arbre convrant minimum) */
	template<typename EdgeData, typename GraphModel>
	static std::pair<GraphModel, EdgeData> kruskal(const  graph::Graph<EdgeData, GraphModel>& graph);

	/* Applique l'algorithme de Prim au graphe connexe et pondéré "graph" et retourne la paire : (un arbre couvrant minimum, pondération totale de l'arbre couvrant minimum)*/
	template<typename EdgeData, typename GraphModel>
	static std::pair<GraphModel, EdgeData> prim(const graph::Graph<EdgeData, GraphModel>& graph);

	// Shortest path

	/* Applique l'algorithme de Djikstra afin de trouver le plus cours chemin entre le sommets passé en paramètres et chaque sommet d'un graphe d'entrée positivement valué (orienté ou non).
	* Si le graphe est pondéré par des valeurs négatives, le comportement est indéfini.
	*/
	template<typename EdgeData, typename GraphModel>
	static std::map<typename GraphModel::vertex_t, std::pair<EdgeData, typename GraphModel::vertex_t>> djikstra(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start);

	/* Applique l'algorithme de Bellman-Ford sur un graphe valué (orienté ou non) afin de trouver le plus cours chemin entre le sommets passé en paramètres et chaque sommet d'un graphe d'entrée positivement valué (orienté ou non).
	* Retourne (<tableau d'exécution>, true) si le graphe comporte un cycle d'absorpsion.
	*/
	template<typename EdgeData, typename GraphModel>
	static std::pair<std::vector<std::map<typename GraphModel::vertex_t, EdgeData>>, bool> bellmanFord(const graph::Graph<EdgeData, GraphModel>& graph, typename GraphModel::vertex_t start);

	// Coloration.

	/* Retourne un vecteur contenant la couleur de chaque sommet d'un graphe non-orienté calculée à l'aide de l'algorithme Welsh-Powell.
	* Notez que cette coloration peut ne pas être optimale.
	*/
	template <typename GraphModel>
	static std::vector<unsigned> welsh_powell(const GraphModel& graph);
}

#include "GraphAlgorithms.tpp"
#include "GraphBasicsAlgorithms.tpp"

#endif