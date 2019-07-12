#include "CPUProgram.h"
#include <iostream>
#include <string>
#include <vector>
#include<fstream>

using namespace std;

CPUProgram::CPUProgram(string file){
    
    arrBoyut=0;
    ReadFile(file);
}
CPUProgram::CPUProgram(int option){

	secenek=option;
	
}

CPUProgram::CPUProgram(const CPUProgram& obje1){

	secenek=obje1.secenek;
	arrBoyut=obje1.arrBoyut;
	arrBosluksuz=obje1.arrBosluksuz;

}


CPUProgram::CPUProgram(vector<string> v1,int boyut,int option){

	arrBosluksuz=v1;
	arrBoyut=boyut;
	secenek=option;
	
}


void CPUProgram::operator +=(string str){

	arrBosluksuz.push_back(str);
	arrBoyut++;
	
}
string CPUProgram::operator [](int index)const{

	if(index<0 || index>arrBoyut-1){

	cerr<<"BOYLE BİR SATIR BULUNMAMAMTADIR"<<endl;

	exit(0);
	}

	return arrBosluksuz[index];
}

const CPUProgram CPUProgram::operator--(){


		arrBosluksuz.pop_back();
		setSize(arrBosluksuz.size());

		return (*this);
}

const CPUProgram CPUProgram::operator--(int){

	vector<string> temp;

	temp=arrBosluksuz;

	arrBosluksuz.pop_back();	
	setSize(arrBosluksuz.size());

	return CPUProgram(temp,temp.size(),secenek);

}

const CPUProgram CPUProgram::operator ()(int first,int last)const{

	if(first>last || first<0 || last>arrBoyut-1){
		exit(1);
}

	vector<string> temp;
	
	
	for(int i=first; i<=last; i++){
		
		temp.push_back(arrBosluksuz[i]);
	}
	
	return CPUProgram(temp,temp.size(),secenek);	

}

int CPUProgram::ReadFile(string file){
    
    int i=0;
    ifstream inputFile;
    inputFile.open(file);
	string line;

    if(inputFile.is_open()==false)//dosyanin acilip acilamama kontrolu
    {
        cerr<<file << " is not found!\n";
        exit(-1);
    }

    while(getline(inputFile,line))//dosyayi satir satir okuyarak  tum harfleri buyuk harf yapar
    {

		arr.push_back(line);
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

vector<string> CPUProgram::arraydenBosluklariSil(){
   
	string tmp;
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
                   tmp+=arr[i][j];
                }

            }
        }

		arrBosluksuz.push_back(tmp);
		tmp="";
    }
	
	arrBoyut=arrBosluksuz.size();
	return arrBosluksuz;
}

string CPUProgram::getLine(int satir)const{

	if(satir<0 || satir>arrBoyut-1){

	cout<<"BOYLE BİR SATIR BULUNMAMAMTADIR"<<endl;
	exit(-1);
}
	return arrBosluksuz[satir];
}


const CPUProgram operator +(const CPUProgram& obje,string str){

	vector<string> temp;
	temp=obje.arrBosluksuz;		
	temp.push_back(str);	
	int size=temp.size();
	
	return CPUProgram(temp,size,1);

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


