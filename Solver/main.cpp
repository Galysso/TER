#include "Graph/Graph.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	Graph g("../Instances/petitJouet10");
	g.showGraph();

	cout << "COCO" << endl;
}