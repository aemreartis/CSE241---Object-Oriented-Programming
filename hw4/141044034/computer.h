#ifndef computer_h
#define	computer_h

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "memory.h"
#include "cpu.h"
#include "cpuProgram.h"

using namespace std;

class Computer
{
public:
	Computer(const CPU inCpu , const CPUProgram inProgram , const Memory inMemory, const int inOption);
	Computer(const int option);


	CPU getCPU();
	CPUProgram getCPUProgram();
	Memory getMemory();

	//EXECUTES PROGRAM
	void execute();
	
	void setCPU(CPU iCPU);
	void setCPUProgram(CPUProgram iCPUProgram);
	void setMemory(Memory iMemory);

private:

	CPUProgram myProgram;
	CPU  myCpu;
	Memory myMemory;
	int opt;
	

};
#endif