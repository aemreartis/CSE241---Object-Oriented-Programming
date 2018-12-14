#ifndef cpuProgram_h
#define	cpuProgram_h

#include "requiredIncs.h"

using namespace std;

class CPUProgram
{
public:

	CPUProgram();
	CPUProgram(int option);
	CPUProgram(string fileName);
	
	int getOpt()const;
	void setOpt(int num);

	string getLine(int line);
	int size();
	void ReadFile(string fileName);


	string operator[](int line);
	friend  CPUProgram operator+(const CPUProgram& p1,const string newLine);
	CPUProgram operator+=(const string newLine);
	friend  CPUProgram operator+(const CPUProgram& p1,const CPUProgram& p2);
	bool operator ==(const CPUProgram& p1);
	bool operator !=(const CPUProgram& p1);
	bool operator <=(const CPUProgram& p1);
	bool operator >=(const CPUProgram& p1);
	bool operator >(const CPUProgram& p1);
	bool operator <(const CPUProgram& p1);
	friend ostream & operator<<(ostream &output , const CPUProgram & p1);
	CPUProgram operator()(int i1, int i2);

	CPUProgram operator--(); // prefix
	CPUProgram operator--(int);//post fix
private:
	vector<string> lines;
	int line;
	int opt;


};

#endif