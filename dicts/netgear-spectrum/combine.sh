first=$(cat words.txt)
second=$(cat words.txt)

while read one
do
	while read two
	do
		if [[ $one != $two ]]
		then
			echo $one$two >> netgear-spectrum.txt
		fi
	done <<<"$second"
done <<<"$first"
