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
    
    
    //———————————————————————————追加文件————————————————————————————————//
    File dataFile = SPIFFS.open(file_name, "a");// 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
    dataFile.println("This is Appended Info."); // 向dataFile添加字符串信息
    dataFile.close();   
    
    //——————————————————————————获取目录——————————————————————————————————//
    
    String folder_name = "/tachi-maker";
    Dir dir = SPIFFS.openDir(folder_name);  //建立目录对象
    
    while(dir.next()){          //检查是否还有下一个文件
        Serial.println(dir.fileName()); //  输出文件名
    }
    
    //————————————————————————————删除文件————————————————————————————————//
    if (SPIFFS.remove(file_name)){
        Serial.print(file_name);
        Serial.println(" remove sucess");
     }else {
        Serial.print(file_name);
        Serial.println(" remove fail");
    }     、
    
    //————————————————————————————展示系统信息——————————————————————————//
       // 闪存文件系统信息
  SPIFFS.info(fs_info);
 
  // 可用空间总和（单位：字节）
  Serial.print("totalBytes: ");     
  Serial.print(fs_info.totalBytes); 
  Serial.println(" Bytes"); 
 
  // 已用空间（单位：字节）
  Serial.print("usedBytes: "); 
  Serial.print(fs_info.usedBytes);
  Serial.println(" Bytes"); 
 
  // 最大文件名字符限制（含路径和'\0'）
  Serial.print("maxPathLength: "); 
  Serial.println(fs_info.maxPathLength);
 
  // 最多允许打开文件数量
  Serial.print("maxOpenFiles: "); 
  Serial.println(fs_info.maxOpenFiles);
 
  // 存储块大小
  Serial.print("blockSize: "); 
  Serial.println(fs_info.blockSize);
 
  // 存储页大小
  Serial.print("pageSize: ");
  Serial.println(fs_info.pageSize);   
}


void loop(){

}
