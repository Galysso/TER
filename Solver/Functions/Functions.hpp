#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "../Graph/Edges.hpp"

void bubbleSort(int *tab, int size);

void bubbleSort(Edge **edges, int size);

void mergeSort(Edge **edges, int size);

void mergeSort(Edge **E1, Edge **E2, int size);

void merge(Edge **res, Edge **edges, int i1, int i2, int j1, int j2);

void mergeSortRec(Edge **res1, Edge **res2, Edge **E1, Edge **E2, int debut, int fin);

void mergeSortRec(Edge **res, Edge **edges, int debut, int fin);

void merge(Edge **res1, Edge **res2, Edge **E1, Edge **E2, int i1, int i2, int j1, int j2);

void fusion(Edge **E0, Edge **E1, Edge **EX, int nE0, int nE1);

void bubbleSortVertices(int *v, bool *b, int *w, int size);

int dichotomySearch(int *tab, int size, int val);

void showEdges(Edge **e, int n);

#endif