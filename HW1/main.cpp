#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int ustAl(int taban,int ust);//ust alma fonksiyonu
int integeracevir(string str);//instruction da const verilen sayilari
//integera donusturur.
string harfcevir(string str);//verilen stringdeki tum harfleri buyuk harfe cevirir.
int mov1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi);
//Registerin ismini string olarak alÄ±r ve de
//hangi sayinin kopyalacagini alarak mov islemini gerÃ§ekleÅŸtirir.
int mov2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi mov islemini gerceklestirir.
int add1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile toplanacagini alarak add islemini gerceklestirir.
int add2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2);
//RegisterlarÄ±n ismini string olarak alir ve
//de registerlar arasi add iÅŸlemini gerceklestirir.
int Sub1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi);
//Registerin ismini string olarak alir ve de
//hangi sayi ile cikarilcagini alarak sub islemini gerceklestirir.
int Sub2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2);
//Registerlarin ismini string olarak alir ve
//de registerlar arasi sub islemini gerceklestirir.
int printOfRegister(int& R1,int& R2,int& R3,int& R4,int& R5,string reg);
//Verilen registeri ekrana print eder.
int instruction(int& R1,int& R2,int& R3,int& R4,int& R5,string str,string sub1,int boyut);
//Dosya dizinindeki her bir satirdaki
//atadigimiz string arrayini alarak talimatlara gore fonksiyon cagirir.
int jmp(int& R1,int& R2,int& R3,int& R4,int& R5,string str);
//RegisterÄ±n ismini string olarak alir ve de icerde verilen registerin 0 olup
//olmadigini kontrol ederek atlayacagi satiri return eder.


int main(int argc,char** argv)
{

    int R1=0,R2=0,R3=0,R4=0,R5=0;//baslangicta register degerlerini 0 yapiyoruz.
    int kontrol=0;//Hlt icin sayac yapÄ±yoruz
    int i=0;
    int k=0;
    int arrBoyut=0;//dosyadaki satir sayisini verir.

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

    for(i=0; i<arrBoyut; i++)//komutlara gore fonksiyon cagirip islem yapma
    {

        string instruct=arrBosluksuz[i].substr(0,3);
        kontrol=arrBosluksuz[i].length();//satirin sizeni hesaplama.

        if(instruct=="JMP")
        {
            string sub2=arrBosluksuz[i].substr(3,3);
            if(sub2=="R1," || sub2=="R2," ||
                    sub2=="R3," || sub2=="R4," ||
                    sub2=="R5,")
            {
                string sub3=arrBosluksuz[i].substr(6);
                int p=jmp(R1,R2,R3,R4,R5,sub2);
                if(p == -1)
                {
                    return -1;
                }
                else if(p)
                {
                    atlamaSatiri=integeracevir(sub3);
                    if(atlamaSatiri<1 || atlamaSatiri>arrBoyut )
                    {

                        cerr<<"can not found like the ROW..."<<endl;
                        return -1;
                    }
                    else
                    {
                        i=atlamaSatiri-2;

                    }
                }

            }
            else if(kontrol<6)
            {

                string sub3=arrBosluksuz[i].substr(3);
                atlamaSatiri=integeracevir(sub3);
                if(atlamaSatiri<1 || atlamaSatiri>arrBoyut )
                {

                    cerr<<"can not found like the ROW..."<<endl;
                    return -1;
                }
                else
                {
                    i=atlamaSatiri-2;
                }
            }
            else return -1;
        }
        else if(instruct=="HLT")
        {

            return 0;

        }


        else
        {

            if(instruction(R1,R2,R3,R4,R5,arrBosluksuz[i],instruct,arrBoyut)==-1)
            {

                cerr<<"HATA...!GOOD BYE.."<<endl;
                return -1;
            };

        }
       if(argv[2][0]=='1'){
        cout<<arrBosluksuz[i]<<"-"<<"R1="<<R1<<","<<"R2="<<R2<<","<<"R3="<<R3<<","<<"R4="<<R4<<","<<"R5="<<R5<<endl<<endl;
        }
    }
    return 0;
}

int instruction(int& R1,int& R2,int& R3,int& R4,int& R5,string str,string sub1,int boyut)
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

            deger=integeracevir(sub3);
            return mov1(R1,R2,R3,R4,R5,sub2,deger);

        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

            return  mov2(R1,R2,R3,R4,R5,sub2,sub3);
        }
    }
    else if(sub1=="ADD")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5")
        {

            deger=integeracevir(sub3);
            return add1(R1,R2,R3,R4,R5,sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

            return add2(R1,R2,R3,R4,R5,sub2,sub3);
        }
    }
    else if(sub1=="SUB")
    {

        string sub3=str.substr(6);
        if(sub3!="R1" && sub3!="R2" &&
                sub3!="R3" && sub3!="R4" &&
                sub3!="R5")
        {

            deger=integeracevir(sub3);
            return Sub1(R1,R2,R3,R4,R5,sub2,deger);
        }
        else if(sub3=="R1" || sub3=="R2" ||
                sub3=="R3" || sub3=="R4" ||
                sub3=="R5")
        {

            return Sub2(R1,R2,R3,R4,R5,sub2,sub3);
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

            return printOfRegister(R1,R2,R3,R4,R5,sub2);
        }
    }

    return -1;
}

int mov1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi)//verilen registera const degeri kopyalar.
{

    if(str=="R1,")
        R1=sayi;
    else if(str=="R2,")
        R2=sayi;
    else if(str=="R3,")
        R3=sayi;
    else if(str=="R4,")
        R4=sayi;
    else if(str=="R5,")
        R5=sayi;
    else
    {

        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int mov2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2)//1. verilen registeri 2. ye kopyalar.
{

    if(str1=="R1," && str2=="R2")
        R2=R1;
    else if(str1=="R1," && str2=="R3")
        R3=R1;
    else if(str1=="R1," && str2=="R4")
        R4=R1;
    else if(str1=="R1," && str2=="R5")
        R5=R1;
    else if(str1=="R2," && str2=="R1")
        R1=R2;
    else if(str1=="R2," && str2=="R3")
        R3=R2;
    else if(str1=="R2," && str2=="R4")
        R4=R2;
    else if(str1=="R2," && str2=="R5")
        R5=R2;
    else if(str1=="R3," && str2=="R1")
        R1=R3;
    else if(str1=="R3," && str2=="R2")
        R2=R3;
    else if(str1=="R3," && str2=="R4")
        R4=R3;
    else if(str1=="R3," && str2=="R5")
        R5=R3;
    else if(str1=="R4," && str2=="R1")
        R1=R4;
    else if(str1=="R4," && str2=="R2")
        R2=R4;
    else if(str1=="R4," && str2=="R3")
        R3=R4;
    else if(str1=="R4," && str2=="R5")
        R5=R4;
    else if(str1=="R5," && str2=="R1")
        R1=R5;
    else if(str1=="R5," && str2=="R2")
        R2=R5;
    else if(str1=="R5," && str2=="R3")
        R3=R5;
    else if(str1=="R5," && str2=="R4")
        R4=R5;
    else
    {

        cerr<<"not found like the REGÄ°STER..."<<endl;
        return -1;
    }

    return 0;
}
int add1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi)//register ve const arasinda toplama islemi yapar.
{

    if(str=="R1,")
        R1=R1+sayi;
    else if(str=="R2,")
        R2=R2+sayi;
    else if(str=="R3,")
        R3=R3+sayi;
    else if(str=="R4,")
        R4=R4+sayi;
    else if(str=="R5,")
        R5=R5+sayi;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int add2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2)//iki register arasindaki toplama islemini yapar.
{

    if(str1=="R1," && str2=="R2")
    {
        R1+=R2;
    }
    else if(str1=="R1," && str2=="R3")
    {
        R1+=R3;
    }
    else if(str1=="R1," && str2=="R4")
    {
        R1+=R4;
    }
    else if(str1=="R1," && str2=="R5")
    {
        R1+=R5;
    }
    else if(str1=="R2," && str2=="R1")
    {
        R2+=R1;
    }
    else if(str1=="R2," && str2=="R3")
    {
        R2+=R3;
    }
    else if(str1=="R2," && str2=="R4")
        R2+=R4;
    else if(str1=="R2," && str2=="R5")
        R2+=R5;
    else if(str1=="R3," && str2=="R1")
        R3+=R1;
    else if(str1=="R3," && str2=="R2")
        R3+=R2;
    else if(str1=="R3," && str2=="R4")
        R3+=R4;
    else if(str1=="R3," && str2=="R5")
        R3+=R5;
    else if(str1=="R4," && str2=="R1")
        R4+=R1;
    else if(str1=="R4," && str2=="R2")
        R4+=R2;
    else if(str1=="R4," && str2=="R3")
        R4+=R3;
    else if(str1=="R4," && str2=="R5")
        R4+=R5;
    else if(str1=="R5," && str2=="R1")
        R5+=R1;
    else if(str1=="R5," && str2=="R2")
        R5+=R2;
    else if(str1=="R5," && str2=="R3")
        R5+=R3;
    else if(str1=="R5," && str2=="R4")
        R5+=R4;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
    }

    return 0;
}

int Sub1(int& R1,int& R2,int& R3,int& R4,int& R5,string str,int sayi)//register ile const arasindaki cikarma islemini yapar.
{

    if(str=="R1,")
        R1=R1-sayi;
    else if(str=="R2,")
        R2=R2-sayi;
    else if(str=="R3,")
        R3=R3-sayi;
    else if(str=="R4,")
        R4=R4-sayi;
    else if(str=="R5,")
        R5=R5-sayi;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;

        return -1;
    }

    return 0;

}
int Sub2(int& R1,int& R2,int& R3,int& R4,int& R5,string str1,string str2)//iki registerÄ±n cikarma islemini yapar.
{

    if(str1=="R1," && str2=="R2")
        R1-=R2;
    else if(str1=="R1," && str2=="R1")
        R1-=R1;
    else if(str1=="R1," && str2=="R3")
        R1-=R3;
    else if(str1=="R1," && str2=="R4")
        R1-=R4;
    else if(str1=="R1," && str2=="R5")
        R1-=R5;
    else if(str1=="R2," && str2=="R2")
        R2-=R2;
    else if(str1=="R2," && str2=="R1")
        R2-=R1;
    else if(str1=="R2," && str2=="R3")
        R2-=R3;
    else if(str1=="R2," && str2=="R4")
        R2-=R4;
    else if(str1=="R2," && str2=="R5")
        R2-=R5;
    else if(str1=="R3," && str2=="R3")
        R3-=R3;
    else if(str1=="R3," && str2=="R1")
        R3-=R1;
    else if(str1=="R3," && str2=="R2")
        R3-=R2;
    else if(str1=="R3," && str2=="R4")
        R3-=R4;
    else if(str1=="R3," && str2=="R5")
        R3-=R5;
    else if(str1=="R4," && str2=="R3")
        R4-=R3;
    else if(str1=="R4," && str2=="R1")
        R4-=R1;
    else if(str1=="R4," && str2=="R2")
        R4-=R2;
    else if(str1=="R4," && str2=="R4")
        R4-=R4;
    else if(str1=="R4," && str2=="R5")
        R4-=R5;
    else if(str1=="R5," && str2=="R3")
        R5-=R3;
    else if(str1=="R5," && str2=="R1")
        R5-=R1;
    else if(str1=="R5," && str2=="R2")
        R5-=R2;
    else if(str1=="R5," && str2=="R4")
        R5-=R4;
    else if(str1=="R5," && str2=="R5")
        R5-=R5;
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
    }

    return 0;

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

int jmp(int& R1,int& R2,int& R3,int& R4,int& R5,string str)//registerÄ±n 0 olup olmadigini kontrol ederek return degerÅŸ cevirir.
{
    if(str=="R1,")
    {
        if(R1==0)
        {
            return 1;
        }
    }
    else if(str=="R2,")
    {

        if(R2==0)
        {
            return 1;
        }
    }
    else if(str=="R3,")
    {
        if(R3==0)
        {
            return 1;
        }
    }
    else if(str=="R4,")
    {
        if(R4==0)
        {
            return 1;
        }
    }
    else if(str=="R5,")
    {
        if(R5==0)
        {
            return 1;
        }
    }
    else
    {
        cerr<<"not found like the REGISTER..."<<endl;
        return -1;
    }

    return 0;
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




