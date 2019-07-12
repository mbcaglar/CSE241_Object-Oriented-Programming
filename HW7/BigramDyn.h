#ifndef BIGRAMDYN_H
#define	BIGRAMDYN_H

#include <string>
#include <map>
#include <utility>
#include <exception>
#include "error.h"
#include "Bigram.h"


using namespace std;

template<class T>
class BigramDyn: public Bigram<T>
{
public:
    BigramDyn(int datatype);
	~BigramDyn();
    virtual void readFile(string file) throw (Hata);
    virtual int numGrams()const;
    virtual int numOfGrams(const T first,const T second);
    virtual ostream &print(ostream &out);
    virtual pair<T,T> maxGrams();
    
private:
    int dataType;
    int size;
    T *arr;
    
};

#endif	/* BIGRAMMAP_H */

