#ifndef COMPUTER_H
#define	COMPUTER_H

#include "CPUProgram.h"
#include "CPU.h"
#include "Memory.h"
#include <string>
#include <iostream>

using namespace std;

class Computer {
public:
    Computer(int option);
    Computer(CPU &obj1,CPUProgram &obj2,Memory &obj3,int option);
    CPU getCPU()const{ return myCPU;}
    CPUProgram getCPUProgram()const{ return myCPUProgram;}
    Memory getMemory()const{ return myMemory;}
    void setCPU(const CPU obj){ myCPU=obj; }
    void setCPUProgram(const CPUProgram obj){ myCPUProgram=obj; }
    void setMemory(const Memory obj){ myMemory=obj; }
    int execute();
private:
    CPU myCPU;
    CPUProgram myCPUProgram;
    Memory myMemory;
    int secenek;
};

#endif	/* COMPUTER_H */

