#ifndef BigramDyn_h
#define	BigramDyn_h


#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Bigram.h"


using namespace std;

template <class T>
class BigramDyn:public Bigram<T>
{
public:
	BigramDyn();
	BigramDyn(int dType);

	~BigramDyn();
	void readFile(const char* fileName)throw(myexception);
	int numGrams();
	int numOfGrams(T p1 , T p2);
	ostream& print(ostream& os) ;
	pair <T, T>maxGrams();



private:

	int dataType;
	T* data ;
	pair<T,T>* bigrams ;
	int dataSize;

};


#endif