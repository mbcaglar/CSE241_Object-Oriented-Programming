#include "CPUProgram.h"
#include <iostream>
#include <string>
#include<fstream>

using namespace std;

CPUProgram::CPUProgram(string file){
    
    arrBoyut=0;
    readFile(file);
}

int CPUProgram::readFile(string file){
    
    int i=0;
    ifstream inputFile;
    inputFile.open(file);

    if(inputFile.is_open()==false)//dosyanin acilip acilamama kontrolu
    {
        cerr<<file << " is not found!\n";
        return -1;
    }

    while(getline(inputFile,arr[i]))//dosyayi satir satir okuyarak  tum harfleri buyuk harf yapar
    {

        arr[i]=changeToUpper(arr[i]);
        i++;
    }
    inputFile.close();
    arrBoyut=i;
    arraydenBosluklariSil();
    return 0;
}

string CPUProgram::changeToUpper(string str){
    
    int k=str.size();

    for(int i=0; i<k; i++)
    {

        if(str[i]>='a' && str[i]<='z')
        {
            str[i]-=('z'-'Z');

        }

    }

    return str;
}

string* CPUProgram::arraydenBosluklariSil(){
   
    for(int i=0; i<arrBoyut; ++i)//arrayi bosluklardan kurtarma
    {

        int boyut=arr[i].size();
        for(int j=0; j<boyut; j++)
        {

            if(arr[i][j]!=' ')
            {
                if(arr[i][j]==';')
                {
                    j=boyut+1;
                }
                else
                {
                    arrBosluksuz[i]+=arr[i][j];
                }

            }
        }


    }
    return arrBosluksuz;
}

string CPUProgram::getLine(int satir)const{

	return arrBosluksuz[satir-1];
}


