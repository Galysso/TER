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
		j2 = j1;
		while ((j2 < n2) && (E1[i] != E2[j2]) && (E2[j2]->w <= E1[i]->w)) {
			++j2;
		}
		if (E1[i] == E2[j2]) {
			j1 = j2;
		} else {
			res[nRes] = E1[i];
			++nRes;
		}
	}
	return res;
}

Edge **MGabowTarjan::firstL() {
	Edge **L = new Edge * [nbSwap];
	int il, iu, iubis, n;
	il = 0;
	iu = edges->getCard()-2;
	n = 0;

	while ((iu >= 0) && (Bu[iu]->b)) {
		--iu;
	}
	++iu;
	while (n < nbSwap) {
		if (Bl[il]->b) {		// Si on utilise BlPlus, les coûts b de 0 et 1 son mélangés
		iubis = iu;
			while ((iubis < edges->getCard()-1) && (Bu[iubis]->w <= Bl[il]->w) && (Bl[il] != Bu[iubis])) {
				++iubis;
			}
			if ((iubis == edges->getCard()-1) || (Bu[iubis] != Bl[il])) {
				iu = iubis;
				L[n] = Bl[il];
				++n;
			}
		}
		++il;
	}

	return L;
}

Edge **MGabowTarjan::firstU() {
	Edge **U = new Edge * [nbSwap];
	int il, iu, ilbis, n;
	il = edges->getCard()-2;
	iu = 0;
	n = 0;

	while ((il >= 0) && (!Bl[il]->b)) {
		--il;
	}
	++il;
	while (n < nbSwap) {
		ilbis = il;
		while ((ilbis < edges->getCard()-1) && (Bl[il]->w <= Bu[ilbis]->w) && (Bl[ilbis] != Bu[iu])) {
			++ilbis;
		}
		if ((ilbis == edges->getCard()-1) || (Bu[iu] != Bl[ilbis])) {
			il = ilbis;
			U[n] = Bu[iu];
			++n;
		}
		++iu;
	}

	return U;
}

Edge **MGabowTarjan::UlessU1(Edge **U, Edge **U1, int n, int nU1, int &nU2) {
	nU2 = n;
	Edge **U2 = new Edge * [nU2];
	int iU, iU1, iU1bis, nU2Actual;
	iU = 0;
	iU1 = 0;
	nU2Actual = 0;
	while (iU < n) {
		iU1bis = iU1;
		while ((iU1bis < nU1) && (U1[iU1bis]->w <= U[iU]->w) && (U[iU] != U1[iU1bis])) {
			++iU1bis;
		}
		if ((iU1bis == nU1) || (U[iU] != U1[iU1bis])) {
			U2[nU2Actual] = U[iU];
			++nU2Actual;
		}
		++iU;
	}
	nU2 = nU2Actual;
	return U2;
}

void MGabowTarjan::P(Edge **L, Edge **U, int n) {
	if (n == 1) {
		toAdd[nActual] = U[0];
		toDelete[nActual] = L[0];
		++nActual;
	} else {
		int nU1 = n/2;
		int nU2;
		Edge **U1 = new Edge * [nU1];
		for (int i = 0; i < nU1; ++i) {
			U1[i] = E0[i];
		}
		Edge **U2 = UlessU1(U, U1, n, nU1, nU2);


		cout << endl << "U1 :" << endl;
		showEdges(U1, nU1);

		cout << endl << "U2 :" << endl;
		showEdges(U2, nU2);
	}
}

MGabowTarjan::MGabowTarjan(Edges *edges) {
	this->edges = edges;
	E0 = edges->getE0();
	E1 = edges->getE1();
	MonoObj mono(edges);
	mono.calculateBl();
	Bl = mono.getBl();
	b = mono.getB();
	w = mono.getW();
	nbSwap = b;
	mono.calculateBu();
	Bu = mono.getBu();
	nbSwap -= mono.getB();				// The number of swap is the difference of the number of edges with cost b equals 1
	nActual = 0;

	cout << endl << "Bl : " << endl;
	showEdges(Bl, edges->getCard()-1);

	cout << endl << "Bu : " << endl;
	showEdges(Bu, edges->getCard()-1);

	Edge **L = firstL();
	cout << endl << "L : " << endl;
	showEdges(L, nbSwap);

	Edge **U = firstU();
	cout << endl << "U : " << endl;
	showEdges(U, nbSwap);

	P(L, U, nbSwap);
}

void MGabowTarjan::calculateSolutions() {

}