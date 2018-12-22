#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cpu.h"
#include "cpuProgram.h"
#include "memory.h"
#include "computer.h"

using namespace std;

	Computer::Computer(const CPU inCpu , const CPUProgram inProgram , const Memory inMemory, const int option)
	{
		
		setCPU(inCpu);
		setCPUProgram(inProgram);
		setMemory(inMemory);

		opt= option;
	}

	Computer::Computer(const int option)
	{
		opt=option;
	}



	void Computer::execute(){

		//OPTION CHECK
	    if (opt !=1 && opt !=0 && opt !=2)
	    {
	        cerr << "Unknown option.Try 0, 1 or 2. "<<endl;
	        exit(1);
	    }  
		while (!myCpu.halted(myMemory))
		{	        
	     
	     	//CHECK SIZE
	        if(myProgram.size() > 200)
	        {
	            cerr<<"FILE SIZE OVER 200"<<endl;
	           	exit(1);
	        }

	        //PRINT REGİSTERS IF OPTION EQUAL TO 1 OR 2 
	        if(opt ==1 || opt ==2)
	            myCpu.printRegisters();

	        //EXECUTE INSTRUCTION
		    myCpu.execute(myProgram.getLine(myCpu.getPC()-1),myMemory);
	        
	        //IF OPTION EQUAL TO 2 PRINT MEMORY
	        if(opt ==2)
	            myMemory.printMemory();
		}
	}

	CPU Computer::getCPU()
	{
		return myCpu;
	}
	
	CPUProgram Computer::getCPUProgram()
	{
		return myProgram;
	}
	
	Memory Computer::getMemory()
	{
		return myMemory;
	}

	void Computer::setCPU(CPU iCPU)
	{
		int i;
		for(i=0;i<5;++i)
			myCpu.setRegister(i,iCPU.getRegister(i));
		myCpu.setPC(iCPU.getPC());	
	}
	
	void Computer::setCPUProgram(CPUProgram iCPUProgram){
		int i ;
		for(i=0;i<200;++i)
			myProgram.lines[i]=iCPUProgram.getLine(i);

	}
	
	void Computer::setMemory(Memory iMemory){
		int i ;
		for(i=0;i<50;++i)
			myMemory.setMemory(i,iMemory.getMemory(i));
	}
