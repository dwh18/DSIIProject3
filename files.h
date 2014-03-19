/*
 * Files.h
 *
 *  Created on: Jan 16, 2014
 *      Author: david
 */

#ifndef FILES_H_
#define FILES_H_

#include <stdio.h>
#include <stdlib.h>
#include "TSP.h"

FILE * fileIn(char * fileName);
/* fileIn - opens a file based on the file name passed in as a parameter
@param char * fileName - the string of a file to be opened
@return FILE * - returns a file pointer to that file specified
*/

FILE * fileClose(FILE * file);
/* fileClose - closes a file pointer that is passed as a parameter
@param FILE * file - the file pointer to be closed
@return FILE * - returns a file pointer that should be null if closed succesfully
*/

char * fileRead(FILE * file);
/* fileRead - reads from a file that is passed in as a parameter
@param FILE * file  - the file pointer to a file that has been opened and needs
to be read into the program
@return char * - returns a character string of the entire file
*/

sets * readPresets(FILE * fin);

distance * readCities(FILE * fin, sets * st);

distance * generateDistance(sets * st);

char * toBeReadIn();
/* toBeReadIn - returns a list of files that are to be read into the program
@return char * - returns a character string of all the files to be read in 
*/

void commandLine();
/*

*/

char ** fileNames(int numOfFiles, FILE * fin);
/* fileNames - reads from "inputfiles.txt" and counts the number of files
then splits file names into a two dimensional array
@param int * numOfFiles - the number of files there are to be read in
@param FILE * fin - the file pointer to "inputfiles.txt"
@return char ** - returns a two dimensional array of all the file names
*/

int countFiles(FILE * file);
/* countFiles - reads from "inputfiles.txt" and counts the number of files and returns the number
@param FILE * file - a file pointer to "inputfiles.txt"
@return int - returns the number of files in "current directory/files"
*/

void emptyBuffer(char * arr, int size);
/*emptyBuffer - a utility function that makes sure that a char array is empty before use
I use this to lower or eliminate the chance of errors
@param char * arr - a character array that needs to be reset
@param int size - the size of the character array
*/

void emptyBuffer2(char ** arr, int size);
/*emptyBuffer2 - a utility function that makes sure that a char array is empty before use
I use this to lower or eliminate the chance of errors
@param char ** arr - a two dimensional character array that needs to be reset
@param int size - the size of the character array
*/

char ** retainFiles();
/* retainFiles - the main function that gets the information out of a file "inputfiles.txt" and returns as
a two dimensional character array listing all the files that need to be read in
@return char ** - returns a two dimensional array of all the file names
*/

void printFileNames(char ** arr, int size);


void breakUp(int sentenceSize, char * content);

void eliminateNewLine(char * str);

void showASCII(char * str);

int countWords(char * str);

char ** createTwoArray(int wordCount, int sentenceSize, int * arraySize);

void printTwoArray(char ** arry, int * arraySize);

void stringAppend(char * str1, char * str2, int * postion);

int isPrintable(char * str, int * postion);

void parseSentences(char * content, char ** arry, int words, int * position);

void findSentence(char * content, int words, int * position, char * newStr);

int nextPosition(char * content, int position, int length);

void endArray(char ** arry, char * content, int words, int * position, int length, int lastArrayNum);

char * untilEnd(char * content, int * position, int length);

void transferOver(char * str, char ** arry, int arrayNum);

#endif /* FILES_H_ */
