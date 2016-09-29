/* playfairHelper.c */
#include <string.h>
#include "playfairHelper.h"
#include "qgr.h"

/* DEFINES */

/* G VARS */
extern float quadgram_table[];


/*
	Deciphers the ciphertext using the key
	by reversing the Playfair cipher
*/
void *decipher(char *key, char *text, char *cracked)
{
	int i = 0;
	int d1, d2;
	int row1, row2;
	int col1, col2;

	do
	{
		// search through the key for indices of the digram (i, i+1)
		d1 = (int)(strchr(key, text[i]) - key);
		d2 = (int)(strchr(key, text[i + 1]) - key);
		// turn the key into a "5 x 5 matrix" according to the indices
		// divide by 5 to get the row value (rounds to correct row)
		// mod 5 to get the column value (remainder is correct column)
		row1 = d1 / 5;
		row2 = d2 / 5;
		col1 = d1 % 5;
		col2 = d2 % 5;

		// effectively, this is what we have created:
		// (note: letters may not be necessarily in this order)

		/*   c0	 c1	 c2	 c3	 c4
			_____________________
			|   |   |   |   |   |
			| a | b | c | d | e |  r0
			|___|___|___|___|___|
			|   |   |   |   |   |
			| f | g | h | i | k |  r1
			|___|___|___|___|___|
			|   |   |   |   |   |
			| l | m | n | o | p |  r2
			|___|___|___|___|___|
			|   |   |   |   |   |
			| q | r | s | t | u |  r3
			|___|___|___|___|___|
			|   |   |   |   |   |
			| v | w | x | y | z |  r4
			|___|___|___|___|___|
		*/

		// time for the translation...
		// if we are on the same row, we decipher by shifting 1 char left
		if (row1 == row2)
		{
			cracked[i] = key[d1 - 1];
			cracked[i + 1] = key[d2 - 1];
			// but if we are at the beginning of the row,
			// we must swap with the last element
			// check & shift accordingly for both digram letters
			if (col1 == 0) {
				cracked[i] = key[d1 + 4];
				cracked[i + 1] = key[d2 - 1];
			} else if (col2 == 0) {
				cracked[i] = key[d1 - 1];
				cracked[i + 1] = key[d2 + 4];
			}

		// if we are on the same column, we decipher by shifting 1 char up
		} else if (col1 == col2)
		{
			cracked[i] = key[d1 - 5];
			cracked[i + 1] = key[d2 - 5];
			// but if we are at the beginning of the column,
			// we must swap with the bottom element in the column
			// check & shift accordingly for both digram letters
			if (row1 == 0) {
				cracked[i] = key[d1 + 20];
				cracked[i + 1] = key[d2 - 5];
			} else if (row2 == 0) {
				cracked[i] = key[d1 - 5];
				cracked[i + 1] = key[d2 + 20];
			}

		// lastly, we have the rectangle to reverse
		// find the opposite row of i by multiplying by total # of rows,
		// find the column by then adding the key index value
		} else {
			cracked[i] = key[5 * row1 + col2];
			cracked[i + 1] = key[5 * row2 + col1];
		}

		// iterate per digram
		i += 2;

	} while (i < LENGTH);

	// insert a null so we know where to stop
	cracked[i] = '\0';
}


/*
	Calculates the fitness score of quadgrams in the text,
	the quadgram score values in the lookup table were
	referenced from http://practicalcryptography.com
*/
float score(char *text)
{
	int i = 0;
	char quadgram[4];
	float score = 0;

	// we iterate through quadgrams in the text
	// then we assign the score based on the indices in the table
    do {
    	quadgram[0] = text[i] - 'A';
    	quadgram[1] = text[i + 1] - 'A';
    	quadgram[2] = text[i + 2] - 'A';
        quadgram[3] = text[i + 3] - 'A';
        score += quadgram_table[17576 * quadgram[0] + 676 * quadgram[1] + 26 * quadgram[2] + quadgram[3]];
        i++;
    } while (i < LENGTH - 3);

    return score;
}
