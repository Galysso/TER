#include "Edges.hpp"
#include "../Functions/Functions.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Edges::Edges(string fileName) {
	srand(5555);
	ifstream f(fileName.c_str());

	if (f) {
		int i, j;
		int vi, vj, nEX, cardGraph, nEdges, tmp;

		f >> cardGraph;
		f >> nEX;

		card = cardGraph;

		E0 = new Edge * [nEX];
		E1 = new Edge * [nEX];
		nE0 = 0;
		nE1 = 0;
		cardV = new int [cardGraph];
		Edge *e;

		for (i = 0; i < cardGraph; ++i) {
			f >> vi;
			f >> nEdges;
			cardV[vi] = nEdges;
			for (j = 0; j < nEdges; ++j) {
				f >> vj;
				if (vj > vi) {
					e = new Edge;
					e->w = 1 + rand() % cardGraph;
					e->v1 = vi;
					e->v2 = vj;
					if ((rand()%2) == 0) {
						e->b = false;
						E0[nE0] = e;
						nE0++;
					} else {
						e->b = true;
						E1[nE1] = e;
						nE1++;
					}
					/*cout << i << ", " << j << endl;
					showDebug();
					cout << endl << endl;*/
					//cout << nE0+nE1 << ": {" << e->v1 << "," << e->v2 << "} " << e->b << ", " << e->w << endl;
				}
			}
		}
		f.close();
		/*cout << endl << endl << endl;
		showDebug();*/

		bubbleSort(E0, nE0);
		bubbleSort(E1, nE1);
	} else {
		cout << "Fichier inexistant" << endl;
	}
}

Edges::Edges() {
	Edge *e;
	E0 = new Edge * [5];
	E1 = new Edge * [6];
	cardV = new int [7];
	cardV[0] = 2;
	cardV[1] = 5;
	cardV[2] = 3;
	cardV[3] = 3;
	cardV[4] = 3;
	cardV[5] = 4;
	cardV[6] = 2;

	nE0 = 5;
	nE1 = 6;
	card = 7;

	e = new Edge;
	e->v1 = 3;
	e->v2 = 4;
	e->b = 0;
	e->w = 8;
	E0[0] = e;

	e = new Edge;
	e->v1 = 1;
	e->v2 = 4;
	e->b = 0;
	e->w = 9;
	E0[1] = e;

	e = new Edge;
	e->v1 = 1;
	e->v2 = 5;
	e->b = 0;
	e->w = 7;
	E0[2] = e;

	e = new Edge;
	e->v1 = 2;
	e->v2 = 5;
	e->b = 0;
	e->w = 5;
	E0[3] = e;

	e = new Edge;
	e->v1 = 2;
	e->v2 = 6;
	e->b = 0;
	e->w = 4;
	E0[4] = e;

	e = new Edge;
	e->v1 = 0;
	e->v2 = 1;
	e->b = 1;
	e->w = 1;
	E1[0] = e;

	e = new Edge;
	e->v1 = 0;
	e->v2 = 3;
	e->b = 1;
	e->w = 4;
	E1[1] = e;

	e = new Edge;
	e->v1 = 1;
	e->v2 = 3;
	e->b = 1;
	e->w = 2;
	E1[2] = e;

	e = new Edge;
	e->v1 = 1;
	e->v2 = 2;
	e->b = 1;
	e->w = 2;
	E1[3] = e;

	e = new Edge;
	e->v1 = 4;
	e->v2 = 5;
	e->b = 1;
	e->w = 3;
	E1[4] = e;

	e = new Edge;
	e->v1 = 5;
	e->v2 = 6;
	e->b = 1;
	e->w = 6;
	E1[5] = e;

	bubbleSort(E0, nE0);
	bubbleSort(E1, nE1);
}

Edges::~Edges() {
	delete [] E0;
	delete [] E1;
}

Edge **Edges::getE0() {
	return E0;
}

Edge **Edges::getE1() {
	return E1;
}

int Edges::getNE0() {
	return nE0;
}

int Edges::getNE1() {
	return nE1;
}

int Edges::getNEX() {
	return nE1 + nE0;
}

int Edges::getCard() {
	return card;
}

int Edges::getCardV(int i) {
	return cardV[i];
}

void Edges::showDebug() {
	for (int i = 0; i < nE0; ++i) {
		cout << i << ": {" << E0[i]->v1 << "," << E0[i]->v2 << "} " << E0[i]->b << ", " << E0[i]->w << endl;
	}
	cout << endl;
	for (int i = 0; i < nE1; ++i) {
		cout << i << ": {" << E1[i]->v1 << "," << E1[i]->v2 << "} " << E1[i]->b << ", " << E1[i]->w << endl;
	}
}