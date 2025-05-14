int sensor_pin = A0;
#include<DHT.h>
#include <ConsentiumThings.h>
ConsentiumThingsDalton board;
const char *ssid = "YOUR_WIFI_SSID";      
const char *pass = "YOUR_WIFI_PASSWORD";  
const char *SendApiKey = "YOUR_API_KEY";      
const char *BoardApiKey = "YOUR_BOARD_API_KEY"; 
constexpr int interval = 7000;  
void setup() {
  board.initWiFi(ssid, pass);
  board.beginSend(SendApiKey, BoardApiKey);
}
void loop() {
  double data_0 = sensor_readings(sensor_pin);  
  vector<double> sensorValues = {data_0};  
  const char* sensorInfo[] = {"Temperature"}; 
  board.sendData(sensorValues, sensorInfo, LOW_PRE); 
  delay(interval);
}
float sensor_readings(int temp_pin){
  int adc_reading = analogRead(temp_pin);
  float reading_C = (adc_reading*(3300.0/4096.0))/10;
  return reading_C;
}
