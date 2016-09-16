#ifndef EXAMPLES_H
#define EXAMPLES_H

/* Affiche les d�tails d'un graphe. */
template<typename GraphModel>
void details(const GraphModel& graph)
{
	std::cout << "Graph : " << std::endl;
	std::cout << "Directed : " << std::boolalpha << graph.isDirected() << std::endl;
	graph.show();
}

void basicsAlgorithms(); // Parcours et composantes connexes.
void kruskal(); // Algorithme de Kruskal.
void prim(); // Algorithme de Prim.
void djikstra(); // Algorithme de Djikstra.
void bellmanFord(); // Algorithme de Bellman-Ford.
void bellmanFord_negativeWeightCycle(); // Algorithme de Bellman-Ford sur un graphe avec cycle d'absorption.
void welshPowell(); // Algorithme de Welsh-Powell.
void welshPowell_colorationComparison(); // Comparaison de deux ex�cution de l'algorithme de Welsh-Powell sur un graphe couronne � 8 sommets enregistr� de deux mani�re diff�rentes.

#endif