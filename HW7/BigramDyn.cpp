//***********************************************************
//*                M.BEDİRHAN ÇAĞLAR                        *
//*                                                         *
//*                  25.12.2016                             *
//*                                                         *
//* BigramDyn classımız stl kullanmadan bir map gibi        *
//* çalışır. Template bir class olup Bigram classından      *
//* inherit olmuştur..                                      *
//*                                                         *
//***********************************************************



#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <exception>
#include "error.h"
#include "BigramDyn.h"

using namespace std;

template<class T>
BigramDyn<T>::BigramDyn(int datatype){
    
    dataType=datatype;	
	arr=new T[100];
	
}
template<class T>
BigramDyn<T>::~BigramDyn(){

	delete [] arr;
}
template<class T>
void BigramDyn<T>::readFile(string file)throw (Hata){

    int i=0;
    ifstream inputFile;
    inputFile.open(file.c_str());
    T line;

    if(inputFile.is_open()==false)//dosyanin acilip acilamama kontrolu
    {
      throw Hata();
    }
	

    while(!inputFile.eof())//dosyayi satir satir okuyarak  tum harfleri buyuk harf yapar
    {
       if(inputFile>>line){

       	 	arr[i]=line;
        	i++;
		}
		else{
		
			throw Hata();	
		}
    }
    
    size=i; 
    inputFile.close();

}
template<class T>

int BigramDyn<T>::numGrams()const{

    return size-1;
}
template<class T>
int BigramDyn<T>::numOfGrams(const T first,const T second){
   
    int count=0;
    for(int i=0; i<size-1; i++){
        
        if(arr[i]==first && arr[i+1]==second){
            count++;
        }
    }
    return count;
}

template<class T>
pair<T,T> BigramDyn<T>::maxGrams(){
    

    int max=numOfGrams(arr[0],arr[1]);

    pair<T,T> temp=make_pair(arr[0],arr[1]);

    for(int i=1; i<numGrams(); i++){
        
        if(max<numOfGrams(arr[i],arr[i+1])){
        
            max=numOfGrams(arr[i],arr[i+1]);
            temp=make_pair(arr[i],arr[i+1]);
        }
    }

    return temp;
}

template<class T>
ostream& BigramDyn<T>::print(ostream &out){

	pair<T,T> temp;  
	/*vector< pair<T,T> > mypair;
	for(int i=0; i<numGrams(); i++){

		temp=make_pair(arr[i],arr[i+1]);
		mypair.push_back(temp);		
	}
	*/
	pair<T,T> *mypair=new pair<T,T>[numGrams()];
	for(int i=0; i<numGrams(); i++){
	
		temp=make_pair(arr[i],arr[i+1]);
		mypair[i]=temp;
	}



	for(int i=0; i<size-1; i++){

		for(int j=0; j<numGrams()-1; j++){

			if(numOfGrams(mypair[j].first,mypair[j].second)<=numOfGrams(mypair[j+1].first,mypair[j+1].second)){
	
								mypair[j].swap(mypair[j+1]);
			}
		}
	}

    for(int i=0; i<size-1; i++){
        
		out<<mypair[i].first<<"   "<<mypair[i].second<<"("<<numOfGrams(mypair[i].first,mypair[i].second)<<")"<<endl;
		i=i+numOfGrams(mypair[i].first,mypair[i].second)-1;

    }
    
    return out;
}
     
