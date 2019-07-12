#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__
#define MAX_ARRAY_SIZE 200

#include <iostream>
#include <string>

using namespace std;

class CPUProgram{

    public:
        CPUProgram(){
        //bilerek bos birakildi
        }
        CPUProgram(string file);

        int readFile(string file);
        int size(){return arrBoyut;}

        string getLine(int satir)const;
        const string* getArray()const{return arr;}
        const string* getBosluksuzArray()const{return arrBosluksuz;}
      
        
    private:
    
        string arr[MAX_ARRAY_SIZE];
        string arrBosluksuz[MAX_ARRAY_SIZE];

        int arrBoyut;
        
        string changeToUpper(string str);
        string* arraydenBosluklariSil();
    
    
};

#endif	/* CPUPROGRAM_H */

