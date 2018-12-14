#ifndef cpu_h
#define cpu_h

#include "requiredIncs.h"

using namespace std;



class CPU 
{
public:
	CPU();
	CPU(int option);
	void setRegister(int registerAdress,int newValue);
	int getRegister(int registerAdress);
	
	void setPC(int line);	
	int getPC();
	
	void print();
	bool halted(Memory myMemory);
	void execute(string instructionLine,Memory& myMemory);
	int strToInt(string number) ;


private:
	int opt;
	int registers[5];
	int programCounter;
	string instruction,input1,input2,upper;

	void mov1() ;
	void mov2() ;
	void mov3(Memory& myMemory) ;
	void mov4(Memory& myMemory) ;
	void mov5(Memory& myMemory) ;
	void add1() ;
	void add2() ;
	void add3(Memory& myMemory) ;
	void sub1() ;
	void sub2() ;
	void sub3(Memory& myMemory) ;
	void jmp1() ;
	void jmp2() ;
	void jpn(Memory& myMemory) ;
	void prn1() ;
	void prn2() ;
	void prn3(Memory& myMemory) ;

	void parseInstructionLine(string instructionLine);
	string makeUpper(string line) ; 	
	bool checkSyntax(Memory myMemory);
	bool isRegister( string item) ;
	int getRegisterAdress( string input_) ;
	bool isInt( string input_) ;

};

#endif