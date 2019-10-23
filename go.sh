#!/bin/sh
compile() {
    # Usage: compile <source file> <obj pathname>
    if [ -f $2 ]; then
        a=`stat -c %Y $1`
        b=`stat -c %Y $2`

        if [ $a -gt $b ]; then
            echo compiling...
            g++ $1 -o $2 -std=c++11 -Wall
            suc=$?
            if [ $suc -eq 0 ]; then
                echo compile completed
            else
                echo Verdict: CE
                exit 0
            fi
        fi
    else
        echo compiling...
        g++ $1 -o $2 -std=c++11 -Wall
        suc=$?
        if [ $suc -eq 0 ]; then
            echo compile completed
        else
            echo Verdict: CE
            exit 0
        fi
    fi
}
run() {
    echo running $1
    if [ $# -gt 2 ]; then
        echo log: to files
        time $1 < $2 > $3
    elif [ $# -gt 1 ]; then
        echo ===========OUTPUT===========
        time $1 < $2
        echo ============END=============
    else
        echo ===========OUTPUT===========
        time $1
        echo ============END=============
    fi
}

echo ============================
echo .
echo . Weaver_zhu\'s ACM
echo . v1.0
echo . Powered by linux bash
echo .
echo 
if [ $# -eq 0 ]; then
    compile "./main.cpp" "./bin/main"
    run "./bin/main" "./input/in.txt"
elif [ $1 = "gen" ]; then
    echo $1
    echo log: generating data input
    compile "./judger/generator.cpp" "./bin/gen"
    run "./bin/gen" "./input/in.txt" "./input/in.txt"
elif [ $1 = "bin" ]; then
    g++ main.cpp -o bin/main -std=c++11 -Wall
elif [ $1 = "stdin" ]; then
    compile "./main.cpp" "./bin/main"
    run "./bin/main"
elif [ $1 = "judge" ]; then
    compile "./judger/generator.cpp" "./bin/gen"
    
    while true; do
        run "./bin/gen" "./input/in.txt" "./input/in.txt"
        compile "./main.cpp" "./bin/main"
        run "./bin/main" "./input/in.txt" "./output/out"
        compile "./judger/std.cpp" "./bin/std"
        run "./bin/std" "./input/in.txt" "./output/std"
        if diff "./output/out" "./output/std"; then
            echo Verdict: AC
        else
            echo Verdict: WA
            exit 0
        fi
    done
elif [ $1 = "newf" ]; then
    run "./bin/starter" "./judger/starter.txt" "./main.cpp"
elif [ $1 = "compile" ]; then
    compile "./main.cpp" "./bin/main"
elif [ $1 = "test" ]; then
    compile "./main.cpp" "./bin/main"
    run "./bin/main" "./input/in.txt" "./output/out"
    compile "./judger/std.cpp" "./bin/std"
    run "./bin/std" "./input/in.txt" "./output/std"
    if diff "./output/out" "./output/std"; then
        echo Verdict: AC
    else
        echo Verdict: WA
    fi
elif [ $1 = "python" ]; then
    python3 "./main.py" < "./input/in.txt"
else
    echo log: wrong input
fi