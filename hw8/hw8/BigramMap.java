
import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
 

public class BigramMap<T> implements Bigram<T>{

    private int dType;    
    private Map<Integer,Pair> Bigrams = new HashMap() ;
    Object[] Data ; 
    BigramMap(int dataType){
        dType =dataType;
    }
    
    @Override
    public void readFile(String fileName)throws IOException
    {
        String dataLine;
                
        try(InputStream fileIS = new FileInputStream(fileName);
        InputStreamReader ISReader = new InputStreamReader(fileIS);
        BufferedReader BReader = new BufferedReader(ISReader);){
        while((dataLine =BReader.readLine()) !=null)
            Data = dataLine.split(" ");          
        }
  
        for(int i=0;i < Data.length - 1;i++){

            Pair temp = new Pair();
            temp.first = Data[i];
            temp.second = Data[i+1];
            Bigrams.put(i,temp);
        }
    }
     
    @Override
    public int numGrams()
    {
         return Bigrams.size(); 
    }
    
    @Override
    public int numOfGrams(T p1 , T p2)
    {
        int count=0;
        
        for(int i=0;i<Bigrams.size();i++)
        {
            if(p1.toString().equals(Bigrams.get(i).first.toString()) && p2.toString().equals( Bigrams.get(i).second.toString()))
                ++count;
        }
    

    return count;
    }
    @Override
    public String toString() 
{

    int tempIndex=-1;
    int tempOccurence=0;

    Pair tempP=new Pair();
    Pair tempPB = new Pair();
    Map <Integer , Pair > tempB = new HashMap(); 

    tempB.putAll(Bigrams);
      

    for(int j=0;j<tempB.size();j++){
        for(int i =j;i< tempB.size();i++)
        {
            if(numOfGrams((T)tempB.get(i).first , (T)tempB.get(i).second ) > tempOccurence )
            {
                tempOccurence = numOfGrams((T)tempB.get(i).first,(T)tempB.get(i).second);
                tempIndex = i ;
            }
        }
        
        tempP.first=tempB.get(tempIndex).first;
        tempP.second=tempB.get(tempIndex).second;
        
        tempB.get(tempIndex).first=tempB.get(j).first;
        tempB.get(tempIndex).second=tempB.get(j).second;

        tempB.get(j).first=tempP.first;
        tempB.get(j).second=tempP.second;
        tempOccurence=0;
    }

    
    for(int i =0 ; i<Bigrams.size();i++)
    {
        System.out.print("Bigram = " + tempB.get(i).first+ "--"+tempB.get(i).second );
        System.out.print("Occurence: " + numOfGrams((T)tempB.get(i).first,(T)tempB.get(i).second)); 

        i+=numOfGrams((T)tempB.get(i).first,(T)tempB.get(i).second);
    }
    return "";
}
}
