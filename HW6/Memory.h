#ifndef MEMORY_H
#define	MEMORY_H

#include <iostream>

using namespace std;

class Memory{
public:

	Memory(){/*bos alan*/}
	Memory(int option);
	int getMem(int index)const{ return memory[index];}
	void setMem(int index,int deger){ memory[index]=deger; }
	void printAll();
private:
	unsigned memory[50];
    int secenek;
};


#endif	/* MEMORY_H */

