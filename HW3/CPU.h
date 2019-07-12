#ifndef _CPU_H__
#define _CPU_H__

#include <iostream>
#include <string>

using namespace std;

class CPU{
public:
    CPU(){ /*bos alan*/  }
    const int *getRegisters()const{return registers;}
    int getPC()const{return PC;}
    int execute(string str);
    int arrSize;
    void setRegisters(int deger,int index){ registers[index]=deger;}
    void setPC(int satir);
    void print()const;
    
    bool halted()const;
    
private:

    int registers[5]={0,0,0,0,0};
    
    static int PC;
    
    int mov1(string str,int sayi);
//Registerin ismini string olarak alÄ±r ve de
//hangi sayinin kopyalacagini alarak mov islemini gerÃ§ekleÅŸtirir.
    int mov2(string str1,string str2);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi mov islemini gerceklestirir.
    int add1(string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile toplanacagini alarak add islemini gerceklestirir.
    int add2(string str1,string str2);
//RegisterlarÄ±n ismini string olarak alir ve
//de registerlar arasi add iÅŸlemini gerceklestirir.
    int Sub1(string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile cikarilcagini alarak sub islemini gerceklestirir.
    int Sub2(string str1,string str2);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi sub islemini gerceklestirir.
    int printOfRegister(string reg);//Verilen registeri ekrana print eder.

    int instruction(string str,string sub1,int boyut,int control);
//Dosya dizinindeki her bir satirdaki
//atadigimiz string arrayini alarak talimatlara gore fonksiyon cagirir.
    int jmp(string str);

    int coverToInteger(string expression);
    int mypow(int taban,int ust);
};
#endif	/* CPU_H */

