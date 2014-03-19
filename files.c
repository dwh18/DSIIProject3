#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "TSP.h"


/* fileIn - opens a file based on the file name passed in as a parameter
@param char * fileName - the string of a file to be opened
@return FILE * - returns a file pointer to that file specified
*/
FILE * fileIn(char * fileName)
{
	FILE * file;
	file = fopen(fileName, "r");
	if(file == NULL)
	{
		perror("Error: Could not open file\n");
	}
	return file;
}

/* fileClose - closes a file pointer that is passed as a parameter
@param FILE * file - the file pointer to be closed
@return FILE * - returns a file pointer that should be null if closed succesfully
*/
FILE * fileClose(FILE * file)
{
	int i;
	i = fclose(file);
	if(i == EOF)
	{
		perror("Error: Could not close file\n");
	}
	file = NULL;
	return file;
}

/* fileRead - reads from a file that is passed in as a parameter
@param FILE * file  - the file pointer to a file that has been opened and needs
to be read into the program
@return char * - returns a character string of the entire file

*/
char * fileRead(FILE * file)
{
	fseek(file, 0, SEEK_END);
	long fileLength = ftell(file);
	rewind(file);

	char * fileIn = (char *)malloc((sizeof(char)*fileLength + 5));
	size_t result = fread(fileIn, sizeof(char), fileLength, file);
	if(result != fileLength)
	{
		perror("Error");
		printf("\nfileLegth = %ld\n", fileLength);
		printf("\nresult = %lf\n", (double)result);
		return fileIn;
	}
	return fileIn;
}

sets * readPresets(FILE * fin)
{
	sets * st = (sets *)malloc(1+sizeof(sets));
	fscanf(fin, "%d", &st->numCities);
	fscanf(fin, "%d", &st->numTours);
	fscanf(fin, "%d", &st->numGens);
	fscanf(fin, "%lf", &st->numMutation);
	fscanf(fin, "%lf", &st->elites);
	return st;
}

distance * readCities(FILE * fin, sets * st)
{
	distance * dist = generateDistance(st);
	int i, j;
	for(i = 0; i < (st->numCities); i++)
	{
		for(j = 0; j < (st->numCities); j++)
		{
			if(j == i)
			{
				dist->dist[i][j] = 0;
			}
			else
			{
				fscanf(fin, "%lf", &dist->dist[i][j]);
			}
		}
	}


	return dist;
}

distance * generateDistance(sets * st)
{
	distance * temp = (distance *)malloc(1+sizeof(distance));
	temp->dist = (double **)malloc(1+(st->numCities) * (sizeof(double *)));
	int i, j;
	for(i = 0; i < (st->numCities); i++)
	{
		temp->dist[i] = (double *)malloc(1+(st->numCities) * (sizeof(double)));
	}
	temp->numCities = (st->numCities);
	temp->numTours = (st->numTours);
	temp->permutations = factorial(st->numCities);
	temp->brutNum = 0;
	temp->lowerBound = 0;
	temp->upperBound = 0;
	temp->tourDistance = (double *)malloc(1+ (temp->permutations)*(sizeof(double)));
	temp->brutArray = (int **)malloc(1+(temp->permutations)*(sizeof(int *)));
	for(i = 0; i < (temp->permutations); i++)
	{
		temp->brutArray[i] = (int *)malloc(1 + (st->numCities + 1)*(sizeof(int)));
	}
	for(i = 0; i < (temp->permutations); i++)
	{
		for(j = 0; j < (st->numCities + 1); j++)
		{
			temp->brutArray[i][j] = 0;
		}
	}
	return temp;
}


/* toBeReadIn - returns a list of files that are to be read into the program
@return char * - returns a character string of all the files to be read in 

*/
char * toBeReadIn()
{
	system("ls  > inputfile.txt");
	//system("ls");	
	//system("ls > inputfile.txt");
	FILE * temp;
	temp = fileIn("inputfile.txt");
	char * str = fileRead(temp);
	return str;
}

void commandLine()
{
	char i = 'y';
	int numFiles = 0;
	while(i == 'y')
	{
		printf("How many files do you want to compare");
		scanf("%d", &numFiles);
		printf("Do you want to run the program again(\'y\' for yes\n");
		printf("\'n\' for no)");
		scanf("%c", &i);
	}
}

/* fileNames - reads from "inputfiles.txt" and counts the number of files
then splits file names into a two dimensional array
@param int * numOfFiles - the number of files there are to be read in
@param FILE * fin - the file pointer to "inputfiles.txt"
@return char ** - returns a two dimensional array of all the file names
*/
char ** fileNames(int numOfFiles, FILE * fin)
{
	int j = 0, p = 0;
	char ** files;
	files = (char **)malloc(1 + numOfFiles * (sizeof(char*)));
	for(j = 0; j < numOfFiles; j++)
	{
		files[j] = (char *)malloc((sizeof(char))*30 + 1);
	}
	char * sentence = (char *)malloc((sizeof(char))*100+1);
	emptyBuffer(sentence, 100);
	char letter = '\0';
	j = 0;
	while(((letter = getc(fin))!= EOF) && (j < numOfFiles))
	{
		if(letter == '\n')
		{
			strcpy(files[j], sentence);
			j++;
			p = 0;
			emptyBuffer(sentence, 100);
		}
		else
		{
			sentence[p] = letter;
			p++;
		}
	}
	return files;
}

/*emptyBuffer - a utility function that makes sure that a char array is empty before use
I use this to lower or eliminate the chance of errors
@param char * arr - a character array that needs to be reset
@param int size - the size of the character array
*/
void emptyBuffer(char * arr, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		arr[i] = '\0';
	}
}

/*emptyBuffer2 - a utility function that makes sure that a char array is empty before use
I use this to lower or eliminate the chance of errors
@param char ** arr - a two dimensional character array that needs to be reset
@param int size - the size of the character array
*/
void emptyBuffer2(char ** arr, int size)
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < 30; j++)
		{
			arr[i] = '\0';
		}
	}
}

/* countFiles - reads from "inputfiles.txt" and counts the number of files and returns the number
@param FILE * file - a file pointer to "inputfiles.txt"
@return int - returns the number of files in "current directory/files"
*/
int countFiles(FILE * file)
{
	rewind(file);
	char temp;
	int i = 0;
	while((temp = getc(file))!=EOF)
	{
		if(temp == '\n')
		{
			i++;
		}
	}
	rewind(file);
	return i;
}

/* retainFiles - the main function that gets the information out of a file "inputfiles.txt" and returns as
a two dimensional character array listing all the files that need to be read in
@return char ** - returns a two dimensional array of all the file names
*/
char ** retainFiles()
{
	FILE * fileList;
	fileList = fopen("inputfile.txt", "r");
	toBeReadIn();
	char ** files;
	int numOfFiles = countFiles(fileList);
	files = fileNames(numOfFiles, fileList);
	printFileNames(files, numOfFiles);

	return files;
}

void printFileNames(char ** arr, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		printf("File %d : %s\n", (i+1), arr[i]);
	}
}

void breakUp(int sentenceSize, char * content)
{
	//int sizeOfFile = strlen(content);
	int i = 0, j = 0, wordCount;
	int * arraySize = (int *)malloc((sizeof(int))+1);
	char * temp = (char *)malloc(1+100*(sizeof(char)));
	printf("\nSentence size is %d\n", sentenceSize);

	wordCount = countWords(content);
	eliminateNewLine(content);
	printf("The number of words is %d\n", wordCount);
	printf("The number of sentence is %d\n", (wordCount-sentenceSize));
	char ** arry = createTwoArray(wordCount, sentenceSize, arraySize);
	printf("The arraySize is %d\n", *arraySize);
	temp = strtok(content, " .");
	while((temp != NULL) && (j < 12))
	{
		printf("Sentence %d is : ", (j+1));
		fflush(stdout);
		while((i < sentenceSize) && (temp != NULL))
		{
			printf("%s ", temp);
			fflush(stdout);
			temp = strtok(NULL, " .");
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
	free(temp);
	free(arry);
}

void eliminateNewLine(char * str)
{
	int i, sentSize;
	sentSize = strlen(str);
	//showASCII(str);
	printf("String length is %d\n", sentSize);
	for(i = 0; i < sentSize; i++)
	{
		if((str[i] == '\n') || (str[i] == '.'))
		{
			str[i] = ' ';
		}
	}
	//printf("Content is: %s\n\n", str);
	//showASCII(str);
	//printf("\n\n");
}

void showASCII(char * str)
{
	int i, sentSize, j;
	sentSize = strlen(str);
	for(i = 0; i < (sentSize-1); i = i + 10)
	{
		for(j = 0; j < 10; j++)
		{
			printf("%d ", str[i+j]);
		}
		printf("\n");
	}
	//printf("Char at last position is %c with %d\n", str[sentSize], (int)str[sentSize]);
	printf("\nThe End of showASCII\n");
}

int countWords(char * str)
{
	int count = 0, strln, i = 0;
	strln = strlen(str);
	while(i < strln)
	{
		if((str[i] == 32) || (str[i] == 10))
		{
			count++;
		}
		i++;
	}
	return (count+1);
}

char ** createTwoArray(int wordCount, int sentenceSize, int * arraySize)
{
	int i;
	*arraySize = (wordCount - sentenceSize) + 1;
	printf("ArraySize is %d\n", *arraySize);
	char ** arr = (char **)malloc(1+((*arraySize))*(sizeof(char *)));
	for(i = 0; i <= *arraySize; i++)
	{
		arr[i] = (char *)malloc(1 + 100*(sizeof(char)));
	}
	return arr;
}

void stringAppend(char * str1, char * str2, int * postion)
{
	str1[*postion] = 32;
	*postion = *postion + 1;
	strncat(str1, str2, (100 - strlen(str1)));
}

void printTwoArray(char ** arry, int * arraySize)
{
	int i;
	for(i = 0; i < *arraySize; i++)
	{
		printf("%s\n", arry[i]);
	}

}

int isPrintable(char * str, int * postion)  //return 1 if found space or new line
{
	int i = 0;
	if((str[*postion] == 32) || (str[*postion] == 10))
	{
		i = 1;
	}
	return i;
}

void parseSentences(char * content, char ** arry, int words, int * position)
{
	int i = 0, lgth;
	eliminateNewLine(content);
	char * curSentence = (char *)malloc(1+200*(sizeof(char)));
	lgth = strlen(content);
	int wordC = countWords(content);
	printf("The number of words is %d\n", wordC);
	while(i < ((wordC - words)))
	{
		printf("String %d is ", (i+1));
		emptyBuffer(curSentence, 200);
		findSentence(content, words, position, curSentence);
		strncpy(arry[i], curSentence, 200);
		//printf("  Position before %d  ", *position);
		*position = nextPosition(content, *position, lgth);
		//printf("  Position after %d  ", *position);
		//printf("\t\tEnd of Sentence %d\n", (i+1));
		i++;
	}
	//endArray(arry, content, words, position, lgth, (wordC - words));
	printf("Reached end of parseSentences\n");
}

int nextPosition(char * content, int position, int length)
{
	if(position > length)
	{
		return 0;
	}
	int temp = isPrintable(content, &position);	//locates next character that
	while((temp == 0) && (position < length))							//is a space or new line
	{
		position = position + 1;
		temp = isPrintable(content, &position);
	}

	while((temp == 1) && (position < length))						//locates next character that
	{											//is not a space or new line
		position = position + 1;
		temp = isPrintable(content, &position);
	}
	return position;
}

void findSentence(char * content, int words, int * position, char * newStr)
{
	//printf("in parseSentences\n");
	int contentSize = strlen(content);
	int currentPosition = *position;
	int newStringPosition = 0;
	//char * newStr = (char *)malloc(1+100*(sizeof(char)));
	int i = 0;
	while((currentPosition != contentSize) && (i < words))
	{
		if(isPrintable(content, &currentPosition) == 1)
		{
			newStr[newStringPosition] = 32;
			newStringPosition++;
			currentPosition = nextPosition(content, currentPosition, contentSize);
			i++;
		}
		else if(newStringPosition < 100)
		{
			newStr[newStringPosition] = content[currentPosition];
			newStringPosition++;
			currentPosition++;
		}
	}
	strcat(newStr, "\0");
	printf(" %s\n", newStr);
	//return newStr;
}

void endArray(char ** arry, char * content, int words, int * position, int length, int lastArrayNum)
{
	if(*position > length)
	{
		return;
	}
	char * newStr;
	printf("The current position is %d\n", *position);
	printf("The length is %d\n", length);
	printf("The last array number is %d\n", lastArrayNum);
	printf("The words is %d\n", words);
	newStr = untilEnd(content, position, length);
	printf("\n\n");
	showASCII(newStr);
	//transferOver(newStr, arry, lastArrayNum);
	free(newStr);
}

char * untilEnd(char * content, int * position, int length)
{
	int i = *position;
	int j = 0;
	char * newStr = (char *)malloc(1+200*(sizeof(char)));
	emptyBuffer(newStr, 200);
	while(i < (length-1))
	{
		printf("\nThe current character at %d is %c", i, content[i]);
		if(j < 200)
		{
			newStr[j] = content[i];
			j++;
		}
		i++;
	}
	return newStr;
}

void transferOver(char * str, char ** arry, int arrayNum)
{
	printf("\nStart Transfer Over\n");
	printf("string is: %s\n", str);
	if(str == NULL)
	{
		return;
	}
	if(arry[arrayNum] == NULL)
	{
		printf("error with finding space for last string\n");
		arry[arrayNum] = (char *)malloc(1+200*(sizeof(char)));
	}
	int co = strlen(str);
	int i = 0;
	while(i < (co - 1))
	{
		arry[arrayNum][i] = str[i];
		printf("%c", str[i]);
		fflush(stdout);
		i++;
	}
	printf("\nEnd Transfer Over\n");
}

char * nextFileName(char ** files, int * currentFileNum, int fileNums)
{
	char * fil;
	if(*currentFileNum > fileNums)
	{
		perror("Reached end of files\n");
		exit(1);
	}
	else
	{
		fil = (char *)malloc(1 + 20*(sizeof(char)));
		strcpy(fil, files[*currentFileNum]);
	}	
	return fil;
}
