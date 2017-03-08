#include "Graph/Edges.hpp"
#include "Algorithms/MonoObj.hpp"
#include "Algorithms/Naive.hpp"
#include "Algorithms/MGabowTarjan.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	clock_t start, stop;

	//Edges edges("../Instances/jouetManuel11");
	//Edges edges("../Instances/test1000");
	Edges edges;
	cout << "graph :" << endl;
	edges.showDebug();
	Naive naive(&edges);
	//MGabowTarjan mGaTar(&edges);
	
	start = clock();
	naive.calculateSolutions();
	//mGaTar.calculateSolutions();
	stop = clock();

	cout << endl << "temps : " << (double)(stop-start)/CLOCKS_PER_SEC << "s" << endl;

	/*mono.showDebug();
	cout << "b=" << mono.getB() << endl;
	cout << "w=" << mono.getW() << endl;*/

	cout << endl<< "COCO" << endl;
}
