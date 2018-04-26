
#include <ArduinoJson.h>
#include <Http.h>


unsigned int RX_PIN = 11;
unsigned int TX_PIN = 10;
unsigned int RST_PIN = 9;


void setup(){

  Serial.begin(9600);
  
  sendRequest();
}

void loop()
{

}

void sendRequest(){
  HTTP http(9600, RX_PIN, TX_PIN, RST_PIN);
  http.configureBearer("movistar.es"); 
  http.connect();

  char response[256];
  Result result = http.post("http://uaiot-server.herokuapp.com/serv/log", "{\"latitude\" : -19.936517,  \"longitude\" : -43.978054 , \"thing\": { \"id\" : \"123412\"  }}", response);

  Serial.println(response);

  http.disconnect();
}


