OBJ: ./obj/main.o ./obj/help.o ./obj/ids.o ./obj/ida.o

all: main check

main: $(OBJ)
	g++ $(OBJ) -o main -std=c++17

check: ./obj/check.o ./obj/help.o
	g++ check.o help.o -o check -std=c++17

./obj/main.o: main.cpp ./lib/help.h ./lib/ids.h ./lib/ida.h
	g++ main.cpp -c -std=c++17 -o ./obj/main.o

./obj/check.o: check.cpp ./lib/help.h
	g++ check.cpp -c -std=c++17 -o ./obj/check.o

./obj/help.o: ./lib/help.cpp ./lib/help.h
	g++ ./lib/help.cpp -c -std=c++17 -o ./obj/help.o

./obj/ids.o: ./lib/ids.cpp ./lib/ids.h ./lib/help.h
	g++ ./lib/ids.cpp -c -std=c++17 -o ./obj/ids.o

./obj/ida.o: ./lib/ida.cpp ./lib/ida.h ./lib/help.h
	g++ ./lib/ida.cpp -c -std=c++17 -o ./obj/ida.o

.PHONY: clean

clean: 
	rm -r ./obj/*.o


