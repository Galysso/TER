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

void generate(int card, int min, int max, char *fileName) {
	ofstream file(fileName, ios::out | ios::trunc);
	assert(file);
	srand(time(NULL));
	
	file << card << endl;
	
	/** the vertices related to Vcard */
	int *vertices[card];
	/** the vertices cardinality */
	int cardVertices[card];
	/** random cardinality */
	int randCardMin;
	
	int i, j;
	
	for (i = 0; i < card; ++i) {
		cardVertices[i] = 0;
		vertices[i] = new int[card-1];
	}
}

int main(int argc, char *argv[]) {
	checkParameters(argc, argv);
	generate(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4]);
	
	cout << "COCO" << endl;
	
	return 0;
}
