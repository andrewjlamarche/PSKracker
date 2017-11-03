/*
 * Thank you to mrfancypants for research and preliminary Python code for ATTXXXXXXX networks.
 */

#include <stdint.h>

#define ATT_NVG5XX_PSK_LEN 13

void genpass589(uint32_t x, unsigned char *psk) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	int i;

	uint64_t one = x * 465661287.5245797; // thank you mrfancypants for finding this number
	uint64_t two = one;
	psk[ATT_NVG5XX_PSK_LEN - 1] = 0;

	for (i = 0; i < 6; i++) { // select character from the charset at given position
		int key1 = CHARSET[two % 37];
		two /= 37;
		int key2 = 50 + (two % 8);
		two /= 37;
		psk[(10 - (i * 2)) + 1] = key1;
		psk[(10 - (i * 2))] = key2;
	}
}

void genpass599(uint32_t x, unsigned char *psk) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	int i;

	uint64_t one = (double) (x * ((1l << 32) + 2));
	psk[ATT_NVG5XX_PSK_LEN -1] = 0;

	for (i = 1; i < ATT_NVG5XX_PSK_LEN; i++, one /= 37) {
		psk[ATT_NVG5XX_PSK_LEN - i - 1] = CHARSET[one % 37];
	}
}

// nvg599 password algorithm
/*void genpass599(unsigned x, unsigned char *buf) {
   static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
   buf[12] = 0; // create buffer for password

   fnn = (double) (x * ((1l << 32) + 2));
   for (i = 1; i < PW_LENGTH; i++, fnn /= 37) {
   buf[PW_LENGTH - i - 1] = CHARSET[fnn % 37];
   }
   }*/
