all: main check

main: ./obj/main.o ./obj/help.o ./obj/ids.o ./obj/ida.o ./obj/cli.o
	g++ ./obj/main.o ./obj/help.o ./obj/ids.o ./obj/ida.o ./obj/cli.o -O3 -o main -std=c++17

check: ./obj/check.o ./obj/help.o
	g++ ./obj/check.o ./obj/help.o -O3 -o check -std=c++17

./obj/main.o: main.cpp ./lib/help.h ./lib/ids.h ./lib/ida.h ./lib/cli.h
	g++ main.cpp -O3 -c -std=c++17 -o ./obj/main.o

./obj/check.o: check.cpp ./lib/help.h
	g++ check.cpp -O3 -c -std=c++17 -o ./obj/check.o

./obj/help.o: ./lib/help.cpp ./lib/help.h
	g++ ./lib/help.cpp -O3 -c -std=c++17 -o ./obj/help.o

./obj/ids.o: ./lib/ids.cpp ./lib/ids.h ./lib/help.h
	g++ ./lib/ids.cpp -O3 -c -std=c++17 -o ./obj/ids.o

./obj/ida.o: ./lib/ida.cpp ./lib/ida.h ./lib/help.h
	g++ ./lib/ida.cpp -O3 -c -std=c++17 -o ./obj/ida.o

./obj/cli.o: ./lib/cli.cpp ./lib/cli.h ./lib/help.h
	g++ ./lib/cli.cpp -O3 -c -std=c++17 -o ./obj/cli.o

.PHONY: clean

clean: 
	rm -r ./obj/*.o


