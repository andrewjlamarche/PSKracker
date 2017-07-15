# Overview

Various ATTxxxxxxx wireless gateways, including Arris NVG589 and NVG599, are vulnerable to a default password generator. This tool generates all 2.1 billion possibilities for these models.

# Requirements

GCC compiler

# Setup

**Download**

`git clone https://github.com/soxrok2212/PSKracker`

**Build**

```
cd PSKracker/att
gcc att.c -o att
```

# Usage

```
Usage: att <arguments>

Required Arguments:

	-m, --mode        : Target model nvg89 or nvg599
```

# Usage Example

```
att -m nvg589
```

# Supported OS

This code should compile on most *nix and Widnows systems.

# Acknowledgements

Thank you to mrfancypants for sourcing the original Python code and discovery of the algorithm. https://hashcat.net/forum/thread-6170-post-35595.html#pid35595