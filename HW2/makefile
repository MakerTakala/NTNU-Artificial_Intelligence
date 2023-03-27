all: main

main: main.cpp algo.cpp
	g++ main.cpp algo.cpp -std=c++17 -o main

.PHONY:case

case: 
	python3 case_generator.py $(filter-out $@,$(MAKECMDGOALS))