#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <list>

#include "examples.h"

int main(int argc, char* argv[])
{
	try
	{
		basicsAlgorithms(); // Parcours et composantes connexes.
		kruskal(); // Algorithme de Kruskal.
		prim(); // Algorithme de Prim.
		djikstra(); // Algorithme de Djikstra.
		bellmanFord(); // Algorithme de Bellman-Ford.
		bellmanFord_negativeWeightCycle(); // Algorithme de Bellman-Ford sur un graphe avec cycle d'absorption.
		welshPowell(); // Algorithme de Welsh-Powell.
		welshPowell_colorationComparison(); // Comparaison de deux exécution de l'algorithme de Welsh-Powell sur un graphe couronne à 8 sommets enregistré de deux manière différentes.
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception." << std::endl;
		return -1;
	}

	return 0;
}