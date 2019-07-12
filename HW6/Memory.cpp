
#include <iostream>
#include <string>
#include <fstream>
#include "Memory.h"

using namespace std;

Memory::Memory(int option){
	
	for(int i = 0; i < 50; i++) {

        memory[i]=0;

    }
	secenek=option;
}
void Memory::printAll(){
	
    for(int i = 0; i < 50; i++) {

       cout<<"["<<i<<"]"<<" "<<"->"<<" "<<unsigned(memory[i])<<endl;

    }
}

