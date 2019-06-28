#! /bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NORMAL='\033[0m'
#Set number of iterations
if [ $# -eq 0 ]
then
	ITER_NUM=20
else
	ITER_NUM=$1
fi
#Functions
{
	function error_output
	{
	 	echo -e "${RED}KO${NORMAL}\n"
		echo "Input: $1"
		echo "Entered commands:"
		echo -e "$2" | cat -e
		echo -e "Your output: $3" | cat -e
		echo -e "Must be: $4" | cat -e
	}
	function test_push_swap
	{
		let "max = $1 / 2"
		let "min = $max * (-1)"
		let "rest = $1 % 2"
		if [[ "$rest" -eq 0 ]]
		then
			let "max -= 1"
		fi
		echo -n "$1 random number test ($min..$max): "
		I=0
		SUM=0
		MAX=-1
		while [ $I -lt $ITER_NUM ]
		do
			ARG=`ruby -e "puts ($min..$max).to_a.shuffle.join(' ')"`
			OPERATIONS_COUNT=`./push_swap $ARG | wc -l`
			if [[ "$MAX" -lt "$OPERATIONS_COUNT" ]]
			then
				let "MAX = $OPERATIONS_COUNT"
			fi
			RESULT=`./push_swap $ARG | ./checker $ARG 2>&1`
			if [[ "$RESULT" != "OK" ]]
			then
				error_output "$ARG" "Run your push_swap whith arguments above" "$RES" "OK"
				return -1
			fi
			let "SUM += $OPERATIONS_COUNT"
			let "I += 1"
		done
		echo -e ${GREEN}OK${NORMAL}
		let "RES = $SUM / $ITER_NUM"
		COLOUR=$GREEN
		if [[ "$MAX" -gt "$2" ]]
		then
			COLOUR=$RED
		fi
		echo -e "Average numbers of operations: $RES (Max = ${COLOUR}$MAX${NORMAL})\n"
		return $RES
	}
	function test_errors1
	{
		RES=`echo pb | ./checker $1 2>&1`
		if [[ "$RES" != "Error" ]]
		then
			error_output "$1" "pb\n" "$RES" "Error"
			return -1
		fi
		return 0
	}
	function test_errors2
	{
		RES=`./checker`
		if [[ "$RES" != "" ]]
		then
			error_output "$1" "none" "$RES" ""
			return -1
		fi
		return 0
	}
	function test_errors3
	{
		RES=`echo "$1" | ./checker 9 1 5 2>&1`
		if [[ "$RES" != "Error" ]]
		then
			error_output "9 1 5 2" "$1" "$RES" "Error"
			return -1
		fi
		return 0
	}
	function test_false_input
	{
		RES=`echo -e "$1" | ./checker $2`
		if [[ "$RES" != "KO" ]]
		then
			error_output "$2" "$1" "$RES" "KO"
			return -1
		fi
		return 0
	}
	function test_right1
	{
		RES=`echo -n | ./checker $1 2>&1`
		if [[ "$RES" != "OK" ]]
		then
			error_output "$1" "none" "$RES" "OK"
			return -1
		fi
		return 0
	}
	function test_right2
	{
		RES=`echo -e "$1" | ./checker $2 2>&1`
		if [[ "$RES" != "OK" ]]
		then
			error_output "$2" "$1" "$RES" "OK"
			return -1
	 	fi
		return 0
	}
	function test_identity
	{
		RES=`./push_swap $1`
		if [[ "$RES" != "" ]]
		then
			error_output "$1" "none" "$RES" ""
			return -1
		fi
		return 0
	}
	function test_simple
	{
		COMMANDS=`ARG="$1"; ./push_swap $ARG`
		RES=`ARG="$1"; ./push_swap $ARG | ./checker $ARG 2>&1`
		if [[ "$RES" != "OK" ]]
		then
			echo -e "${RED}KO${NORMAL}\n"
			echo "Input: $1"
			echo "Push_swap output commands:"
			echo -e "$COMMANDS" | cat -e
			echo -e "Checker output: $3" | cat -e
			echo -e "Must be: $4" | cat -e
			return -1
		fi
		COM_COUNT=`ARG="$1"; ./push_swap $ARG | wc -l`
		if [[ "$COM_COUNT" -gt "$2" ]]
		then
			echo -e "${RED}KO${NORMAL}\n"
			echo "Input: $1"
			echo -n "Commands count:"
			echo -e "${RED}$COM_COUNT${NORMAL}"
			echo -e "Must be less then ${GREEN}$2${NORMAL}"
			return -1
		fi
		return 0
	}
}
#Middle version
{
	echo "Middle version."
	test_push_swap 500 1500
}
#Advansed version
{
	echo "Advanced version."
	test_push_swap 500 11500
}

exit 0
