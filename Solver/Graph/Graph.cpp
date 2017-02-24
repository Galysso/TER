#include "Graph.hpp"

#include "../Functions/Functions.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Graph::Graph(string fileName) {
	ifstream f(fileName.c_str());

	if (f) {
		bool sorted;
		int i, j, tmp;
		int cardG, cardV;
		f >> cardG;

		_cardG = cardG;
		_cardV = new int [cardG];
		_vertices = new int * [cardG];

		for (i = 0; i < cardG; ++i) {
			f >> tmp;					// the first column corresponds to i
			f >> cardV;
			_vertices[i] = new int [cardV];
			_cardV[i] = cardV;

			for (j = 0; j < cardV; ++j) {
				f >> _vertices[i][j];
			}
			bubbleSort(_vertices[i], cardV);
		}
	} else {
		cout << "Fichier inexistant" << endl;
	}
}

Graph::~Graph() {}

bool Graph::areLinked(int v1, int v2) {
	bool res;

	if (_cardV[v1] < _cardV[v2]) {
		res = (dichotomySearch(_vertices[v1], _cardV[v1], v2) != -1);
	} else {
		res = (dichotomySearch(_vertices[v2], _cardV[v2], v1) != -1);
	}

	return res;
}

void Graph::showGraph() {
	cout << "|G|=" << _cardG << endl;

	for (int i = 0; i < _cardG; ++i) {
		cout << i << ": (" << _cardV[i] << ") ";
		for (int j = 0; j < _cardV[i]; ++j) {
			cout << _vertices[i][j] << " ";
		}
		cout << endl;
	}
}