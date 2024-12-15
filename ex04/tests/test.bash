#!/bin/zsh

test_driver() {
	if [[ ! -z $MAIN ]]; then
		test_main
	fi
	if [[ ! -z $INVALIDS ]]; then
		test_invalids
	fi
}

test_main() {
	build &&
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
	test big_text "?" "kong" &&
	manual_test submatch_in_middle $'f\nrom' "to" $'q23fawgfwegwfrogw3323fffasdto' &&
	manual_test three_nl $'\n\n\n' ' ' $'ONE TWO THREE NEWLINES\nTO\nSPACE'
}

test_invalids() {
	build &&
	check_error big_text "non" "" 1 $'Wrong command line arguments count\nUsage: test file substring_to_be_replaced substring_to_replace' &&
	check_error big_tex "non" "1" 3 $'Can\'t open the file for reading' &&
	check_error readonly "readonly" "write" 4 $'Can\'t open the file for writing' &&
	check_error big_text "" "non" 7 $'The replacing substring can\'t be empty'
}

check_error() {
	echo "[INVALID TEST '$1' '$2' '$3' '$4' '$5']"
	local error
	error=$($VALGRIND ./../replace "$1" "$2" $3 2>&1)
	local code=$?
	local result
	if [[ $code -eq $4 && $error == $5 ]]; then
		echo OK
		result=0
	else
		echo "Yours: $code $error"
		echo "Expected: $4 $5"
		echo KO
		result=1
	fi
	return $result
}

manual_test() {
	echo "[TEST '$1' '$2' '$3']"
	$VALGRIND ./../replace "$1" "$2" "$3"
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
	(tmp=$(sed -e s/"$2"/"$3"/g "$1") && echo -n $tmp > "$1.sed.replace") &&
	$VALGRIND ./../replace "$1" "$2" "$3" &&
	diff "$1.replace" "$1.sed.replace"
	local output=$?
	if [[ output -eq 0 ]]; then
		rm "$1.sed.replace" "$1.replace"
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
	make -C .. fclean $target
	return $?
}

while [[ $# -gt 0 ]]; do
	case $1 in
		-v|--valgrind)
			if [[ $(uname -s) == "Linux" ]]; then
				VALGRIND="valgrind --error-exitcode=100 -q --leak-check=full --show-leak-kinds=all --track-origins=yes"
			fi
			shift
			;;
		-m|--main)
			MAIN=1
			shift
			;;
		-i|--invalids)
			INVALIDS=1
			shift
			;;
		*)
			echo "bad arguments"
			exit 1
			;;
	esac
done

if [[ -z $MAIN && -z $INVALIDS ]]; then
	MAIN=1
	INVALIDS=1
fi

test_driver
