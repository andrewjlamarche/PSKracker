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

#ifndef PSKRACKER_H_
#define PSKRACKER_H_

/* General */
#define BSSID_LEN 6


/* TARGET */
#define STR_MODEL_NVG589 "nvg589"
#define STR_MODEL_NVG599 "nvg599"
//#define STR_MODEL_7550      "7550"
//#define STR_MODEL_5268AC  "5268ac"
#define STR_MODEL_DPC3939 "dpc3939"
#define STR_MODEL_DPC3941 "dpc3941"
#define STR_MODEL_TG1682G "tg1682g"

/* ISP */
#define STR_ISP_ATT "att"
#define STR_ISP_COMCAST "comcast"
#define STR_ISP_XFINITY "xfinity"

/* MANUFACTURER */
#define STR_MANUF_BELKIN "belkin"

void list_att_supported_models() {
	printf(
	"Supported AT&T targets:\n"
	"SSID pattern: ATTXXXXXXX\n"
	"[+] nvg589\n"
	"[+] nvg599\n"
//	"[+] 5268ac\n"
	);
}

void list_belkin_supported_models() {
	printf(
	"Supported Belkin targets:\n"
	"SSID pattern: Belkin.xxxx, belkin.xxxx, belkin.xxx\n"
	"[!] Not all are supported\n"
	"[+] F7K*\n"
	"[+] F9K*\n"
	);
}

void list_xfintiy_supported_models() {
	printf(
	"Supported Comcast/Xfinity targets:\n"
	"SSID pattern: HOME-XXXX, HOME-XXXX-2.4, HOME-XXXX-5\n"
	"[+] dpc3939\n"
	"[+] dpc3941\n"
	"[+] tg1682g\n"
	);
}

#endif /* PSKRACKER_H_ */
