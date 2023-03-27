all: IDS IDA

IDS: IDS.cpp
	g++ IDS.cpp -std=c++17 -o IDS
IDA: IDA*.cpp
	g++ IDA.cpp -std=c++17 -o IDA


.PHONY:case clean run

clean:
	rm IDA IDS

case: 
	python3 case_generator.py $(filter-out $@,$(MAKECMDGOALS))