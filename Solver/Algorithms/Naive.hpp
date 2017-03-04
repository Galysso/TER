#ifndef NAIVE_HPP
#define NAIVE_HPP

#include "../Graph/Edges.hpp"

class Naive {
	private:
		Edges *edges;	// Les arrêtes
		Edge **toAdd;	// liste des arêtes potentiellement ajoutables	E0\Bl
		int nToAdd;
		Edge **sol;		// Solution courante
		Edge ***Si;		// Liste des solutions
		Edge ***near;	// Matrice des arêtes reliées à un sommet dans la solution courante
		int *nNear;		// Matrice des nombre d'arêtes reliés à un sommet dans la solution courante
		int nSol;
		Edge **cycle;	// Liste des arêtes dans le dernier cycle trouvé
		int nCycle;
		bool found;

	private:
		void calculateToAdd();
		void calculateNear();
		void swap(Edge *e0, Edge* e1);
		void addEdge(Edge *e);
		void deleteEdge(Edge *e);
		Edge *minimalSwapWith(Edge *e0);
		// OPTIMISATION POSSIBLE (Ne plus utiliser de cycle, simplement considérer chaque arête et choisir la meilleure en descendant)
		bool edgesInCycle(Edge **cycle, int n, int v0, int v1, int v2);

	public:
		Naive(Edges *edges);
		void calculateSolutions();
		Edge ***getSolutions();
		int getNSol();
};

#endif
