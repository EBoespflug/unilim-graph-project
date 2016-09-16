#ifndef ADJACENCYBOOLEANMATRIXMODEL_H
#define ADJACENCYBOOLEANMATRIXMODEL_H

#include <vector>
#include <set>
#include <string>

#include <iostream>

namespace graph {

	inline namespace basic_graph_model {
		/* Structure de donn�e permettant de stocker la structure d'un graphe simple orient� (et implicitement non-orient�).
		 * Utilisable comme mod�le de graphe dans pour graph::Graph<T, U>
		 */
		class AdjacencyMatrixModel
		{
		public:
			/* It�rateur de sommet. */
			using vertex_t = size_t;
			/* It�rateur d'arc. */
			using edge_t = vertex_t;

			AdjacencyMatrixModel() = default;
			AdjacencyMatrixModel(size_t size) : _data(size*size, false), _vertexCount{ size } { }
			AdjacencyMatrixModel(const AdjacencyMatrixModel&) = default;
			AdjacencyMatrixModel(AdjacencyMatrixModel&&) = default;
			AdjacencyMatrixModel& operator = (const AdjacencyMatrixModel&) = default;
			AdjacencyMatrixModel& operator = (AdjacencyMatrixModel&&) = default;

			/* Retourne vrai si le graphe est orient�. */
			bool isDirected() const;

			/* Retourne un it�rateur d'arc pour les sommets pass�s en param�tres. */
			edge_t edge(vertex_t origin, vertex_t destination) const;

			/* V�rifie si le sommet existe.*/
			bool existVertex(vertex_t vertex) const;
			/* V�rifie que l'arc existe. L'arc doit �tre valide (relier deux sommets existants). */
			bool existEdge(edge_t edge) const;

			/* Ajoute un arc.*/
			void addEdge(edge_t edge);
			/* Supprime un arc. */
			void removeEdge(edge_t edge);

			/* Affiche le graphe sur la sortie standard.*/
			void show() const; // Debuging. 

			/* Retourne le nombre de sommets.*/
			size_t vertexCount() const { return _vertexCount; }
			/* Retourne le nombre d'arcs.*/
			size_t edgeCount() const;
			/* Retourne la paire : (nombre de sommets, nombre d'arcs).*/
			std::pair<size_t, size_t> size() const { return std::make_pair(vertexCount(), edgeCount()); }

			/*Retourne l'it�rateur du premier sommet.*/
			vertex_t begin() const { return 0u; }
			/* Retourne l'it�rateur suivant le dernier sommet. */
			vertex_t end() const { return _vertexCount; }
			/*Retourne l'it�rateur du premier sommet (const).*/
			const vertex_t cbegin() const { return begin(); }
			/* Retourne l'it�rateur suivant le dernier sommet. (const)*/
			const vertex_t cend() const { return end(); }

		private:
			size_t _vertexCount;
			std::vector<bool> _data; // INV : _data.size() == nodeCount�
		};
	}
}


#endif