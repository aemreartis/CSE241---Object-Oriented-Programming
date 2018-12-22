#ifndef cpu_h
#define cpu_h

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;



class CPU 
{
public:
	CPU();
	void setRegister(int registerAdress,int newValue);
	int getRegister(int registerAdress);
	int getPC();
	void setPC(int line);
	void printRegisters();
	bool halted();
	void execute(string instructionLine);
	int strToInt(string number) ;


private:

	int registers[5];
	int programCounter;
	string instruction,input1,input2,upper;

	void mov1() ;
	void mov2() ;
	void add1() ;
	void add2() ;
	void sub1() ;
	void sub2() ;
	void jmp1() ;
	void jmp2() ;
	void prn1() ;
	void prn2() ;
	void parseInstructionLine(string instructionLine);
	string makeUpper(string line) ; 	
	bool checkSyntax();
	bool isRegister( string item) ;
	int getRegisterAdress( string input_) ;
	bool isInt( string input_) ;

};

#endif