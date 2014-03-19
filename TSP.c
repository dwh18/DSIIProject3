#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "files.h"

#define  MAX  10000;

int factorial(int n)
{
    if(n!=1)
     return n*factorial(n-1);
    else
     return 1;
}

void printDistanceTable(distance * dist)
{
	int i, j;
	for(i = 0; i < (dist->numCities); i++)
	{
		for(j = 0; j < (dist->numCities); j++)
		{
			printf("%lf ", dist->dist[i][j]);
		}
		printf("\n");
	}
}

void possiblePermutations(distance * dist)
{
	int i;
	int * arry =(int *)malloc(1+(dist->numCities)*(sizeof(int)));
	for(i = 0; i < dist->numCities; i++)
	{
		arry[i] = (i + 1);
	}
	permutation(dist, arry, 0, dist->numCities);
	free(arry);
}

void printPermutations(distance * dt, int * arry, int size)
{
	int i = 0, temp = 0;
	if(arry != 0)
	{
		for(i = 0; i < size; i++)
		{
			temp = arry[i];
			dt->brutArray[(dt->brutNum)][i] = temp;
		}
		dt->brutArray[dt->brutNum][size] = dt->brutArray[dt->brutNum][0];
		dt->brutNum++;
	}
}

void swap(int * arry, int num1, int num2)
{
	int temp = arry[num1];
	arry[num1] = arry[num2];
	arry[num2] = temp;
}

void rotation(int * arry, int startNum, int size)
{
	int temp = arry[startNum];
	int i = startNum;
	for(; i < size-1; i++)
	{
		arry[i] = arry[i+1];
	}
	arry[size-1] = temp;
}

void permutation(distance * dt, int * arry, int startNum, int size)
{
	printPermutations(dt, arry, size);
	int i, j;
	if(startNum < size)
	{
		for(i = size-2; i >= startNum; i--)
		{
			for(j = i + 1; j < size; j++)
			{
				swap(arry, i, j);
				permutation(dt, arry, i+1, size);
			}
			rotation(arry, i, size);
		}
	}
}


void printPossiblePermutations(distance * dist)
{
	int i, j;
	for(i = 0; i < dist->permutations; i++)
	{
		printf("For %d:  ", i);
		for(j = 0; j < (dist->numCities + 1); j++)
		{
			printf("%d ", dist->brutArray[i][j]);
		}
		printf("\n");
	}
}

void calculateTourDistance(distance * dist)
{
	int num1 = 0, num2 = 0;
	double sum = 0;
	int i = 0, j = 0;
	for(i = 0; i < dist->permutations; i++)
	{
		num1 = dist->brutArray[i][j];
		for(j = 1; j < (dist->numCities + 1); j++)
		{
			num2 = dist->brutArray[i][j];
			sum = sum + dist->dist[(num1-1)][(num2-1)];
			printf("Sum is %lf\n", sum);
			num1 = num2;
		}
		printf("The sum is %lf with array\n", sum);
		dist->tourDistance[i] = sum;
		for(j = 0; j < dist->numCities; j++)
		{
			printf("%d ", dist->brutArray[i][j]);
		}
		sum = 0;
		j = 0;
	}
	printf("\n");

	for(i = 0; i < dist->permutations; i++)
	{
		printf("For %d distance is %lf\n", (i + 1), dist->tourDistance[i]);
	}

}

void findBruteOptimal(distance * dist)
{
	int i, optimal = 0;
	for(i = 1; i < dist->permutations; i++)
	{
		if(dist->tourDistance[i] < dist->tourDistance[optimal])
		{
			optimal  = i;
		}
	}

	printf("The optimal travel with brute force is ");
	for(i = 0; i < (dist->numCities + 1); i++)
	{
		printf("%d ", dist->brutArray[optimal][i]);
	}
	printf("  with distance of %lf\n", dist->tourDistance[optimal]);
}

void calculateLowerBound(distance * dist)
{

}

void calculateUpperBound(distance * dist)
{

}

void kruskal(distance * dist)
{
	int ** minTree = (int **)malloc(1+ (dist->numCities)*(sizeof(int*)));
	int visited[dist->numCities];
	double ** bigArray = copyBigArray(dist);
	printDoubleArray(bigArray, dist->numCities);
	//int edges = ((dist->numCities - 1 ) * (dist->numCities))/2;
	int i,j, tempX = 0, tempY = 0, arraySize = dist->numCities, treeSize = 0;
	double temp, sum = 0;
	for(i = 0; i < dist->numCities; i++)
	{
		visited[i] = 0;
	}
	for(i = 0; i < dist->numCities; i++)
	{
		minTree[i] = (int *)malloc(1 + 2 * sizeof(int));
		for(j = 0; j < 2; j++)
		{
			minTree[i][j] = 0;
		}
	}
	while(arraySize > 1)
	{
		temp = 1000;
		for(i = 1; i < dist->numCities; i++)
		{
			for(j = 1; j < dist->numCities; j++)
			{
				if((bigArray[i][j] < temp) && (bigArray[i][j] != 0))
				{
					tempX = i;
					tempY = j;
					temp = bigArray[i][j];
				}
			}
		}
		printf("The temp is %lf\n", temp);
		if(temp != 1000)
		{
			 printArray(visited, dist->numCities);
			 if((visited[tempX] != 2) || (visited[tempY] != 2))
			 {
				 if((connectedTree(bigArray, minTree, tempX, tempY, (int *)&treeSize)) == 1)
				 {
					 printf(" %d -> %d with temp: %lf ", (tempX +1), (tempY+1), temp);
					if((visited[tempX] == 0) && (visited[tempY] == 0))
						 arraySize -= 2;
					 else
						 arraySize -= 1;
					sum = sum + temp;
					visited[tempX] += 1;
					visited[tempY] += 1;
					bigArray[tempX][tempY] = MAX;
					minTree[treeSize][0] = tempX;
					minTree[treeSize][1] = tempY;
					treeSize++;
				 }
			 }
			 else
			 {
				 bigArray[tempX][tempY] = MAX;
			 }
			 printArray(visited, dist->numCities);
			 printDoubleArray(bigArray, dist->numCities);
		}
	}

	printf("The sum is %lf\n", sum);
	free(bigArray);
	free(minTree);
}

double ** copyBigArray(distance * dist)
{
	double ** bigArray = (double **)malloc(1 + (dist->numCities)*(sizeof(double *)));
	int i, j;
	for(i = 0; i < dist->numCities; i++)
	{
		bigArray[i] = (double *)malloc(1 + (dist->numCities)*(sizeof(double)));
	}
	for(i = 0; i < dist->numCities; i++)
	{
		for(j = 0; j < dist->numCities; j++)
		{
			bigArray[i][j] = dist->dist[i][j];
		}
	}
	return bigArray;
}

void printArray(int * arry, int size)
{
	int i;
	printf("The visited number are: ");
	for(i = 0; i < size; i++)
	{
		printf(" %d ", arry[i]);
	}
	printf("\n");
}

void printDoubleArray(double ** arry, int size)
{
	int i, j;
	printf("\n\nThe big Array\n");
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			printf("%lf ", arry[i][j]);
		}
		printf("\n");
	}
}

int connectedTree(double ** arry, int ** tree, int x, int y, int * size)
{
	if(*size != 0)
	{
		int ans = 1, i;
		for(i = 0; i < *size; i++)
		{
			if((tree[i][0] == x) && (tree[i][1] == y))
			{
				ans = 0;
			}
			if((tree[i][0] == y) && (tree[i][1] == x))
			{
				ans = 0;
			}
		}
		if(ans == 0)
		{
			arry[x][y] = MAX;
		}
		return ans;
	}
	return 1;
}

int findLastTwo(distance * dist, double ** arry)
{
	int ans = 0;
	int i, j;
	double temp = MAX;
	while()
	{
		for(i = 0; i < dist->numCities; i++)
		{

		}
	}
	return ans;
}

