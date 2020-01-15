all: output output2

output: main.o 
	gcc main.o  -o main -l pthread

output2: reader.o  
	gcc reader.o  -o reader -l pthread

main.o: main.c
	gcc -c main.c -l pthread

reader.o: reader.c
	gcc -c reader.c -l pthread