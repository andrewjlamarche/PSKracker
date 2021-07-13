#!/bin/bash

for i in $(cat 5.txt) ; do seq -f $i%04.0f 0 9999 ; done > 5num.txt
for i in $(cat 6.txt) ; do seq -f $i%04.0f 0 9999 ; done > 6num.txt
