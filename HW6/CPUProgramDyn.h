#ifndef CPUPROGRAMDYN_H
#define	CPUPROGRAMDYN_H

#include <iostream>
#include <string>

//using std::ostream;
//using std::endl;
//using std::string;
//using std::cerr;

using namespace std;

namespace bedo{
class CPUProgramDyn{

public:
    CPUProgramDyn();
	CPUProgramDyn(int option);
	CPUProgramDyn(const CPUProgramDyn& obje1);
    CPUProgramDyn(string dosya);
	CPUProgramDyn(string* v1,int boyut,int option);
	~CPUProgramDyn(){ delete [] arr; delete [] arrBosluksuz;};
    int ReadFile(string dosya);
    int size()const{return arrBoyut;}
        
	friend bool operator==(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend bool operator!=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend bool operator<(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend bool operator>=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend bool operator>(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend bool operator<=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	friend ostream& operator<<(ostream& out,const CPUProgramDyn& program);                
	friend const CPUProgramDyn operator +(const CPUProgramDyn& obje,string str);
	friend const CPUProgramDyn operator +(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2);
	
	void operator +=(string str);		
	string operator [](int index)const;
    const string getLine(int satir)const;
	
	const CPUProgramDyn operator ()(int first,int last)const;		
	const CPUProgramDyn operator--();
	const CPUProgramDyn operator--(int);


	void setSize(int boyut){ arrBoyut=boyut; }
    void setCapasite(int kapasite){capasite=kapasite;}
    int getCapasite()const{ return capasite;}
    bool dolu()const { return (capasite == arrBoyut); }
    void capasiteArtir(int kat=2);
private:
    
        string *arr;
        string *arrBosluksuz;

        int arrBoyut;
		int capasite;
        int secenek;
        
        string changeToUpper(string str);
        void arraydenBosluklariSil();

};

}
#endif	/* CPUPROGRAMDYN_H */


