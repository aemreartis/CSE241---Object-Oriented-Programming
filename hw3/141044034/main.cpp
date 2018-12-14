#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cpu.h"
#include "cpuProgram.h"
using namespace std;

int main(int argc,char** argv) 
{
	const int OPTION =2;
    int line;

	string instructionLine;

    CPU myCPU;
    CPUProgram myProgram(argv[1]);
    
    //Checks option , if it is not equal to 1 or 0 ,program ends.
    if (myCPU.strToInt(argv[OPTION]) !=1 && myCPU.strToInt(argv[OPTION]) !=0)
    {
        cerr << "Unknown option.Try 0, 1 or 2. "<<endl;
        return 1;
    }  
	while (!myCPU.halted())
	{	
        
        //GET INSTRUCTION LINE
        instructionLine = myProgram.getLine(myCPU.getPC());

        if(myProgram.size() > 200)
        {
            cerr<<"FILE SIZE OVER 9000"<<endl;
            return 1;
        }
        //PRINT REGİSTERS IF OPTION EQUAL TO 1 
        if(myCPU.strToInt(argv[OPTION]) ==1)
            myCPU.printRegisters();
	    //EXECUTE INSTRUCTION

	    myCPU.execute(instructionLine);
	}	

    myCPU.printRegisters();
 
	return 0;
}
