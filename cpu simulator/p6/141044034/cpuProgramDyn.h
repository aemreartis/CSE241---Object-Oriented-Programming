#ifndef CPUProgramDyn_h
#define	CPUProgramDyn_h

#include "requiredIncs.h"

using namespace std;

namespace dynamicC {
    class CPUProgramDyn
    {
    public:

        CPUProgramDyn();
        CPUProgramDyn(int option);
        CPUProgramDyn(string fileName);

        CPUProgramDyn(const CPUProgramDyn & p1);
        ~CPUProgramDyn();
        CPUProgramDyn& operator=(const CPUProgramDyn & p1);	

        int getOpt()const;
        void setOpt(int num);

        string getLine(int line);
        int size();
        void ReadFile(string fileName);


        string operator[](int line);
        friend  CPUProgramDyn operator+(const CPUProgramDyn& p1,const string newLine);
        CPUProgramDyn operator+=(const string newLine);
        friend  CPUProgramDyn operator+(const CPUProgramDyn& p1,const CPUProgramDyn& p2);
        bool operator ==(const CPUProgramDyn& p1);
        bool operator !=(const CPUProgramDyn& p1);
        bool operator <=(const CPUProgramDyn& p1);
        bool operator >=(const CPUProgramDyn& p1);
        bool operator >(const CPUProgramDyn& p1);
        bool operator <(const CPUProgramDyn& p1);
        friend ostream & operator<<(ostream &output , const CPUProgramDyn & p1);
        CPUProgramDyn operator()(int i1, int i2);

        CPUProgramDyn operator--(); // prefix
        CPUProgramDyn operator--(int);//post fix
    private:
        string* lines;
        int line;
        int opt;


    };

}
#endif
