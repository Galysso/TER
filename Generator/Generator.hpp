/*!
 * \file Generator.hpp
 * \author Jocelin C.
 * \brief Generate a related graph G=(V,E)\n
 * 			Exemple of data format\n
 * 			Vi is the vertex indexes, VCij is the indexes of vertices related to Vi :\n
 * 				|V|\n
 * 				V0 |V0| VC00 VC01 VC02 VC03\n
 * 				V1 |V1| VC10 VC11 VC12 VC13 VC14 VC15\n
 * 				V2 |V2| VC20\n
 * 				V3 |V3| VC30 VC31\n
 * 				V4 |V4| VC40 VC41 VC42\n
 * 
 * \param 1 (card)	: graph cardinality, |V| (card > 1)
 * \param 2 (min)	: minimum degree of vertices ((min > 0) AND (min < card))
 * \param 3 (max)	: maximum degree of vertices ((max > min-1) AND (min < card))
 * \param 4 (file)	: name of the generated file
 */

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

bool stringIsInt(char *string);
void checkParameters(int argc, char *argv[]);
void generate(int card, int min, int max, char *fileName);
//~ int selectVertex(int card, 

#endif //GENERATOR_HPP
