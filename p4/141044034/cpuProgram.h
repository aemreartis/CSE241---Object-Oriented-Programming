#ifndef cpuProgram_h
#define	cpuProgram_h

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class CPUProgram
{
public:

	CPUProgram();
	CPUProgram(int option);
	CPUProgram(string fileName);
	
	string getLine(int line);
	int size();
	string lines[200];
	void readFile(string fileName);


private:
	int line;
	int opt;
};

#endif