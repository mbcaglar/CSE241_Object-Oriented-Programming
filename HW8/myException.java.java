/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw8;
import java.lang.Exception;
/**
 *
 * @author BEDO
 */
public class myException extends Exception{

    private String message;
    public myException(String out) {
    
        message=out;
    }
    
    
    @Override
   public String toString(){
       return message;
   }
    
}
