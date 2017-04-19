#include "MGabowTarjan.hpp"
#include "../Functions/Functions.hpp"

Edge **MGabowTarjan::E1lessE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes) {
	Edge **res = new Edge * [n1];
	int j1, j2;
	nRes = 0;
	j1 = 0;

	for (int i = 0; i < n1; ++i) {
		while ((j1 < n2) && (E2[j1]->w < E1[i]->w)) {
			++j1;
		}
		j2 = j1;
		while ((j2 < n2) && (E1[i] != E2[j2]) && (E2[j2]->w <= E1[i]->w)) {
			++j2;
		}
		if ((j2 == n2) || (E1[i] != E2[j2])) {
			res[nRes] = E1[i];
			++nRes;
		}
	}
	return res;
}

Edge **MGabowTarjan::E1interE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes) {
	int n;
	if (n1 < n2) {
		n = n1;
	} else {
		n = n2;
	}
	Edge **res = new Edge * [n];
	int j1, j2;
	nRes = 0;
	j1 = 0;
	for (int i = 0; i < n1; ++i) {
		while ((j1 < n2) && (E2[j1]->w < E1[i]->w)) {
			++j1;
		}
		j2 = j1;
		while ((j2 < n2) && (E1[i] != E2[j2]) && (E2[j2]->w <= E1[i]->w)) {
			++j2;
		}
		if ((j2 < n2) && (E1[i] == E2[j2])) {
			res[nRes] = E1[i];
			++nRes;
		}
	}
	return res;
}

Edge **MGabowTarjan::E1unionE2(Edge **E1, Edge **E2, int n1, int n2, int &nRes) {
	Edge **res = new Edge * [n1+n2];
	int notCopy[n2];
	int  i, j, k, j1, j2, nc;
	nRes = 0;
	j1 = 0;
	nc = 0;

	for (i = 0; i < n1; ++i) {
		while ((j1 < n2) && (E2[j1]->w < E1[i]->w)) {
			++j1;
		}
		j2 = j1;
		while ((j2 < n2) && (E1[i] != E2[j2]) && (E2[j2]->w <= E1[i]->w)) {
			++j2;
		}
		if ((j2 < n2) && (E1[i] == E2[j2])) {
			notCopy[nc] = i;
			++nc;
		}
	}

	i = 0;
	j = 0;
	k = 0;
	while ((i < n1) && (j < n2)) {
		if (E1[i]->w <= E2[j]->w) {
			if ((k < nc) && (notCopy[k] == i)) {
				++k;
			} else {
				res[nRes] = E1[i];
				++nRes;
			}
			++i;
		} else {
			res[nRes] = E2[j];
			++nRes;
			++j;
		}
	}
	for (i; i < n1; ++i) {
		if ((k < nc) && (notCopy[k] == i)) {
			++k;
		} else {
			res[nRes] = E1[i];
			++nRes;
		}
	}
	for (j; j < n2; ++j) {
		res[nRes] = E2[j];
		++nRes;
	}

	return res;
}

void MGabowTarjan::P(Edge **M, Edge **L, Edge **U, Edge **S, int m, int s, int n) {
	if (n == 1) {
		toAdd[nActual] = U[0];
		toDelete[nActual] = L[0];
		++nActual;
	} else {
		Edge **U1, **U2, **G, **Mbis, **Lbis, **Ubis, **Sbis, **Etmp, **Etmp2;
		int nu1, nu2, ng, nmbis, nlbis, nubis, nsbis, netmp;
		nu1 = n/2;
		U1 = new Edge * [nu1];
		int i, j;
		i = 0;
		j = 0;
		while (i < nu1) {
			if (M[j]->b) {
			} else {
				U1[i] = M[j];
				++i;
			}
			++j;
		}

		G = mono->calculateBase(S, L, U1, s, n, nu1, ng);
		U2 = E1lessE2(U, U1, n, nu1, nu2);

		Etmp = E1lessE2(L, G, n, ng, netmp);

		Sbis = E1unionE2(S, Etmp, s, netmp, nsbis);
//		delete [] Etmp;

		Etmp = E1lessE2(M, U2, m, nu2, netmp);
		Mbis = E1lessE2(Etmp, Sbis, netmp, nsbis, nmbis);
//		delete [] Etmp;

		P(Mbis, G, U1, Sbis, nmbis, nsbis, nu1);

//		delete [] Mbis;
//		delete [] Sbis;

		Sbis = E1unionE2(S, U1, s, nu1, nsbis);
		Etmp = E1lessE2(M, G, m, ng, netmp);
		Mbis = E1lessE2(Etmp, U1, netmp, nu1, nmbis);
//		delete [] Etmp;
		Lbis = E1lessE2(L, G, n, ng, nlbis);

		P(Mbis, Lbis, U2, Sbis, nmbis, nsbis, nlbis);

//		delete [] Sbis;
//		delete [] Mbis;
//		delete [] Lbis;
	}
}

void MGabowTarjan::mergeEdges(Edge **&e, int n) {
	bool bbeg, bend;
	bbeg = e[0]->b;
	bend = e[n-1]->b;
	if (bbeg != bend) {
		Edge **res = new Edge * [n];
		int ibeg, iend, imid;
		ibeg = 0;
		iend = n-2;
		while (e[iend]->b == bend) {
			--iend;
		}
		++iend;
		imid = iend;
		for (int i = 0; i < n; ++i) {
			if ((iend == n) || ((ibeg < imid) && (e[ibeg]->w <= e[iend]->w))) {
				res[i] = e[ibeg];
				++ibeg;
			} else {
				res[i] = e[iend];
				++iend;
			}
		}
		delete [] e;
		e = res;
	}
}

MGabowTarjan::MGabowTarjan(Edges *edges) {
	this->edges = edges;
}

void MGabowTarjan::calculateSolutions(bool plus) {
	int card = edges->getCard();
	mono = new MonoObj(edges);
	if (plus) {
		mono->calculateBlPlus();
		Bl = mono->getBlPlus();
	} else {
		mono->calculateBl();
		Bl = mono->getBl();
	}
	b = mono->getB();
	w = mono->getW();

	/*cout << endl << "Bl :" << endl;
	showEdges(Bl, card-1);*/
	cout << "Bi=("<<w<<","<<b<<")" << endl;

	nbSwap = b;
	mono->calculateBu();
	Bu = mono->getBu();
	nbSwap -= mono->getB();				// The number of swap is the difference of the number of edges with cost b equals 1
	
	toDelete = new Edge * [nbSwap];
	toAdd = new Edge * [nbSwap];

	nActual = 0;

	if (!plus) {
		mergeEdges(Bl, card-1);
	}
	mergeEdges(Bu, card-1);

	Edge **L = E1lessE2(Bl, Bu, card-1, card-1, nbSwap);

	Edge **U = E1lessE2(Bu, Bl, card-1, card-1, nbSwap);

	int m, s, mbis;
	Edge **M, **S, **Mbis;
	Mbis = E1unionE2(Bl, Bu, card-1, card-1, mbis);
	S = E1interE2(Bl, Bu, card-1, card-1, s);
	M = E1lessE2(Mbis, S, mbis, s, m);

	//delete [] Mbis;

	P(M, L, U, S, m, s, nbSwap);

	mergeSort(toAdd, toDelete, nbSwap);

	for (int i = 0; i < nbSwap; ++i) {
		w = w - toDelete[i]->w + toAdd[i]->w;
		b = b - toDelete[i]->b + toAdd[i]->b;
		cout << endl << "min swap : {" << toDelete[i]->v1 << "," << toDelete[i]->v2 << "} <-> {" << toAdd[i]->v1 << "," << toAdd[i]->v2 << "} c=" << toAdd[i]->w - toDelete[i]->w << endl;
		cout << "Bi=(" << w << "," << b << ")" << endl;
	}
}