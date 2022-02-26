#include  <ESP8266WIFI.h>
const char *ssid = "Xiaomi_AF65_5G";    //wifi名称  ssid  :Service Set Identifier
const char *password = "lzbql87801338";

void setup(){       //arduino 的源码中 main函数第一个运行的函数是init初始化环境，然后就运行setup函数，则setup是来设置板子的
    WiFi.begin(ssid, password); //启动网络连接
    Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
    Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接

    int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
    while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。
        delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED
        Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
    }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
    // 这个读秒是通过变量i每隔一秒自加1来实现的。

    Serial.println("");                          // WiFi连接成功后
    Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
    Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
    Serial.println(WiFi.localIP());               //调用localIP()来输出DHCP分配的地址

}

void loop(){        //在arduino源码中loop是死循环

}
