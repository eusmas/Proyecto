#include <Arduino.h>      //incluir libreria arduino por estar usando platformio
#include <SoftwareSerial.h>     //libreria serial
#include <CurrentSensor.h>      //Incluir libreria creada para el sensor de corriente
#include <Buffer.h>             //Incluir libreria creada para el buffer de datos

//configuracion WIFI
#include <ESP8266WiFi.h>
const char* ssid = "USSI";
const char* password = "930808025";
WiFiServer server(80); 
int estado = LOW;
//Fin WIFI

CurrentSensor sensor; //creacion del sensor
BufferStat datos=BufferStat(5); //creacion del buffer de 5 posiciones

const uint8_t SENSOR_PIN = 0;     //definicion de pin analogo
const uint8_t RESOLUCION_PIN = 10;      //definicio de la recolucion del pin analogo en bits
const float NIVELMAX_LECTURA = 5;     //definicion del nivel maximo de lectura, para la prueba de simula con 5 voltios
unsigned long current_time, prev_time;      //creacion de variables para medicion de tiempo y no usar delay
uint16_t dt_ms=2000;     //valor del "delay" y velocidad de muestreo

void setup() {
  Serial.begin(9600);
  sensor.setup(SENSOR_PIN, RESOLUCION_PIN, NIVELMAX_LECTURA);     //se inicializa el sensor y sus variables de entrada
  prev_time=millis();     //Se inicializa el tiempo previo

//Conexion WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WIFI...");
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  server.begin();
  Serial.println("Servidor inicializado");
  Serial.printf("\n\nUtiliza esta URL para conectar: http://%s/\n", WiFi.localIP().toString().c_str());
//Fin WIFI
}


void loop() {
  current_time=millis();

  if (current_time - prev_time > dt_ms){
    prev_time=current_time;

    datos.add(sensor.read());
    
    //Serial.print("Medida Sensor: ");
    //Serial.println(sensor.read());
    //Serial.print("Nivel Logico: ");
    //Serial.println(sensor.getMeasure()); 
    ////Serial.println(sensor.getMeasure(SENSOR_MEASURE)); //otra forma de entregar la medida del sensor

    //Serial.print("Minimo: ");
    //Serial.println(datos.min());
    //Serial.print("Maximo: ");
    //Serial.println(datos.max());
    //Serial.print("Promedio: ");
    //Serial.println(datos.avg());
    //Serial.print("Moda: ");
    //Serial.println(datos.moda());
    //Serial.print("Mediana: ");
    //Serial.println(datos.median());
    //Serial.println("...Fin...");
  }

  //WIFI
  WiFiClient client = server.available();  
  if (!client) {
    return;
  }
  
  while(!client.available()){
  delay(1);
  }

  String peticion = client.readStringUntil('\r');
  client.flush();

  client.println("<h1 align=center>Esteban Usma Sierra");
  client.println("<h1 align=center>Lenguajes Tecnicos de Programacion - 2021/2");
  client.println("<h1 align=center>__________________________________");


  if (peticion.indexOf('/SW=ON') != -1 || peticion.indexOf('/SW=OFF') != -1)
  {
    client.print("<h1 align=center>Lectura de Sensor:   ");
    client.println(sensor.read());
    client.print("<h1 align=center>Lectura Minima del Sensor:   ");
    client.println(datos.min());
    client.print("<h1 align=center>Lectura Maxima del Sensor:   ");
    client.println(datos.max());
    client.print("<h1 align=center>Lectura Promedio del Sensor:   ");
    client.println(datos.avg());
    
    estado = !estado;
  } 
  /*
  client.println("HTTP/1.1 200 OK");
  client.println("");                         
  client.println("");
  client.println("");
  client.println("");
  */

  client.print("<h1 align=center>__________________________________");
  client.println("<h1 align=center>Presione la imagen para actualizar");

 if(estado == HIGH) 
 {client.print("<input type='image' src='https://media.springernature.com/original/springer-static/image/chp%3A10.1007%2F978-3-030-31019-6_49/MediaObjects/488332_1_En_49_Fig1_HTML.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/SW=ON'>");}
 if(estado == LOW) 
 {client.print("<input type='image' src='https://media.springernature.com/original/springer-static/image/chp%3A10.1007%2F978-3-030-31019-6_49/MediaObjects/488332_1_En_49_Fig1_HTML.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/SW=OFF'>");}
  
  
  client.println("</html>");
  delay(1);

}
