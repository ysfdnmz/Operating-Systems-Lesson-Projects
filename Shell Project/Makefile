all: output output2 output3

output: accountant.o 
	g++ accountant.o  -o accountant

output2: inserter.o 
	g++ inserter.o  -o inserter

output3: calculate.o 
	g++ calculate.o  -o calc

accountant.o: accountant.c
	g++ -c accountant.c

inserter.o: inserter.c
	g++ -c inserter.c

calculate.o: calculate.c
	g++ -c calculate.c