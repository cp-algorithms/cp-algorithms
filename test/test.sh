#!/bin/bash

script_start=`date +%s%N`

python extract_snippets.py

if [ -z "$CXX" ];
then
    CXX=g++
fi

red=`tput setaf 1`
green=`tput setaf 2`
no_color=`tput sgr0`

success=0
failed_tests=()

for cppfile in *.cpp;
do
    echo -n "Running $cppfile - "
    start=`date +%s%N`

    $CXX -std=c++17 -fsanitize=undefined -fno-sanitize-recover $cppfile -o $cppfile.out 
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
            echo ${red}"$cppfile failed!"${no_color}
            failed_tests+=($cppfile)
        fi

        rm $cppfile.out
    else
        echo ${red}"Compilation error on $cppfile!"${no_color}
        failed_tests+=($cppfile)
    fi
done

script_end=`date +%s%N`
time_taken=$(echo "$script_start $script_end" | awk '{printf "%.2f\n", ($2-$1)/1000000000.0}')

if [ ${#failed_tests[@]} -eq 0 ];
then
    echo -e ${green}"\n$success PASSED in $time_taken seconds${no_color}"
    exit 0
else
    echo -e ${red}"\n${#failed_tests[@]} FAILED, ${green}$success PASSED${red} in $time_taken seconds${no_color}\n"
    for cppfile in "${failed_tests[@]}"
    do
        echo ${red}"$cppfile failed!"${no_color}
    done
    exit 1
fi
