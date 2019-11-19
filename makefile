./bin/main: main.cpp
	g++ main.cpp -o ./bin/main -std=c++11 -fsanitize=address -Wall
clean:
	rm -f main
	rm -f gen
	rm -f std
	rm -f ./output/*
./bin/gen: ./judger/generator.cpp
	g++ ./judger/generator.cpp -o ./bin/gen -O2 -std=c++11 -fsanitize=address
./bin/std: ./judger/std.cpp
	g++ ./judger/std.cpp -o ./bin/std -O2 -std=c++11 -fsanitize=address
