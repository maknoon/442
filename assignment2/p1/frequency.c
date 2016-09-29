#include <stdio.h>
#include <string.h>

#define CIPHERFILE  "cipher.txt"
#define TOTAL		462.0

int main(int argc, char *argv[]) {

	printf("\n");

	FILE *cipher;
	int l, c, count;
	char letter[26] = {'A','B','C','D','E','F','G','H','I','J',
	'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	for (l = 0; l < strlen(letter); l++)
	{
		cipher = fopen(CIPHERFILE, "r");
		count = 0;
		while(1) {
			c = fgetc(cipher);
			if (feof(cipher)) {
				break; }
			if (c == letter[l]) { count++; }
			//printf("%c", c);
		}
		fclose(cipher);
		printf("%c: %d (%.2f percent)\n", letter[l], count, count / TOTAL * 100.0);
	}
	printf("\n");

	return 0;
}
