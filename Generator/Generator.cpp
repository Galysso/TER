#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include "Generator.hpp"

using namespace std;

bool stringIsInt(char *str) {
	while(*str != 0) {
		if(isdigit(*str)) {
			++str;
		} else {
			return false;
		}
	}
	return true;
}

void checkParameters(int argc, char *argv[]) {
	assert(argc == 5);
	for (int i = 1; i < 4; ++i) {
		assert(stringIsInt(argv[i]));
	}
	assert(atoi(argv[1]) > 1);
	assert(atoi(argv[2]) > 0);
	assert(atoi(argv[2]) < atoi(argv[1]));
	assert(atoi(argv[3]) > (atoi(argv[2])-1));
	assert(atoi(argv[3]) < atoi(argv[1]));
}

void deleteTwoElements(int ind1, int ind2, int *size, int *table) {
	int i, j, ind;
	*size = *size - 2;
	if (ind1 < ind2) {
		i = ind1;
		j = ind2 - 1;
	} else {
		i = ind2;
		j = ind1 - 1;
	}
	for (ind = i; ind < j; ++ind) {
		table[ind] = table[ind+1];
	}
	for (ind = j; ind < *size; ++ind) {
		table[ind] = table[ind+2];
	}
}

void deleteElement(int ind, int *size, int *table) {
	*size = *size - 1;
	for (int i = ind; i < *size; ++i) {
		table[i] = table[i+1];
	}
}

void connect(int V1, int V2, int **graph) {
	int cardV;
	
	cardV = graph[V1][0];
	graph[V1][cardV+1] = V2;
	graph[V1][0] = cardV + 1;
	
	cardV = graph[V2][0];
	graph[V2][cardV+1] = V1;
	graph[V2][0] = cardV + 1;
}

bool areConnected(int V1, int V2, int **graph) {
	bool res = false;
	int Vi, Vj, card, ind;
	
	if (graph[V2][0] < graph[V1][0]) {
		card = graph[V2][0];
		Vi = V2;
		Vj = V1;
	} else {
		card = graph[V1][0];
		Vi = V1;
		Vj = V2;
	}
	
	ind = 1;
	while (!res && (ind <= card)) {
		res = (graph[Vi][ind] == Vj);
		++ind;
	}
	
	return res;
}

void generate(int card, int min, int max, char *fileName) {
	ofstream file(fileName, ios::out | ios::trunc);
	assert(file);
	//~ srand(5);
	srand(time(NULL));
	
	file << card << endl;
	
	int cpt, randCard, ind, i, j, Vi, Vj;
	
	/** The table of the unconnected vertices */
	int *unconnected = new int[card];
	/** The number of unconnected vertices */
	int nbUnconnected = card;
	/** The table of the connected vertices */
	int *vertices = new int[card];
	/** The number of connected vertices */
	int nbConnected = 0;
	/** The graph
	 * let i be the vertex considered
	 * graph[i][0], the number of vertices connected to i
	 * graph[i][j], j > 0 a vertex connected to i
	 */
	int **graph = new int *[card];
	
	// We set the indexes of the unconnected vertices (0 to card-1)
	for (i = 0; i < card; ++i) {
		unconnected[i] = i;
		graph[i] = new int[card];
	}
	
	// We select the two first vertices to connect
	Vi = rand() % (card-1);
	Vj = rand() % card;
	if (Vi == Vj) {
		++Vj;
	}
	
	// We set the graph
	connect(Vi, Vj, graph);
	
	// We add them to the connected vertices
	vertices[0] = Vi;
	vertices[1] = Vj;
	nbConnected = 2;
	
	// We delete the two elements and shift the table of the unconnected vertices;
	deleteTwoElements(Vi, Vj, &nbUnconnected, unconnected);
	
	// We create a random covering tree
	while (nbUnconnected > 0) {
		i = rand() % nbConnected;
		j = rand() % nbUnconnected;
		Vi = vertices[i];
		Vj = unconnected[j];
		connect(Vi, Vj, graph);
		vertices[nbConnected] = Vj;
		++nbConnected;
		deleteElement(j, &nbUnconnected, unconnected);
	}
	
	// We add randoms connections
	for (Vi = 0; Vi < card-1; ++Vi) {
		randCard = min + rand() % (max-min+1);
		while (graph[Vi][0] < randCard) {
			Vj = Vi + 1 + (rand() % (card-Vi-1));
			cpt = 0;
			while ((Vj < card) && ((areConnected(Vi, Vj, graph)) || (graph[Vj][0] >= max))) {
				Vj = (Vj+1) % card;
			}
			connect(Vi, Vj, graph);
		}
	}
	
	int moy = 0;
	// We write in the file
	for (i = 0; i < card; ++i) {
		file << i << " ";
		moy = moy + graph[i][0];
		for (j = 0; j <= graph[i][0]; ++j) {
			file << graph[i][j] << " ";
		}
		file << endl;
	}
	
	cout << "moy=" << (double)moy/(double)card << endl;
	file.close();
}

/// PROBLEMES :
/// - NE FINIT PAS TOUJOURS (quand min et max sont proches)
/// - LES SOMMETS D'INDICES PLUS ELEVES ONT EN MOYENNE UNE CARDINALITE PLUS ELEVEE
/// - LA MOYENNE DES CARDINALITES DES SOMMETS EST PLUS ELEVEE QUE CELLE QUE L'ON DEVRAIT AVOIR
int main(int argc, char *argv[]) {
	checkParameters(argc, argv);
	generate(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4]);
	cout << "done" << endl;	
	return 0;
}
