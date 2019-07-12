/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw8;


public class Mypair<F,S> {
   
    public F first;
    public S second;
    
    public Mypair(F f, S s){
        this.first = f;
        this.second = s;
    }

    Mypair() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    @Override
     public String toString(){
         
        return String.format("%s %s\n",first,second);
     }
}