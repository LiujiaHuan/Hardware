#include <ESP8266WiFi.h>        // 本程序使用 ESP8266WiFi库
#include <ESP8266WiFiMulti.h>   //  ESP8266WiFiMulti库
#include <ESP8266WebServer.h>   //  ESP8266WebServer库

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'

ESP8266WebServer esp8266_server(80);// 建立ESP8266WebServer对象，对象名称为esp8266_server
// 括号中的数字是网路服务器响应http请求的端口号
// 网络服务器标准http端口号为80，因此这里使用80为端口号

void setup(void){
    Serial.begin(9600);          // 启动串口通讯

    //通过addAp函数存储  WiFi名称       WiFi密码
    wifiMulti.addAP("taichi-maker", "12345678");  // 这三条语句通过调用函数addAP来记录3个不同的WiFi网络信息。
    wifiMulti.addAP("taichi-maker2", "87654321"); // 这3个WiFi网络名称分别是taichi-maker, taichi-maker2, taichi-maker3。
    wifiMulti.addAP("taichi-maker3", "13572468"); // 这3个网络的密码分别是123456789，87654321，13572468。
    // 此处WiFi信息只是示例，请在使用时将需要连接的WiFi信息填入相应位置。
    // 另外这里只存储了3个WiFi信息，您可以存储更多的WiFi信息在此处。

    int i = 0;
    while (wifiMulti.run() != WL_CONNECTED) {  // 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
        delay(1000);                             // 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
        Serial.print(i++); Serial.print(' ');    // 将会连接信号最强的那一个WiFi信号。
    }                                          // 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。这也是
    // 此处while循环判断是否跳出循环的条件。

    // WiFi连接成功后将通过串口监视器输出连接成功信息
    Serial.println('\n');                     // WiFi连接成功后
    Serial.print("Connected to ");            // NodeMCU将通过串口监视器输出。
    Serial.println(WiFi.SSID());              // 连接的WiFI名称
    Serial.print("IP address:\t");            // 以及
    Serial.println(WiFi.localIP());           // NodeMCU的IP地址

//--------"启动网络服务功能"程序部分开始-------- //  此部分为程序为本示例程序重点1
    esp8266_server.begin();                   //  这个函数的作用是让ESP8266-NodeMCU来启动网络服务功能
    esp8266_server.on("/", handleRoot);       //  指挥NodeMCU来如何处理浏览器的http请求 param1: 位置 ‘/‘代表首页  param:访问对应页面执行函数
    esp8266_server.onNotFound(handleNotFound);
//--------"启动网络服务功能"程序部分结束--------
    Serial.println("HTTP esp8266_server started");//  告知用户ESP8266网络服务功能已经启动
}



void loop(void){
    esp8266_server.handleClient();     // 处理http服务器访问
    /*handleClient函数。它的主要作用之一是检查有没有设备通过网络向NodeMCU发送请求。
     函数handleClient每次被调用时，NodeMCU都会检查一下是否有人发送http请求。
     因此我们需要把它放在loop函数中，从而确保它能经常被调用。假如我们的loop函数里有类似delay一类的函数延迟程序运行，那么这时候就一定要注意了。
     如果handleClient函数长时间得不到调用，NodeMCU的网络服务会变得很不稳定。因此在使用NodeMCU执行网络服务功能的时候，一定要确保handleClient函数经常得以调用。
     我在这里反复强调这一点是因为这一点非常关键，请务必注意！*/
}


void handleRoot() {   //处理网站根目录“/”的访问请求
    esp8266_server.send(200, "text/plain", "Hello from ESP8266");   // NodeMCU将调用此函数。       param1:状态码  param2:Content-type param3:输出内容
}

// 设置处理404情况的函数'handleNotFound'
void handleNotFound(){                                        // 当浏览器请求的网络资源无法在服务器找到时，
    esp8266_server.send(404, "text/plain", "404: Not found");   // NodeMCU将调用此函数。
}
