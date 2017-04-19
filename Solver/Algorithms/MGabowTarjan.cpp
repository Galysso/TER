#include "MGabowTarjan.hpp"

void MGabowTarjan::showEdges(Edge **e, int n) {
	for (int i = 0; i < n; ++i) {
		cout << i << ": (" << e[i]->v1 << "," << e[i]->v2 << ") b=" << e[i]->b << " c=" << e[i]->w << endl;
	}
}

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
	int  k, j, j1, j2, nc;
	nRes = 0;
	j1 = 0;
	nc = 0;

	for (int i = 0; i < n1; ++i) {
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

	k = 0;
	j = 0;
	for (int i = 0; i < n1; ++i) {
		while ((j < n2) && (E2[j]->w <= E1[i]->w)) {
			res[nRes] = E2[j];
			++nRes;
			++j;
		}
		if (notCopy[k] == i) {
			++k;
		} else {
			res[nRes] = E1[i];
			++nRes;
		}
	}
	while (j < n2) {
		res[nRes] = E2[j];
		++nRes;
		++j;
	}

	return res;
}

void MGabowTarjan::P(Edge **M, Edge **L, Edge **U, Edge **S, int s, int m, int n) {
	if (n == 1) {
		toAdd[nActual] = U[0];
		toDelete[nActual] = L[0];
		++nActual;
	} else {
		int nU1 = n/2;
		Edge **U1 = new Edge * [nU1];
		int i, j;
		i = 0;
		j = 0;
		while (i < nU1) {
			if (M[j]->b) {
			} else {
				U1[i] = M[j];
				++i;
			}
			++j;
		}
		int nU2;
		Edge **U2 = E1lessE2(U, U1, n, nU1, nU2);


		cout << endl << "U1 :" << endl;
		showEdges(U1, nU1);

		cout << endl << "U2 :" << endl;
		showEdges(U2, nU2);
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

MGabowTarjan::MGabowTarjan(Edges *edges, bool plus) {
	this->edges = edges;
	int card = edges->getCard();
	E0 = edges->getE0();
	E1 = edges->getE1();
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
	nbSwap = b;
	mono->calculateBu();
	Bu = mono->getBu();
	nbSwap -= mono->getB();				// The number of swap is the difference of the number of edges with cost b equals 1
	nActual = 0;

	if (!plus) {
		mergeEdges(Bl, card-1);
	}
	mergeEdges(Bu, card-1);

	cout << endl << "Bl : " << endl;
	showEdges(Bl, card-1);

	cout << endl << "Bu : " << endl;
	showEdges(Bu, card-1);

	Edge **L = E1lessE2(Bl, Bu, card-1, card-1, nbSwap);

	cout << endl << "L : " << endl;
	showEdges(L, nbSwap);

	Edge **U = E1lessE2(Bu, Bl, card-1, card-1, nbSwap);
	cout << endl << "U : " << endl;
	showEdges(U, nbSwap);

	int m, s, mbis;
	Edge **M, **S, **Mbis;
	Mbis = E1unionE2(Bl, Bu, card-1, card-1, mbis);
	S = E1interE2(Bl, Bu, card-1, card-1, s);
	M = E1lessE2(Mbis, S, mbis, s, m);

	cout << endl << "S :" << endl;
	showEdges(S, s);

	cout << endl << "M :" << endl;
	showEdges(M, m);

	delete [] Mbis;

	P(M, L, U, S, m, s, nbSwap);
}

void MGabowTarjan::calculateSolutions() {

}