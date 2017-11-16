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

#ifndef PSKRACKER_H_
#define PSKRACKER_H_

/* General */
#define BSSID_LEN 6

/* Encryption */
#define STR_ENC_WPA "wpa"
#define STR_ENC_WPS "wps"

/* Targets */
#define STR_TARGET_NVG589   "nvg589"
#define STR_TARGET_NVG599   "nvg599"
#define STR_TARGET_DPC3939  "dpc3939"
#define STR_TARGET_DPC3941  "dpc3941"
#define STR_TARGET_TG1682G  "tg1682g"

#endif /* PSKRACKER_H_ */
