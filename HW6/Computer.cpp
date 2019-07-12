
#include "Computer.h"
#include "Memory.h"
#include "CPUProgram.h"
#include "CPU.h"
#include <iostream>
#include <string>
#include <fstream>


Computer::Computer(int option) { 


    secenek=option; 
    
}

Computer::Computer(CPU &obj1,CPUProgram &obj2,Memory &obj3,int option){
   
    myCPU=obj1;
    myCPUProgram=obj2;
    myMemory=obj3;
    secenek=option;
}

int Computer::execute() {

int sonsatir;
myCPU.arrSize=myCPUProgram.size();

while(!myCPU.halted()){

	int satir=myCPU.getPC();
	string instruction=myCPUProgram.getLine(myCPU.getPC()-1);
        
	if(myCPU.execute(instruction,myMemory)==-1){

		exit(1);
	}

	int i=myCPU.getPC();	

	/*if(secenek==1){
		
		myCPU.setPC(satir);		
		myCPU.print();       
	 }*/

	myCPU.setPC(i);
	sonsatir=satir;
}
	if(secenek==1){
		
		myCPU.setPC(sonsatir);		
		myCPU.print();       
	 }
	 if(secenek==2){
			
		myMemory.printAll();       
	 }

return 0;

}

