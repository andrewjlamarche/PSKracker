#!/bin/bash

mkdir lists

# (?d)-word-?d
awk '{print "-" $0 "-"}' altice-optimum.txt > tmp.txt
for i in $(cat tmp.txt) ; do seq -f $i%02.0f 0 99 ; done > lists/2-altice-optimum.txt
for i in $(cat tmp.txt) ; do seq -f $i%03.0f 0 999 ; done > lists/3-altice-optimum.txt
for i in $(cat tmp.txt) ; do seq -f $i%04.0f 0 9999 ; done > lists/4-altice-optimum.txt
rm tmp.txt

# word-?d-word
awk '{print $0 "-"}' altice-optimum.txt > tmp.txt
dash="-"
for i in $(cat tmp.txt) ; do seq -f $i%02.0f$dash 0 99 ; done > lists/altice-optimum-2.txt
for i in $(cat tmp.txt) ; do seq -f $i%03.0f$dash 0 999 ; done > lists/altice-optimum-3.txt
for i in $(cat tmp.txt) ; do seq -f $i%04.0f$dash 0 9999 ; done > lists/altice-optimum-4.txt
rm tmp.txt
