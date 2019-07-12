/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw8;

/**
 *
 * @author BEDO
 * @param <T>
 */
public interface Bigram<T>{
    
    public void readFile(String file)throws Exception;
    public int numGrams();
    public int numOfGrams(T first,T second);
    public String toString();
    
}