# Overview

Comcast/Xfinity's SMC SMCD3GNV uses an insecure default WPS PIN generation algorithm. By converting the fourth octet of the MAC address and the last four characters of the SSID to decimal, we obtain the WPS PIN. This model is also vulnerable to [pixiewps](https://github.com/wiire/pixiewps). This may or may not work for other devices.

# Requirements

GCC compiler

# Setup

**Download**

`git clone https://github.com/soxrok2212/PSKracker`

**Build**

```
cd PSKracker/smc
gcc smcwps.c -o smcwps
```

# Usage

```
Usage: smcwps <arguments>

Required Arguments:

	-s, --ssid=<ssid>         SSID of the target AP
	-m, --mac=<mac>           BSSID of the target AP
```

# Usage Example

```
smcwps -s HOME-ABCD -m 001122334455
```

# Supported OS

This code should compile on most *nix and Widnows systems.

# Acknowledgements

Code written by:
`wiire`

Vulnerability found and small modifications to code by:
`soxrok2212`
