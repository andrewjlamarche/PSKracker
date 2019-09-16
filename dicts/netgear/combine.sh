adjective=$(cat adjective_large.txt)
noun=$(cat noun_large.txt)

while read adj
do
	while read nn
	do
		echo $adj$nn >> netgear_large.txt
	done <<<"$noun"
done <<<"$adjective"
