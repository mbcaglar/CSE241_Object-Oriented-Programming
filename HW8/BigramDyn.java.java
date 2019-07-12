/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw8;

import java.io.File;
import java.io.FileNotFoundException;
import static java.lang.System.exit;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;
import java.lang.Exception;
import java.rmi.UnexpectedException;

/**
 *
 * @author BEDO
 */
public class BigramDyn<T> implements Bigram<T>
{

    
    private int size;
    private final int datatype;
    
    private T arr[];
    
    public BigramDyn(int type){
        
        arr =(T[]) new Objects[100];
        datatype=type;
    }

    @Override
        public void readFile(String file)throws Exception{
        
        int i=0;
        File inputFile = new File(file);
        
        
        try {
            Scanner inp= new Scanner(inputFile);
           
            
            if(datatype==1){
                
                Integer input = null;
                while(inp.hasNext()){
                    
                    if(inp.hasNextInt()){
                        input = inp.nextInt();
                        arr[i]=(T) input;
                        i++;
                    } 
                    else {
                     
                        
                    }
                }
            }
            else if(datatype==2){
            
               String input=inp.next();

                arr[i]=(T) input;
                i++;
                while(inp.hasNext()){
                    
                   
                    input = inp.next();
                    arr[i]=(T) input;
                    i++;
                }

            }
            else if(datatype==3){
            
                Double input = null;
                while(inp.hasNext()){
                    
                    if(inp.hasNextDouble()){
                        input = inp.nextDouble();
                        arr[i]=(T) input;
                        i++;
                    } 
                    else {
                     
                        
                    }
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
        
            if(arr[i].equals(first) && arr[i+1].equals(second)){
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
	
                pair.first=(T)arr[i];
                pair.second=(T)arr[i+1];
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
