#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include "cpuProgram.h"

using namespace std;


CPUProgram::CPUProgram()
{
	line=0;
}


CPUProgram::CPUProgram(int option)
{
	opt=option;
	line=0;
}


CPUProgram::CPUProgram(string fileName){
	readFile(fileName);
}


//READS FILE AND SAVES IT TO LINES ARRAY
void CPUProgram::readFile(string fileName)
{

	ifstream insFile(fileName);
    if(insFile.is_open() == false)
    {
        cerr << "Can not open file" << endl;
        exit(1);
    }
    while(!insFile.eof() ) {
        getline(insFile, lines[line]);	
        ++line;
    }
    insFile.close();
}

string CPUProgram::getLine(int nthline)
{
	return lines[nthline];
}

int CPUProgram::size()
{
	return line;
}
