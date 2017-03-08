#include "Naive.hpp"
#include "../Graph/Edges.hpp"
#include "MonoObj.hpp"

Naive::Naive(Edges *edges) {
	this->edges = edges;
	toAdd = new Edge * [edges->getNE0()];
	near = new Edge ** [edges->getCard()];
	nNear = new int [edges->getCard()];
}

void Naive::calculateToAdd() {
	nToAdd = 0;
	bool isPresent;
	int i, j;
	int nE0 = edges->getNE0();
	Edge **E0 = edges->getE0();
	Edge *e;
	int v, cardV;

	for (i = 0; i < nE0; ++i) {
		e = E0[i];
		v = e->v1;
		isPresent = false;
		j = 0;
		cardV = nNear[v];
		while ((j < cardV) && (!isPresent)) {
			isPresent = (e == near[v][j]);
			++j;
		}
		if (!isPresent) {
			toAdd[nToAdd] = e;
			++nToAdd;
		}
	}
}

void Naive::calculateNear() {
	int card = edges->getCard();
	Edge *e;
	int i, v1, v2;

	for (i = 0; i < card; ++i) {
		nNear[i] = 0;
		near[i] = new Edge * [edges->getCardV(i)];
	}

	for (i = 0; i < card-1; ++i) {
		e = sol[i];
		v1 = e->v1;
		v2 = e->v2;

		near[v1][nNear[v1]] = e;
		++nNear[v1];

		near[v2][nNear[v2]] = e;
		++nNear[v2];
	}
}

void Naive::swap(Edge *e0, Edge *e1) {
	int i = edges->getCard()-1;
	while (sol[i] != e1) {
		--i;
	}
	sol[i] = e0;

	addEdge(e0);
	deleteEdge(e1);

	i = 0;
	while (toAdd[i] != e0) {
		++i;
	}
	for (i = i+1; i < nToAdd; ++i) {
		toAdd[i-1] = toAdd[i];
	}
	--nToAdd;
}

void Naive::addEdge(Edge *e) {
	near[e->v1][nNear[e->v1]] = e;
	++nNear[e->v1];
	near[e->v2][nNear[e->v2]] = e;
	++nNear[e->v2];
}

void Naive::deleteEdge(Edge *e) {
	int i = 0;
	while (near[e->v1][i] != e) {
		++i;
	}
	for (i = i+1; i < nNear[e->v1]; ++i) {
		near[e->v1][i-1] = near[e->v1][i];
	}
	--nNear[e->v1];

	i = 0;
	while (near[e->v2][i] != e) {
		++i;
	}
	for (i = i+1; i < nNear[e->v2]; ++i) {
		near[e->v2][i-1] = near[e->v2][i];
	}
	--nNear[e->v2];
}

Edge *Naive::minimalSwapWith(Edge *e0) {
	Edge *minEdge = NULL;
	found = false;
	
	edgesInCycle(minEdge, e0->v2, e0->v1, e0->v2);

	return minEdge;
}

bool Naive::edgesInCycle(Edge *&minEdge, int v0, int v1, int v2) {

	if (found) {
		return false;
	} else {
		int i = 0;
		bool foundHere = false;
		int v1Next;
		Edge *e;
		while ((i < nNear[v1]) && (!found)) {
			e = near[v1][i];
			if (e->v1 == v1) {
				v1Next = e->v2;
			} else {
				v1Next = e->v1;
			}

			if (v1Next == v2) {
				foundHere = true;
				found = true;
				if (e->b) {
					minEdge = e;
				}
			} else if (v0 != v1Next) {
				foundHere = edgesInCycle(minEdge, v1, v1Next, v2);
				if (foundHere && e->b && ((minEdge == NULL) || (e->w > minEdge->w))) {
					minEdge = e;
				}
			}
			++i;
		}
		return foundHere;
	}
}

void Naive::calculateSolutions() {
	Edge *e, *minE0, *minE1;
	int minCost;
	bool minSwapFound;
	int sum, bools;

	MonoObj mono(edges);
	//mono.calculateBlPlus();
	mono.calculateBl();
	sum = mono.getW();
	bools = mono.getB();
	cout << "Bi=(" << sum << "," << bools << ")" << endl;
	/*cout << endl << "first sol :" << endl;
	mono.showDebug();*/

	//sol = mono.getBlPlus();
	sol = mono.getBl();
	calculateNear();
	calculateToAdd();

	Si = new Edge ** [mono.getB()];
	Si[0] = sol;
	nSol = 1;
	do {

///////////////////////////////////
		/*cout << endl << "to add :" << endl;
		for (int i = 0; i < nToAdd; ++i) {
			e = toAdd[i];
			cout << i << ": {" << e->v1 << "," << e->v2 << "} " << e->b << ", " << e->w << endl;
		}*/
//////////////////////////////////








		minSwapFound = false;
		for (int i = 0; i < nToAdd; ++i) {
			e = minimalSwapWith(toAdd[i]);
			if (e != NULL) {
				if (minSwapFound) {
					if (minCost > toAdd[i]->w - e->w) {
						minE0 = toAdd[i];
						minE1 = e;
						minCost = minE0->w - e->w;
					}
				} else {
					minSwapFound = true;
					minE0 = toAdd[i];
					minE1 = e;
					minCost = minE0->w - e->w;
				}
			}
		}
		if (minSwapFound) {
			cout << endl << "min swap : {" << minE0->v1 << "," << minE0->v2 << "} <-> {" << minE1->v1 << "," << minE1->v2 << "} c=" << minCost << endl;
			swap(minE0, minE1);
			Si[nSol] = sol;
			++nSol;
		






/////////////////////////////////
		/*int sum = 0;
		int bools = 0;
		cout << endl << "next sol :" << endl;
		for (int i = 0; i < edges->getCard()-1; ++i) {
			e = sol[i];
			cout << i << ": {" << e->v1 << "," << e->v2 << "} " << e->b << ", " << e->w << endl;
			bools = bools + e->b;
			sum = sum + e->w;
		}*/
		sum = sum - minE1->w + minE0->w;
		bools = bools - minE1->b + minE0->b;
		cout << "Bi=(" << sum << "," << bools << ")" << endl;
	}


///////////////////////////////////







	} while (minSwapFound);

}
