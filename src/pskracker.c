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

static const char *option_string = "t:e:s:m:h";
static const struct option long_options[] = {
		{ "target",     required_argument, 0, 't' },
		{ "encryption", required_argument, 0, 'e' },
		{ "serial",     required_argument, 0, 's' },
		{ "mac",        required_argument, 0, 'm' },
		{ "help",       no_argument,       0, 'h' },
		{ 0,            0,                 0,  0  }
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
		"    -t, --target       : Target model number\n"
		"    -e, --encryption   : Security/encryption type\n"
		"\n"
		"Optional Arguments:\n"
		"\n"
		"    -s, --serial       : Serial number\n"
		"    -m, --mac          : Mac address\n"
		"\n"
		"Example:\n"
		"\n"
		"    pskracker -t <target> -e <security/encryption mode> -s <serial number> -m <mac address>\n"
		"\n"
	);
	exit(1);
}

// target selection
enum model {nvg589 = 0x00, nvg599 = 0x01, dpc3939 = 0x02, dpc3941 = 0x03, tg1682g = 0x04, ENDMODEL = END};
enum encryption {wpa = 0x00, wpa2 = 0x01, wps = 0x02, ENDENC = 0x03};

enum model getModel(char *inModel) {
	static const char *models[] = {"nvg589", "nvg599", "dpc3939", "dpc3941", "tg1682g"};
	uint8_t i;
	for(i = 0; i < ENDMODEL; ++i) {
		if(!strcmp(models[i], inModel)) {
			return i;
		}
	}
	return ENDMODEL;
}

enum encryption getEncryption(char *inEnc) {
	static const char *enctypes[] = {"wpa", "wpa2", "wps"};
	uint8_t i;
	for(i = 0; i < ENDENC; ++i) {
		if(!strcmp(enctypes[i], inEnc)) {
			return i;
		}
	}
	return ENDENC;
}

void bruteforce(uint8_t m, uint8_t e, uint8_t *mac) {

	if(m == 0) {
		int32_t i;
		unsigned char psk[ATT_NVG5XX_PSK_LEN];
		for (i = 0; i < INT_MAX; i++) {
			genpass589(i, psk);
			printf("%s\n", psk);
		}
	}
	else if(m == 1) {
		int32_t i;
		unsigned char psk[ATT_NVG5XX_PSK_LEN];
		for (i = 0; i < INT_MAX; i++) {
			genpass599(i, psk);
			printf("%s\n", psk);
		}
	}
	else if(m == 2 || m == 3 || m == 4) {
		if(mac == NULL) {
			printf("Invalid MAC address\n");
			exit(1);
		}
		printf("PSK: %s\n", genpassXHS(mac));
	}
}

int main(int argc, char **argv) {
	uint8_t mac[6], *pMac = 0;
	uint8_t model;
	uint8_t enc;

	int opt = 0;
	int long_index = 0;
	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) {

		case 't': // target model number selection
			model = (uint8_t) getModel(optarg);
			if(model == END) {
				usage_err();
			}
			break;

		case 'e': // security/encryption mode selection
			enc = (uint8_t) getEncryption(optarg);
			if(enc == 0x03) {
				usage_err();
			}
			break;

		case 'm': // mac address selection
			if (hex_string_to_byte_array(optarg, mac, BSSID_LEN)) {
				printf("Invalid MAC address\n");
				exit(2);
			}
			pMac = mac;
			break;

		case 'h': // display usage menu
			usage_err();
			break;

		default:
			usage_err();
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	bruteforce(model, enc, pMac);
	return 0;
}
