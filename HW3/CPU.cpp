#include "CPU.h"
#include <iostream>
#include <string>

using namespace std;


int CPU::PC=1;
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
int CPU::execute(string str){

    //komutlara gore fonksiyon cagirip islem yapma
     string instruct=str.substr(0,3);
     int kontrol=str.length();//satirin sizeni hesaplama.

        if(instruct=="JMP")
        {
            int  k=instruction(str,instruct,arrSize,kontrol);
            
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

            if(instruction(str,instruct,arrSize,kontrol)==-1)
            {

                cerr<<"HATA...!GOOD BYE.."<<endl;
                return -1;
            }
            PC++;

        }
     
    return 0;
}


int CPU::instruction(string str,string sub1,int boyut,int control)
{

    int i=0;
    int deger;
    int atlamaSatiri;
    string sub2=str.substr(3,3);

    if(sub1!="ADD" && sub1!="MOV" &&
            sub1!="JMP" && sub1!="SUB" &&
            sub1!="HLT" && sub1!="PRN")
    {

        cerr<<"INSTRUCTION FAULT...";
        return -1;
    }
    if(sub1=="MOV")
    {
        string sub3=str.substr(6);

        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5")
        {

            deger=coverToInteger(sub3);
            return mov1(sub2,deger);

        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

	    return  mov2(sub2,sub3);
        }
    }
    else if(sub1=="ADD")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5")
        {

            deger=coverToInteger(sub3);
            return add1(sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

            return add2(sub2,sub3);
        }
    }
    else if(sub1=="SUB")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5")
        {

            deger=coverToInteger(sub3);
            return Sub1(sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

            return Sub2(sub2,sub3);
        }
    }
    else if(sub1=="PRN")
    {

        string sub2=str.substr(3,2);
        if(sub2!="R1" && sub2!="R2" &&
                sub2!="R3" && sub2!="R4" &&
                sub2!="R5")
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
    else if(sub1=="JMP"){
		
	if(sub2!="R1," && sub2!="R2," && sub2!="R3," && sub2!="R4," &&
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
        
    return -1;
}
int CPU::mov1(string str,int sayi)//verilen registera const degeri kopyalar.
{

    if(str=="R1,")
        registers[0]=sayi;
    else if(str=="R2,")
        registers[1]=sayi;
    else if(str=="R3,")
        registers[2]=sayi;
    else if(str=="R4,")
        registers[3]=sayi;
    else if(str=="R5,")
        registers[4]=sayi;
    else
    {

        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int CPU::mov2(string str1,string str2)//1. verilen registeri 2. ye kopyalar.
{
	string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
	string arr2[5]={"R1","R2","R3","R4","R5"};

	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++){

			if(arr1[i]==str1 && arr2[j]==str2){
				
				registers[j]=registers[i];

				return 0;
			}
		}
	}	
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}
int CPU::add1(string str,int sayi)//register ve const arasinda toplama islemi yapar.
{

    if(str=="R1,")
        registers[0]= registers[0]+sayi;
    else if(str=="R2,")
        registers[1]=registers[1]+sayi;
    else if(str=="R3,")
        registers[2]=registers[2]+sayi;
    else if(str=="R4,")
        registers[3]=registers[3]+sayi;
    else if(str=="R5,")
        registers[4]=registers[4]+sayi;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int CPU::add2(string str1,string str2)//iki register arasindaki toplama islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    string arr2[5]={"R1","R2","R3","R4","R5"};

	for(int i=0; i<5; i++)
	{
            for(int j=0; j<5; j++){
                
                if(arr1[i]==str1 && arr2[j]==str2){
                    
                    registers[i]+=registers[j];
                   		return 0;
		}
            }
	}	
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}
int CPU::Sub1(string str,int sayi)//register ile const arasindaki cikarma islemini yapar.
{

    if(str=="R1,")
        registers[0]=registers[0]-sayi;
    else if(str=="R2,")
        registers[1]=registers[1]-sayi;
    else if(str=="R3,")
        registers[2]=registers[2]-sayi;
    else if(str=="R4,")
        registers[3]=registers[3]-sayi;
    else if(str=="R5,")
        registers[4]=registers[4]-sayi;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int CPU::Sub2(string str1,string str2)//iki registerÄ±n cikarma islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    string arr2[5]={"R1","R2","R3","R4","R5"};

	for(int i=0; i<5; i++)
	{
            for(int j=0; j<5; j++){

		if(arr1[i]==str1 && arr2[j]==str2){
			
                    registers[i]-=registers[j];
				
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
        cout<<"R1="<<registers[0]<<endl;
    else if(reg=="R2")
        cout<<"R2="<<registers[1]<<endl;
    else if(reg=="R3")
        cout<<"R3="<<registers[2]<<endl;
    else if(reg=="R4")
        cout<<"R4="<<registers[3]<<endl;
    else if(reg=="R5")
        cout<<"R5="<<registers[4]<<endl;
    else{return -1;}

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








