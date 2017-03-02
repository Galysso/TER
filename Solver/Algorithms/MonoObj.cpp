#include "MonoObj.hpp"
#include "../Functions/Functions.hpp"

MonoObj::MonoObj(Edges *e) {
	edges = e;
	roots = new int [e->getCard()];
	tree = new Edge * [e->getCard()-1];
	b = 0;
	w = 0;
}

MonoObj::~MonoObj() {
	delete [] roots;
}

int MonoObj::getRoot(int indV) {
	while (roots[indV] != indV) {
		indV = roots[indV];
	}
	return indV;
}

void MonoObj::setRoot(int indV, int ind) {
	int root = roots[indV];
	while (root != indV) {
		roots[indV] = ind;
		indV = root;
		root = roots[root];
	}
	roots[indV] = ind;
}

void MonoObj::calculateBl() {
	b = 0;
	w = 0;
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();

	Edge *e;

	int cpt = 0;
	int i = 0;

	for (i = 0; i < card; ++i) {
		roots[i] = i;
	}

	i = 0;
	while ((i < nE1) && (cpt < card-1)) {
		e = E1[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
			b = b + e->b;
			w = w + e->w;
		}
		++i;
	}
	i = 0;
	while (cpt < card-1) {
		e = E0[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
			b = b + e->b;
			w = w + e->w;
		}
		++i;
	}
}

void MonoObj::calculateBlPlus() {
	b = 0;
	w = 0;
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();

	Edge *e;

	int cpt = 0;
	int i0, i1;

	for (i0 = 0; i0 < card; ++i0) {
		roots[i0] = i0;
	}

	cpt = 0;
	i0 = 0;
	i1 = 0;
	while (cpt < card-1) {
		if (E1[i1]->w < E0[i0]->w) {
			e = E1[i1];
			++i1;
		} else {
			e = E0[i0];
			++i0;
		}
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
			b = b + e->b;
			w = w + e->w;
		}
	}
}

void MonoObj::calculateBu() {
	b = 0;
	w = 0;
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();

	Edge *e;

	int cpt = 0;
	int i = 0;

	for (i = 0; i < card; ++i) {
		roots[i] = i;
	}

	cpt = 0;
	i = 0;
	while ((i < nE0) && (cpt < card-1)) {
		e = E0[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
			b = b + e->b;
			w = w + e->w;
		}
		++i;
	}

	i = 0;
	while (cpt < card-1) {
		e = E1[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
			b = b + e->b;
			w = w + e->w;
		}
		++i;
	}
}

int MonoObj::getB() {
	return b;
}

int MonoObj::getW() {
	return w;
}

Edge **MonoObj::getTree() {
	return tree;
}


void MonoObj::showDebug() {
	int card = edges->getCard();
	Edge *e;
	for (int i = 0; i < card-1; ++i) {
		e = tree[i];
		cout << i << ": {" << e->v1 << "," << e->v2 << "} " << e->b << ", " << e->w << endl;
	}
}

// 1 à 2
// 2 à 3
// 3 à 4
// 4 à 5


// listes d'arrêtes pour chaque sommet

