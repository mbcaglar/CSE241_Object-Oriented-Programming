#ifndef BIGRAMMAP_H
#define	BIGRAMMAP_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <exception>
#include "error.h"
#include "Bigram.h"


using namespace std;

template<class T>
class BigramMap: public Bigram<T>
{
public:
    BigramMap(int datatype);
    virtual void readFile(string file)throw (Hata);
    virtual int numGrams()const;
    virtual int numOfGrams(const T first,const T second);
    virtual ostream &print(ostream &out);
    virtual pair<T,T> maxGrams();
    
private:
    int dataType;
    int size;
    map<int,T> arr;
    
};

#endif	/* BIGRAMMAP_H */

