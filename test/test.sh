#!/bin/sh

script_start=`date +%s%N`

python extract_snippets.py

if [ -z "$CXX" ];
then
    CXX=g++
fi

red=`tput setaf 1`
green=`tput setaf 2`
no_color=`tput sgr0`

total=0
success=0

for cppfile in *.cpp;
do
    echo -n "Running $cppfile - "

    total=$((total + 1))
    start=`date +%s%N`

    $CXX -std=c++11 $cppfile -o $cppfile.out 
    COMPILATION=$?
    if [ $COMPILATION -eq 0 ];
    then
        ./$cppfile.out
        test_success=$?
        if [ $test_success -eq 0 ];
        then
            success=$((success + 1))
            end=`date +%s%N`
            echo ${green}Passed in $(((end - $start)/1000000)) ms${no_color}
        else
            echo ${red}"Test $cppfile failed!"${no_color}
        fi

        rm $cppfile.out
    else
        echo ${red}"Error while compiling $cppfile!"${no_color}
    fi
done

script_end=`date +%s%N`
time_taken=$(echo "$script_start $script_end" | awk '{printf "%.2f\n", ($2-$1)/1000000000.0}')

if [ $success -eq $total ];
then
    echo ${green}"\n$success PASSED in $time_taken seconds${no_color}"
    exit 0
else
    echo ${red}"\n$(($total - $success)) FAILED, ${green}$success PASSED${red} in $time_taken seconds${no_color}"
    exit 1
fi
