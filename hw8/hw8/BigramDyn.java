import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;


public class BigramDyn <T> implements Bigram<T>{
    private Pair[] Bigrams;
    private String[] Data;
    BigramDyn(int dataType){

    }
    
    @Override
    public void readFile(String fileName) throws IOException
    {
        String dataLine;
        
        try(InputStream fileIS = new FileInputStream(fileName);
        InputStreamReader ISReader = new InputStreamReader(fileIS);
        BufferedReader BReader = new BufferedReader(ISReader);){
            while((dataLine =BReader.readLine()) !=null)
                Data = dataLine.split(" ");         
        }
        
        Bigrams = new Pair[(Data.length)-1];

        for(int i=0;i < Data.length-1;i++){
            Bigrams[i] = new Pair();
            Bigrams[i].set(1,Data[i]);
            Bigrams[i].set(2,Data[i+1]);
        }
        
    }
     
    @Override
    public int numGrams()
    {
         return Bigrams.length; 
    }
    
    @Override
    public int numOfGrams(T p1 , T p2)
    {
        int count=0;
        for(int i=0;i<Bigrams.length;i++)
        {

            if(p1.toString().equals(Bigrams[i].first.toString()) && p2.toString().equals( Bigrams[i].second.toString()))
                ++count;
        }
    return count;
    }
        @Override
    public String toString() 
{

    int tempIndex=-1;
    int tempOccurence=0;

    Pair tempP= new Pair();
    Pair tempPB = new Pair();
    Pair []tempB = new Pair[Bigrams.length]; 

    for(int i=0;i<Bigrams.length;i++)
        tempB[i] =Bigrams[i];
      

    for(int j=0;j<tempB.length;j++){
        for(int i =j;i< tempB.length;i++)
        {
            if(numOfGrams((T)tempB[i].first , (T)tempB[i].second ) > tempOccurence )
            {
                tempOccurence = numOfGrams((T)tempB[i].first,(T)tempB[i].second);
                tempIndex = i ;
            }
        }
        
        tempP.first=tempB[tempIndex].first;
        tempP.second=tempB[tempIndex].second;
        
        tempB[tempIndex].first=tempB[j].first;
        tempB[tempIndex].second=tempB[j].second;

        tempB[j].first=tempP.first;
        tempB[j].second=tempP.second;
        tempOccurence=0;
    }

    
    for(int i =0 ; i<Bigrams.length;i++)
    {
        System.out.print("Bigram = " + tempB[i].first+ "--"+tempB[i].second );
        System.out.print("Occurence: " + numOfGrams((T)tempB[i].first,(T)tempB[i].second)); 

        i+=numOfGrams((T)tempB[i].first,(T)tempB[i].second);
    }
    return "";
}
}
