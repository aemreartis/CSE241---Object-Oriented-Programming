#include <string>
#include <iostream>
#include <cstdlib>
#include "cpu.h"
#include "memory.h"

using namespace std;

CPU::CPU(){
	registers[0]=0;
	registers[1]=0;
	registers[2]=0;
	registers[3]=0;
	registers[4]=0;
	programCounter=1;
}
CPU::CPU(int option){
	registers[0]=0;
	registers[1]=0;
	registers[2]=0;
	registers[3]=0;
	registers[4]=0;
	programCounter=1;
	opt= option;

}


void CPU::setRegister(int registerAdress,int newValue)
{
	registers[registerAdress] = newValue ;
}

int CPU::getRegister(int registerAdress)
{
	return registers[registerAdress];
}

int CPU::getPC()
{
	return programCounter;
}

void CPU::setPC(int newLine)
{
	programCounter = newLine;
}

void CPU::printRegisters()
{
	int i=0;

        cout <<"--------------------------------------------------------------------"
        << "------------------------------"<< endl ;

		cout<<instruction<<"   "<<input1<<"   "<<input2<<endl;	
	for(i=0;i<5;++i){
		cout <<"R"<<i+1<<" : "<< registers[i]<<"    ";
	}
	cout << endl<<endl;
}

bool CPU::halted(Memory myMemory)
{
	if(instruction == "HLT"){
			//when the instruction equal to halt ,prints memory and register values.  
	    cout <<"------------------------------------------PROGRAM-HALTED-----------"
    	<< "------------------------------"<< endl ;

	    printRegisters();
	 	myMemory.printMemory();
		return true;;
	}
	else
		return false;
}

void CPU::execute(string instructionLine,Memory& myMemory)
{
	upper = makeUpper(instructionLine);


	parseInstructionLine(upper);

	if(!checkSyntax(myMemory))
	{
		cerr<< "abort mission.syntax is down i repeat abort mission."<<endl;
		cerr<<"roger that"<<endl;
		exit(1);
	}


    //checks instructions and inputs then executes instruction.
    if (instruction == "MOV")
    {
        if (isRegister(input1))
        {
	        if (isRegister(input2))
		        mov1();
	        else if (isInt(input2))
		        mov2();
		    else if (myMemory.isMemoryAdress(input2))
		        mov3(myMemory);
		    
		    else
		    {
                cerr << "Cannot found executable function for this inputs. "<< endl;
		        exit(1);
		    }
		}
		else if (myMemory.isMemoryAdress(input1))
		{
		    if(isRegister(input2))
		        mov4(myMemory);
		    else if (isInt(input2))
		        mov5(myMemory);
		    else
		    {
                cerr << "Cannot found executable function for this inputs."<< endl;
		        exit(1);
		    }		
		}
	    else
	    {
            cerr << "Wrong input "<< endl;
		        exit(1);
	    }
    }
    else if (instruction == "ADD")
    {
        if (isRegister(input1))
	        if (isRegister(input2))
		        add1();
	        else if (isInt(input2))
		        add2();
		    else if (myMemory.isMemoryAdress(input2))
		        add3(myMemory);
		    
		    else
		    {
                cerr << "Cannot found executable function for this inputs."<< endl;
		        exit(1);
		    }
    }

    else if (instruction == "SUB") 
    {
        if (isRegister(input1))
	        if (isRegister(input2))
		        sub1();
	        else if (isInt(input2))
		        sub2();
		    else if (myMemory.isMemoryAdress(input2))
		        sub3(myMemory);
		    else
		    {
                cerr << "Cannot found executable function for this inputs. "<< endl;
		        exit(1);
		    }
            
    }
    else if (instruction == "JMP") 
    {
        if (isRegister(input1) && isInt(input2) ) 
		        jmp1();
        else if (isInt(input1) && (input2) == "EMPTY")
		        jmp2();
	    else
	    {
            cerr << "Cannot found executable function for this inputs."<< endl;
		        exit(1);
		}

    }
    else if (instruction == "JPN")
    {
        if (isRegister(input1) && isInt(input2) ) 
		        jpn(myMemory);    
	    else
	    {
            cerr << "Cannot found executable function for this inputs."<< endl;
	        exit(1);
	    }    
    }
    else if (instruction == "PRN" && input2 == "EMPTY") 
    {
        if (isRegister(input1))
	        prn1();
        else if (isInt(input1))
	        prn2();
        else if(myMemory.isMemoryAdress(input1))
            prn3(myMemory);
	    
   		else
	    {
            cerr << "Cannot found executable function for this inputs. "<< endl;
		        exit(1);
	    }
    }

    if(instruction != "JMP" && instruction !="JPN")
    {
    	setPC(programCounter+1);
    }
}



void CPU::parseInstructionLine(string line)
{
	
	int i;

    //Skips spaces
	for (i = 0; line[i] == ' '; i++)
		;
	line = &line[i];

    //Gets instruction
	for (i = 0; line[i] != ' '; i++)
		;
	instruction = line.substr(0, i);
	line = &line[i];
	
	//Skips spaces
	for (i = 0; line[i] == ' '; i++)
		;
	line = &line[i];

    //Gets input1
	for (i = 0;  line[i] != ',' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0' ; i++)
		;
	input1 = line.substr(0, i);
    
    //Skips spaces
    if(line[i]==' ')
    {
		line = &line[i];
		for (i = 0;line[i] == ' '; i++)
			;        
    }
	
	line = &line[i];
	i=0;
    
    //Checks second input if it exist gets it else fills input2 as EMPTY 
	if (line[i] == ',') 
	{
	
		for (i = 0; line[i] == ',' || line[i] == ' '; i++)
			;
		line = &line[i];
		for (i = 0; line[i] != ' ' && line[i] != '\n' && line[i] != '\0'&& line[i] != ';'; i++)
			;
		input2 = line.substr(0, i);
		line = &line[i];
	}
	else
		input2 = "EMPTY";
    
    if(instruction == "HLT")
    {	
        input1 = "EMPTY";
		input2 = "EMPTY";        
    }

    for (i = 0; line[i] == ' '; i++)
			;
    
    line = &line[i];
    i=0;

    if(line[i] != '\n' && line[i] != '\0' && line[i] != ';'){
    	cerr << "Wrong syntax"<<endl;
    	exit(1);
    }

}


void CPU::mov1()
{ 
	setRegister(getRegisterAdress(input2),getRegister(getRegisterAdress(input1))) ;
}

void CPU::mov2()
{
	setRegister(getRegisterAdress(input1),strToInt(input2)) ;
}

void CPU::mov3(Memory& myMemory)
{
    myMemory.setMemory(myMemory.getMemoryAdress(input2),getRegister(getRegisterAdress(input1)));
}
void CPU::mov4(Memory& myMemory)
{
    setRegister(getRegisterAdress(input2),myMemory.getMemory(myMemory.getMemoryAdress(input1))) ;

}
void CPU::mov5(Memory& myMemory)
{
    myMemory.setMemory( myMemory.getMemoryAdress(input1) , strToInt(input2)) ;

}

void CPU::add1() 
{
	setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))+getRegister(getRegisterAdress(input2)));
}

void CPU::add2() 
{
	setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))+strToInt(input2));
}
void CPU::add3(Memory& myMemory) 
{
    setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))+ myMemory.getMemory(myMemory.getMemoryAdress(input2)));
}


void CPU::sub1() 
{
	setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))-getRegister(getRegisterAdress(input2)) );
}

void CPU::sub2() 
{
	setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))-strToInt(input2));
}
void CPU::sub3(Memory& myMemory) 
{
    setRegister(getRegisterAdress(input1),getRegister(getRegisterAdress(input1))-myMemory.getMemory(myMemory.getMemoryAdress(input2)));
}

//If register is equal to 0 it jumps to line adress in file .
void CPU::jmp1() 
{
    if(getRegister(getRegisterAdress(input1)) == 0)
        setPC(strToInt(input2));
    
    else
    	setPC(programCounter+1);
}
//Jumps to given line adress in file.
void CPU::jmp2() 
{
    setPC(strToInt(input1));
}

//If register <= 0  it jumps to line adress in file .
void CPU::jpn(Memory& myMemory) 
{
    if(getRegister(getRegisterAdress(input1)) <= 0)
        setPC(strToInt(input2));   
    
    else
    	setPC(programCounter+1);
}

// This functions prints given item
void CPU::prn1() 
{
	cout << getRegister(getRegisterAdress(input1)) << endl;
}
void CPU::prn2() 
{
	cout << input1 << endl;
}

void CPU::prn3(Memory& myMemory)
{
	cout << myMemory.getMemory(myMemory.getMemoryAdress(input1)) << endl;
}


int CPU::getRegisterAdress(string reg)
{
    return reg[1]-'1';
}    

//Converts given integer string to an integer.
int CPU::strToInt(string number) 
{
	int i, convertedInt = 0;

	for ((number[0]=='-') ? i=1 : i=0; i < number.size(); ++i)
		convertedInt = number[i] - '0' + convertedInt * 10;

	(number[0]=='-') ? convertedInt*= -1 : convertedInt*=1;

	return convertedInt;
}

//Checks string, if it is an integer number it returns true
bool CPU::isInt(string input_) 
{
	int i = 0;

	for ( i = 0; i < input_.size() ; i++)
	{
		if ((input_[i] < '0' || input_[i] > '9') && input_[0] != '-')
			return false;
	}
	return true;
}

//Checks characters in string if it is lower case makes it upper case.
string CPU::makeUpper(string instructionLine) 
{
	int i;

	for (i = 0; (instructionLine).size() > i; ++i) 
		if (instructionLine[i] <= 'z' && instructionLine[i] >= 'a')
			instructionLine[i] -= ('a'-'A'); 
		return instructionLine;
}

bool CPU::checkSyntax(Memory myMemory)
{
    if((instruction=="JMP" || instruction=="JPN" || instruction=="ADD" || 
       instruction=="SUB" || instruction=="PRN" || instruction=="MOV"|| instruction =="HLT")&&
       (isInt(input1)||myMemory.isMemoryAdress(input1)||isRegister(input1)||input1=="EMPTY") &&
        (isInt(input2)||myMemory.isMemoryAdress(input2)||isRegister(input2)||input2=="EMPTY")
     )
        return true;
    else
        return false;
}
// checks item if it is a register it returns true ,else returns false.
bool CPU::isRegister(string item)
{
	if (item[0] == 'R' && (item[1] >= '1' && item[1] <= '5')&& item.size()==2)
		return true;  
	else
		return false;
}
