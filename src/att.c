/*
* Thank you to mrfancypants for research and preliminary Python code for ATTXXXXXXX networks.
*/

#define PW_LENGTH 13
#include <stdint.h>

#include "att.h"

int i;
uint64_t fen; // FiveEightNine
uint64_t fent; // FiveEightNine2
uint64_t fnn; // FiveNineNine

// nvg589 password algorithm, about 80% accurate
void genpass589(unsigned x, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	fen = x * 465661287.5245797; // thank you mrfancypants for finding this number
	fent = fen;
	buf[12] = 0; // create buffer for password

	/*
	 * This code finds the associated ascii value in the charset specified above
	 * If we knew the seed they were using, we wouldn't have to bruteforce every
	 * possibility
	 */
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[fent % 37];
		// calcualate one character of key
		fent /= 37;
		int k2 = 50 + (fent % 8);
		// calculate next character of key
		fent /= 37;
		buf[(10 - (i * 2)) + 1] = k1;
		buf[(10 - (i * 2)) + 0] = k2;
	}
}

// nvg599 password algorithm
void genpass599(unsigned x, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	buf[12] = 0; // create buffer for password

	/*
	* This code finds the associated ascii value in the charset specified above
	* If we knew the seed they were using, we wouldn't have to bruteforce every
	* possibility
	*/

	fnn = (double) (x * ((1l << 32) + 2));
	for (i = 1; i < PW_LENGTH; i++, fnn /= 37) {
		buf[PW_LENGTH - i - 1] = CHARSET[fnn % 37];
	}
}
