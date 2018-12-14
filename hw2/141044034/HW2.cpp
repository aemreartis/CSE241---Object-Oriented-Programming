#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int strToInt(string number);
int getMemoryAdress(string input2);
int getRegisterAdress(string reg);
bool isInt(string input2);
bool isMemoryAdress(string input_);
bool isRegister(string item);
bool checkSyntax(string instruction,string input1,string input2);
bool executeInstruction(string line,string* instruction,string* input1, 
                        string* input2,int* r,unsigned int* m,int* i);
void mov1(int* register1, int* register2) ;
void mov2(int* register1, int constant) ;
void mov3(int* register_ , unsigned int* memory);
void mov4(unsigned int* memory, int*  register_ );
void mov5(unsigned int* memory, int constant );  
void add1(int* register1, int* register2) ;
void add2(int* register1, int constant) ;
void add3(int* register1, unsigned int* memory) ;
void sub1(int *register1, int* register2) ;
void sub2(int* register1, int constant) ;
void sub3(int* register1, unsigned int* memory) ;
void jmp1(int register1, int lineAdress,int* i);
void jmp2(int lineAdress, int* i);
void jpn(int register1, int lineAdress,int* i); 
void prn1(int reg) ;
void prn2(string constant) ;
void prn3(unsigned int memory);

void parseString(string line, string* instruction, string* input1, string* input2);
void makeUpper(string* line);
void printMemory(unsigned int* memory,const int SIZE_OF_MEMORY_ARRAY);
void printRegisters(int* registers, const int SIZE_OF_REGISTER_ARRAY);


int main(int argc,char** argv) 
{
	const int TXT_LINE_SIZE =200;
	const int SIZE_OF_REGISTER_ARRAY = 5;
	const int SIZE_OF_MEMORY_ARRAY =50 ;
	const int OPTION =2;
	const int INSTRUCTION_FILE =1;

	string lines[TXT_LINE_SIZE];
	string instruction,input1,input2;
	int r[SIZE_OF_REGISTER_ARRAY] = {0,0,0,0,0};//register
	unsigned int m[SIZE_OF_MEMORY_ARRAY]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//memory
	int line=0;
	
	//Opens instruction file , if it fails , program ends.
	ifstream insFile(argv[INSTRUCTION_FILE]);
    if(insFile.is_open() == false)
    {
        cerr << "Can not open file" << endl;
        return 0;
    }
    
    //Checks option , if it is not equal to 1,2 or 0 ,program ends.
    if (strToInt(argv[OPTION]) !=1 && strToInt(argv[OPTION]) !=2 && strToInt(argv[OPTION]) !=0)
    {
        cerr << "Unknown option.Try 0, 1 or 2. "<<endl;
        return 0;
    }
	
    while(!insFile.eof()){
        getline(insFile, lines[line]);		
        ++line;
    }
    insFile.close();

    if(line >= TXT_LINE_SIZE)// program ends if the txt file has more than 200 lines .
        return 0;    
	else
	    line=0;
	
	do
	{	
        //makes uppercase all leters in line.
        makeUpper(&lines[line]);
        
        //Parses line to instruction and inputs 
	    parseString(lines[line], &instruction, &input1, &input2);

        //Checks instruction and inputs.
	    if( checkSyntax(instruction,input1,input2)== false )
	    {
            cerr << "Wrong syntax."<<endl;    
            return 0;    	
	    }   

        //If the option is equal to 1 (or 2) it prints instructions and register values .
        if(strToInt(argv[OPTION]) == 1 || strToInt(argv[OPTION]) == 2)
        {      
	        cout <<"------------------------------------------------------------"
	        << "--------------------------------------"<< endl ;	                    		           
	        cout <<endl<< instruction << " "<< input1<< ", " << input2 << endl ;	
            printRegisters(r,SIZE_OF_REGISTER_ARRAY);          
        }
        
	    //Executes instruction.
	    if(executeInstruction(lines[line], &instruction, &input1, &input2, r, m, &line) == false )
	        return 0;
        
        //If the option is equal to 2 prints memory values.
        if(strToInt(argv[OPTION]) == 2)
            printMemory(m,SIZE_OF_MEMORY_ARRAY);                        

	    ++line;
	}while (instruction != "HLT");
	
	//when the instruction equal to halt ,prints memory and register values.  
    cout <<"------------------------------------------PROGRAM-HALTED-----------"
    << "------------------------------"<< endl ;
    printMemory(m,SIZE_OF_MEMORY_ARRAY);    
    printRegisters(r,SIZE_OF_REGISTER_ARRAY);
 
	return 0;
}

//This function gets a command line and parses it to instruction and inputs.
void parseString(string line, string* instruction,string *input1,string *input2)
{
	
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
	for (i = 0;  line[i] != ',' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0' ; i++)
		;
	*input1 = line.substr(0, i);
    
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
		*input2 = line.substr(0, i);
		line = &line[i];
	}
	else
		*input2 = "EMPTY";
    
    if(*instruction == "HLT")
    {	
        *input1 = "EMPTY";
		*input2 = "EMPTY";        
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
//Checks parameters.
bool checkSyntax(string instruction,string input1,string input2)
{
    if((instruction=="JMP" || instruction=="JPN" || instruction=="ADD" || 
       instruction=="SUB" || instruction=="PRN" || instruction=="MOV"|| instruction =="HLT")&&
       (isInt(input1)||isMemoryAdress(input1)||isRegister(input1)||input1=="EMPTY") &&
        (isInt(input2)||isMemoryAdress(input2)||isRegister(input2)||input2=="EMPTY")
     )
        return true;
    else
        return false;
}

//Checks characters in string if it is lower case makes it upper case.
void makeUpper(string* line) 
{
	int i;

	for (i = 0; (*line).size() > i; ++i) 
		if ((*line)[i] <= 'z' && (*line)[i] >= 'a')
			(*line)[i] -= ('a'-'A'); 
}
// checks item if it is a register it returns true ,else returns false.
bool isRegister(string item)
{
	if (item[0] == 'R' && (item[1] >= '1' && item[1] <= '5')&& item.size()==2)
		return true;  
	else
		return false;
}

bool executeInstruction(string line,string* instruction
    ,string* input1,string* input2,int* r,unsigned int* m,int* i)//r =register ,m=memory , i = line.
{
    //checks instructions and inputs then executes instruction.
    if (*instruction == "MOV")
    {
        if (isRegister(*input1))
        {
	        if (isRegister(*input2))
		        mov1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        mov2(&r[getRegisterAdress(*input1)], strToInt(*input2));
		    else if (isMemoryAdress(*input2))
		        mov3(&r[getRegisterAdress(*input1)],&m[getMemoryAdress(*input2)]);
		    else
		    {
                cerr << "Cannot found executable function for this inputs. "<< endl;
		        return false;
		    }
		}
		else if (isMemoryAdress(*input1))
		{
		    if(isRegister(*input2))
		        mov4(&m[getMemoryAdress(*input1)] , &r[getRegisterAdress(*input2)]);
		    else if (isInt(*input2))
		        mov5(&m[getMemoryAdress(*input1)] , strToInt(*input2));
		    else
		    {
                cerr << "Cannot found executable function for this inputs."<< endl;
		        return false;
		    }		
		}
	    else
	    {
            cerr << "Wrong input "<< endl;
	        return false;
	    }
    }
    else if (*instruction == "ADD")
    {
        if (isRegister(*input1))
	        if (isRegister(*input2))
		        add1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        add2(&r[getRegisterAdress(*input1)], strToInt(*input2));
		    else if (isMemoryAdress(*input2))
		        add3(&r[getRegisterAdress(*input1)] , &m[getMemoryAdress(*input2)]);
		    else
		    {
                cerr << "Cannot found executable function for this inputs."<< endl;
		        return false;
		    }
    }

    else if (*instruction == "SUB") 
    {
        if (isRegister(*input1))
	        if (isRegister(*input2))
		        sub1(&r[getRegisterAdress(*input1)], &r[getRegisterAdress(*input2)]);
	        else if (isInt(*input2))
		        sub2(&r[getRegisterAdress(*input1)], strToInt(*input2));
		    else if (isMemoryAdress(*input2))
		        sub3(&r[getRegisterAdress(*input1)] , &m[getMemoryAdress(*input2)]);
		    else
		    {
                cerr << "Cannot found executable function for this inputs. "<< endl;
		        return false;
		    }
            
    }
    else if (*instruction == "JMP") 
    {
        if (isRegister(*input1) &&isInt(*input2) ) 
		        jmp1(r[getRegisterAdress(*input1)], strToInt(*input2),i);
        else if (isInt(*input1) && (*input2) == "EMPTY")
		        jmp2(strToInt(*input1),i);
	    else
	    {
            cerr << "Cannot found executable function for this inputs."<< endl;
	        return false;
		}

    }
    else if (*instruction == "JPN")
    {
        if (isRegister(*input1) &&isInt(*input2) ) 
		        jpn(r[getRegisterAdress(*input1)], strToInt(*input2),i);    
	    else
	    {
            cerr << "Cannot found executable function for this inputs."<< endl;
	        return false;
	    }    
    }
    else if (*instruction == "PRN" && *input2 == "EMPTY") 
    {
        if (isRegister(*input1))
	        prn1(r[getRegisterAdress(*input1)]);
        else if (isInt(*input1))
	        prn2(*input1);
        else if(isMemoryAdress(*input1))
            prn3(m[getMemoryAdress(*input1)]);
	    else
	    {
            cerr << "Cannot found executable function for this inputs. "<< endl;
	        return false;
	    }
    }
    
    return true;
}

void mov1(int* register1, int* register2)
{
	*register2 = *register1;
}

void mov2(int* register_, int constant)
{
	*register_ = constant;
}
void mov3(int* register_ , unsigned int* memory)
{
    *memory = *register_ ;
}
void mov4(unsigned int* memory, int*  register_ )
{
    *register_ = *memory ;
}
void mov5(unsigned int* memory, int constant )
{
    *memory = constant ;
}

void add1(int* register1, int* register2) 
{
	*register1 += *register2;
}

void add2(int* register_, int constant) 
{
	*register_ += constant;
}

void add3(int* register1, unsigned int* memory) 
{
    *register1 += *memory;
}

void sub1(int *register1, int* register2) 
{
	*register1 -= *register2;
}

void sub2(int* register_, int constant) 
{
	*register_ -= constant;
}
void sub3(int* register1, unsigned int* memory) 
{
    *register1 -= *memory ;
}
//If register1 is equal to 0 it jumps to line adress in file .
void jmp1(int register1, int lineAdress,int* i) 
{
    if(register1 == 0)
    {
        *i = lineAdress-2;   //array starts from 0 but txt lines start from 1 (-1)and main program adds 1 to i for execute next instruction (-1).
    }
}
//Jumps to given line adress in file.
void jmp2(int lineAdress, int* i) 
{
    *i = lineAdress-2;
}
void jpn(int register1, int lineAdress,int* i) 
{
    if(register1 <= 0)
    {
        *i = lineAdress-2;   
    }
            
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
void prn3(unsigned int memory) 
{
	cout << memory << endl;
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
bool isInt(string input_) 
{
	int i = 0;

	for ( i = 0; i < input_.size() ; i++)
	{
		if ((input_[i] < '0' || input_[i] > '9') && input_[0] != '-')
			return false;
	}
	return true;
}
//If the input is a memory adress return true, else return false.
bool isMemoryAdress(string input_)
{
    if(input_[0] == '#')
        return isInt(&(input_[1]));
    else
        return false;    
}

int getMemoryAdress(string input_)
{
        return strToInt(&(input_[1]));
}

void printMemory(unsigned int* memory, const int SIZE_OF_MEMORY_ARRAY )
{
    int i ;
    
    cout<< endl;
    for(i=0;i<SIZE_OF_MEMORY_ARRAY;++i)
    {
        cout <<"#"<< i << " = "<< memory[i] <<"   ";
    	if(((i+1)%10)==0 )
    		cout<<endl;
    }
    cout << endl;    
}

void printRegisters(int* registers,const int SIZE_OF_REGISTER_ARRAY)
{
    int i ;
    cout<<endl;

    for(i=0;i<SIZE_OF_REGISTER_ARRAY;++i)
        cout << "R"<< i+1 << " = "<< registers[i] <<"   ";
    cout << endl;
}
