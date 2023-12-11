
#include <SoftwareSerial.h>

// Define the GPS module pins
const int gpsTxPin = D4; // GPS module transmit pin (connected to NodeMCU RX)
const int gpsRxPin = D3; // GPS module receive pin (connected to NodeMCU TX)

// Create a SoftwareSerial object for GPS communication
SoftwareSerial gpsSerial(gpsRxPin, gpsTxPin);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize GPS communication
  gpsSerial.begin(9600);
}

void loop() {
  // Read GPS data if available
  while (gpsSerial.available() > 0) {
    // Read the NMEA sentence from the GPS module
    String sentence = gpsSerial.readStringUntil('\n');

    // Check if the sentence starts with "$GPRMC" (recommended minimum data for GPS)
    if (sentence.startsWith("$GPRMC")) {
      // Split the sentence into individual data fields
      char data[100];
      sentence.toCharArray(data, 100);
      char* token = strtok(data, ",");

      // Extract the latitude and longitude values
      char* time = strtok(NULL, ",");
      char* status = strtok(NULL, ",");
      char* latitude = strtok(NULL, ",");
      char* latitudeDir = strtok(NULL, ",");
      char* longitude = strtok(NULL, ",");
      char* longitudeDir = strtok(NULL, ",");

      // Check if latitude and longitude values are valid
      if (latitude != NULL && longitude != NULL) {
        // Convert latitude and longitude to the desired format
        double latDegrees = atof(latitude) / 100;
        double latMinutes = fmod(atof(latitude), 100);
        double latDecimal = latMinutes / 60.0;
        double latitudeResult = latDegrees + latDecimal;

        double lonDegrees = atof(longitude) / 100;
        double lonMinutes = fmod(atof(longitude), 100);
        double lonDecimal = lonMinutes / 60.0;
        double longitudeResult = lonDegrees + lonDecimal;

        // Print the converted latitude and longitude
        Serial.print("Latitude: ");
        Serial.print(latitudeResult, 5);
        Serial.print(", Longitude: ");
        Serial.println(longitudeResult, 5);
      }
    }
  }
}
