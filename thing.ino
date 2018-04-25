#include<SoftwareSerial.h>

SoftwareSerial client(2,3);


String reading="{  \" : 1,  \"latitude\" : 12.983027,  \"longitude\" : 80.2594,  \"timestamp\" : 100,  }";

void setup()
{
  Serial.begin(9600);
  client.begin(9600);
  delay(500);

  if(client.available())
  {
    Serial.print("Connected");
  }
  else
  {
    Serial.print("NotConnected");
  }

  //initSIM();
  connectGPRS();
  connectHTTP();
}

void loop()
{

}



void connectGPRS()
{ 
  client.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);
  ShowSerialData();

  client.println("AT+SAPBR=3,1,\"APN\",\"www\"");//APN
  delay(1000);
  ShowSerialData();

  client.println("AT+SAPBR=1,1");
  delay(1000);
  ShowSerialData();

  client.println("AT+SAPBR=2,1");
  delay(1000);
  ShowSerialData();
}

void connectHTTP()
{
  client.println("AT+HTTPINIT");
  delay(1000);
  ShowSerialData();

  client.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);
  ShowSerialData();

  client.println("AT+HTTPPARA=\"URL\",\"http://xxx.xxx.xx/Listener/\"");//Public server IP address
  client.println("AT+HTTPPARA=\"URL\",\"http://testServer/Listener/\"");//Public server address
  delay(1000);
  ShowSerialData();

  client.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(1000);
  ShowSerialData();


  client.println("AT+HTTPDATA=" + String(reading.length()) + ",100000");
  delay(1000);
  ShowSerialData();

  client.println(reading);
  delay(1000);
  ShowSerialData;

  client.println("AT+HTTPACTION=1");
  delay(1000);
  ShowSerialData();

  client.println("AT+HTTPREAD");
  delay(1000);
  ShowSerialData();

  client.println("AT+HTTPTERM");
  delay(1000);
  ShowSerialData;
}

void ShowSerialData()
{
  while(client.available()!=0)
  {
  Serial.write(client.read());
  delay(100);
  }
}
