#ifndef BigramMap_h
#define	BigramMap_h

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Bigram.h"


using namespace std;

template <class T>
class BigramMap:public Bigram<T>
{
public:
	BigramMap(int dType);
	void readFile(const char* fileName)throw(myexception);
	int numGrams();
	int numOfGrams(T p1 , T p2);
	ostream& print(ostream& os) ;
	pair <T, T>maxGrams();


private:
	map<int ,T> data ;
	map<int, pair<T ,T> > bigrams;
	int dataType;
};



#endif