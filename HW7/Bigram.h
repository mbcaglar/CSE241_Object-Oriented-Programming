
// ABSTRUCT BİR CLASS DIR OBJESİ YAPILAMAZ.

 
#ifndef BIGRAM_H
#define	BIGRAM_H
#include <string>
#include <exception>
#include "error.h"

using namespace std;

template <class T>
class Bigram {
public:
    virtual void readFile(string file) throw(Hata) =0;
    virtual int numGrams()const=0;
    virtual int numOfGrams(const T first,const T second)=0;
    friend ostream &operator<<(ostream &out,Bigram<T> &obje){
        return obje.print(out);
    }

    virtual ostream& print(ostream &out)=0;
    virtual pair<T,T> maxGrams()=0;
};

#endif	/* BIGRAM_H */

