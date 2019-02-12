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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <getopt.h>

#include "pskracker.h"
#include "version.h"

#include "att.c"
#include "belkin.c"
#include "xfinity.c"
#include "tools.c"

static const char *option_string = "t:b:s:WGVfh";
static const struct option long_options[] = {
	{ "target",     required_argument,	0, 't' },
	{ "bssid", 	required_argument,	0, 'b' },
	{ "wps", 	no_argument,		0, 'W' },
	{ "guest", 	no_argument,		0, 'G' },
	{ "serial",     required_argument,	0, 's' },
	{ "force",	no_argument,		0, 'f' },
	{ "help",       no_argument,		0, 'h' },
	{ "version",	no_argument,		0, 'V' },
	{ 0, 0,	0, 0 }
};

void usage_err() {
	printf(
			"\n"
			" PSKracker %s WiFi Security Auditing Toolkit\n"
			" Copyright (c) 2017-2019, soxrok2212 <soxrok2212@gmail.com>\n"
			"\n"
			" Usage: pskracker <arguments>\n"
			"\n"
			" Required Arguments:\n"
			"\n"
			"	-t, --target	: Target model number\n"
			"\n"
			" Optional Arguments:\n"
			"\n"
			"	-b, --bssid	: BSSID of target\n"
			"	-W, --wps	: Output possible WPS pin(s) only\n"
			"	-G, --guest	: Output possible guest WPA key(s) only\n"
			"	-s, --serial	: Serial number\n"
			"	-f, --force	: Force full output\n"
			"	-h, --help	: Display help/usage\n"
			"\n"
			" Example:\n"
			"\n"
			" pskracker -t <target model> -b <bssid> -s <serial number>\n"
			"\n", LONG_VERSION
			);
	exit(1);
}

void specify_bssid(char *target) {
	printf("[!] Specify target bssid for target %s: -b <bssid>\n", target);
        exit(1);
}

void bruteforce(char *target, uint8_t mode, uint8_t guest, uint8_t force, uint8_t *pMac) {
	/* WPA */
	if(mode == 0) {
		if(force)  {
			/* All ATT */
			if(!strcmp(STR_ISP_ATT, target)) {
				int i;
				unsigned char psk[ATT_NVG5XX_PSK_LEN];
				for (i = 0; i < INT_MAX; i++) {
					genpass589(i, psk);
					printf("%s\n", psk);
					genpass599(i, psk);
					printf("%s\n", psk);
				}
			}
			/* All Belkin */
			else if(!strcmp(STR_MANUF_BELKIN, target)) {
				if(pMac != NULL) {	
					genpassBelkinOld(pMac);
				}
				else {
                                	specify_bssid(target);
				}
			}
			/* All Comcast/Xfinity */
			else if(!strcmp(STR_ISP_XFINITY, target) || !strcmp(STR_ISP_COMCAST, target)) {
				if(pMac != NULL) {
                                        printf("PSK: %s\n", genpassXHS(pMac));
                                }
                                else {
                                        specify_bssid(target);
                                }
			}
		}
		else if (guest) {
			exit(0);
		}
		else {
			/* ATT NVG589 */
			if(!strcmp(STR_MODEL_NVG589, target)) {
				int i;
				unsigned char psk[ATT_NVG5XX_PSK_LEN];
				for (i = 0; i < INT_MAX; i++) {
					genpass589(i, psk);
					printf("%s\n", psk);
				}
			}
			/* ATT NVG599 */
			else if(!strcmp(STR_MODEL_NVG599, target)) {
				int i;
				unsigned char psk[ATT_NVG5XX_PSK_LEN];
				for (i = 0; i < INT_MAX; i++) {
					genpass599(i, psk);
					printf("%s\n", psk);
				}
			}
			/* Comcast/Xfinity Home Security DPC3939, DPC3491, TG1682G */
			else if (!strcmp(STR_MODEL_DPC3939, target) || !strcmp(STR_MODEL_DPC3941, target) || !strcmp(STR_MODEL_TG1682G, target)) {
				if(pMac != NULL) {
					printf("PSK: %s\n", genpassXHS(pMac));
				}
				else {
					specify_bssid(target);
				}
			}
			/* All ATT */
			else if (!strcmp(STR_ISP_ATT, target)) {
				list_att_supported_models();
			}
			/* All Belkin */
                        else if(!strcmp(STR_MANUF_BELKIN, target)) {
                                list_belkin_supported_models();
                        }
			/* All Comcast/Xfintiy */
			else if (!strcmp(STR_ISP_XFINITY, target) || !strcmp(STR_ISP_COMCAST, target)) {
				list_xfintiy_supported_models();
			}
			else {
				printf("[!] WPA not supported for target %s\n", target);
			}
		}
	}
	/* WPS */
	else if (mode == 1){
		printf("[!] WPS not supported for target %s\n", target);
	}
	/* Neither, exit */
	else {
		usage_err();
	}
}

int main(int argc, char **argv) {
	uint8_t mac[6], mode = 255, guest = 0, force = 0, *pMac = 0;
	char *target;

	int opt = 0;
	int long_index = 0;
	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) {

			case 't':
				mode = 0; // set WPA (bruteforce())
				target = optarg;
				break;

			case 'b':
				if (hex_string_to_byte_array(optarg, mac, BSSID_LEN)) {
					printf("[!] Invalid MAC Address\n");
					exit(1);
				}
				pMac = mac;
				break;

			case 'W':
				mode = 1; // set WPS (bruteforce())
				break;
			case 'G':
				guest = 1; // set guest WPA key
				break;
			case 's':
				break;
			case 'f':
				force = 1;
				break;
			case 'h': // display usage menu
				usage_err();
				break;

			case 'V': // display version
				if(argc > 2) {
					printf("[!] Bad use of argument --version (-V)\n");
					exit(1);
				} 
				else {
					printf("PSKracker %s\n", LONG_VERSION);
					exit(0);
				}
				break;
			default:
				break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	bruteforce(target, mode, guest, force, pMac);
	return 0;
}
