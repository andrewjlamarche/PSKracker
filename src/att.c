/*
 * PSKracker: WPA/WPA2/WPS default key/pin generator written in C.
 *
 * Copyright (c) 2017-2019, soxrok2212 <soxrok2212@gmail.com>
 * SPDX-License-Identifier: GPL-3.0+
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Thank you to mrfancypants for research and preliminary Python code for ATTXXXXXXX networks.
 */

#include <stdint.h>

#define ATT_NVG5XX_PSK_LEN 13

uint64_t do_rounding(uint64_t x) {
	int idx = 63 - __builtin_clzll(x);
	if (idx > 52) {
		x >>= idx - 52 - 1;
		x = (x >> 1) + (x & 1);
		x <<= idx - 52;
	}
	return x;
}

void genpass589(uint32_t x, unsigned char *psk) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	int i;

	uint64_t y = x;
	y = y + (y << 31);
	y = do_rounding(y);
	y = (uint64_t) ( ((__int128)y * (__int128)1000000000000000000ull) >> 61 ); 
	y = do_rounding(y);
	uint64_t one = y>> 1;
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

	uint64_t key = x;
	key <<= 32;
	key += x << 1;
	key = do_rounding(key);
	psk[ATT_NVG5XX_PSK_LEN -1] = 0;

	for (i = 1; i < ATT_NVG5XX_PSK_LEN; i++, key /= 37) {
		psk[ATT_NVG5XX_PSK_LEN-1 - i] = CHARSET[key % 37];
	}
}
