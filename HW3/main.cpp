/***********************************************************/
/*                M.BEDİRHAN ÇAĞLAR                        */
/*                                                         */
/*                  25.10.2016                             */
/*                                                         */
/* 		Class kullanarak basit bir CPU tasarlama...        */
/*                                                         */
/*                                                         */
/***********************************************************/

#include <iostream>
#include <string>
#include "CPU.h"
#include "CPUProgram.h"
#include<fstream>
using namespace std;


int main(int argc,char** argv){
    
    
CPUProgram myProg;
CPU myCPU;//classları default constructer ile tanımlama.


//dosya okuma islemi
if(myProg.readFile(static_cast<string>(argv[1]))==-1){

	return -1;
}
myCPU.arrSize=myProg.size();//dosya satir sayisini 

//dosya satirlari ile verilen talimatları yapma islemi. 
while(!myCPU.halted()){

	int satir=myCPU.getPC();//PC değgerini ekrana basmak icin tanımladıgım degisken.
	string instruction=myProg.getLine(myCPU.getPC());
        
	if(myCPU.execute(instruction)==-1){

		return -1;
	}

	int i=myCPU.getPC();//halted fonksiyonunun kontrolunu sağlayan degisken	
	
	if(argv[2][0]=='1'){
		
		myCPU.setPC(satir);		
		myCPU.print();       
	 }
	myCPU.setPC(i);

}

return 0;

}
