#ifndef MGABOWTARJAN_HPP
#define MGABOWTARJAN_HPP

#include "../Graph/Edges.hpp"
#include "../Graph/Graph.hpp"
#include "MonoObj.hpp"

class MGabowTarjan {
	private:
		int b;
		int w;
		MonoObj *mono;
		Edges *edges;
		Edge **Bl;
		Edge **Bu;
		Edge **toAdd;		// Edges to add
		Edge **toDelete;	// Edges to delete (toAdd[i], toDelete[i]) is a minimal swap
		int nbSwap;			// The number of swaps
		int nActual;

	private:
		void mergeEdges(Edge **&e, int n);
		void P(Edge **M, Edge **L, Edge **U, Edge **S, int m, int s, int n);
		Edge **E1interE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes);
		Edge **E1unionE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes);
		Edge **E1lessE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes);	// E1 et E2 triés dans l'ordre croissant selon c
		
	public:
		MGabowTarjan(Edges *edges);
		void calculateSolutions(bool plus);
		

		// M le graphe
		// L les arêtes dans Bl mais pas Bu (celles qui vont être retirées)
		// U Les arêtes dans Bu mais pas Bl (celles qui vont être ajoutées)
		// |L| = |U|

		// Retour : Un swap minimum (e,f) ou deux appels récursifs de P

		// Si |U|=1
			// Alors on ajoute (e,f) à la liste des swaps où L={e} et U={f}
		// Sinon
			// Alors Soient
				// * U1 la moitié (partie entière supérieure) des élements de U de taille minimum
				// selon c dont b=0
				// * U2 les autres éléments

				// Déterminer G inclu dans L tel que B=(L\G)uU1 forme un arbre couvrant de M pour
				// c et satisfaisant BnE0=U1




		// 5) Déterminer les arêtes de L telles que si on les retire et qu'on les unit avec U1 nous obtenons
		//	une base minimale du graphe selon c et telles que les arêtes de E0 de la base sont égales à U1

		// En d'autres termes :
		// Trouver la base qui contient tous les éléments de U1 (les E0) et les meilleurs éléments

};

#endif
