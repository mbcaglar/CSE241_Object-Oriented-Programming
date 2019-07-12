#include "CPU.h"
#include "Memory.h"
#include <iostream>
#include <string>

using namespace std;

int CPU::PC=1;

CPU::CPU(int option){
    
    secenek=option;
}
string CPU::deleteSpaces(string str){

		int i=0;
        int boyut=0;
		string tmp=str;
		while(str[boyut]!='\0'){
		boyut++;
}
        for(int j=0; j<boyut; j++)
        {

            if(str[j]!=' ')
            {
                if(str[j]==';')
                {
                    j=boyut+1;
                }
                else
                {
                    tmp[i]=str[j];
					i++;
                }

            }
        }
	tmp=tmp.substr(0,i);

    return tmp;
}

int CPU::coverToInteger(string expression)//string olarak verilen sayiyi integera cevirip return eder.
{
    int deger=0;
    int tmp=0;
    int k=0,j=0;
    int i=expression.length();

    int basamak=mypow(10,i-1);

    if(expression[0]!='-'  )
    {

        for(j=basamak; j>0; j/=10)
        {

            expression[k]-='0';
            tmp=expression[k];
            deger+=(j*tmp);
            k++;

        }
        return deger;
    }
    else if(expression[0]=='-')
    {
        k=0;

        for(j=basamak; j>0; j/=10)
        {

            expression[k]+='0';
            tmp=expression[k];
            deger+=(basamak*tmp);
            k++;
        }

        deger=0-deger;

        return deger;
    }
    return 0;
}
int CPU ::mypow(int taban,int ust){

    int i;
    taban=1;
    for(i=0; i<ust; i++){
        taban=taban*10;

    }
    return taban;

}


void CPU::print()const{
    cout<<"R1="<<registers[0]<<endl;
    cout<<"R2="<<registers[1]<<endl;
    cout<<"R3="<<registers[2]<<endl;
    cout<<"R4="<<registers[3]<<endl;
    cout<<"R5="<<registers[4]<<endl;

    cout<<"PC="<<PC<<endl;
    return ;

}
void CPU::setPC(int satir){

    PC=satir;

}
bool CPU::halted()const{

	return PC==0 ;

}
int CPU::execute(string str,Memory &obje){

    //komutlara gore fonksiyon cagirip islem yapma
	str=deleteSpaces(str);
     string instruct=str.substr(0,3);
     int kontrol=str.length();//satirin sizeni hesaplama.

        if(instruct=="JMP")
        {
            int  k=instruction(str,instruct,arrSize,kontrol,obje);
            
            if(k==-1){

                cerr<<"Errors..."<<endl;
                return -1;
            }
            else if(k!=0){
                    PC=k+1;
            }
            PC++;

	}
        else if(instruct=="JPN")
        {
            int  k=instruction(str,instruct,arrSize,kontrol,obje);
            
            if(k==-1){

                cerr<<"Errors..."<<endl;
                return -1;
            }
            else if(k!=0){
                    PC=k+1;
            }
            PC++;

	}
        else if(instruct=="HLT")
        {
            PC=0;
            return 0;

        }


        else
        {

            if(instruction(str,instruct,arrSize,kontrol,obje)==-1)
            {

                cerr<<"HATA...!GOOD BYE.."<<endl;
                return -1;
            }
            PC++;

        }
     
    return 0;
}


int CPU::instruction(string str,string sub1,int boyut,int control,Memory &obje)
{

    int i=0;
    int deger;
    int atlamaSatiri;
    string sub2=str.substr(3,3);

	if(sub1!="ADD" && sub1!="MOV" &&
            sub1!="JMP" && sub1!="SUB" &&
            sub1!="HLT" && sub1!="PRN" && sub1!="JPN")
    {

        cerr<<"INSTRUCTION FAULT...";
        return -1;
    }
    if(sub1=="MOV")
    {
        if(sub2[0]!='#'){
        
            string sub3=str.substr(6);

            if(sub3!="R1" && sub3!="R2" && sub3!="R3" && sub3!="R4" &&
               sub3!="R5" && sub3[0]!='#')
            {
		deger=coverToInteger(sub3);
                return mov1(sub2,deger);

            }
            else if(sub3=="R1" || sub3=="R2" || sub3=="R3" || sub3=="R4" ||
                    sub3=="R5")
            {
                
                return  mov2(sub2,sub3,obje);
            }
            else if(sub3[0]=='#'){
               
                return movM3(sub2,sub3,obje);
                                
            }
        }
        else{
        
            int found=str.find(',');
            found++;
            string sub2=str.substr(3,found-4);
            string sub3=str.substr(found);
            
            if(sub3!="R1" && sub3!="R2" && sub3!="R3" && sub3!="R4" &&
               sub3!="R5")
            {

                deger=coverToInteger(sub3);
                return movM1(sub2,deger,obje);

            }
            else if(sub3=="R1" || sub3=="R2" || sub3=="R3" || sub3=="R4" ||
                    sub3=="R5")
            {
 
                return  movM2(sub2,sub3,obje);
            }
            
            else{
                
                cerr<<"not found like the Register..!!!"<<endl;
                return -1;      
            }
        }
    }
    else if(sub1=="ADD")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5" && sub3[0]!='#')
        {

            deger=coverToInteger(sub3);
            return add1(sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5" || sub3[0]=='#')
        {

            return add2(sub2,sub3,obje);
        }
    }
    else if(sub1=="SUB")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5" && sub3[0]!='#')
        {

            deger=coverToInteger(sub3);
            return Sub1(sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5" || sub3[0]=='#')
        {

            return Sub2(sub2,sub3,obje);
        }
    }
    else if(sub1=="PRN")
    {

        string sub2=str.substr(3);
        
        if(sub2[0]!='#'){
           
            if(sub2!="R1" && sub2!="R2" &&
                sub2!="R3" && sub2!="R4" &&
                sub2!="R5" )
            {

                cerr<<"can not print like the REGISTER..."<<endl;
                return -1;

            }
            else if(sub2=="R1" || sub2=="R2" ||
                sub2=="R3" || sub2=="R4" ||
                sub2=="R5")
            {

                return printOfRegister(sub2);
            }
        }   
            
        else{
            
            return printOfMemory(sub2,obje);
            
        }
    }
    else if(sub1=="JMP"){

		if(sub2!="R1," && sub2!="R2," &&
                sub2!="R3," && sub2!="R4," &&
                sub2!="R5," && control<6)
        {
            string sub3=str.substr(3);
            atlamaSatiri=coverToInteger(sub3);

		if(atlamaSatiri<1 || atlamaSatiri>boyut){

                	cerr<<"Not found the row..!"<<endl;
			return -1;

		}
		return atlamaSatiri-2;

        }
		else if(sub2=="R1," || sub2=="R2," ||
                sub2=="R3," || sub2=="R4," ||
                sub2=="R5,")
        {
            
        string sub3=str.substr(6);
        atlamaSatiri=coverToInteger(sub3);
		int p=jmp(sub2);

		if(p==-1){
	
                    return -1;
		}
		else if(p){

                    if(atlamaSatiri<1 || atlamaSatiri>boyut){

						cerr<<"Not found the row..!"<<endl;
                        return -1;

                    }

		return atlamaSatiri-2;

		}
		else return 0;

        }
    }
    else if(sub1=="JPN"){

	if(sub2!="R1," && sub2!="R2," &&  sub2!="R3," && sub2!="R4," &&
          sub2!="R5," && control<6)
        {
            string sub3=str.substr(3);
            atlamaSatiri=coverToInteger(sub3);

            if(atlamaSatiri<1 || atlamaSatiri>boyut){

              	cerr<<"Not found the row..!"<<endl;
				return -1;

            }
		return atlamaSatiri-2;

        }
		else if(sub2=="R1," || sub2=="R2," ||
                sub2=="R3," || sub2=="R4," ||
                sub2=="R5,")
        {
            
        string sub3=str.substr(6);
        atlamaSatiri=coverToInteger(sub3);
		int p=jpn(sub2);

		if(p==-1){
	
                    return -1;
		}
		else if(p){

                    if(atlamaSatiri<1 || atlamaSatiri>boyut){

			cerr<<"Not found the row..!"<<endl;
                        return -1;

                    }

		return atlamaSatiri-2;

		}
		else return 0;

        }
    }

    
    return -1;
}

int CPU::mov1(string str,int sayi)//verilen registera const degeri kopyalar.
{

    if(str=="R1,")
        setRegisters(sayi,0);
    else if(str=="R2,")
        setRegisters(sayi,1);
    else if(str=="R3,")
        setRegisters(sayi,2);
    else if(str=="R4,")
        setRegisters(sayi,3);
    else if(str=="R5,")
        setRegisters(sayi,4);
    else
    {

        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int CPU::mov2(string str1,string str2,Memory &obje)//1. verilen registeri 2. ye kopyalar.
{
	string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
	string arr2[5]={"R1","R2","R3","R4","R5"};
	if(str2[0]!='#'){

		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++){

				if(arr1[i]==str1 && arr2[j]==str2){
				
					setRegisters(registers[i],j);

					return 0;
				}
			}
		}
	}
	else if(str2[0]=='#'){
           
            string memoryLocation=str2.substr(1);
            int index=coverToInteger(memoryLocation);
        
            if(index<0 || index>50){
            
                cerr<<"False adress..ERROR!!!"<<endl;
                return -1;
            }
            for(int i=0; i<5; i++){
                
                if(arr1[i]==str1){
                    
                    obje.setMem(index,registers[i]);
                    return 0;
                }
            }
            
        }
	
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}
int CPU::movM1(string str,int sayi,Memory &obje){
    
    string memoryLocation=str.substr(1);
    int index=coverToInteger(memoryLocation);
        
    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
    }
        
    obje.setMem(index,sayi);
    return 0;
    
}
int CPU::movM2(string str1,string str2,Memory &obje){
    
    string memoryLocation=str1.substr(1);
 	int index=coverToInteger(memoryLocation);
        
    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
    }

    string arr1[5]={"R1","R2","R3","R4","R5"};
    for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str2){
		
                setRegisters(obje.getMem(index),i);
                return 0;
            }
   
    }
    return -1;
}
int CPU::movM3(string str1,string str2,Memory &obje){
    
    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    string memoryLocation=str2.substr(1);
	int index=coverToInteger(memoryLocation);
        
    if(index<0 || index>50){
            
        cerr<<"False adress..ERROR!!!"<<endl;
        return -1;
    }
        
    for (int i = 0; i < 5; i++) {
           
        if(arr1[i]==str1){
            obje.setMem(index,registers[i]);
            return 0;
        }
    }
    cerr<<"not found like register..."<<endl;
    return -1;
}

int CPU::add1(string str,int sayi)//register ve const arasinda toplama islemi yapar.
{

    if(str=="R1,")
        setRegisters(registers[0]+sayi,0);
    else if(str=="R2,")
		setRegisters(registers[1]+sayi,1);
    else if(str=="R3,")
        setRegisters(registers[2]+sayi,2);
    else if(str=="R4,")
        setRegisters(registers[3]+sayi,3);
    else if(str=="R5,")
     	setRegisters(registers[4]+sayi,4);
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int CPU::add2(string str1,string str2,Memory &obje)//iki register arasindaki toplama islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    
	if(str2[0]!='#'){

		string arr2[5]={"R1","R2","R3","R4","R5"};

		for(int i=0; i<5; i++)
		{
		        for(int j=0; j<5; j++){
		            
		            if(arr1[i]==str1 && arr2[j]==str2){
		                
		                setRegisters(registers[i]+registers[j],i);
		               		return 0;
					}
		        }
		}
	}
	else if(str2[0]=='#'){
        
        string memoryLocation=str2.substr(1);
        int index=coverToInteger(memoryLocation);
        
        if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
        }
        
        for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str1){
		
                setRegisters(registers[i]+obje.getMem(index),i);
                return 0;
                
            }

        }
    }
	
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}
int CPU::Sub1(string str,int sayi)//register ile const arasindaki cikarma islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
   
    for (int i = 0; i < 5; i++) {
    
        if(arr1[i]==str){
            
            setRegisters(registers[i]-sayi,i);
         
            return 0;
        }

    }
    
    cerr<<"not found like the REGISTER..."<<endl;

    return -1;
   

}

int CPU::Sub2(string str1,string str2,Memory &obje)//iki registerÄ±n cikarma islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    
	if(str2[0]!='#'){

		string arr2[5]={"R1","R2","R3","R4","R5"};

		for(int i=0; i<5; i++)
		{
		        for(int j=0; j<5; j++){
		            
		            if(arr1[i]==str1 && arr2[j]==str2){
		                
		                setRegisters(registers[i]-registers[j],i);
		               		return 0;
					}
		        }
		}
	}
	else if(str2[0]=='#'){
        
        string memoryLocation=str2.substr(1);
        int index=coverToInteger(memoryLocation);
        
        if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
        }
        
        for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str1){
		
                setRegisters(registers[i]-obje.getMem(index),i);
                return 0;
                
            }

        }
    }
	
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}
int CPU::printOfRegister(string reg)
{

    if(reg=="R1")
        cout<<"R1="<<getRegisters(0)<<endl;
    else if(reg=="R2")
        cout<<"R2="<<getRegisters(1)<<endl;
    else if(reg=="R3")
        cout<<"R3="<<getRegisters(2)<<endl;
    else if(reg=="R4")
        cout<<"R4="<<getRegisters(3)<<endl;
    else if(reg=="R5")
        cout<<"R5="<<getRegisters(4)<<endl;
    else{return -1;}

    return 0;

}

int CPU::printOfMemory(string str,Memory& obje){
    
    string memoryLocation=str.substr(1);
    int index=coverToInteger(memoryLocation);

    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
     }
    
    cout<<"Memory["<<index<<"]"<<" = "<<obje.getMem(index)<<endl;

    return 0;
        
}


int CPU::jmp(string str)//registerin 0 olup olmadigini kontrol ederek return degeri cevirir.
{

	string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};

	for(int i=0; i<5; i++){

		if(arr1[i]==str){

			if(registers[i]==0){

  			    return 1;
			}

			return 0;
	     }

	}

        cerr<<"not found like the REGISTER..."<<endl;
        return -1;

}
int CPU::jpn(string str)//registerin 0 olup olmadigini kontrol ederek return degeri cevirir.
{

	string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};

	for(int i=0; i<5; i++){

		if(arr1[i]==str){

			if(registers[i]==0 || registers[i]<0){

  			    return 1;
			}

			return 0;
	     }

	}

        cerr<<"not found like the REGISTER..."<<endl;
        return -1;

}
