#ifndef PSKRACKER_H_
#define PSKRACKER_H_

#include "att.h"

char usage[] =
	"\n"
	"PSKracker WiFi Security Auditing Toolkit\n"
	"Copyright (c) 2017, soxrok2212 <soxrok2212@gmail.com>\n"
	"\n"
	"Usage: pskracker <arguments>\n"
	"\n"
	"Required Arguments:\n"
	"\n"
	"	-t, --target		: Target model number\n"
	"	-w, --mode		: Security type\n"
	"\n"
	"Optional Arguments:\n"
	"\n"
	"	-s, --serial		: Serial number\n"
	"	-m, --maddr		: Mac address\n"
	"\n"
	"Example:\n"
	"\n"
	"	pskracker -t <target> -w <security mode> -s <serial number> -m <mac address>\n"
	"\n";

char usage_verbose[] =
	"\n"
	"PSKracker WiFi Security Auditing Toolkit\n"
	"Copyright (c) 2017, soxrok2212 <soxrok2212@gmail.com>\n"
	"\n"
	"Usage: pskracker <arguments>\n"
	"\n"
	"Required Arguments:\n"
	"\n"
	"	-t, --target		: Target model number\n"
	"	-w, --mode		: Security type\n"
	"\n"
	"Optional Arguments:\n"
	"\n"
	"	-s, --serial		: Serial number\n"
	"	-m, --maddr		: Mac address\n"
	"\n"
	"Example:\n"
	"\n"
<<<<<<< HEAD
	"	pskracker -t <target>  -w <security mode> -s <serial number> -m <mac address>\n"
=======
	"	pskracker -t <target> -w <security mode> -s <serial number> -m <mac address>\n"
>>>>>>> 7f58f05483f5fbf968da8aead3e24b059f87eec7
	"\n"
	"Supported attacks:\n"
	"\n"
	"|SSID		|Model Number	|target (-t)	|mode (-w)	|serial (-s)	|maddr (-m)\n"
	"+===============+===============+===============+===============+===============+==========\n"
	"|ATTXXXXXXX	|Arris NVG589	|nvg589		|wpa		|no		|no\n"
	"|ATTXXXXXXX	|Arris NVG599	|nvg599		|wpa		|no		|no\n"
	"|HOME-XXXX	|SMCD3GNV	|smcd3gnv	|wps		|no		|yes\n"
	"\n";

#endif /* PSKRACKER_H_ */
