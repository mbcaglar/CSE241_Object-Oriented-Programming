all: hw4 clean

hw4:CPU.o CPUProgram.o Memory.o Computer.o main.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o hw4 -std=c++11
main.o:main.cpp

	g++ -c main.cpp -std=c++11

CPU.o:CPU.cpp
	g++ -c CPU.cpp -std=c++11


CPUProgram.o:CPUProgram.cpp
	g++ -c CPUProgram.cpp -std=c++11

Memory.o:Memory.cpp
	g++ -c Memory.cpp -std=c++11

Computer.o:Computer.cpp
	g++ -c Computer.cpp -std=c++11
clean:

	./hw4 hw.txt 2
	rm *.o hw4
