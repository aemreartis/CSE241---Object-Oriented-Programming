#ifndef Bigram_h
#define	Bigram_h

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;


template <class T>
class Bigram
{
	public:

		virtual void readFile(const char* fileName)=0;
		virtual int numGrams()=0;
		virtual int numOfGrams(T p1 , T p2)=0;
		virtual ostream& print(ostream& os) = 0;
		virtual pair<T, T> maxGrams()=0;

		friend ostream& operator<< (std::ostream& os,  Bigram& b)
		{
			b.print(os);
			return os;
		}
};




class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
}exc;


#endif
