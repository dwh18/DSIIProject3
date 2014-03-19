#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#ifndef TSP_H_
#define TSP_H_

typedef struct sets
{
	int numCities;
	int numTours;
	int numGens;
	double numMutation;
	double elites;
}sets;

typedef struct distance
{
	double ** dist;
	int numCities;
	int numTours;
	int permutations;
	int upperBound;
	int lowerBound;
	int brutNum;
	int ** brutArray;
	double * tourDistance;
}distance;
/*
 * factorial - generates the number of permutations for the number of cities
 * @param int temp - the number that you want to generate the factorial for
 * @return int - the number of the factorial returned
 */
int factorial(int temp);

/*
 * printDistanceTable - prints the distance in a table format
 */
void printDistanceTable(distance * dist);

/*
 * possiblePermutations - generate the permutations
 */
void possiblePermutations(distance * dist);

/*
 * printPermutations - prints out all the permutations
 */
void printPermutations(distance * dt, int * num, int size);

/*
 * swap - swaps numbers in the array
 */
void swap(int * arry, int num1, int num2);

/*
 * rotation - rotates the numbers in the array in order to find the different permutations
 */
void rotation(int * arry, int startNum, int size);

/*
 * permutations - just figures out the permutations of the routes
 */
void permutation(distance * dt, int * arry, int startNum, int size);

/*
 * printPossiblePermutations - a utility function that prints the permutations
 */
void printPossiblePermutations(distance * dist);

/*
 * calculatesTourDistance - calculates the distance for the tours in the brute force
 */
void calculateTourDistance(distance * dist);

/*
 * findBruteOptimal - searches the number for the most optimal route for all the brute force
 */
void findBruteOptimal(distance * dist);

void calculateLowerBound(distance * dist);

void calculateUpperBound(distance * dist);

double ** copyBigArray(distance * dist);

void kruskal(distance * dist);

void printArray(int * arry, int size);

void printDoubleArray(double ** arry, int size);

int connectedTree(double ** arry, int ** tree, int x, int y, int * size);

int findLastTwo(distance * dist, double ** arry);

#endif /* TSP_H_ */
