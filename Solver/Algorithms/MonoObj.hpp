#ifndef MONOOBJ_HPP
#define MONOOBJ_HPP

#include "../Graph/Edges.hpp"

class MonoObj {
	private:
		Edges *edges;
		Edge **Bl;
		Edge **BlPlus;
		Edge **Bu;
		int *roots;
		int b;
		int w;

	private:
		int getRoot(int indV);
		void setRoot(int indV, int ind);

	public:
		MonoObj(Edges *e);
		~MonoObj();
		void calculateBl();
		void calculateBlPlus();
		void calculateBu();
		int getB();
		int getW();
		Edge **getBl();
		Edge **getBlPlus();
		Edge **getBu();

		void showDebug();
};

#endif