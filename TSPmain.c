/*
*	TSPmain.c
*	Data Structures II
*	by David Hunt
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

int main(int argc, char ** argv)
{
	FILE * fin;
	fin = fileIn("Presets.txt");
	sets * st;
	st = readPresets(fin);  //reads in the presets
	fileClose(fin);
	fin = fileIn("cities.txt");
	distance * dist;
	dist = readCities(fin, st); //read in the distance of the cities
	fileClose(fin);
	printDistanceTable(dist); //print the distance table generated from reading in the cities distances
	printf("The number of permutations for the brute force %d\n", dist->permutations);
	possiblePermutations(dist);
	printPossiblePermutations(dist);
	calculateTourDistance(dist);
	findBruteOptimal(dist);
	kruskal(dist);
	free(dist);
	free(st);
	return 0;
}
