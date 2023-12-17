#!/bin/bash

if ! g++ @opcjeCpp tester.cpp ../kol.cpp -O3 -o kol.exe; then
    echo "Compilation error!"
    exit
fi

wrong_test=-1

for((i = 0; i < 1000; i++)) {
    
    
    if ! ./kol.exe $i; then
        wrong_test=$i
        break
    else
        echo "Test $i correct"
    fi
    
    echo ""
}

if [ $wrong_test -ne -1 ]; then
    echo "Wrong answer or runtime error on test $wrong_test"
else
    echo "Congrats! All tests passed :)"
fi
