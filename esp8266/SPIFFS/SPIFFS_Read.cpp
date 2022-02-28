#include <FS.h>
String file_name = "/LJH/TEST.txt";     //要读取的文件位置和名称

void setup(){
    Serial.begin(9600);
    Serial.println(" ");


    //—————————————————————————启动闪存文件系统————————————————————————//

    if(SPIFFS.begin()){                
        Serial.println("SPIFFS Started");
    }else{
        Serial.println("SPIFFS Failed to start");
    }

    //——————————————————————————检查引用是否错误————————————————————————//

    if(SPIFFS.exist(file_name)){
        Serial.print(file_name);
        Serial.println("Found");
    }else{
        Serial.print(file_name);
        Serial.print("Not Found")；
    }

    //——————————————————————————建立对象，读取文件，并输出————————————————//

    File dataFile = SPIFFS.open(file_name,"r");

    for(int i = 0 ; i < dataFile.size() ; i++ ){
        Serial.print((char)dataFile.read());
    }

    dataFile.close();
}


void loop(){

}
