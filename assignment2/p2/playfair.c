#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "playfairHelper.h"

/* DEFINES */
#define CIPHERFILE  "cipher2.txt"
#define TRUE		1
#define FALSE		0
#define HEATCHECK	-15000.00

/* FUNCTION HEADERS */
static char* readCipherFile(char *buf);
static char* getShuffledKey(char *key);


/* START HERE */
int main(int argc, char *argv[]) {

	/* 75% HILL-CLIMBING METHOD, 25% HUMAN GUESSING */

	// open ciphertext file, copy into new array
	// malloc some other large arrays to Playfair with
	// fetch the input key. must be in capital letters (and no J's)
	char *buf = 0;
	char *cipher = readCipherFile(buf);
	char *cracked = malloc(sizeof(char) * (LENGTH + 1));
	char *crackedTemp = malloc(sizeof(char) * (LENGTH + 1));
	free(buf);

	//char key[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; (starting point)
	//char key[] = "WAQSIRYLPGENXCVBHOUFKMDTZ"; good guess
	//char key[] = "GRWAQSILPEFYNXCVBHOZUDMKT"; good guess
	//char key[] = "RWAQSIEFYNXCPVBHOUMDKLZGT"; good guess
	//char key[] = "TRWALQIEFYOPSNXCVBHUMDKZG"; good guess
	//char key[] = "TRQWALIEFYOPSNXCVBHUMDKZG"; SAVING THIS REALLY GOOD GUESS
	char key[] = "TRQWALIFYEOPSXNCVBHUMDKZG"; // last guess! best guess :)
	float formerScore, currentScore;
	int win = FALSE;

	// STEP 0a: use the ciphertext as a baseline to doublecheck
	// STEP 0b: score the ciphertext
	// STEP 0c: decipher using the guessed key
	// STEP 0d: score the new deciphered text
	printf("\nCiphertext;; \n%s\n\n", cipher);
	currentScore = score(cipher);
	printf("Ciphertext score;; %2f\n", currentScore);
	printf("\n! Trying manual key;; %s\n", key);
	decipher(key, cipher, cracked);
	printf("\nDeciphertext;; \n%s\n\n", cracked);
	formerScore = currentScore;
	currentScore = score(cracked);
	printf("Deciphertext score;; %2f\n", currentScore);

	// If we pass the heat check then we probably solved the cipher
	if (currentScore > HEATCHECK) {
		printf("Manual key score %2f passes the heat check!\n\n", currentScore);
		return 0;
	}

	// Otherwise iterate the fun part
	while (win == FALSE)
	{
		// STEP 1a: use the new key as a guess
		// STEP 1b: next, decipher the ciphertext using this key
		// STEP 1c: score the new "deciphered" text with this key, compare them
		//			if the old score is better, shuffle the new key
		getShuffledKey(key);
		printf("\n! Trying new key;; %s\n", key);
		decipher(key, cracked, crackedTemp);
		printf("\nCrackedtext;; \n%s\n\n", crackedTemp);
		formerScore = currentScore;
		currentScore = score(crackedTemp);
		printf("Crackedtext score;; %2f\n", currentScore);

		// C is awesome, computes shit too fast,
		// Us humans can't keep up with technology ohhh yeah
		sleep(1);

		// STEP 2a) If we win substantially, stop the program and try this key manually
		if (currentScore > formerScore) {
			printf("=== %2f beats %2f! ===\n\n", currentScore, formerScore);
			win = TRUE;

		// STEP 2b) If we lose, decipher the text using the shuffled key and try again
		} else {
			printf("=== %2f wins over %2f... ===\n\n", formerScore, currentScore);
		}
	}
		
	free(cracked);
	free(crackedTemp);

	return 0;
}


/*
	Open ciphertext from file since it is freakin huge
*/
static char* readCipherFile(char *buf)
{
	long len;
	FILE *cipherfile = fopen(CIPHERFILE, "rb");
	if (cipherfile)
	{
		fseek(cipherfile, 0, SEEK_END);
		len = ftell(cipherfile);
		fseek(cipherfile, 0, SEEK_SET);
		buf = malloc(len);

		if (buf) { fread(buf, 1, len, cipherfile); }
		fclose(cipherfile);
	} else { 
		printf("Cannot open cipherfile.\n");
	}
	return buf;
}

/*
	Fisher-Yates key shuffle
	https://en.wikipedia.org/wiki/Fisher-Yates_shuffle#The_modern_algorithm
*/
static char* getShuffledKey( char *key )
{
	int i = 0;
	int s;
	char swap;

	printf("Old Key;; %s\n", key);
	do {
		// s = random int s.t. 0 <= j <= i
		s = rand() % (i + 1);
		// exchange positions of s and i
		swap = key[s];
		key[s] = key[i];
		key[i] = swap;
		i++;
	} while (i < 24);
	printf("New Key;; %s\n", key);

	return key;
}

