#include "requiredIncs.h"

using namespace std;

namespace dynamicC{
CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn & p1){
    line=p1.line;
    opt= p1.opt;
    lines= new string[line];
    
    for(int i = 0 ; i<line ;i++)
        lines[i]=p1.lines[i];
}

CPUProgramDyn::~CPUProgramDyn(){
   
    delete [] lines;
    lines = nullptr;
}

CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn & p1){
    if(&p1 != this){
        line = p1.line;
        opt = p1.opt;
        delete [] lines;
        lines = new string[line];
        for (int i=0; i< line ;i++)
            lines[i]=p1.lines[i];
        
    }
    return *this ;
}
	

CPUProgramDyn::CPUProgramDyn()
{
	line=0;
	lines = new string[1];
}


CPUProgramDyn::CPUProgramDyn(int option)
{
	opt=option;
	line=0;
	lines = new string[1];
}


CPUProgramDyn::CPUProgramDyn(string fileName){
    line=0;
	ReadFile(fileName);
	lines = new string[1];

}
 int CPUProgramDyn::getOpt()const
{
    return opt;
}
void CPUProgramDyn::setOpt(int num)
{
    opt = num;
}
    

//READS FILE AND SAVES IT TO LINES ARRAY
void CPUProgramDyn::ReadFile(string fileName)
{
    delete [] lines;
    
	ifstream insFile(fileName);
    string instructionLine;//temp string

    if(insFile.is_open() == false)
    {
        cerr << "Can not open file" << endl;
        exit(1);
    }
    while(!insFile.eof() ) {
        getline(insFile, instructionLine);	
        line++;
    }
    --line;
    lines = new string [line];
    insFile.close();

    insFile.open(fileName);

    for(int i =0;i<line;i++ ) {
        getline(insFile, lines[i]);	
    }

    insFile.close();
}

string CPUProgramDyn::getLine(int nthline)
{

    return lines[nthline];
}

int CPUProgramDyn::size()
{
	return line;
}



string CPUProgramDyn::operator[](int nth)
{
    if(line <= nth)
    {
        cerr<< "that line doesnt exist"<< endl;
        return "";
    }    
    return lines[nth];
}

CPUProgramDyn operator+(const CPUProgramDyn& p1,const string newLine)
{
    CPUProgramDyn newProgram;

    newProgram = p1;
    delete [] newProgram.lines;
    newProgram.line ++;
    newProgram.lines = new string[newProgram.line];
    for(int i=0;i<p1.line;i++)
        newProgram.lines[i] = p1.lines[i];
    newProgram.lines[newProgram.line - 1] = newLine;
                    
    return newProgram;
}


CPUProgramDyn CPUProgramDyn::operator+=(const string newLine)
{
    if(newLine== ""){
        CPUProgramDyn p1;
        cerr<< "empty line"<<endl;
        return p1 ;
    }
    string temp[line];
    
    for (int i = 0 ; i< line ; i++)
        temp[i]= lines[i];
        
    delete [] lines;
    ++line;
    lines = new string[line];
    
    for(int i = 0 ; i< line - 1 ;i++)
        lines[i] = temp[i];
    
    lines[line-1] = newLine ;
    
    return *this;
}

 CPUProgramDyn operator+(const CPUProgramDyn& p1,const CPUProgramDyn& p2)
{
    CPUProgramDyn newProgram;
    int count = 0;
    
    newProgram.line = p1.line + p2.line ;
    delete [] newProgram.lines;
        
    newProgram.setOpt(p1.getOpt());

    newProgram.lines = new string[newProgram.line];

    for(int i=0; i < p1.line ; i++){
        newProgram.lines[i] = p1.lines[i] ;
        ++count;
    }

    for(int j=0; j < p2.line ; j++){
        newProgram.lines[count] = p2.lines[j];
        ++count;
    }

    return newProgram;
}

bool CPUProgramDyn::operator ==(const CPUProgramDyn& p1)
{
    if(line==p1.line)
        return true;
    else    
        return false;
}


bool CPUProgramDyn::operator !=(const CPUProgramDyn& p1)
{
    if(line!=p1.line)
        return true;
    else    
        return false;
}

bool CPUProgramDyn::operator <=(const CPUProgramDyn& p1)
{
    if(line<=p1.line)
        return true;
    else    
        return false;
}

bool CPUProgramDyn::operator >=(const CPUProgramDyn& p1)
{
    if(line>=p1.line)
        return true;
    else    
        return false;
}

bool CPUProgramDyn::operator >(const CPUProgramDyn& p1)
{
    if(line>p1.line)
        return true;
    else    
        return false;
}

bool CPUProgramDyn::operator <(const CPUProgramDyn& p1)
{
    if(line<p1.line)
        return true;
    else    
        return false;
}


CPUProgramDyn CPUProgramDyn::operator--() // prefix
{
    --line;
    string temp[line];
    for(int i=0;i<line;i++)
        temp[i]= lines[i];
    
    delete [] lines;
    lines = new string[line];
    
    for (int i =0 ;i<line ;i++)
        lines[i] = temp[i];

    return *this;
}
CPUProgramDyn CPUProgramDyn::operator--(int)//post fix
{
    CPUProgramDyn p1;

    p1 = *this;
    
    --line;
    string temp[line];
    for(int i=0;i<line;i++)
        temp[i]= lines[i];
    
    delete [] lines;
    lines = new string[line];
    
    for (int i =0 ;i<line ;i++)
        lines[i] = temp[i];

    
    return p1;

}
CPUProgramDyn CPUProgramDyn::operator()(int i1, int i2)
{   

    CPUProgramDyn newProgram;
    int count = 0;
    
    if(i1<1 || i1>i2 || i2>line){
        cerr << "invalid index " << endl;
        return newProgram;
    }

    newProgram = *this;
    delete [] newProgram.lines;
    newProgram.line = i2 - i1 + 1;
    newProgram.lines = new string[newProgram.line];
    
    for (int i=i1-1;i<i2;i++ ){
        newProgram.lines[count] = lines[i];
        count++;
    }
    return newProgram;
}
ostream & operator<<(ostream &output , const CPUProgramDyn & p1)
{
    for(int i =0;i<p1.line;i++)
        cout << p1.lines[i]<<endl;

    return output;
}

}
