# altice-optimum

## Background
Altice (or as I believe was previously Optimum) is an ISP serving some northeastern states uses a few different mutations for their WPA keygen. They are:

* word(-2-4) # altice-optimum.txt # mode 6
* word(-3-3) # altice-optimum.txt # mode 6
* word(-4-2) # altice-optimum.txt # mode 6
* (4)-word-2 # 2-altice-optimum.txt # mode 7
* (3)-word-3 # 3-altice-optimum.txt # mode 7
* (2)-word-4 # 4-altice-optimum.txt # mode 7
* (4-2-)word # altice-optimum.txt # mode 7
* (3-3-)word # altice-optimum.txt # mode 7
* (2-4-)word # altice-optimum.txt # mode 7
* word-2-(2) # altice-optimum-2.txt # mode 6
* word-2-(3) # altice-optimum-3.txt # mode 6
* word-2-(4) # altice-optimum-4.txt # mode 6

...where 2-4 are ?d?d, ?d?d?d and ?d?d?d?d respectively. The parts in () parenthesis are the hybrid part that hashcat generates. Due to the way hashcat's hybrid mode is implemented (and how GPUs spread work out across all the cores), it is not very efficient at "hybridizing" small lists with large masks, so the resulting speed may be excessively slow. A solution might be to use hashcat with --stdout and pipe into another hashcat session.

To generate the lists, just run the generate scripts. `generate.sh` creates lists from the expected keyspace.

Example scenarios:

To crack the password `emerald-20-8491`, the hashcat syntax might look something like `hashcat -m 22000 altice.22000 -a 6 alice-optimum.txt -1 - ?1?d?d?1?d?d?d?d`

To crack the password `103-emerald-328`, the hashcat syntax might look something like `hashcat -m 22000 altice.22000 -a 7 ?d?d?d 3-altice-optimum.txt`

To crack the password `4992-30-emerald`, the hashcat syntax might look something like `hashcat -m 22000 altice.22000 -a 7 -1 - ?d?d?d?d?1?d?d?1 altice-optimum.txt`

To crack the password `emerald-71-maroon`, the hashcat syntax might look something like `hashcat -m 22000 altice.22000 -a 1 altice-optimum-2.txt altice-optimum.txt`
