#include <stdio.h>

#define CIPHERFILE 	"cipher.txt"

int main(int argc, char *argv[]) {

	FILE *cipher;
	int c;

	cipher = fopen(CIPHERFILE, "r");
	while(1) {
		c = fgetc(cipher);
		if (feof(cipher)) {
			break; }

		if (c == 'A') { printf("%c", 'T'); }
		else if (c == 'B') { printf("%c", 'G'); }
		else if (c == 'C') { printf("%c", 'Q'); }
		else if (c == 'D') { printf("%c", 'B'); }
		else if (c == 'E') { printf("%c", 'C'); }
		else if (c == 'F') { printf("%c", 'W'); }
		else if (c == 'G') { printf("%c", 'J'); }
		else if (c == 'H') { printf("%c", 'K'); }
		else if (c == 'I') { printf("%c", 'A'); }
		else if (c == 'J') { printf("%c", 'F'); }
		else if (c == 'K') { printf("%c", 'V'); }
		else if (c == 'L') { printf("%c", 'Y'); }
		else if (c == 'M') { printf("%c", 'L'); }
		else if (c == 'N') { printf("%c", 'R'); }
		else if (c == 'O') { printf("%c", 'I'); }
		else if (c == 'P') { printf("%c", 'O'); }
		else if (c == 'Q') { printf("%c", 'N'); }
		else if (c == 'R') { printf("%c", 'U'); }
		else if (c == 'S') { printf("%c", 'P'); }
		else if (c == 'T') { printf("%c", 'H'); }
		else if (c == 'U') { printf("%c", 'S'); }
		else if (c == 'V') { printf("%c", 'Z'); }
		else if (c == 'W') { printf("%c", 'M'); }
		else if (c == 'Y') { printf("%c", 'E'); }
		else if (c == 'X') { printf("%c", 'X'); }
		else if (c == 'Z') { printf("%c", 'D'); }

	}
	fclose(cipher);

	printf("\n");

	return 0;
}