all: hw3 clean

hw3: main.o CPU.o CPUProgram.o
	g++ main.o CPU.o CPUProgram.o -o hw3 -std=c++11
main.o:main.cpp

	g++ -c main.cpp -std=c++11
CPU.o:CPU.cpp
	g++ -c CPU.cpp -std=c++11


CPUProgram.o:CPUProgram.cpp
	g++ -c CPUProgram.cpp -std=c++11
clean:

	./hw3 hw3.txt 0
	rm *.o hw3
