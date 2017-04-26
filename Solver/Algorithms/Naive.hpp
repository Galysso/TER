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
		Edge **Tu;
		int *nNear;		// Matrice des nombre d'arêtes reliés à un sommet dans la solution courante
		int nSol;
		bool found;

	private:
		void calculateToAdd();
		void calculateNear();
		void swap(Edge *e0, Edge* e1);
		void addEdge(Edge *e);
		void deleteEdge(Edge *e);
		Edge *minimalSwapWith(Edge *e0);
		// OPTIMISATION POSSIBLE (Ne plus utiliser de cycle, simplement considérer chaque arête et choisir la meilleure en descendant)
		bool edgesInCycle(Edge *&minEdge, int v0, int v1, int v2);

	public:
		Naive(Edges *edges);
		void calculateSolutions(bool plus);
		Edge ***getSolutions();
		int getNSol();
};

#endif
