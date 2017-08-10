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
	-m, --mode		: Security type
	
Optional Arguments:
	-s, --serial		: Serial number
	-m, --maddr		: Mac address

```

# Usage Example

`pskracker -t <target> -w <security mode> -s <serial number> -m <mac address>`

# Supported OS

PSKracker should compile on any *nix system

# Acknowledgements

Thank you to rofl0r and datahead for my first C endeavours!