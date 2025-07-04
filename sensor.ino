void readAllSensors() {
  readTemperatureHumidity();
  readSoilMoisture();
  readRainfall();
  readSoilPH();
}

float readTemperatureHumidity() {
  int tempInt = 0, humInt = 0;
  int result = dht11.readTemperatureHumidity(tempInt, humInt);

  if (result == 0) {
    temperature = tempInt;
    humidity = humInt;
  } else {
    Serial.println(DHT11::getErrorString(result));
  }
  return temperature && humidity;
}

float readSoilMoisture() {
  moistureSens = analogRead(moisturePin);
  moistureSens = map(moistureSens, 0, 1023, 0, 100);
  return moistureSens;
}

float readRainfall() {
  rainSens = analogRead(rainPin);
  rainSens = map(rainSens, 0, 1023, 0, 100);
}

float readSoilPH() {
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(phPin);
    delay(30);
  }

  // Sort the samples
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  // Average middle 6 values
  unsigned long avgval = 0;
  for (int i = 2; i < 8; i++) {
    avgval += buffer_arr[i];
  }

  float volt = (float)avgval * 5.0 / 1024 / 6;
  ph = -5.70 * volt + calibration_value;
  return ph;
}
