#include <string>
#include<iostream>
#include<fstream>
using namespace std;

bool parseString(string line, string* instruction, string* input1, string* input2);
bool isRegister(string item);
bool isInt(string input2);
int strToInt(string number);
void makeUpper(string* line);
void mov1(int* register1, int* register2) ;
void mov2(int* register1, int constant) ;
void add1(int* register1, int* register2) ;
void add2(int* register1, int constant) ;
void sub1(int *register1, int* register2) ;
void sub2(int* register1, int constant) ;
void jmp1(int register1, int lineAdress,ifstream& file);
void jmp2(int lineAdress, ifstream& file);
void prn1(int reg) ;
void prn2(string constant) ;
int getRegisterAdress(string reg);
void executeInstruction(string line,string* instruction,string* input1,string* input2,int* r,ifstream& insFile);

int main(int argc,char** argv) 
{
	string line, instruction,input1,input2;
	int r[5] = {0,0,0,0,0};
	ifstream insFile(argv[1]);
	
	do{	
        //Gets lines from file.
        getline(insFile, line);		
        //makes uppercase all leters in line.
        makeUpper(&line);
        
        //Parses line to instructions and inputs ,if it successful continues
	    if (parseString(line, &instruction, &input1, &input2) == true) 
	    {
	        //Executes instruction.
		    executeInstruction(line, &instruction,&input1,&input2,r,insFile);
		  
		  //Checks option that given from terminal.
		  //If it equal to 1 it prints instructions and register values ,
		  //If it equals to 0 it just executes instructions.
		  //else gives error.
          if(strToInt(argv[2]) == 1){              		           
	            cout << instruction << " "<< input1<< ", " << input2 ;	
                cout << " - R1="<< r[0] <<", R2=" << r[1]<< ", R3=" <<r[2];
                cout<< ", R4="<< r[3]<< ", R5="<< r[4]<<endl;
          }
          else if(strToInt(argv[2]) != 0){
                cerr<< "UNKNOWN OPTİON.THE OPTİON MUST BE 0 OR 1"<< endl;
                return 0 ;
           }
	    }
	    else{
		    cerr << "WRONG SYNTAX ";
	        return 0;
	    }
	} while (instruction != "HLT");
 
	return 0;
}
//This function gets a command line and parses it to instruction and inputs.
bool parseString(string line, string* instruction,string *input1,string *input2) {
	
	int i;

    //Skips spaces
	for (i = 0; line[i] == ' '; i++)
		;
	line = &line[i];

    //Gets instruction
	for (i = 0; line[i] != ' '; i++)
		;
	*instruction = line.substr(0, i);
	line = &line[i];
	
	//Skips spaces
	for (i = 0; line[i] == ' '; i++)
		;
	line = &line[i];

    //Gets input1
	for (i = 0;  line[i] != ',' && line[i] != ' '; i++)
		;
	*input1 = line.substr(0, i);
    
    //Skips spaces
    if(line[i]==' ')
    {
		line = &line[i];
		for (i = 0;line[i] == ' '; i++)
			;        
    }
    
    //Checks second input if it exist gets it else fills input2 as EMPTY 
	if (line[i] == ',') 
	{
		line = &line[i];
		for (i = 0; line[i] == ',' || line[i] == ' '; i++)
			;
		line = &line[i];
		for (i = 0; line[i] != ' '; i++)
			;
		*input2 = line.substr(0, i);
	}
	else
		*input2 = "EMPTY";
		
	if((isInt(*input1)||isRegister(*input1))&& (isInt(*input2)||isRegister(*input2)|| (*input2)=="EMPTY"))
	    return true;
	else
	    return false;
}
//Checks characters in string if it is lower case makes it upper case.
void makeUpper(string* line) 
{
	int i;

	for (i = 0; (*line).size() > i; ++i) {
		if ((*line)[i] <= 'z' && (*line)[i] >= 'a')
			(*line)[i] -= 32;
	}
}
// checks item if it is a register it returns true else false
bool isRegister(string item)
{
	if (item[0] == 'R' && (item[1] >= '1' && item[1] <= '5')&& item.size()==2)
		return true;  
	else
		return false;
}

void executeInstruction(string line,string* instruction
    ,string* input1,string* input2,int* r,ifstream& insFile)
{
    //checks instructions and inputs then executes instruction
    if (*instruction == "MOV")
    {
        if (isRegister(*input1))
	        if (isRegister(*input2))
		        mov1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        mov2(&r[getRegisterAdress(*input1)], strToInt(*input2));
    }
    else if (*instruction == "ADD")
    {
        if (isRegister(*input1))
	        if (isRegister(*input2))
		        add1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        add2(&r[getRegisterAdress(*input1)], strToInt(*input2));
    }

    else if (*instruction == "SUB") 
    {
        if (isRegister(*input1))
	        if (isRegister(*input2))
		        sub1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        sub2(&r[getRegisterAdress(*input1)], strToInt(*input2));
    }
    else if (*instruction == "JMP") 
    {
        if (isRegister(*input1) &&isInt(*input2) ) 
		        jmp1(r[getRegisterAdress(*input1)], strToInt(*input2),insFile);
        
        else if (isInt(*input1) && *input2 == "EMPTY")
		        jmp2(strToInt(*input1),insFile);
    }
    else if (*instruction == "PRN" && *input2 == "EMPTY") 
    {
        if (isRegister(*input1))
	        prn1(r[getRegisterAdress(*input1)]);
        else if (isInt(*input1))
	        prn2(*input1);
    }
    else if(*instruction !="HLT"){
        cerr << "unknown instruction";
    }
}
/*****************************************************************************/

void mov1(int* register1, int* register2)
{
	*register2 = *register1;
}

void mov2(int* register1, int constant)
{
	*register1 = constant;
}

void add1(int* register1, int* register2) 
{
	*register1 += *register2;
}

void add2(int* register1, int constant) 
{
	*register1 += constant;
}

void sub1(int *register1, int* register2) 
{
	*register1 -= *register2;
}

void sub2(int* register1, int constant) 
{
	*register1 -= constant;
}
//if register1 is equal to 0 it jumps to line adress in file 
void jmp1(int register1, int lineAdress,ifstream& file) 
{
    int i =0;
    string garbage;
  
    if(register1 == 0)
    {
        file.seekg (0, file.beg);
        for(i=0;i<lineAdress -1;i++)
            getline(file, garbage);
    }
}
//Jump to given line adress in file
void jmp2(int lineAdress, ifstream& file) 
{
    string garbage ;
    int i ;
  
    file.seekg (0, file.beg);
            for(i=0;i<lineAdress-1;i++)
            getline(file, garbage);
}
// This functions prints given item
void prn1(int reg) 
{
	cout << reg << endl;
}
void prn2(string constant) 
{
	cout << constant << endl;
}

int getRegisterAdress(string reg)
{
    return reg[1]-'1';
}    

//Converts given integer string to an integer.
int strToInt(string number) 
{
	int i, convertedInt = 0;

	for ((number[0]=='-') ? i=1 : i=0; i < number.size(); ++i)
		convertedInt = number[i] - '0' + convertedInt * 10;

	(number[0]=='-') ? convertedInt*= -1 : convertedInt*=1;

	return convertedInt;
}

//Checks string, if it is an integer number it returns true
bool isInt(string input2) 
{
	int i = 0;

	for ( i = 0; i < input2.size() ; i++)
	{
		if (input2[i] <= '0' && input2[i] >= '9'&& input2[0] != '-')
			return false;
	}
	return true;
}
