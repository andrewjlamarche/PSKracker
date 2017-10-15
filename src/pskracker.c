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
#include "att.h"
#include "xfinity.h"
#include "version.h"

char TARGET[9];
char MODE[4];

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

unsigned int hex_string_to_byte_array(char *in, uint8_t *out, const unsigned int n_len) {
	unsigned int o, i, j;
	unsigned int len = strlen(in);
	unsigned int b_len = n_len * 2 + n_len - 1;

	if (len != n_len * 2 && len != b_len)
		return 1;
	for (i = 0; i < n_len; i++) {
		o = 0;
		for (j = 0; j < 2; j++) {
			o <<= 4;
			if (*in >= 'A' && *in <= 'F')
				*in += 'a'-'A';
			if (*in >= '0' && *in <= '9')
				o += *in - '0';
			else
				if (*in >= 'a' && *in <= 'f')
					o += *in - 'a' + 10;
				else
					return 1;
			in++;
		}
		*out++ = o;
		if (len == b_len) {
			if (*in == ':' || *in == '-' || *in == ' ' || *in == 0)
				in++;
			else
				return 1;
		}
	}
	return 0;
}

char *bruteforce(uint8_t *mac) {
	unsigned char pw[13]; // set size of password (12)
	int k;
	if (((strcmp(STR_TARGET_NVG589, TARGET)) == 0) && ((strcmp(STR_ENC_WPA, MODE)) == 0)) {
		for (k = 0; k < INT_MAX; k++) {
			genpass589(k, pw);
			printf("%s\n", pw);
		}
	} else if (((strcmp(STR_TARGET_NVG599, TARGET)) == 0) && ((strcmp(STR_ENC_WPA, MODE)) == 0)) {
		for (k = 0; k < INT_MAX; k++) {
			genpass599(k, pw);
			printf("%s\n", pw);
		}
	} else if ((((strcmp(STR_TARGET_DPC3939, TARGET)) == 0)
			|| ((strcmp(STR_TARGET_DPC3941, TARGET)) == 0)
			|| ((strcmp(STR_TARGET_TG1682G, TARGET)) == 0))
			&& ((strcmp(STR_ENC_WPA, MODE)) == 0)
			&& mac) {
		return genpassXHS(mac);
	} else {
		usage_err();
	}
}

int main(int argc, char **argv) {
	uint8_t mac[6], *ptrmac = 0;

	int opt = 0;
	int long_index = 0;
	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) {

		case 't': // target model number selection
			if ((strcmp(STR_TARGET_NVG589, optarg)) == 0
					|| (strcmp(STR_TARGET_NVG599, optarg)) == 0
					|| (strcmp(STR_TARGET_SMCD3GNV, optarg)) == 0
					|| (strcmp(STR_TARGET_DPC3939, optarg)) == 0
					|| (strcmp(STR_TARGET_DPC3941, optarg)) == 0
					|| (strcmp(STR_TARGET_TG1682G, optarg)) == 0) {
				strcpy(TARGET, optarg);
			} else {
				usage_err();
			}
			break;

		case 'e': // security/encryption mode selection
			if ((strcmp(STR_ENC_WPA, optarg)) == 0
					|| (strcmp(STR_ENC_WPS, optarg)) == 0) {
				strcpy(MODE, optarg);
			} else
				usage_err();
			break;

		case 'm': // mac address selection
			if (hex_string_to_byte_array(optarg, mac, BSSID_LEN)) {
				printf("Invalid MAC Address\n");
				exit(2);
			}
			ptrmac = mac;
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
	char *psk = bruteforce(ptrmac);
	if (psk) {
		printf("PSK is \'%s\'\n", psk);
		free(psk);
	}
	return 0;
}
