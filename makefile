main: main.cpp
	g++ main.cpp -o ./main -std=c++11 -fsanitize=address -Wall
mainO2: main.cpp
	g++ main.cpp -o ./main -std=c++11 -fsanitize=address -mainO2 -Wall
clean:
	rm -f main
	rm -f gen
	rm -f std
	rm -f ./output/*
gen: ./judger/generator.cpp
	g++ ./judger/generator.cpp -o ./gen -O2 -std=c++11 -fsanitize=address
std: ./judger/std.cpp
	g++ ./judger/std.cpp -o ./gen -O2 -std=c++11 -fsanitize=address
