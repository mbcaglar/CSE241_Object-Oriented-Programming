/*

//***********************************************************/
//*                M.BEDİRHAN ÇAĞLAR                        */
//*                                                         */
//*                  14.11.2016                             */
//*                                                         */
//* Bu program assemble instructionlari ile  mov , add, sub */
//*prn, jmp, jpn gibi islemleri yapan basit cpu yapisidir.  */
//*                                                         */
//*Ayrica bu program CPU,CPUProgram,Memory ve Computer      */
//*classları ile işlemleri gerçekleştirmektedir.            */
//                                                          */
//CPUProgram classı update edilip overloading yapılmıştır.  */
//***********************************************************/

#include "requiredIncs.h"//global fonksiyonlarım bu headerda olup CPUProgramda friend olarak declera edilmiştir.

using namespace std;

int main(int argc, char** argv){
//////////////////////////////////////////////////////////////////////////
//command line parameters
const char* filename = argv[1];
int option = atoi(argv[2]);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPUProgram
//op []

CPUProgram myCPUProgram(option);
myCPUProgram.ReadFile(filename);
cout << myCPUProgram[0] << endl;
cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
//op +
cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size()]) << endl;

//op +=

myCPUProgram += "MOV R2, #50";
cout << myCPUProgram[myCPUProgram.size() - 1] << endl;

//op + <<
CPUProgram myOtherCPUProgram(option);
myOtherCPUProgram.ReadFile(filename);
cout << (myCPUProgram + myOtherCPUProgram) << endl;

//op COMP --
cout<< (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
cout<< (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
cout<< (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
--myOtherCPUProgram;

cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;

//op ()

cout << myCPUProgram(5,10) << endl;

//error check
cout << myCPUProgram[myCPUProgram.size()] << endl;
myCPUProgram += "";
cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
//////////////////////////////////////////////////////////////////////////
return 0;
}

