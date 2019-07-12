/*

//***********************************************************/
//*                M.BEDİRHAN ÇAĞLAR                        */
//*                                                         */
//*                  05.11.2016                             */
//*                                                         */
//* Bu program assemble instructionlari ile  mov , add, sub */
//*prn, jmp, jpn gibi islemleri yapan basit cpu yapisidir.  */
//*                                                         */
//*Ayrica bu program CPU,CPUProgram,Memory ve Computer      */
//*classları ile işlemleri gerçekleştirmektedir.            */
//***********************************************************/

#include "requiredIncs.h"

using namespace std;


int main(int argc, char** argv) {

    int option = atoi(argv[2]);
    const char* filename = argv[1];
   

CPU myCPU(option);
Memory myMemory(option);

CPUProgram myCPUProgram(option);
myCPUProgram.ReadFile(filename);
cout << myCPUProgram.getLine(1) << endl;
cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class Computer

Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
Computer myComputer2(option);
myComputer2.setCPU( myComputer1.getCPU() );
myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
myComputer2.setMemory(myComputer1.getMemory() );
myComputer2.execute();


	Memory myMemory1(option);
//index, value
	myMemory1.setMem(0, 100);
	cout << myMemory1.getMem(0) << endl;
//should print in a way that similar to this:
//Memory Values:
//[0] -> 100
//[1] -> 0
//[2] -> 0
//.
//.
//[49] -> 0
myMemory1.printAll();
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPU
CPU myCPU1(option);
myCPU1.execute("MOV #0,  R1", myMemory1);
myCPU1.execute("MOV R1  ,  #1", myMemory1);
myCPU1.print();
//should print in a way that similar to this:
//Memory Values:
//[0] -> 100
//[1] -> 100
//[2] -> 0
//.
//.
//[49] -> 0
myMemory1.printAll();
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPUProgram

//////////////////////////////////////////////////////////////////////////
return 0;
   

}
