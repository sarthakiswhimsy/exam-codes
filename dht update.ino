
#include <DHT.h>
#include <ConsentiumThings.h>
#define DHTPIN 2            // Change to the actual pin you're using
#define DHTTYPE DHT11       // Or DHT22 depending on your sensor

DHT dht(DHTPIN, DHTTYPE);
// Create ConsentiumThings object
ConsentiumThingsDalton board;

// Define WiFi credentials
const char *ssid = "YOUR_WIFI_SSID";      // WiFi SSID
const char *pass = "YOUR_WIFI_PASSWORD";  // WiFi password

// Define API keys
const char *SendApiKey = "YOUR_API_KEY";      // API key for sending data
const char *BoardApiKey = "YOUR_BOARD_API_KEY"; // API key for the board

// Define the interval for data sending
constexpr int interval = 7000;  // 7 seconds

void setup() {
  // Consentium IoT branding message
  Serial.println("Consentium IoT - Edge Board Library");
  Serial.println("------------------------------------");
  Serial.println("Initializing ConsentiumThings Board...");

  // Begin WiFi connection
  board.initWiFi(ssid, pass);

  // Initialize the board for sending data
  board.beginSend(SendApiKey, BoardApiKey);

  Serial.println("ConsentiumThings Board Initialized!");
  Serial.println("------------------------------------");
  Serial.println();
}

void loop() {
  float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
  // Prepare sample sensor data
 
  vector<double> sensorValues = {humidity,temperature};;  // Sensor data vector
  const char* sensorInfo[] = {"Temperature","Humidity"}; // Sensor info array

  board.sendData(sensorValues, sensorInfo, LOW_PRE);  // Send over REST with low precision

  // Wait before sending the next batch of data
  delay(interval);
}
