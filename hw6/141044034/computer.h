#ifndef computer_h
#define	computer_h

#include "requiredIncs.h"

using namespace std;

class Computer
{
public:
	Computer();
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