#ifndef memory_h
#define	memory_h

#include "requiredIncs.h"

using namespace std;

class Memory
{
public:
	Memory();
	Memory(int option);

	unsigned int getMem(int memoryAdress);
	void setMem(int memoryAdress , unsigned int newValue);

	void printAll();
	int getMemoryAdress(string input2);
	bool isMemoryAdress(string input_);

private:
	unsigned int memory[50];
	
	int opt;
	int strToInt(string number);
	bool isInt(string input_) ;
};

#endif