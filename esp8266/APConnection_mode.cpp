#include  <ESP8266WIFI.h>
const char *ssid = "Xiaomi_AF65_5G";    //wifi名称  ssid  :Service Set Identifier
const char *password = "lzbql87801338";

void setup(){       //arduino 的源码中 main函数第一个运行的函数是init初始化环境，然后就运行setup函数，则setup是来设置板子的
    Serial.begin(9600); //启动串口通讯    9600是speed
    WiFi.softAP(ssid,password); //***此语句用来启动8266的AP模式 也就是自身作为wifi Access point
    Serial.print("Access Point: ");    // 通过串口监视器输出信息
    Serial.println(ssid);              // 告知用户NodeMCU所建立的WiFi名
    Serial.print("IP address: ");      // 以及NodeMCU的IP地址
    Serial.println(WiFi.softAPIP());   // 通过调用WiFi.softAPIP()可以得到Nod
}

void loop(){        //在arduino源码中loop是死循环

}