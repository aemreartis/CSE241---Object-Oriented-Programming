#ifndef memory_h
#define	memory_h

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class Memory
{
public:
	Memory();
	Memory(int option);

	unsigned int getMemory(int memoryAdress);
	void setMemory(int memoryAdress , unsigned int newValue);

	void printMemory();
	int getMemoryAdress(string input2);
	bool isMemoryAdress(string input_);

private:
	unsigned int memory[50];
	
	int opt;
	int strToInt(string number);
	bool isInt(string input_) ;
};

#endif