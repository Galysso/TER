#include "Graph/Edges.hpp"
#include "Algorithms/MonoObj.hpp"
#include "Algorithms/Naive.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	clock_t start, stop;
	/*Graph g("../Instances/petitJouet10");
	g.showGraph();*/

	//Edges edges("../Instances/jouetManuel11");
	//Edges edges("../Instances/jouet100");
	Edges edges;
	cout << "graph :" << endl;
	edges.showDebug();
	Naive naive(&edges);
	naive.calculateSolutions();



	/*MonoObj mono(&edges);
	start = clock();
	for (int i = 0; i < 10000000; ++i) {
		mono.calculateBu();
	}
	stop = clock();

	cout << "temps : " << (double)(stop-start)/CLOCKS_PER_SEC << "s" << endl;

	mono.showDebug();
	cout << "b=" << mono.getB() << endl;
	cout << "w=" << mono.getW() << endl;*/

	cout << "COCO" << endl;
}