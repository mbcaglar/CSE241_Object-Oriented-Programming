all: calistir

calistir:CPU.o CPUProgram.o CPUProgramDyn.o Memory.o Computer.o _mainTester.o
	g++ _mainTester.o CPU.o CPUProgram.o CPUProgramDyn.o Memory.o Computer.o -o hw6 -std=c++11
_mainTester.o:_mainTester.cpp

	g++ -c _mainTester.cpp -std=c++11

CPU.o:CPU.cpp
	g++ -c CPU.cpp -std=c++11


CPUProgram.o:CPUProgram.cpp
	g++ -c CPUProgram.cpp -std=c++11

CPUProgramDyn.o:CPUProgramDyn.cpp
	g++ -c CPUProgramDyn.cpp -std=c++11
Memory.o:Memory.cpp
	g++ -c Memory.cpp -std=c++11

Computer.o:Computer.cpp
	g++ -c Computer.cpp -std=c++11



run1:
	./hw6 hw.txt 0

run2:
	./hw6 hw.txt 1

run3:
	./hw6 hw.txt 2

clean:

	rm *.o hw6
