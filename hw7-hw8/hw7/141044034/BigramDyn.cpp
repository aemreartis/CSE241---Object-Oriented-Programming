#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Bigram.h"
#include "BigramDyn.h"

 using namespace std;

template <class T>
BigramDyn<T>::BigramDyn(){

	data = new T[1];
	bigrams =new pair<T,T>[1] ;
}

template <class T>
BigramDyn<T>::BigramDyn(int dType){

	data = new T[1];
	bigrams =new pair<T,T>[1] ;
	dataType=dType;	
}

template <class T>
BigramDyn<T>::~BigramDyn()
{
	delete [] data;
	delete [] bigrams;
}


template <class T>
void BigramDyn<T>::readFile(const char * fileName) throw(myexception)
{

    ifstream dataFile(fileName);

    T a;
    if(dataFile.is_open() == false)
    {
    	throw(exc);
    }
    
    dataSize=0;
    
    for(int i=0 ; !dataFile.eof();i++)
    {
       
        if(!(dataFile >> a))
        	throw(exc); 

        dataSize++;
    }        

    
    dataFile.seekg (0, dataFile.beg);

    data = new T[dataSize];
    bigrams = new pair<T,T>[dataSize-1];

    for(int i=0 ; !dataFile.eof();i++)
    {
        dataFile >> data[i];    
        /*if(a == false)
            throw()*/
    }   

    for(int i=0;i < dataSize-1;i++)
    {
        bigrams[i].first=data[i];
        bigrams[i].second=data[i+1];
    }    
}


template <class T>
int BigramDyn<T>::numGrams()
{
    return dataSize-1;// if we have n data , number of bigram equals n-1
}



template <class T>
int BigramDyn<T>::numOfGrams(T p1 , T p2)
{
    int count=0;
    pair<T ,T> check;
    check.first =p1;
    check.second=p2;

    for(int i=0;i<numGrams();i++)
    {

        if(check == bigrams[i])
            ++count;
    }

    return count;
}


template <class T>
pair<T,T> BigramDyn<T>::maxGrams()
{
    int tempIndex=-1;
    int tempOccurence=0;
    for(int i =0;i<numGrams();i++)
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
ostream& BigramDyn<T>::print(ostream& os) 
{

    int tempIndex=-1;
    int tempOccurence=0;
    int i;
    pair<T,T> tempP;
    pair<T,T> tempB[dataSize-1];


    for(i=0;i<numGrams();i++){
        tempB[i].first=bigrams[i].first;
        tempB[i].second=bigrams[i].second;
    }


    for(int j=0;j<numGrams();j++){
        for(int i =j;i<numGrams();i++)
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

    for(i =0 ; i<numGrams();i++)
    {
        os<<"Bigram = " << tempB[i].first << "--"<<tempB[i].second <<endl;
        os<< "Occurence: " << numOfGrams(tempB[i].first,tempB[i].second)<<endl; 

        i+=numOfGrams(tempB[i].first,tempB[i].second)-1;
    }
    return os;
}