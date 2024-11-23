#!/bin/bash

test_driver() {
	for i in {1..20}; do
		echo "STANDARD_BUFFER_SIZER = $i"
		build $i
		test repeatitive_from from to &&
		manual_test newlines $'\n' "" "hello" &&
		test repeatitive_from "fwef" "?" &&
		test big_text "Suspend" "MIMIMI Pappa burritto" &&
		test liquam_after_full "liquam" ';' &&
		test liquam_all_letters_in_but_not_at_start "liquam" ';' &&
		test liquam_first_letter "liquam" ';' &&
		test liquam_one_letter_out "liquam" ';' &&
		test big_text "liquam" $';' &&
		test big_text "non" "stop" &&
		test big_text "turpis" "mama" &&
		test big_text "oh-oh mamargarita" "" &&
		test big_text "?" "kong"
		if [[ $? -ne 0 ]]; then
			break
		fi
	done
}

test_invalids() {
	build 14
	echo $VALGRIND
}

manual_test() {
	echo "[TEST '$1' '$2' '$3']"
	$VALGRIND ./../replace $1 "$2" "$3"
	local result=$(cat $1.replace)
	[[ $result == "$4" ]]
	local output=$?
	if [[ output -eq 0 ]]; then
		echo OK
		rm $1.replace
	else
		echo KO
	fi
	return $output
}

test() {
	echo "[TEST '$1' '$2' '$3']"
	sed -e s/"$2"/"$3"/g $1 > $1.sed.replace
	$VALGRIND ./../replace "$1" "$2" "$3" &&
	diff $1.replace $1.sed.replace
	local output=$?
	if [[ output -eq 0 ]]; then
		rm $1.sed.replace $1.replace
		echo OK
	else
		echo KO
	fi
	return $output
}

build() {
	local target
	if [[ ! -z $VALGRIND ]]; then
		target=debug
	else
		target=all
	fi
	make BUFFER_SIZE=$1 -C .. fclean $target
}

if [[ $(uname -s) == "Linux" && $1 == "valgrind" ]]; then
	VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"
fi

test_driver
