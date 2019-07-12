//***********************************************************
//*                M.BEDİRHAN ÇAĞLAR                        *
//*                                                         *
//*                  15.10.2016                             *
//*                                                         *
//* Bu program assemble instructionlari ile  mov , add, sub *
//*prn, jmp, jpn gibi islemleri yapan basit cpu yapisidir.  *
//*                                                         *
//***********************************************************

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int ustAl(int taban,int ust);//ust alma fonksiyonu

int integeracevir(string str);//instruction da const verilen sayilari
//integera donusturur.

string harfcevir(string str);//verilen stringdeki tum harfleri buyuk harfe cevirir.
int mov1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array);
//Registerin ismini string olarak alÄ±r ve de
//hangi sayinin kopyalacagini alarak mov islemini gerÃ§ekleÅŸtirir.

int mov2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi mov islemini gerceklestirir.

int movM1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,
        int sayi,uint8_t *adress);//verilen memorye const ataması yapar.

int movM2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
          int *array,uint8_t *adress);//verilen memorye registerdaki değeri atar.

int movM3(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
          int *array,uint8_t *adress);//registera memorydeki degeri atar.

int add1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array);
//Registerin ismini string olarak alir ve de
//hangi sayi ile toplanacagini alarak add islemini gerceklestirir.

int add2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress);
//Registerlarin ismini string olarak alir ve verilen dizine gore 
//registerlar arasi yada register memory arasi add islemini gerceklestirir.

int Sub1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array);
//Registerin ismini string olarak alir ve de hangi sayi ile cikarilcagini
//alarak sub islemini gerceklestirir.

int Sub2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress);
//Registerlarin ismini string olarak alir ve verilen dizine gore 
//registerlar arasi yada register memory arasi add islemini gerceklestirir.

int printOfRegister(int& R1,int& R2,int& R3,int& R4,int& R5,string reg);
//Verilen registeri ekrana print eder.

int printOfMemory(string str,uint8_t *adress);//Verilen memoryi ekrana print eder.

int instruction(int& R1,int& R2,int& R3,int& R4,int& R5,string str,string sub1,
               int boyut,int control,uint8_t *adress);
//Dosya dizinindeki her bir satirdaki
//atadigimiz string arrayini alarak talimatlara gore fonksiyon cagirir.
int jmp(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int *array);
//RegisterÄ±n ismini string olarak alir ve de icerde verilen registerin 0 olup
//olmadigini kontrol ederek atlayacagi satiri return eder.
int jpn(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int *array);


int main(int argc,char** argv)
{

    int R1=0,R2=0,R3=0,R4=0,R5=0;//baslangicta register degerlerini 0 yapiyoruz.
    int kontrol=0;//Hlt icin sayac yapÄ±yoruz
    int i=0;
    int k=0;
    int arrBoyut=0;//dosyadaki satir sayisini verir.
    uint8_t memory[50];//# ifadesi ile verilen alan icin ayirdigimiz int arrayimiz.
    int atlamaSatiri;
    string arr[200];//dosya dizinin atadigimiz string array.
    string arrBosluksuz[200]="";//bosluklari atarak elde ettigimiz son arrayimiz
    ifstream inputFile;
    inputFile.open(argv[1]);

    if(inputFile.is_open()==false)//dosyanin acilip acilamama kontrolu
    {
        cerr<<"FAILED...";
        return -1;
    }

    while(getline(inputFile,arr[i]))//dosyayi satir satir okuyarak  tum harfleri buyuk harf yapar
    {

        arr[i]=harfcevir(arr[i]);
        i++;
    }
    arrBoyut=i;

    for(i=0; i<arrBoyut; ++i)//arrayi bosluklardan kurtarma
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
    for(i=0; i<arrBoyut; i++)//dosyada fazladan harf girilmis mi bunun kontrolu
    {

        k=arrBosluksuz[i].length();
        if(k>9)
        {
            cerr<<"Hatali dosya dizini..."<<endl;
            return -1;
        }
    }
    for(i=0; i<arrBoyut; i++)//arrayi substr ile instructionlara bolme komutlari elde etme
    {

        string instruct=arrBosluksuz[i].substr(0,3);

        if(instruct=="HLT")
        {
            kontrol++;
        }
    }

    if(kontrol!=1)
    {
        cerr<<"Bu programda sonlanamaz...ERROR HLT!!!"<<endl;
        return -1;
    }
    
    for(int i = 0; i < 50; i++) {

        memory[i]=0;

    }


    for(i=0; i<arrBoyut; i++)//komutlara gore fonksiyon cagirip islem yapma
    {
        string instruct=arrBosluksuz[i].substr(0,3);
        kontrol=arrBosluksuz[i].length();//satirin sizeni hesaplama.

        if(instruct=="JMP")
        {
            k=instruction(R1,R2,R3,R4,R5,arrBosluksuz[i],instruct,arrBoyut,
                         kontrol,memory);

		if(k==-1){

                    cerr<<"Errors..."<<endl;
                    return -1;
		}
		else if(k!=0){
                    i=k;

		}

	}
        else if(instruct=="JPN"){

            k=instruction(R1,R2,R3,R4,R5,arrBosluksuz[i],instruct,arrBoyut,
                         kontrol,memory);

		if(k==-1){

                    cerr<<"Errors..."<<endl;
                    return -1;
		}
		else if(k!=0){
                    i=k;

		}


        }
        else if(instruct=="HLT")
        {

            return 0;

        }


        else
        {

            if(instruction(R1,R2,R3,R4,R5,arrBosluksuz[i],instruct,arrBoyut,
              kontrol,memory)==-1)
            {

                cerr<<"HATA...!GOOD BYE.."<<endl;
                return -1;
            }

        }
       if(argv[2][0]=='1' && instruct!="JMP" && instruct!="JPN"){
        cout<<arrBosluksuz[i]<<"-"<<"R1="<<R1<<","<<"R2="<<R2<<","<<"R3="<<R3<<","<<"R4="<<R4<<","<<"R5="<<R5<<endl<<endl;
        }
       else if(argv[2][0]=='2' && instruct!="JMP" && instruct!="JPN"){
                
           for (int i = 0; i < 50; i++) {
                cout<<"Memory["<<i<<"]= "<<unsigned(memory[i])<<endl;

            }
       }
    }
    return 0;
}

int instruction(int& R1,int& R2,int& R3,int& R4,int& R5,string str,string sub1,
               int boyut,int control,uint8_t *adress)
{

    int i=0;
    int deger;
    int atlamaSatiri;
    string sub2=str.substr(3,3);
    int array[5]={R1,R2,R3,R4,R5};


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
                deger=integeracevir(sub3);
                return mov1(R1,R2,R3,R4,R5,sub2,deger,array);

            }
            else if(sub3=="R1" || sub3=="R2" || sub3=="R3" || sub3=="R4" ||
                    sub3=="R5")
            {
                
                return  mov2(R1,R2,R3,R4,R5,sub2,sub3,array,adress);
            }
            else if(sub3[0]=='#'){
               
                return movM3(R1,R2,R3,R4,R5,sub2,sub3,array,adress);
                                
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

                deger=integeracevir(sub3);
                return movM1(R1,R2,R3,R4,R5,sub2,deger,adress);

            }
            else if(sub3=="R1" || sub3=="R2" || sub3=="R3" || sub3=="R4" ||
                    sub3=="R5")
            {
 
                return  movM2(R1,R2,R3,R4,R5,sub2,sub3,array,adress);
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

            deger=integeracevir(sub3);
            return add1(R1,R2,R3,R4,R5,sub2,deger,array);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5" || sub3[0]=='#')
        {

            return add2(R1,R2,R3,R4,R5,sub2,sub3,array,adress);
        }
    }
    else if(sub1=="SUB")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5" && sub3[0]!='#')
        {

            deger=integeracevir(sub3);
            return Sub1(R1,R2,R3,R4,R5,sub2,deger,array);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5" || sub3[0]=='#')
        {

            return Sub2(R1,R2,R3,R4,R5,sub2,sub3,array,adress);
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

                return printOfRegister(R1,R2,R3,R4,R5,sub2);
            }
        }   
            
        else{
            
            return printOfMemory(sub2,adress);
            
        }
    }
    else if(sub1=="JMP"){

		if(sub2!="R1," && sub2!="R2," &&
                sub2!="R3," && sub2!="R4," &&
                sub2!="R5," && control<6)
        {
			string sub3=str.substr(3);
            atlamaSatiri=integeracevir(sub3);

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
		atlamaSatiri=integeracevir(sub3);
		int p=jmp(R1,R2,R3,R4,R5,sub2,array);

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
            atlamaSatiri=integeracevir(sub3);

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
		atlamaSatiri=integeracevir(sub3);
		int p=jpn(R1,R2,R3,R4,R5,sub2,array);

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

int mov1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array)
//verilen registera const degeri kopyalar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
   
    for (int i = 0; i < 5; i++) {
    
        if(arr1[i]==str){
            
            array[i]=sayi;
            R1=array[0];
            R2=array[1];	
            R3=array[2];
	    R4=array[3];
      	    R5=array[4];
         
            return 0;
        }

    }
    
    cerr<<"not found like the REGISTER..."<<endl;

    return -1;
   

}
int mov2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress)//1. verilen registeri 2. ye kopyalar.
{
	string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
	string arr2[5]={"R1","R2","R3","R4","R5"};

	if(str2[0]!='#'){
        
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<5; j++){

                    if(arr1[i]==str1 && arr2[j]==str2){

                        array[j]=array[i];
                        R1=array[0];
                        R2=array[1];
                        R3=array[2];
                        R4=array[3];
                        R5=array[4];
                    
                        return 0;
                    }
                }
            }
        }
        else if(str2[0]=='#'){
           
            string memoryLocation=str2.substr(1);
            int index=integeracevir(memoryLocation);
        
            if(index<0 || index>50){
            
                cerr<<"False adress..ERROR!!!"<<endl;
                return -1;
            }
            for(int i=0; i<5; i++){
                
                if(arr1[i]==str1){
                    
                    adress[index]=array[i];
                    return 0;
                }
            }
            
        }
        
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;

}
int movM1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,uint8_t *adress){
    
    string memoryLocation=str.substr(1);
    int index=integeracevir(memoryLocation);
        
    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
    }
        
    adress[index]=sayi;    
    
}
int movM2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
          int *array,uint8_t *adress){
    
    string memoryLocation=str1.substr(1);
    int index=integeracevir(memoryLocation);
        
    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
    }

    string arr1[5]={"R1","R2","R3","R4","R5"};
    for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str2){
		
                array[i]=adress[index];
                R1=array[0];
                R2=array[1];
                R3=array[2];
                R4=array[3];
                R5=array[4];
                
                
            }
   
    }
}
int movM3(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
          int *array,uint8_t *adress){
    
    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    string memoryLocation=str2.substr(1);
    int index=integeracevir(memoryLocation);
        
    if(index<0 || index>50){
            
        cerr<<"False adress..ERROR!!!"<<endl;
        return -1;
    }
        
    for (int i = 0; i < 5; i++) {
           
        if(arr1[i]==str1){
            adress[index]=array[i];
            return 0;
        }
    }
    cerr<<"not found like register..."<<endl;
    return -1;
}
int add1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array)
//register ve const arasinda toplama islemi yapar. 
{ 
    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
   
    for (int i = 0; i < 5; i++) {
    
        if(arr1[i]==str){
            
            array[i]+=sayi;
            R1=array[0];
            R2=array[1];	
            R3=array[2];
	    R4=array[3];
      	    R5=array[4];
         
            return 0;
        }

    }
    
    cerr<<"not found like the REGISTER..."<<endl;

    return -1;
}

int add2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress)//iki register arasindaki toplama islemini yapar.
{
 
    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    
    if(str2[0]!='#'){
        
            string arr2[5]={"R1","R2","R3","R4","R5"};

            for(int i=0; i<5; i++)
            {
		for(int j=0; j<5; j++){

			if(arr1[i]==str1 && arr2[j]==str2){

				array[i]+=array[j];
				R1=array[0];
				R2=array[1];
				R3=array[2];
				R4=array[3];
				R5=array[4];

				return 0;
			}
		}
            }
    }
    else if(str2[0]=='#'){
        
        string memoryLocation=str2.substr(1);
        int index=integeracevir(memoryLocation);
        
        if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
        }
        
        for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str1){
		
                array[i]+=adress[index];
		R1=array[0];
        	R2=array[1];
                R3=array[2];
		R4=array[3];
		R5=array[4];
                return 0;
                
            }

        }
    }
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}

int Sub1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi,int *array)
//register ile const arasindaki cikarma islemini yapar.
{

    string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
   
    for (int i = 0; i < 5; i++) {
    
        if(arr1[i]==str){
            
            array[i]-=sayi;
            R1=array[0];
            R2=array[1];	
            R3=array[2];
	    R4=array[3];
      	    R5=array[4];
         
            return 0;
        }

    }
    
    cerr<<"not found like the REGISTER..."<<endl;

    return -1;
   

}
int Sub2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2,
        int *array,uint8_t *adress)//iki registerÄ±n cikarma islemini yapar.
{
string arr1[5]={"R1,","R2,","R3,","R4,","R5,"};
    
    if(str2[0]!='#'){
        
        string arr2[5]={"R1","R2","R3","R4","R5"};

        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++){

                if(arr1[i]==str1 && arr2[j]==str2){

                    array[i]-=array[j];
                    R1=array[0];
                    R2=array[1];
                    R3=array[2];
                    R4=array[3];
                    R5=array[4];

                    return 0;
                    }
		}
            }
    }
    else if(str2[0]=='#'){
        
        string memoryLocation=str2.substr(1);
        int index=integeracevir(memoryLocation);
        
        if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
        }
        
        for (int i = 0; i < 5; i++) {
           
            if(arr1[i]==str1){
		
                array[i]-=adress[index];
		R1=array[0];
        	R2=array[1];
                R3=array[2];
		R4=array[3];
		R5=array[4];
                return 0;                
                
            }

        }
    }
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
}

int printOfRegister(int& R1,int& R2,int& R3,int& R4,int& R5,string reg)
{

    if(reg=="R1")
        cout<<"R1="<<R1<<endl;
    else if(reg=="R2")
        cout<<"R2="<<R2<<endl;
    else if(reg=="R3")
        cout<<"R3="<<R3<<endl;
    else if(reg=="R4")
        cout<<"R4="<<R4<<endl;
    else if(reg=="R5")
        cout<<"R5="<<R5<<endl;


    return 0;

}
int printOfMemory(string str,uint8_t *adress){
    
    string memoryLocation=str.substr(1);
    int index=integeracevir(memoryLocation);

    if(index<0 || index>50){
            
            cerr<<"False adress..ERROR!!!"<<endl;
            return -1;
        }
    
    cout<<"Memory["<<index<<"]"<<" = "<<unsigned(adress[index])<<endl;

    return 0;
    
    
}

int jmp(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int *array)//registerin 0 olup olmadigini kontrol ederek return degeri cevirir.
{

	string arr[5]={"R1,","R2,","R3,","R4,","R5,"};

	for(int i=0; i<5; i++){

		if(arr[i]==str){

			if(array[i]==0){

  			    return 1;
			}

			return 0;
	     }

	}

        cerr<<"not found like the REGISTER..."<<endl;
        return -1;

}
int jpn(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int *array){

    string arr[5]={"R1,","R2,","R3,","R4,","R5,"};

	for(int i=0; i<5; i++){

            if(arr[i]==str){

		if(array[i]==0 || array[i]<0){

  		    return 1;
		}

		return 0;
	    }

	}

        cerr<<"not found like the REGISTER..."<<endl;
        return -1;


}
string harfcevir(string str)
{

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
int integeracevir(string str)//string olarak verilen sayiyi integera cevirip return eder.
{
    int deger=0;
    int tmp=0;
    int k=0,j=0;
    int i=str.length();

    int basamak=ustAl(10,i-1);

    if(str[0]!='-'  )
    {

        for(j=basamak; j>0; j/=10)
        {

            str[k]-='0';
            tmp=str[k];
            deger+=(j*tmp);
            k++;

        }
        return deger;
    }
    else if(str[0]=='-')
    {
        k=0;

        for(j=basamak; j>0; j/=10)
        {

            str[k]+='0';
            tmp=str[k];
            deger+=(basamak*tmp);
            k++;
        }

        deger=0-deger;

        return deger;
    }
    return 0;
}
int ustAl(int taban,int ust){

    int i;
    taban=1;
    for(i=0; i<ust; i++){
        taban=taban*10;

    }
    return taban;

}



