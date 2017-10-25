# Overview

**PSKracker** is a collection of WPA/WPA2/WPS default algorithms/password generators/pingens written in C.

# Requirements

GCC compiler

# Setup

**Download**

`git clone https://github.com/soxrok2212/PSKracker`

**Build**

```bash
cd PSKracker/src
make
```

**Install**

`sudo make install`

# Usage

```
Usage: pskracker <arguments>

Required Arguments:

	-t, --target		: Target model number
	-e, --encryption	: Security/encryption type

Optional Arguments:
	-s, --serial		: Serial number
	-m, --mac		: Mac address

```

# Usage Example

`pskracker -t <target> -e <security/encryption type> -s <serial number> -m <mac address>`

# Supported OS

PSKracker should compile on macOS any Linux system.  
It has been tested on macOS Sierra 10.12 and Ubuntu 16.04.  
Embedded systems are not supported. PSKracker is intended to be run on true pentesting environments (Desktop/Workstation/Laptop).

# Acknowledgements

Thank you to `rofl0r`, `wiire` and `datahead` for my first C endeavors!  
Thank you to `AAnarchYY` for research dedication and motivation.

# Disclaimer

This project is intended for testing and securing your own networks or networks you have permission to audit. This is not intended to be used maliciously.

In publishing these documents and source code, I (and other developers/contributors) take no responsibility for your actions. What you do with everything in this repository, as well as any information online, is your responsibility. Use this repo wisely. In light of anything I may have failed to mention regarding laws to any country or civilized region, this does not grant the excuse to include the developers or contributors in any way to your legal statements or prosecutor. Thank you.

# References

### Xfinity Home Security Network Algorithm
* [CVE-2017-9476](https://nvd.nist.gov/vuln/detail/CVE-2017-9476)
* [Bastille DEFCON 25 Whitepaper](https://github.com/BastilleResearch/CableTap/blob/master/doc/pdf/DEFCON-25-Marc-Newlin-CableTap-White-Paper.pdf)

### ATT NVG589 and NVG599 Algorithm
* [Hashcat Forum (mrfancypants)](https://hashcat.net/forum/thread-6170-post-35739.html#pid35739)
