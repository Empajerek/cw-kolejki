#!/bin/bash

if ! cd ../build/cmake ..; then
    echo "Compilation error!"
    exit
fi

executable = ../build/cw-kolejki.exe

wrong_test=-1

for((i = 0; i < 20; i++)) {
    echo "-------------------Test number $i-------------------"
    
    
    if ! ./kol $i; then
        wrong_test=$i
        break
    else
        echo "-------------------All correct!----------------------"
    fi
    
    echo ""
}

if [ $wrong_test -ne -1 ]; then
    echo "Wrong answer or runtime error on test $wrong_test"
else
    echo "Congrats! All tests passed :)"
fi
