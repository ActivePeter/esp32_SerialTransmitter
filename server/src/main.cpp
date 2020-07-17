

#include <WiFi.h>

WiFiServer server(23);


const char *ssid = "MyESP32AP";

const char *password = "00000000";


void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network


    WiFi.softAP(ssid, password);

    Serial.println(WiFi.softAPIP());

    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      String dataReceived="";
      if (Serial.available()) {
      //把串口调试器发过来的数据 发送给client
        size_t len = Serial.available();
        uint8_t sbuf[len];
        Serial.readBytes(sbuf, len);
        client.write(sbuf, len);
        delay(1);
      }
      size_t len = client.available();
      while(len)
      {
        dataReceived+=(char)(client.read());
        len--;
      }
      if(dataReceived.length()>0){
        Serial.print(dataReceived);
        dataReceived="";
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}