void sendAlertSMS() {
  int optimalConditions = calculateOptimalConditions();
  String message = "Fungal Growth Advisory:\n";
  
  message += "Temp: " + String(temperature) + "C ";
  message += (temperature >= 20 && temperature <= 30) ? "(Optimal)\n" : "\n";
  
  message += "Humidity: " + String(humidity) + "% ";
  message += (humidity >= 60 && humidity <= 80) ? "(Optimal)\n" : "\n";
  
  message += "Moisture: " + String(moistureSens) + "% ";
  message += (moistureSens >= 30 && moistureSens <= 70) ? "(Optimal)\n" : "\n";
  
  message += "Rain: " + String(rainSens) + "% ";
  message += (rainSens >= 40 && rainSens <= 70) ? "(Optimal)\n" : "\n";
  
  message += "pH: " + String(ph, 2) + " ";
  message += (ph >= 5.5 && ph <= 6.5) ? "(Optimal)\n\n" : "\n\n";
  
  message += "Risk Level: ";
  if (optimalConditions >= 3) {
    message += "HIGH (" + String(optimalConditions) + "/5 optimal)\n";
    message += "Action: Inspect crops and consider fungicide";
  } else if (optimalConditions > 0) {
    message += "MODERATE (" + String(optimalConditions) + "/5)\n";
    message += "Action: Monitor crops closely";
  } else {
    message += "LOW\n";
    message += "Action: Normal operations";
  }

  Serial.println("Sending SMS...");
  modem.println("AT+CMGF=1");
  delay(100);
  modem.println("AT+CMGS=\"+256760080583\"");
  delay(100);
  modem.print(message);
  delay(100);
  modem.write(26);
  delay(5000);
}

void modemTest() {
  Serial.println("Initializing modem...");
  modem.println("AT");
  updateSerial();
  delay(1000);

  modem.println("AT+CSQ");
  updateSerial();
  delay(1000);

  modem.println("AT+CCID");
  updateSerial();
  delay(1000);

  modem.println("AT+CREG?");
  updateSerial();
  delay(1000);
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    modem.write(Serial.read());
  }
  while (modem.available()) {
    Serial.write(modem.read());
  }
}
