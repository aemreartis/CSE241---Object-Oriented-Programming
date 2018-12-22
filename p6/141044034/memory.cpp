#include "requiredIncs.h"

using namespace std;

Memory::Memory()
{
	int i ;
	for(i=0;i<50;++i)
		memory[i]=0;
}

Memory::Memory(int option)
{
	int i ;
	for(i=0;i<50;++i)
		memory[i]=0;
	opt=option;
}

unsigned int Memory::getMem(int memoryAdress)
{
	
	return memory[memoryAdress];
}
void Memory::setMem(int memoryAdress , unsigned int newValue)
{
	memory[memoryAdress] = newValue;

}


//If the input is a memory adress return true, else return false.
bool Memory::isMemoryAdress(string input_)
{
    if(input_[0] == '#')
        return isInt(&(input_[1]));
    else
        return false;    
}

int Memory::getMemoryAdress(string input_)
{
        return strToInt(&(input_[1]));
}


//CONVERTS GIVEN STRING TO INTEGER
int Memory::strToInt(string number) 
{
	int i, convertedInt = 0;

	for ((number[0]=='-') ? i=1 : i=0; i < number.size(); ++i)
		convertedInt = number[i] - '0' + convertedInt * 10;

	(number[0]=='-') ? convertedInt*= -1 : convertedInt*=1;

	return convertedInt;
}

//CHECKS GIVEN STRING IF IT IS AN INTEGER RETURNS TRUE
bool Memory::isInt(string input_) 
{
	int i = 0;

	for ( i = 0; i < input_.size() ; i++)
	{
		if ((input_[i] < '0' || input_[i] > '9') && input_[0] != '-')
			return false;
	}
	return true;
}


void Memory::printAll()
{
    int i ;
    
    cout<< endl;
    for(i=0;i<50;++i)
    {
        cout <<"#"<< i << " = "<< memory[i] <<"   ";
    	if(((i+1)%10)==0 )
    		cout<<endl;
    }
    cout << endl;    

        cout <<"--------------------------------------------------------------------"
        << "------------------------------"<< endl ;

}