#include "Graph/Edges.hpp"
#include "Algorithms/MonoObj.hpp"
#include "Algorithms/Naive.hpp"
#include "Algorithms/MGabowTarjan.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	cout << endl;
	clock_t start, stop;

	//Edges edges("../Instances/jouetManuel11");
	//Edges edges("../Instances/I1000_40");
	//Edges edges("../Instances/I100_20");
	Edges edges("../Instances/I1000_test");
	//Edges edges;


	//cout << "graph :" << endl;
	//edges.showDebug();
	Naive naive(&edges);
	MGabowTarjan mGaTar(&edges);

	start = clock();
	//naive.calculateSolutions(false);
	mGaTar.calculateSolutions(false);
	stop = clock();

	cout << endl << "temps : " << (double)(stop-start)/CLOCKS_PER_SEC << "s" << endl;

	cout << endl<< "COCO" << endl;
}
