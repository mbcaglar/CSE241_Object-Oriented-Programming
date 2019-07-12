/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw8;
import java.util.HashMap;
import java.util.Scanner;
import java.io.File;
import java.io.*;
import java.io.FileNotFoundException;
import java.lang.Exception;
import static java.lang.System.exit;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.util.Pair;
import java.rmi.UnexpectedException;
/**
 *
 * @author BEDO
 */
public class BigramMap<T> implements Bigram<T>
{

    private int size;
    private final int datatype;
    
    private final HashMap<Integer,Object> map=new HashMap();
    
    public BigramMap(int type){
        datatype=type;
    }

    @Override
        public void readFile(String file) throws Exception
        {
        
        int i=0;
        File inputFile = new File(file);
        
        
        try {
            Scanner inp= new Scanner(inputFile);
            
            while(inp.hasNext()){
            
            if(datatype==1){
            
            int input=inp.nextInt();
            map.put(i,input);
            i++;
            }
            else if(datatype==2){
            
            String input=inp.next();
            map.put(i,input);
            i++;
            }
            else if(datatype==3){
            
            double input=inp.nextDouble();
            map.put(i,input);
            i++;
            }    
            }
            size=i;
        }
        catch (FileNotFoundException ex) {
        
            throw new myException("Dosya açılamadı..!!!");
            }
        
        catch (NumberFormatException e){
    
        throw new myException("Formata uymayan yapi..HATA.!!!");
    }     
}
    @Override
    public int numGrams() {
        return size-1;
    }

    @Override
    public int numOfGrams(T first, T second) {
       
        int count=0;
        int i;
        for(i=0; i<size-1; i++){
        
            if(map.get(i).equals(first) && map.get(i+1).equals(second)){
                count++;
            }
        }
        return count;
    }
    
   public String toString(){
        
        int i;
        ArrayList< Mypair<T,T> > mypair = new ArrayList< Mypair<T,T> >();
        Mypair<T,T> pair= new Mypair<>();
        for(i=0; i<numGrams(); i++){
	
                pair.first=(T)map.get(i);
                pair.second=(T)map.get(i+1);
		mypair.add(pair);
	}
        for(i=0; i<size-1; i++){

            for(int j=0; j<numGrams()-1; j++){
		
                if(numOfGrams(mypair.get(j).first,mypair.get(j).second)<=
                   numOfGrams(mypair.get(j+1).first,mypair.get(j+1).second)){
                
                    Mypair<T,T> temp = new Mypair<>();
                    
                    temp=mypair.get(j);
                    mypair.set(j,mypair.get(j+1));
                    mypair.set(j+1, temp);
		}
            }
        }
        for(i=0; i<size-1; i++){
        System.out.printf("%s %s (%s)",mypair.get(i).first,mypair.get(i).second,numOfGrams(mypair.get(i).first,mypair.get(i).second));
    }
        return String.format("");
}
}

