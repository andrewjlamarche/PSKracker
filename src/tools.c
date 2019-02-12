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

 /* MAC Address Parser */
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
