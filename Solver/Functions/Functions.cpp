#include "Functions.hpp"
#include "../Graph/Edges.hpp"

#include <iostream>

using namespace std;

void bubbleSort(int *tab, int size) {
	bool sorted;
	int j;
	int tmp;

	do {
		sorted = true;
		for (j = 1; j < size; ++j) {
			if (tab[j-1] > tab[j]) {
				tmp = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = tmp;
				sorted = false;
			}
		}
		--size;
	} while (!sorted);
}

void bubbleSort(Edge **edges, int size) {
	bool sorted;
	int j;
	Edge *tmp;

	do {
		sorted = true;
		for (j = 1; j < size; ++j) {
			if (edges[j-1]->w > edges[j]->w) {
				tmp = edges[j];
				edges[j] = edges[j-1];
				edges[j-1] = tmp;
				sorted = false;
			}
		}
		--size;
	} while (!sorted);
}

void fusion(Edge **E0, Edge **E1, Edge **EX, int nE0, int nE1) {
	int i, nE0b, nE1b, nEX;
	nE0b = 0;
	nE1b = 0;
	nEX = nE1 + nE0;

	for (i = 0; i < nEX; ++i) {
		if (nE0b < nE0) {
			if ((nE1b >= nE1) || (E0[nE0b]->w <= E1[nE1b]->w)) {
				EX[i] = E0 [nE0b];
				++nE0b;
			} else {
				EX[i] = E1[nE1b];
				++nE1b;
			}
		} else {
			EX[i] = E1[nE1b];
			++nE1b;
		}
	}


	/*cout << endl << endl;
	Edge *e;
	for (i = 0; i < nEX; ++i) {
		e = EX[i];
		cout << i << ": {" << e->v1 << "," << e->v2 << "} " << e->b << ", " << e->w << endl;
	}*/
}

void bubbleSortVertices(int *v, bool *b, int *w, int size) {
	bool sorted;
	int j;
	int tmp;
	bool btmp;

	do {
		sorted = true;
		for (j = 1; j < size; ++j) {
			if (v[j-1] > v[j]) {
				sorted = false;
				tmp = v[j];
				v[j] = v[j-1];
				v[j-1] = tmp;

				btmp = b[j];
				b[j] = b[j-1];
				b[j-1] = btmp;

				tmp = w[j];
				w[j] = w[j-1];
				w[j-1] = tmp;
				
			}
		}
		--size;
	} while (!sorted);
}

int dichotomySearch(int *tab, int size, int val) {
	int ind;

	if ((val >= tab[0]) && (val <= tab[size-1])) {
		int lower, upper, indVal;
		lower = 0;
		upper = size;
		ind = upper/2;
		indVal = tab[ind];

		while ((upper > lower+1) && (indVal != val)) {
			if (indVal > val) {
				upper = ind;
			} else {
				lower = ind;
			}
			ind = lower + (upper-lower)/2;
			indVal = tab[ind];
		}

		if (indVal != val) {
			ind = -1;
		}
	} else {
		ind = -1;
	}

	return ind;
}