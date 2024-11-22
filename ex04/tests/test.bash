#!/bin/bash

test_driver() {
	for i in {1..20}; do
		echo "STANDARD_BUFFER_SIZER = $i"
		test repeatitive_from from to $i
		test newlines $'\n' "" $i
		if [[ $? -ne 0 ]]; then
			break
		fi
	done
}

test() {
	echo "[TEST $1]"
	make BUFFER_SIZE=$4 -C .. fclean all
	sed -e "s/$2/$3/g" $1 > $1.sed.replace
	./../replace "$1" "$2" "$3"
	diff $1.replace $1.sed.replace
	output=$?
	if [[ output -eq 0 ]]; then
		rm $1.sed.replace $1.replace
		echo OK
	else
		echo KO
	fi
	return $output
}

test_driver
