/*
 * PSKracker: WPA/WPA2/WPS default key/pin generator written in C.
 *
 * Copyright (c) 2017, soxrok2212 <soxrok2212@gmail.com>
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
