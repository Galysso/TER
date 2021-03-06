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
	int lastSwap = 0;

	do {
		sorted = true;
		for (j = 1; j < size; ++j) {
			if (edges[j-1]->w > edges[j]->w) {
				tmp = edges[j];
				edges[j] = edges[j-1];
				edges[j-1] = tmp;
				sorted = false;
				lastSwap = j;
			}
		}
		size = lastSwap;
	} while (!sorted);
}

void mergeSort(Edge **edges, int size) {
	Edge **res = new Edge * [size];
	mergeSortRec(res, edges, 0, size);
}

void mergeSortRec(Edge **res, Edge **edges, int debut, int fin) {
	if (fin-debut > 2) {
		mergeSortRec(res, edges, debut, debut+(fin-debut)/2);
		mergeSortRec(res, edges, debut+(fin-debut)/2, fin);
		merge(res, edges, debut, debut+(fin-debut)/2, debut+(fin-debut)/2, fin);
	} else {
		merge(res, edges, debut, debut+1, debut+1, fin);
	}
}

void merge(Edge **res, Edge **edges, int i1, int i2, int j1, int j2) {
	int k = i1;
	while (k < j2) {
		if (i1 < i2) {
			if ((j1 == j2) || (edges[i1]->w <= edges[j1]->w)) {
				res[k] = edges[i1];
				++i1;
			} else {
				res[k] = edges[j1];
				++j1;
			}
		} else {
			res[k] = edges[j1];
			++j1;
		}
		++k;
	}
	for (int i = 0; i < j2; ++i) {
		edges[i] = res[i];
	}
}

void mergeSort(Edge **E1, Edge **E2, int size) {
	Edge **res1 = new Edge * [size];
	Edge **res2 = new Edge * [size];
	mergeSortRec(res1, res2, E1, E2, 0, size);
}

void mergeSortRec(Edge **res1, Edge **res2, Edge **E1, Edge **E2, int debut, int fin) {
	if (fin-debut > 2) {
		mergeSortRec(res1, res2, E1, E2, debut, debut+(fin-debut)/2);
		mergeSortRec(res1, res2, E1, E2, debut+(fin-debut)/2, fin);
		merge(res1, res2, E1, E2, debut, debut+(fin-debut)/2, debut+(fin-debut)/2, fin);
	} else {
		merge(res1, res2, E1, E2, debut, debut+1, debut+1, fin);
	}
}

void merge(Edge **res1, Edge **res2, Edge **E1, Edge **E2, int i1, int i2, int j1, int j2) {
	int k = i1;
	while (k < j2) {
		if (i1 < i2) {
			if ((j1 == j2) || ((E1[i1]->w - E2[i1]->w) <= (E1[j1]->w - E2[j1]->w))) {
				res1[k] = E1[i1];
				res2[k] = E2[i1];
				++i1;
			} else {
				res1[k] = E1[j1];
				res2[k] = E2[j1];
				++j1;
			}
		} else {
			res1[k] = E1[j1];
			res2[k] = E2[j1];
			++j1;
		}
		++k;
	}
	for (int i = 0; i < j2; ++i) {
		E1[i] = res1[i];
		E2[i] = res2[i];
	}
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

void showEdges(Edge **e, int n) {
	for (int i = 0; i < n; ++i) {
		cout << i << ": (" << e[i]->v1 << "," << e[i]->v2 << ") b=" << e[i]->b << " c=" << e[i]->w << endl;
	}
}