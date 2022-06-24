# Overview [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/soxrok2212/PSKracker/blob/master/LICENSE)

**PSKracker** is a collection of WPA/WPA2/WPS default algorithms/password generators/pingens written in C.

# Requirements

C compiler

# Setup

**Download**

`git clone https://github.com/soxrok2212/pskracker`

**Build**

```bash
cd pskracker
make
```

**Install**

`sudo make install`

# Usage

```
Usage: pskracker <arguments>

Required Arguments:
	
	-t, --target	: Target model number

Optional Arguments:
	-b, --bssid	: BSSID of target
	-W, --wps	: Output possible WPS pin(s) only
	-G, --guest	: Output possible guest WPA key(s) only
	-s, --serial	: Serial number
	-f, --force	: Force full output
	-h, --help	: Display help/usage
```

# Usage Example

`pskracker -t <target> -s <serial number> -b <bssid>`
* More detailed usage examples and supported models can be found on the [wiki](https://github.com/soxrok2212/PSKracker/wiki/Attack-Types-and-Supported-Models).

# Targeted Example

```
$ pskracker -t nvg599
  ...
  aaae7uas5wrj
  aaae7v3qrvbu
  ...
```

```
$ pskracker -t dpc3941 -b 112233445566
  PSK: 5756C3915966657704
```

# Supported OS

PSKracker should compile on macOS and most Linux system.  
It has been tested on macOS Monterey 12.4, Ubuntu 16, Ubuntu 18, Ubuntu 20, Ubuntu 22 and ArchLinux. 
Embedded systems and Windows are not supported, though may still work. PSKracker is intended to be run on true pentesting environments (Desktop/Workstation/Laptop). Some psk generators (not bruteforce) are still suitable for embedded systems, but I will not provide support due to the nature of the tool.

Some 32-bit systems (Raspberry Pi with Raspbian) do not support 128-bit integers that are currently used for the Arris NVG589 algorithm, and therefore are not supported by PSKracker at this time. You may have luck with a 64-bit OS running on a recent revision, but this has not been tested.

# Acknowledgements

Thank you to `rofl0r`, `wiire` and `datahead` for my first C endeavors!  
Thank you to `AAnarchYY` for research dedication and motivation.

# Disclaimer

This project is intended for testing and securing your own networks or networks you have permission to audit. This is not intended to be used maliciously.

In publishing these documents and source code, I (and other developers/contributors) take no responsibility for your actions. What you do with everything in this repository, as well as any information online, is your responsibility. Use this repo wisely. In light of anything I may have failed to mention regarding laws to any country or civilized region, this does not grant the excuse to include the developers or contributors in any way in your legal statements or prosecutor. Thank you.

# References

### Xfinity Home Security Network Algorithm
* [CVE-2017-9476](https://nvd.nist.gov/vuln/detail/CVE-2017-9476)
* [Bastille DEFCON 25 Whitepaper](https://github.com/BastilleResearch/CableTap/blob/master/doc/pdf/DEFCON-25-Marc-Newlin-CableTap-White-Paper.pdf)

### ATT NVG589 and NVG599 Algorithm
* [Hashcat Forum (mrfancypants)](https://hashcat.net/forum/thread-6170-post-35739.html#pid35739)

### Belkin
* [CVE-2012-4366](https://nvd.nist.gov/vuln/detail/CVE-2012-4366)
* nvram.c from GPL source code center

### Altice-Optimum
* [Hashkiller.io Forum](https://forum.hashkiller.io)
* [@Dawbs](https://forum.hashkiller.io/index.php?members/dawbs.1022870/)
* [@petrovivo1234](https://forum.hashkiller.io/index.php?members/petrovivo1234.1024253/)
* [@AimanRulez](https://forum.hashkiller.io/index.php?members/aimanrulez.1029467/)
