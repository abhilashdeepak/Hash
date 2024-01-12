/*******************************************************************
* File Name          : Source.cpp
* Description        : This code is the implementation of hashing
*					   when running will get data from the console 
*					   
* Author             : Abhilash Deepak
* Date               : 12 December 2021
* Reference			 : https://www.tutorialspoint.com/data_structures_algorithms/hash_data_structure.htm
*********************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int putIntoHashTable(char* ptrInputData, unsigned int bufferLength);    // function to add to hash table
unsigned int getFromHashTable(char* ptrOutputData, unsigned int bufferLength);   // function to retrieve data from hash table

#define INPUT_BUFFER_SIZE         200             // local buffer used for adding data to the hash table (there is no reason in this assignment to change this value)

#define HASH_SIZE    10                          // size of hash table to be used (for testing I suggest making this number much lower)

struct myHashStruct {							// data structure used to keep track of hashed data
	char* ptrBuffer = NULL;                       // pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct myHashStruct* ptrNextHashData = NULL;  // pointer to next item in this hash bucket (or NULL if no more)
};

struct myHashStruct* myHash[HASH_SIZE];           // create an empty hash table structure (note this is basically an array of linked list heads)

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];

	// initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((myHash[i] = (struct myHashStruct*)calloc(1, sizeof(struct myHashStruct))) == NULL)
		{
			printf("calloc failed!\n");
			return(-1);
		}
	}

	// add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// get strings from the console and place in hash until nothing entered
		scanf_s("%199s", inputBuffer, INPUT_BUFFER_SIZE);
		inputBuffer[INPUT_BUFFER_SIZE - 1] = '\0';

		// stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
			break;

		if (putIntoHashTable(inputBuffer, strlen(inputBuffer)) == HASH_SIZE)
			printf("Error putting into hash table\n");
	}

	// check if data is in hash table
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%199s", inputBuffer, INPUT_BUFFER_SIZE);
		inputBuffer[INPUT_BUFFER_SIZE - 1] = '\0';

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
			break;

		if ((hashIndexNumber = getFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
	}

	return 0;
}

// FUNCTION      : myHashFunction
// DESCRIPTION   :
//   Calculate a hash value to use in storing the data into the hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//
// RETURNS       :
//   Hash value calculated ( HASH_SIZE on failure)

unsigned int myHashFunction(char* ptrInputBuffer) {

	// add code to create a hashed value here!!!
	unsigned int calculatedHashValue = 0;
	for (int i = 0; ptrInputBuffer[i]; i++)
		calculatedHashValue = calculatedHashValue + ptrInputBuffer[i];
	// make sure if hash value is larger than the table size, the value wraps
	return calculatedHashValue % HASH_SIZE;
}

// FUNCTION      : putIntoHashTable
// DESCRIPTION   :
//   Put the supplied data into a hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//   bufferLength   - how many characters are in the buffer being put into the hash table
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int putIntoHashTable(char* ptrInputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrInputData);

	// check if the value is in the hash

	// add code to put data into the hash table!!!

	bufferLength = 10;
	// check if the value is in the hash
	if (myHash[hashValue]->ptrBuffer == NULL) {
		char* Ptr_Value = (char*)malloc(INPUT_BUFFER_SIZE);
		if (Ptr_Value != NULL)
			strcpy_s(Ptr_Value, 10, ptrInputData);

		myHash[hashValue]->ptrBuffer = Ptr_Value;

		return hashValue;
	}
	else {
		return HASH_SIZE;
	}
	return hashValue;

}

// FUNCTION      : getFromHashTable
// DESCRIPTION   :
//   Read as much data as there is room for from the hash table
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( return HASH_SIZE value on failure)

unsigned int getFromHashTable(char* ptrOutputData, unsigned int bufferLength)
{
	//Compute the index by using the hash function
	unsigned int hashValue = myHashFunction(ptrOutputData);

	// check if the data is in the hash table here!!!
	if (ptrOutputData == NULL)
	{
		return HASH_SIZE;

	}
	else if (myHash[hashValue]->ptrBuffer == NULL)
	{
		return HASH_SIZE;

	}
	else if (strcmp(ptrOutputData, myHash[hashValue]->ptrBuffer) == 0)
	{
		return hashValue;

	}
	else
	{
		return HASH_SIZE;

	}

	return hashValue;

}