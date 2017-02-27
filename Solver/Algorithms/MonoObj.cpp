#include "MonoObj.hpp"
#include "../Functions/Functions.hpp"

MonoObj::MonoObj(Edges *e) {
	edges = e;
	roots = new int [e->getCard()];
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

Edge **MonoObj::calculateBl() {
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **EX = new Edge * [nEX];
	Edge **tree = new Edge * [card-1];
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();
	copy(E1, E1+nE1, EX);
	copy(E0, E0+nE0, EX+nE1);

	Edge *e;


	int cpt = 0;
	int i = 0;



	for (i = 0; i < card; ++i) {
		roots[i] = i;
	}

	cpt = 0;
	i = 0;
	while (cpt < card-1) {
		e = EX[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
		}
		++i;
	}

	cout << endl;
	for (i = 0; i < card-1; ++i) {
		e = tree[i];
		cout << i << ": " << e->v1 << ", " << e->v2 << " | " << e->b << ", " << e->w << endl;
	}

	return tree;
}

Edge **MonoObj::calculateBlPlus() {
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **EX = new Edge * [nEX];
	Edge **tree = new Edge * [card-1];
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();
	fusion(E0, E1, EX, nE0, nE1);

	Edge *e;


	int cpt = 0;
	int i = 0;



	for (i = 0; i < card; ++i) {
		roots[i] = i;
	}

	cpt = 0;
	i = 0;
	while (cpt < card-1) {
		e = EX[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
		}
		++i;
	}

	cout << endl;
	for (i = 0; i < card-1; ++i) {
		e = tree[i];
		cout << i << ": " << e->v1 << ", " << e->v2 << " | " << e->b << ", " << e->w << endl;
	}

	return tree;
}

Edge **MonoObj::calculateBu() {
	int card = edges->getCard();
	int nE0 = edges->getNE0();
	int nE1 = edges->getNE1();
	int nEX = edges->getNEX();
	Edge **EX = new Edge * [nEX];
	Edge **tree = new Edge * [card-1];
	Edge **E0 = edges->getE0();
	Edge **E1 = edges->getE1();
	copy(E0, E0+nE0, EX);
	copy(E1, E1+nE1, EX+nE0);

	Edge *e;


	int cpt = 0;
	int i = 0;



	for (i = 0; i < card; ++i) {
		roots[i] = i;
	}

	cpt = 0;
	i = 0;
	while (cpt < card-1) {
		e = EX[i];
		if (getRoot(e->v1) != getRoot(e->v2)) {
			setRoot(e->v2, e->v1);
			tree[cpt] = e;
			++cpt;
		}
		++i;
	}

	cout << endl;
	for (i = 0; i < card-1; ++i) {
		e = tree[i];
		cout << i << ": " << e->v1 << ", " << e->v2 << " | " << e->b << ", " << e->w << endl;
	}

	return tree;
}