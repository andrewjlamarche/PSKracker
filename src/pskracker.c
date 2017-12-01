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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <getopt.h>

#include "pskracker.h"
#include "version.h"

#include "att.c"
#include "xfinity.c"
#include "tools.c"

static const char *option_string = "t:b:s:Wh";
static const struct option long_options[] = {
		{ "target",     required_argument,	0, 't' },
		{ "bssid", 		required_argument,	0, 'b' },
		{ "wps", 		no_argument,		0, 'W' },
		{ "serial",     required_argument,	0, 's' },
		{ "help",       no_argument,		0, 'h' },
		{ 0,            0,					0,  0  }
};

void usage_err() {
	printf(
		"\n"
		"PSKracker WiFi Security Auditing Toolkit\n"
		"Copyright (c) 2017, soxrok2212 <soxrok2212@gmail.com>\n"
		"\n"
		"Usage: pskracker <arguments>\n"
		"\n"
		"Required Arguments:\n"
		"\n"
		"   -t, --target		: Target model number\n"
		"\n"
		"Optional Arguments:\n"
		"\n"
		"	-b, --bssid			: BSSID of target\n"
		"	-W, --wps			: Output possible WPS pin(s) only\n"
		"	-s, --serial		: Serial number\n"
		"	-h, --help			: Display help/usage\n"
		"\n"
		"Example:\n"
		"\n"
		"	pskracker -t <target model> -b <bssid> -s <serial number>\n"
		"\n"
	);
	exit(1);
}

void bruteforce(char *target, uint8_t mode, uint8_t *pMac) {
	/* WPA */
	if(mode == 0) {
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
				printf("PSK: %s\n",genpassXHS(pMac));
			}
			else {
				printf("Specify target bssid: -b <bssid>\n");
				exit(1);
			}
		}
	}
	/* WPS */
	else if (mode == 1){
		// nothing implemented yet
	}
	/* Neither, exit */
	else {
		usage_err();
	}
}

int main(int argc, char **argv) {
	uint8_t mac[6], mode = 255, *pMac = 0;
	char *target;

	int opt = 0;
	int long_index = 0;
	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) { // default setting for variable options is 0

		case 't':
			mode = 0; // set WPA (bruteforce())
			target = optarg;
			break;

		case 'b':
			if (hex_string_to_byte_array(optarg, mac, BSSID_LEN)) {
				printf("Invalid MAC Address\n");
				exit(2);
			}
			pMac = mac;
			break;

		case 'W':
			mode = 1; // set WPS (bruteforce())
			break;

		case 's':
			break;

		case 'h': // display usage menu
			usage_err();
			break;

		default:
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	bruteforce(target, mode, pMac);
	return 0;
}
