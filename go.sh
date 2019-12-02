#!/bash
set -o errexit
echo ============================
echo .
echo ". Weaver_zhus ACM"
echo ". v2.0"
echo ". Powered by linux bash & cmake"
echo .

if [ $# -eq 1 ]; then
    if [ $1 = "gen" ]; then
        echo log: generating input data
        make gen
        ./gen > ./input/in.txt
    elif [ $1 = "compile" ]; then
        echo log: just compile main.cpp
        make main
    elif [ $1 = "stdin" ]; then
        echo log: run from stdin
        make main
        echo ------------- output --------------------
        ./main
    elif [ $1 = "judge" ]; then
        echo 'log: judge with huge test cases'
        make main
        make std
        make gen
        echo 'compile completed...'

        while true; do
            ./gen > ./input/in.txt
            ./main < ./input/in.txt > ./output/out.txt
            ./std < ./input/in.txt > ./output/std.txt
            if diff "./output/out" "./output/std"; then
                echo Verdict: AC
            else
                echo Verdict: WA
                exit 0
            fi
        done
    elif [ $1 = "newf" ]; then
        echo log: reset main.cpp
        cat ./judger/starter.txt > main.cpp
    elif [ $1 = "test" ]; then
        echo 'log: run a single test case'
        make main
        make std
        make gen
        echo 'compile completed...'

        ./gen > ./input/in.txt
        time ./main < ./input/in.txt > ./output/out.txt
        time ./std < ./input/in.txt > ./output/std.txt
        if diff "./output/out" "./output/std"; then
            echo Verdict: AC
        else
            echo Verdict: WA
        fi
    elif [ $1 = "python" ]; then
        python3 "main.py" < "./input/in.txt"
    else
        echo log: wrong input
    fi
elif [ $# -eq 0 ]; then
    make main
    echo ------------- output --------------------
    time ./main < ./input/in.txt
else
    echo 'Usage: bash go.sh <command>'
fi
