//#include "Graph/Graph.hpp"
#include "Graph/Edges.hpp"
#include "Algorithms/MonoObj.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	/*Graph g("../Instances/petitJouet10");
	g.showGraph();*/

	Edges edges("../Instances/jouetManuel11");
	//Edges edges;
	edges.showDebug();
	MonoObj mono(&edges);
	Edge **tree = mono.calculateBlPlus();

	cout << "COCO" << endl;
}