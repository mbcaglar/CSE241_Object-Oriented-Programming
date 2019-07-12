#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;

//bir program ile bir stringi toplayıp yeni bir programda bunu return eder.
const CPUProgram operator +(const CPUProgram& obje,string str){

	if(str==""){
		cerr<<"BOS String hatasi"<<endl;
		exit(1);	
	}	
	vector<string> temp;
	temp=obje.arrBosluksuz;		
	temp.push_back(str);	
	int size=temp.size();
	
	return CPUProgram(temp,size,obje.secenek);

}
//iki programı toplayıp yeni bir program return eder.
const CPUProgram operator +(const CPUProgram& obje1,const CPUProgram& obje2){

	
	vector<string> tmp;
	int size;

	tmp=obje1.arrBosluksuz;
	for(int i=0; i<obje2.arrBoyut; i++){	
	
		tmp.push_back(obje2.arrBosluksuz[i]);	
	
	}
	
	size=tmp.size();

	return CPUProgram(tmp,size,obje1.secenek);

}
//sizelara göre kasrşılastırma işlemleri.
bool operator==(const CPUProgram& obje1,const CPUProgram& obje2){

	return (obje1.size()==obje2.size());


}
bool operator!=(const CPUProgram& obje1,const CPUProgram& obje2){

	return !(obje1==obje2);


}

bool operator<(const CPUProgram& obje1,const CPUProgram& obje2){

	return (obje1.size()<obje2.size());


}

bool operator>=(const CPUProgram& obje1,const CPUProgram& obje2){

	return !(obje1<obje2);

}
bool operator>(const CPUProgram& obje1,const CPUProgram& obje2){

	return (obje1.size()>obje2.size());


}
bool operator<=(const CPUProgram& obje1,const CPUProgram& obje2){

	return !(obje1>obje2);


}

//Bir program ekrana basar.
ostream& operator<<(ostream& out,const CPUProgram& program){

	for(int i=0; i<program.size(); i++){

			out<<program.arrBosluksuz[i]<<endl;

	}

	return out;
}


