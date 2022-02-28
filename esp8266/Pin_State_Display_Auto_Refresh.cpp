#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>       //存放wifi信息
#include <ESP8266WiFiServer.h>      //webserver

#define buttonPin D3

ESP8266WiFiMulti wifiMulti; //multiWifi对象

ESP8266WebServer esp8266_server(80);    //建立网络服务器对象

bool pinState;              //存放引脚状态

void setup(){
    //—————————————————————————1.1 基础硬件配置————————————————————————————//
    Serial.speed(9600);     //启动串口通信
    delay(10);
    Serial.println(" ");

    pinMode(buttonPin, INPUT_PULLUP);   //设置引脚D3为上拉模式
    /*
    啥叫上拉模式？
        上拉电阻是当某输入端口未连接设备或处于高阻抗的情况下，一种用于保证输入信号为预期逻辑电平的电阻元件。

        Arduino 微控制器自带内部上拉电阻。如果你需要使用该内部上拉电阻，
        可以通过pinMode()将引脚设置为输入上拉（INPUT_PULLUP）模式。
    */
    //————————————————————————1.2 添加wifi字典——————————————————————//
    
    wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1"); 
    wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); 
    wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); 
    Serial.println("Connecting ...");                           


    //————————————————————————1.3 wifi链接——————————————————————————//
    
    int i = 0;                                 
    while (wifiMulti.run() != WL_CONNECTED) {    
        delay(1000);                             
        Serial.print(i++); Serial.print(' '); 
    }

    //——————————————————1.4 连接成功后提示——————————————————————//
    
    Serial.println('\n');                    
    Serial.print("Connected to ");            
    Serial.println(WiFi.SSID());             
    Serial.print("IP address:\t");           
    Serial.println(WiFi.localIP()); 

    //——————————————————1.5 服务器配置————————————————————————————//

    esp8266_server.begin();
    esp8266_server.on("/",handleRoot);
    esp8266_server.onNotFound(handleNotFound)
    
    Serial.println("HTTP esp8266_server started");//  告知用户ESP8266网络服务功能已经启动
}



void loop(){
    esp8266_server.handleClient();      //调用http服务处理函数
    pinState = digitalRead(buttonPin);  //获取引脚状态
}



//——————————————————————2.0 处理访问根目录函数——————————————————//

void handleRoot(){
    esp8266_server.send(200, "text/html", sendHTML(pinState));
}


//——————————————————————3.0 实时刷新并发送html代码————————————————//
String sendHTML(bool buttonState){
  
  String htmlCode = "<!DOCTYPE html> <html>\n";
  htmlCode +="<head><meta http-equiv='refresh' content='5'/>\n";
  htmlCode +="<title>ESP8266 Butoon State</title>\n";
  htmlCode +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlCode +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlCode +="</style>\n";
  htmlCode +="</head>\n";
  htmlCode +="<body>\n";
  htmlCode +="<h1>ESP8266 BUTTON STATE</h1>\n";
  
  if(buttonState)
    {htmlCode +="<p>Button Status: HIGH</p>\n";}
  else
    {htmlCode +="<p>Button Status: LOW</p>\n";}
    
  htmlCode +="</body>\n";
  htmlCode +="</html>\n";
  
  return htmlCode;
}

void handleNotFound(){                                        // 当浏览器请求的网络资源无法在服务器找到时，
  esp8266_server.send(404, "text/plain", "404: Not found");   // NodeMCU将调用此函数。
}
