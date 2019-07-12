#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__
#define MAX_ARRAY_SIZE 200

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CPUProgram{

    public:
        CPUProgram(){
        //bilerek bos birakildi
        }

		CPUProgram(int option);
        CPUProgram(string file);
		CPUProgram(const CPUProgram& obje1);
		CPUProgram(vector<string> v1,int boyut,int option);

        int ReadFile(string file);
        int size()const{return arrBoyut;}



		friend bool operator==(const CPUProgram& obje1,const CPUProgram& obje2);
		friend bool operator!=(const CPUProgram& obje1,const CPUProgram& obje2);
		friend bool operator<(const CPUProgram& obje1,const CPUProgram& obje2);
		friend bool operator>=(const CPUProgram& obje1,const CPUProgram& obje2);
		friend bool operator>(const CPUProgram& obje1,const CPUProgram& obje2);
		friend bool operator<=(const CPUProgram& obje1,const CPUProgram& obje2);

	 	friend const CPUProgram operator +(const CPUProgram& obje,string str);
		friend const CPUProgram operator +(const CPUProgram& obje1,const CPUProgram& obje2);
		void operator +=(string str);		
		string operator [](int index)const;
        string getLine(int satir)const;
	
		const CPUProgram operator ()(int first,int last)const;		
		const CPUProgram operator--();
		const CPUProgram operator--(int);
		friend ostream& operator<<(ostream& out,const CPUProgram& program);

		void setSize(int boyut){ arrBoyut=boyut; }        
		const vector<string> getArray()const{return arr;}
        const vector<string> getBosluksuzArray()const{return arrBosluksuz;}
      
        
    private:
    
        vector<string> arr;
        vector<string> arrBosluksuz;

        int arrBoyut;
		int secenek;
        
        string changeToUpper(string str);
        vector<string> arraydenBosluklariSil();
    
};

#endif	/* CPUPROGRAM_H */

