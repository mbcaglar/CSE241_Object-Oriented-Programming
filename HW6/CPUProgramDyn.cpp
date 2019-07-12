#include "CPUProgramDyn.h"
#include <iostream>
#include <string>
#include<fstream>

namespace bedo{

CPUProgramDyn::CPUProgramDyn() : capasite(200),arrBoyut(0)
{
    arrBosluksuz=new string[capasite];
    arr=new string[capasite];
}

CPUProgramDyn::CPUProgramDyn(string dosya){
    
    arrBoyut=0;
    capasite=200;
    arrBosluksuz=new string[capasite];
    arr=new string[capasite];
    ReadFile(dosya);
}

CPUProgramDyn::CPUProgramDyn(int option){

    secenek=option;
    arrBoyut=0;
    capasite=200;
    arrBosluksuz=new string[capasite];
    arr=new string[capasite];
	
}
CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& obje1){

	secenek=obje1.secenek;
	arrBoyut=obje1.arrBoyut;
	capasite=obje1.capasite;
	arr=new string[capasite];
	arrBosluksuz=new string[capasite];
	
	for(int i=0; i<arrBoyut; i++){
		
		arrBosluksuz[i]=obje1.arrBosluksuz[i];			
	}

}

CPUProgramDyn::CPUProgramDyn(string *v1,int boyut,int option){

	capasite=boyut*2;
    arrBosluksuz=new string[capasite];
    arr=new string[capasite];
    arrBoyut=boyut;
    secenek=option;
    for(int i=0; i<boyut; i++){

		arrBosluksuz[i]=v1[i];
        
    }    
		
}
void CPUProgramDyn::operator +=(string str){

    if (!dolu()) {
        
        arrBoyut++;
        arrBosluksuz[arrBoyut-1]=str;
        
        }
	 else {
            
            capasiteArtir();
            arrBoyut++;
            arrBosluksuz[arrBoyut-1]=str;
        }

	

}
string CPUProgramDyn::operator [](int index)const{

	if(index<0 || index>arrBoyut-1){

		cerr<<"BOYLE BİR SATIR BULUNMAMAMTADIR"<<endl;

	}

	return arrBosluksuz[index];
}

const CPUProgramDyn CPUProgramDyn::operator--(){


        arrBosluksuz[arrBoyut-1]="";
		arrBoyut--;
		

		return (*this);
}

const CPUProgramDyn CPUProgramDyn::operator--(int){

	string *temp;
    temp=new string[capasite];
    int size=arrBoyut;
	temp=arrBosluksuz;

	arrBosluksuz[arrBoyut-1]="";	
        arrBoyut--;

	return CPUProgramDyn(temp,size,secenek);

}

const CPUProgramDyn CPUProgramDyn::operator ()(int first,int last)const{

	if(first>last || first<0 || last>arrBoyut-1){
		exit(1);
}

	string *temp;
	temp=new string[capasite];
	int k=0;
	for(int i=first; i<=last; i++){
		
		temp[k]=arrBosluksuz[i];
                k++;
        }
	
	return CPUProgramDyn(temp,k,secenek);	

}

int CPUProgramDyn::ReadFile(string dosya){
        
    int i=0;
    ifstream inputFile;

    inputFile.open(dosya.c_str());

    if(inputFile.is_open()==false)//dosyanin acilip acilamama kontrolu
    {
        cerr<<dosya << " is not found!\n";
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

string CPUProgramDyn::changeToUpper(string str){
    
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

void CPUProgramDyn::arraydenBosluklariSil(){
   
    
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
    return;
}


const string CPUProgramDyn::getLine(int satir)const{

	if(satir<0 || satir>arrBoyut-1)
	{

	cout<<"BOYLE BİR SATIR BULUNMAMAMTADiR"<<endl;
	
}
	return arrBosluksuz[satir];
}

void CPUProgramDyn::capasiteArtir(int kat) {

    capasite *= kat;
    string* tmp = new string[capasite];

    for (int i = 0; i < arrBoyut; i++)
        tmp[i] = arrBosluksuz[i];

    delete[] arrBosluksuz;

    arrBosluksuz = tmp;
}


//bir program ile bir stringi toplayıp yeni bir programda bunu return eder.
const CPUProgramDyn operator +(const CPUProgramDyn& obje,string str){

	CPUProgramDyn temp(obje.arrBosluksuz,obje.size(),obje.secenek);

	if (!temp.dolu()) {
        
        temp.arrBoyut++;
        temp.arrBosluksuz[temp.arrBoyut-1]=str;
        
        } else {
            
            temp.capasiteArtir();
            temp.arrBoyut++;
            temp.arrBosluksuz[temp.arrBoyut-1]=str;
        }

	return temp;

}
//iki programı toplayıp yeni bir program return eder.
const CPUProgramDyn operator +(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	
	CPUProgramDyn temp(obje1.arrBosluksuz,obje1.size(),obje1.secenek);

	for(int i=0; i<obje2.arrBoyut; i++){	

		if (!temp.dolu()) {
		    
			temp.arrBoyut++;
			temp.arrBosluksuz[temp.size()-1]=obje2.arrBosluksuz[i];
		    
	    }
		else {
		        
		        temp.capasiteArtir();		  
				temp.arrBoyut++;		        
				temp.arrBosluksuz[temp.size()-1]=obje2.arrBosluksuz[i];
				
		    }
	}
	
	return temp;

}
//sizelara göre kasrşılastırma işlemleri.
bool operator==(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return (obje1.size()==obje2.size());


}
bool operator!=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return !(obje1==obje2);


}

bool operator<(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return (obje1.size()<obje2.size());


}

bool operator>=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return !(obje1<obje2);

}
bool operator>(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return (obje1.size()>obje2.size());


}
bool operator<=(const CPUProgramDyn& obje1,const CPUProgramDyn& obje2){

	return !(obje1>obje2);


}

//Bir program ekrana basar.
ostream& operator<<(ostream& out,const CPUProgramDyn& program){

	for(int i=0; i<program.size(); i++){

			out<<program.arrBosluksuz[i]<<endl;

	}

	return out;
}

}

