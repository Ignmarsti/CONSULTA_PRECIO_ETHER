#include <ESP8266WiFi.h> //librería necesaria para la conexión wifi
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MOVISTAR_382F";
const char* password = "77DBFD8164501F201C5C";

//WiFi.begin("ssid", "password");

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();//Espera a que se complete la transmisión de los datos en serie salientes
    delay(1000);
  }
  WiFi.mode(WIFI_STA);///Para conectarla a una red Wi-Fi a través de un acces point (SSID)
  WiFiMulti.addAP(ssid,password);///Seleccionamos la red a la que nos queremos conectar (con esta librería podríamos conectarnos a varias)
}

void loop() {
  // put your main code here, to run repeatedly:
  if((WiFiMulti.run() == WL_CONNECTED)) {//Si se conecta bien a la red wifi(si hay varias se conectará a la más estable)

    ///----------------------------------------OBJETO: PRECIO ETHER---------------------////
    
    HTTPClient http;///Creamos un objeto HTTP (esta clase proporciona los métodos para crear y enviar la solicitud HTTP) 
    Serial.println("[HTTP] begin...");//Imprimimos por la pantalla que estamos conectados y empezando a hacer cosas. 
    http.begin("api.thingspeak.com", 80,"/apps/thinghttp/send_request?api_key=IIZMBB3Q8P1KM44Z"); //llamamos al método begin y le pasamos la url dónde queremos conectarnos.
    int httpCode = http.GET();//Le mandamosla solicitud http get y guardamos lo que recojamos en un entero.
    
    Serial.println("[HTTP] Get...");

    if(httpCode > 0){//Si tenemos un código  de respuesta
      Serial.printf("[HTTP] GET... code: %d",httpCode);//Imprimimos el código
      if(httpCode = HTTP_CODE_OK){///Si el código es diciendo que hemos obtenido respuesta
        Serial.print("Precio de Ether: ");
        Serial.println(http.getString());///Imprimimos la respuesta
      }
    }
    
    else{
      Serial.printf("[HTTP] GET... Failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    delay(1000);
    
    ///----------------------------------------OBJETO 1: MÍNIMO 24 HORAS---------------------////

    HTTPClient http1;
    http1.begin("api.thingspeak.com", 80,"/apps/thinghttp/send_request?api_key=K9P2JQT9JN9HZJGZ");
    int httpCode1 =http1.GET();
    
    if(httpCode1 > 0){//Si tenemos un código  de respuesta
      Serial.printf("[HTTP] GET... code: %d",httpCode);//Imprimimos el código
      if(httpCode1 = HTTP_CODE_OK){///Si el código es diciendo que hemos obtenido respuesta
        Serial.print("Mínimo 24 horas: ");
        Serial.println(http1.getString());///Imprimimos la respuesta
      }
    }
    
    else{
      Serial.printf("[HTTP] GET... Failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    delay(1000);
    ///----------------------------------------OBJETO 2 MÁXIMO 24 HORAS---------------------////
    HTTPClient http2;
    http2.begin("api.thingspeak.com", 80,"/apps/thinghttp/send_request?api_key=OC4DGPIUMTLYUVNC");
    int httpCode2 =http2.GET();
    
    if(httpCode2 > 0){//Si tenemos un código  de respuesta
      Serial.printf("[HTTP] GET... code: %d",httpCode);//Imprimimos el código
      if(httpCode2 = HTTP_CODE_OK){///Si el código es diciendo que hemos obtenido respuesta
        Serial.print("Máximo 24 horas: ");
        Serial.println(http2.getString());///Imprimimos la respuesta
      }
    }
    
    else{
      Serial.printf("[HTTP] GET... Failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    delay(1000);
    
    http.end();

  }
  delay(1000);
}