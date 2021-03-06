#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cpu.h"
#include "cpuProgram.h"
#include "memory.h"
#include "computer.h"


int strToInt(string number) 
{
	int i, convertedInt = 0;

	for ((number[0]=='-') ? i=1 : i=0; i < number.size(); ++i)
		convertedInt = number[i] - '0' + convertedInt * 10;

	(number[0]=='-') ? convertedInt*= -1 : convertedInt*=1;

	return convertedInt;
}




int main(int argc, char** argv){
//////////////////////////////////////////////////////////////////////////
//command line parameters
const char* filename = argv[1];
int option = strToInt(argv[2]) ;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class Memory
Memory myMemory(option);
//index, value
myMemory.setMemory(0, 100);
cout << myMemory.getMemory(0) << endl;
//should print in a way that similar to this:
//Memory Values:
//[0] -> 100
//[1] -> 0
//[2] -> 0
//.
//.
//[49] -> 0
myMemory.printMemory();
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPU
CPU myCPU(option);
myCPU.execute("MOV #0, R1", myMemory);
myCPU.execute("MOV R1, #1", myMemory);
//should print in a way that similar to this:
//CPU Register Values:
//[0] -> 100
//[1] -> 0
//[2] -> 0
//[3] -> 0
//[4] -> 0
myCPU.printRegisters();
//should print in a way that similar to this:
//Memory Values:
//[0] -> 100
//[1] -> 100
//[2] -> 0
//.
//.
//[49] -> 0
myMemory.printMemory();
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPUProgram
CPUProgram myCPUProgram(option);

myCPUProgram.readFile(filename);

cout << myCPUProgram.getLine(0) << endl;
cout << myCPUProgram.getLine(myCPUProgram.size() - 2) << endl;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class Computer
Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
Computer myComputer2(option);
myComputer2.setCPU( myComputer1.getCPU() );
myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
myComputer2.setMemory(myComputer1.getMemory() );
myComputer2.execute();
//////////////////////////////////////////////////////////////////////////
}