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

PSKracker should compile on any *nix system

# Acknowledgements

Thank you to rofl0r and datahead for my first C endeavours!

# Disclaimer

In publishing these documents and source code, I (and other developers/contributors) take no responsibility for your actions. What you do with everything in this repository, as well as any information online, is your responsibility. Use this repo wisely. In light of anything I may have failed to mention regarding laws, this does not grant excuse to include the developers or contributors in any way to your legal statements. Thank you.
