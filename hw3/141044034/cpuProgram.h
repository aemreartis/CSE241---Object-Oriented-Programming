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
	string getLine(int line);
	int size();
	CPUProgram(string fileName);
	string lines[200];

private:
	int line;
	void readFile(string fileName);
};

#endif