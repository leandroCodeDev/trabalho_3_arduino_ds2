//si usas platformio, si usas arduino ide comentar esta línea.
#include <Arduino.h>

//si usas esp32
//#include <HTTPClient.h>
//#include <WiFi.h>

//si usas esp8266
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "t3nkai-Aspire-A515-51G"
#define STAPSK  "v8N4G2Rx"
#endif
#define pinSensorA A0

const char* ssid     = STASSID;
const char* password = STAPSK;


float FazLeituraUmidade(void);



float FazLeituraUmidade(void)
{
    int ValorADC;
    float UmidadePercentual;
 
     ValorADC = analogRead(pinSensorA);   //1024 -> 5V
     Serial.print("[Leitura ADC] ");
     Serial.println(ValorADC);
 
     //Quanto maior o numero lido do ADC, menor a umidade.
     //Sendo assim, calcula-se a porcentagem de umidade por:
     //      
     //   Valor lido                 Umidade percentual
     //      _    0                           _ 100
     //      |                                |   
     //      |                                |   
     //      -   ValorADC                     - UmidadePercentual 
     //      |                                |   
     //      |                                |   
     //     _|_  1024                        _|_ 0
     //
     //   (UmidadePercentual-0) / (100-0)  =  (ValorADC - 1024) / (-1024)
     //      Logo:
     //      UmidadePercentual = 100 * ((1024-ValorADC) / 1024)  
      
     UmidadePercentual = 100 * ((1024-(float)ValorADC) / 1024);
     Serial.print("[Umidade Percentual] ");
     Serial.print(UmidadePercentual);
     Serial.println("%");
 
     return UmidadePercentual;
}


void setup() {
  delay(10);
  Serial.begin(115200);


  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  Serial.print("  Analogico:");
  Serial.print(analogRead(pinSensorA)); 
  Serial.print("  ");

  Serial.print("  Atuador:");
  if (analogRead(pinSensorA) > 700) {
     Serial.println("SOLENOIDE LIGADO");
     //digitalWrite(pinSolenoide, HIGH);
  } else {
    Serial.println("SOLENOIDE DESLIGADO");
     //digitalWrite(pinSolenoide, LOW);
  }
    float UmidadePercentualLida;
    int UmidadePercentualTruncada;
    char FieldUmidade[13];
    UmidadePercentualLida = FazLeituraUmidade();
    UmidadePercentualTruncada = (int)UmidadePercentualLida;

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    HTTPClient http;
    sprintf(FieldUmidade,"leitura=%d",UmidadePercentualLida);

    http.begin("http://192.168.122.1:3333/leitura");      //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.POST(FieldUmidade);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    http.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }

   delay(15000);
}


