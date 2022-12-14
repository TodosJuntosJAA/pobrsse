/*
  Web Server
 */

#include <SPI.h>
#include <Ethernet.h>
int led = 8;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
EthernetServer server(80);
String readString;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  Ethernet.begin(mac);
  server.begin();
  Serial.print("Server it at ");
  Serial.println(Ethernet.localIP());
}
void loop() {
  EthernetClient client = server.available();
  if (client) {
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.print(c);
        if(readString.length()<100){
          readString +=c;
        }
        if(c='\n'){
          Serial.print(readString);
          client.println("<HTTP/1.1 200 OK>");
          client.println("<Connection-Type: text/html>");
          client.println("<Connection: close>");
          client.println("");
        
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title> Web Serve</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<a href=\"/?button1on\"\"><button>Led on</button></a>");
          client.println("<a href=\"/?button2off\"\"><button>Led off</button></a>");
          client.println("<body style=backgrond-color:powderblue>");

          delay(1);
          client.stop();

          if(readString.indexOf("?button1on")>0){
            digitalWrite(led,HIGH);
          }
          else if(readString.indexOf("?button2off")>0){
            digitalWrite(led,LOW);
          }
          readString="";
        }
      }
    }
  }
}
