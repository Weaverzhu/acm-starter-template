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
        make ./bin/gen
        ./bin/gen > ./input/in.txt
    elif [ $1 = "compile" ]; then
        echo log: just compile main.cpp
        make ./bin/main
    elif [ $1 = "stdin" ]; then
        echo log: run from stdin
        make ./bin/main
        echo ------------- output --------------------
        ./bin/main
    elif [ $1 = "judge" ]; then
        echo 'log: judge with huge test cases'
        make ./bin/main
        make ./bin/std
        make ./bin/gen
        echo 'compile completed...'

        while true; do
            ./bin/gen > ./input/in.txt
            ./bin/main < ./input/in.txt > ./output/out.txt
            ./bin/std < ./input/in.txt > ./output/std.txt
            if diff "./output/out" "./output/std"; then
                echo Verdict: AC
            else
                echo Verdict: WA
                exit 0
            fi
        done
    elif [ $1 = "newf" ]; then
        echo log: reset main.cpp
        cat ./judger/starter.txt > ./bin/main.cpp
    elif [ $1 = "test" ]; then
        echo 'log: run a single test case'
        make ./bin/main
        make ./bin/std
        make ./bin/gen
        echo 'compile completed...'

        ./bin/gen > ./input/in.txt
        time ./bin/main < ./input/in.txt > ./output/out.txt
        time ./bin/std < ./input/in.txt > ./output/std.txt
        if diff "./output/out" "./output/std"; then
            echo Verdict: AC
        else
            echo Verdict: WA
        fi
    elif [ $1 = "python" ]; then
        python3 "./bin/main.py" < "./input/in.txt"
    else
        echo log: wrong input
    fi
elif [ $# -eq 0 ]; then
    make ./bin/main
    echo ------------- output --------------------
    time ./bin/main < ./input/in.txt
else
    echo 'Usage: bash go.sh <command>'
fi
