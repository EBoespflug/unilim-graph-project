#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <list>

#include "AdjacencyMatrixModel.h"
#include "AdjacencyListModel.h"
#include "Graph.h"
#include "GraphAlgorithms.h"
#include "GraphStream.h"
#include "examples.h"

#define NL() std::cout << std::endl << std::endl; // new lines.

void basicsAlgorithms()
{
	std::cout << "BASICS ALGORITHMS EXAMPLES : "; NL();

	auto g{ graph::GraphStream<>::readGraph("basicGraph.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.

	// Affichage des successeurs de chaque sommet du graphe en utilisant un parcours en profondeur.
	graph::depthFirstTraversal(g, g.begin(), [&g](graph::AdjacencyMatrixModel::vertex_t& i) -> auto {
		std::cout << "For " << i << ", 1 depth successor are : ";
		for (const auto& item : graph::successors(g, i))
		{
			std::cout << item << " ";
		}
		std::cout << "." << std::endl;
	});

	NL();

	// Affichage des composantes fortement connexes du graphe.
	auto cc = graph::stronglyConnectedComponents(g);
	for (auto& i : cc)
	{
		std::cout << "Connected component : ";
		for (auto& j : i)
			std::cout << j << ", ";
		std::cout << std::endl;
	}

	NL();
}

void kruskal()
{
	std::cout << "KRUSKAL'S ALGORITHM : " << std::endl << "Minimum covering tree."; NL();

	auto g{ graph::GraphStream<int>::readGraph("minCoverTree.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.

	auto result = graph::kruskal(g); // Exécution de l'algorithme de Kruskal.

	// Affichage de l'arbre couvrant minimum obtenu et de son poids total.
	std::cout << std::endl << "Covering tree :" << std::endl;
	result.first.show();
	std::cout << std::endl << "Total value :" << result.second;

	NL();
}

void prim()
{
	std::cout << "PRIM'S ALGORITHM : " << std::endl << "Minimum covering tree."; NL();

	auto g{ graph::GraphStream<int, graph::AdjacencyListModel>::readGraph("minCoverTree.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.

	auto result = graph::prim(g); // Exécution de l'algorithme de Prim.

	// Affichage de l'arbre couvrant minimum obtenu et de son poids total.
	std::cout << std::endl << "Covering tree :" << std::endl;
	result.first.show();
	std::cout << std::endl << "Total value :" << result.second;

	NL();
}

void djikstra()
{
	std::cout << "DJIKSTRA'S ALGORITHM : " << std::endl << "Shortest path."; NL();

	auto g{ graph::GraphStream<unsigned, graph::AdjacencyListModel>::readGraph("shortestPath.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.
	
	const auto startVertex{ g.begin() }; // Choix du sommet d'origine.
	auto result = graph::djikstra(g, startVertex); // Exécution de l'algorithme de Djikstra.

	// Affichage du résultat.
	for (auto& item : result)
		std::cout << "For the vertex " << item.first << " the distance to " << startVertex << " is " << item.second.first << " and the predecessors is " << item.second.second << "." << std::endl;

	// Fonction permettant la récupération du chemin pour aller de l'origine à un sommet
	auto printPath{ [&](decltype(g)::vertex_t targetVertex) {
		auto currentVertex{ targetVertex }; // On choisi arbitrairement le sixième sommet (cela implique ici que notre graphe doit comporter au moins 6 sommets).
		std::list<decltype(targetVertex)> path;

		if (result.count(targetVertex) == 0) // Si le sommet cible n'est pas dans la même composante fortement connexe que le sommet d'origine.
			std::cout << "The vertex " << targetVertex << " cannot be reached from the vertex " << startVertex << "." << std::endl;
		else
			while (currentVertex != startVertex)
			{
				path.push_front(currentVertex); // On ajoute le sommet au chemin.
				currentVertex = result[currentVertex].second; // On recommence avec le sommet précédant currentVertex dans le plus court chemin pour accéder à currentVertex.
			}

		// Affichage.
		std::cout << "Path to reach " << targetVertex << " :" << startVertex;
		for (auto& i : path)
			std::cout << "=>" << i;
		std::cout << std::endl;
	}};

	// Affichage du chemin pour chaque vertex.
	for (auto i{ g.begin() }; i < g.end(); ++i)
		printPath(i);

	NL();
}

void bellmanFord()
{
	std::cout << "BELLMAN-FORD'S ALGORITHM : " << std::endl << "Shortest path."; NL();

	auto g{ graph::GraphStream<int>::readGraph("shortestPath.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.

	const auto startVertex{ g.begin() }; // Choix du sommet d'origine.
	auto result = graph::bellmanFord(g, startVertex); // Exécution de l'algorithme de Bellman-Ford.

	if (result.second == true) // On vérifie s'il n'y a pas de cycle d'absorption.
		std::cout << "The graph contain at least one negative-weight cycle." << std::endl;
	else // Si non, on affiche le résultat de chaque étape.
		for (auto i{ 0u }; i < result.first.size(); ++i)
		{
			std::cout << "Step " << i << " :" << std::endl;
			for (auto& item : result.first[i])
				std::cout << "For the vertex " << item.first << " the distance to " << startVertex << " is " << item.second << "." << std::endl;
		}

	NL();
}

void bellmanFord_negativeWeightCycle()
{
	std::cout << "BELLMAN-FORD'S ALGORITHM : " << std::endl << "Shortest path with negative weight cycles."; NL();

	auto g{ graph::GraphStream<int>::readGraph("shortestPathNegativeWeightCycle.g") }; // Lecture du graphe.
	details(g); // Affichage du graphe.

	const auto startVertex{ g.begin() }; // Choix du sommet d'origine.
	auto result = graph::bellmanFord(g, startVertex); // Exécution de l'algorithme de Bellman-Ford.

	if (result.second == true) // On vérifie que l'algorithme a bien detecté le cycle d'absorption.
		std::cout << "The graph contain at least one negative-weight cycle." << std::endl;
	else
		std::cout << "Error, expecting negative-weight cycle." << std::endl;

	NL();
}

void welshPowell()
{
	std::cout << "WELSH-POWELL'S ALGORITHM : " << std::endl << "Graph coloration."; NL();

	auto g{ graph::GraphStream<>::readGraph("coloration.g") }; // Lecture du graphe.	
	details(g); // Affichage du graphe.

	auto result = graph::welsh_powell(g); // Exécution de l'algorithme de Welsh-Powell.

	// Affichage de la couleur de chaque élément.
	for (int i = 0; i < g.vertexCount(); ++i)
		std::cout << std::endl << "For the vertex " << i << " the color is : " << result[i] << ".";

	NL();
}

void welshPowell_colorationComparison()
{
	std::cout << "WELSH-POWELL'S ALGORITHM : " << std::endl << "Graph coloration (result quality comparison)."; NL();

	{
		auto g{ graph::GraphStream<>::readGraph("hexaédrique_1.g") }; // Lecture du premier graphe.
		details(g); // Affichage du graphe.

		auto result = graph::welsh_powell(g); // Exécution de l'algorithme de Welsh-Powell.

		// Affichage de la couleur de chaque élément.
		for (int i = 0; i < g.vertexCount(); ++i)
			std::cout << std::endl << "For the vertex " << i << " the color is : " << result[i] << "."; 
	}

	NL();

	// Second graph representation.

	auto g{ graph::GraphStream<>::readGraph("hexaédrique_2.g") }; // Lecture du premier graphe.
	details(g); // Affichage du graphe.

	auto result = graph::welsh_powell(g); // Exécution de l'algorithme de Welsh-Powell.

										  // Affichage de la couleur de chaque élément.
	for (int i = 0; i < g.vertexCount(); ++i)
		std::cout << std::endl << "For the vertex " << i << " the color is : " << result[i] << ".";

	NL();
}