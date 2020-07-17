#include <WiFi.h>


const char *host = "192.168.4.1";
const uint16_t port = 23;

const char *ssid = "MyESP32AP";

const char *password = "00000000";

void setup()
{
  // pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(4, OUTPUT);
  // digitalWrite(LED_BUILTIN, HIGH);
  // digitalWrite(4, LOW);
  // // while (1)
  // // {
  // //   digitalWrite(4, a);
  // //   a = !a;
  // //   delay(1);
  // // }
  // digitalWrite(5, LOW);

  Serial.begin(115200);

  // We start by connecting to a WiFi network
  /*
  Serial.println();sh
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);*/

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void loop()
{
  
  // Serial.print("connecting to ap");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  delay(1000);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  int connect_cnt=0;
  if (!client.connect(host, port))
  {
    while(!client.connect(host, port)){
      delay(500);
      Serial.print("*");
      connect_cnt++;
      if(connect_cnt>4){
        return;
      }
    }
    // Serial.println("connection failed");
    return;
  }
  
  while(1){
    if(WiFi.status() != WL_CONNECTED){
      //Serial.println("wifi lost");
      break;
    }
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
    //Serial.print(""+(char)client.read());
    delay(2);

  }
  
  //  Serial.println(line);
  client.stop();

  delay(1000); // execute once every 5 minutes, don't flood remote service
}