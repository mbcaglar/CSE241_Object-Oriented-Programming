/* 
 * File:   FileIOError.h
 * Author: bedo
 *
 * Created on December 21, 2016, 9:30 PM
 */

#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <exception>

using namespace std;

class Hata: public exception
{

public:

	const char* what() const throw(){

		return "Dosya Hatalı~UYGUN OLMAYAN FORMATLAMA~!!!";
	}
	
};

#endif	/* FILEIOERROR_H */

