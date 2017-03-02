#ifndef EDGES_HPP
#define EDGES_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct Edge {
	int v1;
	int v2;
	bool b;
	int w;
};

class Edges {
	private:
		Edge **E0;
		Edge **E1;
		int nE0;
		int nE1;
		int card;
		int *cardV;	// The cardinality of each vertex

	public:
		Edges(string fileName);
		Edges();
		~Edges();

		Edge **getE0();
		Edge **getE1();
		int getNE0();
		int getNE1();
		int getNEX();
		int getCard();
		int getCardV(int i);

		void showDebug();
};

#endif