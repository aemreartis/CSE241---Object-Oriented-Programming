#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Bigram.h"
#include "BigramMap.h"

using namespace std;
template <class T>
void BigramMap<T>::readFile(const char* fileName)throw(myexception)
{
    ifstream dataFile(fileName);
    if(dataFile.is_open() == false)
    {
        throw(exc);
    }
    //bool a;
     for(int i=0 ; !dataFile.eof();i++){
        if(!(dataFile >> data[i]))
            throw(exc);
        /*if(a == false)
            throw()*/
    }    

    for(int i=0;i < data.size()-1;i++){

        bigrams[i].first=data[i];
        bigrams[i].second=data[i+1];
    
    }
}

template <class T>
int BigramMap<T>::numGrams()
{
    return bigrams.size();
}

template <class T>
int BigramMap<T>::numOfGrams(T p1 , T p2)
{
    int count=0;
    pair<T ,T> check;
    check.first =p1;
    check.second=p2;

    for(int i=0;i<bigrams.size();i++)
    {

        if(check == bigrams[i])
            ++count;
    }

    return count;
}


template <class T>
pair<T,T> BigramMap<T>::maxGrams()
{
    int tempIndex=-1;
    int tempOccurence=0;
    for(int i =0;i<bigrams.size();i++)
    {

        if(numOfGrams(bigrams[i].first,bigrams[i].second) > tempOccurence )
        {
            tempOccurence = numOfGrams(bigrams[i].first,bigrams[i].second);
            tempIndex = i ;
        }
    }
    return bigrams[tempIndex];
}


template <class T>
ostream& BigramMap<T>::print(ostream& os) 
{

    int tempIndex=-1;
    int tempOccurence=0;
    int i;
    pair<T,T> tempP;
    map <int , pair<T,T> > tempB; 

    for(i=0;i<bigrams.size();i++){
        tempB[i].first=bigrams[i].first;
        tempB[i].second=bigrams[i].second;
    }


    for(int j=0;j<tempB.size();j++){
        for(int i =j;i<tempB.size();i++)
        {
            if(numOfGrams(tempB[i].first,tempB[i].second) > tempOccurence )
            {
                tempOccurence = numOfGrams(tempB[i].first,tempB[i].second);
                tempIndex = i ;
            }
        }

        tempP.first=tempB[tempIndex].first;
        tempP.second=tempB[tempIndex].second;
        
        tempB[tempIndex].first = tempB[j].first;
        tempB[tempIndex].second = tempB[j].second;
        
        tempB[j].first = tempP.first;
        tempB[j].second = tempP.second;

        tempOccurence=0;
    }

    for(i =0 ; i<bigrams.size();i++)
    {
        os<<"Bigram = " << tempB[i].first << "--"<<tempB[i].second <<endl;
        os<< "Occurence: " << numOfGrams(tempB[i].first,tempB[i].second)<<endl; 

        i+=numOfGrams(tempB[i].first,tempB[i].second)-1;
    }
    return os;

}

template <class T>
BigramMap<T>::BigramMap(int dType){

    dataType=dType;

}