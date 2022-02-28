#include <FS.h>
String file_name = "/LJH/TEST.txt";             //存放文件名

void setup(){
    Serial.begin(9600);
    Serial.println(" ");

    Serial.println("SPIFFS format start");

    //—————————————————————————————————闪存格式化————————————————————————//
    SPIFFS.format();    //格式化SPIFFS        对闪存文件系统格式化操作
    Serial.println("SPIFFS format finish");


    //——————————————————————————————闪存启动————————————————————————————//
    if(SPIFFS.begin()){ //启动SPIFFS
    /*在每次使用闪存文件系统以前都需要执行这一操作。
    如果闪存文件系统成功启动，该函数的返回值为布尔型，
    如果成功启动闪存文件形同，则返回真。否则将返回假。
    */
        Serial.println("SPIFFS Started.");
    }else{
        Serial.println("SPIFFS Failed to Start");
    }
    

    //————————————————————————————————向闪存写入文件————————————————————//
    File dataFile = SPIFFS.open(file_name, "W");    //建立File对象 用于向SPIFFS的filename写入信息
    dataFile.println("Hello IOT World");            //向dataFile写入字符信息
    dataFile.close();                               //写入完成后关闭文件
    Serial.println("Finished Writing data to SPIFFS");
}


void loop(){

}
