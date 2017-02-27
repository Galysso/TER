#ifndef MONOOBJ_HPP
#define MONOOBJ_HPP

#include "../Graph/Edges.hpp"

class MonoObj {
	private:
		Edges *edges;
		int *roots;

	private:
		int getRoot(int indV);
		void setRoot(int indV, int ind);

	public:
		MonoObj(Edges *e);
		~MonoObj();
		Edge **calculateBl();
		Edge **calculateBlPlus();
		Edge **calculateBu();
};

#endif