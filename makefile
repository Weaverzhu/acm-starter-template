main: main.cpp
	mkdir -p ./bin
	g++ main.cpp -o ./bin/main -std=c++11 -fsanitize=address -Wall
mainO2: main.cpp
	mkdir -p ./bin
	g++ main.cpp -o ./bin/main -std=c++11 -fsanitize=address -mainO2 -Wall
clean:
	rm -f ./bin/*
	rm -f ./output/*
gen: ./judger/generator.cpp
	g++ ./judger/generator.cpp -o ./bin/gen -O2 -std=c++11 -fsanitize=address
std: ./judger/std.cpp
	g++ ./judger/std.cpp -o ./bin/gen -O2 -std=c++11 -fsanitize=address
