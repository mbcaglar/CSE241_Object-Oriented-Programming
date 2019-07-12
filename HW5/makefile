all: hw5 clean

hw5:CPU.o CPUProgram.o Memory.o Computer.o _mainTester.o
	g++ _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o -o hw5 -std=c++11
_mainTester.o:_mainTester.cpp

	g++ -c _mainTester.cpp -std=c++11

CPU.o:CPU.cpp
	g++ -c CPU.cpp -std=c++11


CPUProgram.o:CPUProgram.cpp
	g++ -c CPUProgram.cpp -std=c++11

Memory.o:Memory.cpp
	g++ -c Memory.cpp -std=c++11

Computer.o:Computer.cpp
	g++ -c Computer.cpp -std=c++11
clean:

	./hw5 hw.txt 2
	rm *.o hw5
