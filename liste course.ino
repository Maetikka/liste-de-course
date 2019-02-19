  #include <uTimerLib.h>
  
  #include <Adafruit_MQTT_Client.h>
  #include <Adafruit_MQTT.h>

  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiServer.h>
  

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.115", 1883);
Adafruit_MQTT_Publish compteurPublisher(&mqttClient, "/compteur");

int compteur = 0;


void button() {
  int buttonAdd = digitalRead(2);
  if(buttonAdd == 1){
    compteur++;
     compteurPublisher.publish(compteur); 
  }
  
  int buttonRemove = digitalRead(4); 
  if(buttonRemove == 1){
    compteur--;
   compteurPublisher.publish(compteur);  
  }
}




  void setup() {
  Serial.begin(115200);
  
  WiFi.begin("createch2019", "createch2019");
  delay(2000);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  
  Serial.println(WiFi.localIP());
    TimerLib.setInterval_s(button, 1);

}
 

void loop() {
if (mqttClient.connected()) {
    mqttClient.processPackets(10000);
    mqttClient.ping();
  } else {
    mqttClient.disconnect();
    mqttClient.connect();
  }
}
