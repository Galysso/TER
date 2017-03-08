#ifndef MGABOWTARJAN_HPP
#define MGABOWTARJAN_HPP

#include "../Graph/Edges.hpp"

class MGabowTarjan {
	private:
		Edges *edges;
		
	public:
		MGabowTarjan(Edges *edges);
		void calculateSolutions();
	
};

#endif
