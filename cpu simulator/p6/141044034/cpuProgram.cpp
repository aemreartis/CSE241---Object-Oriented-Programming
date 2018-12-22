#include "requiredIncs.h"

using namespace std;


CPUProgram::CPUProgram()
{
	line=0;
}


CPUProgram::CPUProgram(int option)
{
	opt=option;
	line=0;
}


CPUProgram::CPUProgram(string fileName){
	ReadFile(fileName);
}
 int CPUProgram::getOpt()const
{
    return opt;
}
void CPUProgram::setOpt(int num)
{
    opt = num;
}
    

//READS FILE AND SAVES IT TO LINES ARRAY
void CPUProgram::ReadFile(string fileName)
{

	ifstream insFile(fileName);
    string instructionLine;//temp string

    if(insFile.is_open() == false)
    {
        cerr << "Can not open file" << endl;
        exit(1);
    }
    while(!insFile.eof() ) {
        getline(insFile, instructionLine);	

        lines.push_back(instructionLine); //pushing line to vektor
    }
    insFile.close();
}

string CPUProgram::getLine(int nthline)
{

    return lines[nthline];
}

int CPUProgram::size()
{
	return lines.size();
}



string CPUProgram::operator[](int line)
{
    if(lines.size() <= line)
    {
        cerr<< "that line doesnt exist"<< endl;
        return "";
    }    
    return lines[line];
}

CPUProgram operator+(const CPUProgram& p1,const string newLine)
{
    CPUProgram newProgram;

    newProgram.setOpt(p1.getOpt());
    for(int i=0;i<p1.lines.size();i++)
        newProgram.lines.push_back(p1.lines[i]);

    newProgram.lines.push_back(newLine);

    return newProgram;
}


CPUProgram CPUProgram::operator+=(const string newLine)
{
    if(newLine== ""){
        cerr<< "empty line"<<endl;
        return *this;
    }

    lines.push_back(newLine);
    return *this;
}

 CPUProgram operator+(const CPUProgram& p1,const CPUProgram& p2)
{
    CPUProgram newProgram;
    int i ;

    newProgram.setOpt(p1.getOpt());
    for(i=0; i < p1.lines.size() ; i++)
        newProgram.lines.push_back(p1.lines[i]);

    for(i=0; i < p2.lines.size() ; i++)
        newProgram.lines.push_back(p2.lines[i]);

    return newProgram;
}

bool CPUProgram::operator ==(const CPUProgram& p1)
{
    if(lines.size()==p1.lines.size())
        return true;
    else    
        return false;
}


bool CPUProgram::operator !=(const CPUProgram& p1)
{
    if(lines.size()!=p1.lines.size())
        return true;
    else    
        return false;
}

bool CPUProgram::operator <=(const CPUProgram& p1)
{
    if(lines.size()<=p1.lines.size())
        return true;
    else    
        return false;
}

bool CPUProgram::operator >=(const CPUProgram& p1)
{
    if(lines.size()>=p1.lines.size())
        return true;
    else    
        return false;
}

bool CPUProgram::operator >(const CPUProgram& p1)
{
    if(lines.size()>p1.lines.size())
        return true;
    else    
        return false;
}

bool CPUProgram::operator <(const CPUProgram& p1)
{
    if(lines.size()<p1.lines.size())
        return true;
    else    
        return false;
}


CPUProgram CPUProgram::operator--() // prefix
{
    lines.pop_back();
    return *this;
}
CPUProgram CPUProgram::operator--(int)//post fix
{
    CPUProgram temp;

    temp.setOpt(getOpt());

    for(int i=0;i<lines.size();i++)
        temp.lines.push_back(lines[i]);

    lines.pop_back();
    return temp;

}
CPUProgram CPUProgram::operator()(int i1, int i2)
{   

    CPUProgram newProgram;
    
    if(i1<1 || i1>i2 || i2>lines.size()){
        cerr << "invalid index " << endl;
        return newProgram;
    }

    newProgram.setOpt(getOpt());
    for (int i=i1-1;i<i2;i++ )
        newProgram.lines.push_back(lines[i]);
    return newProgram;
}
ostream & operator<<(ostream &output , const CPUProgram & p1)
{
    for(int i =0;i<p1.lines.size();i++)
        cout << p1.lines[i]<<endl;

    return output;
}