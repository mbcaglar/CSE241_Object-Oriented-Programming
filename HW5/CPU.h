#ifndef _CPU_H__
#define _CPU_H__

#include "Memory.h"
#include <string>

using namespace std;
class CPU{
public:
    CPU(){ /*bos alan*/  }
    CPU(int option);
    int getRegisters(int index)const{return registers[index];}
    int getPC()const{return PC;}
    int execute(string str,Memory& obje);
    int arrSize;
    void setRegisters(int deger,int index){ registers[index]=deger;}
    void setPC(int satir);
    void print()const;
    
    bool halted()const;
    
private:

    int registers[5]={0,0,0,0,0};
    int secenek;
    static int PC;
    
    int mov1(string str,int sayi);
//Registerin ismini string olarak alÄ±r ve de
//hangi sayinin kopyalacagini alarak mov islemini gerÃ§ekleÅŸtirir.
    int mov2(string str1,string str2,Memory &obje);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi mov islemini gerceklestirir.
    int movM1(string str,int sayi,Memory &obje);//verilen memorye const ataması yapar.

    int movM2(string str1,string str2,Memory &obje);//verilen memorye registerdaki değeri atar.

    int movM3(string str1,string str2,Memory &obje);//registera memorydeki degeri atar.

    int add1(string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile toplanacagini alarak add islemini gerceklestirir.
    int add2(string str1,string str2,Memory& obje);
//RegisterlarÄ±n ismini string olarak alir ve
//de registerlar arasi add iÅŸlemini gerceklestirir.
    int Sub1(string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile cikarilcagini alarak sub islemini gerceklestirir.
    int Sub2(string str1,string str2,Memory& obje);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi sub islemini gerceklestirir.
    int printOfRegister(string reg);//Verilen registeri ekrana print eder.

    int printOfMemory(string reg,Memory& obje);
    
    int instruction(string str,string sub1,int boyut,int control,Memory &obje);
//Dosya dizinindeki her bir satirdaki
//atadigimiz string arrayini alarak talimatlara gore fonksiyon cagirir.
    int jmp(string str);
    int jpn(string str);

    int coverToInteger(string expression);
    int mypow(int taban,int ust);
 	string deleteSpaces(string str);
};
#endif	/* CPU_H */

