void displayWelcomeMessage() {
  screen.setCursor(0, 0);
  screen.print("SOIL GUARD FUSARIUM");
  screen.setCursor(6, 1);
  screen.print("DETECTOR");
  screen.setCursor(4, 3);
  screen.print("By Group 19");
}
void displaySensorValues() {
  screen.setCursor(0, 0);
  screen.print("Temp: ");
  screen.print(temperature,1);
  screen.print("C Hum: ");
  screen.print(humidity,0);
  screen.print("%");

  screen.setCursor(0, 1);
  screen.print("M_C: ");
  screen.print(moistureSens,0);
  screen.print("% Rain: ");
  screen.print(rainSens,0);
  screen.print("%");

  screen.setCursor(0, 2);
  screen.print("pH_Value: ");
  screen.print(ph, 2);

  screen.setCursor(7, 3);
  screen.print("SENSORS");
}

void displayAdvice() {
  int optimalConditions = calculateOptimalConditions();

  screen.setCursor(0, 0);
  screen.print("Risk: ");
  if (optimalConditions >= 3) {
    screen.print("HIGH");
  } else if (optimalConditions > 0) {
    screen.print("MODERATE");
  } else {
    screen.print("LOW");
  }
  screen.print(" (");
  screen.print(optimalConditions);
  screen.print("/5)");

  screen.setCursor(0, 1);
  screen.print("Pred: ");
  if (optimalConditions >= 3) {
    screen.print("Likely infection");
  } else if (optimalConditions > 0) {
    screen.print("Pos infection");
  } else {
    screen.print("Low risk");
  }

  screen.setCursor(0, 2);
  screen.print("Action: ");
  if (optimalConditions >= 3) {
    screen.print("Apply fungicide");
  } else if (optimalConditions > 0) {
    screen.print("Monitor");
  } else {
    screen.print("Normal ops");
  }

  screen.setCursor(6, 3);
  screen.print("ADVISORY");
}

int calculateOptimalConditions() {
  int count = 0;

  if (temperature >= 20 && temperature <= 30) count++;
  if (humidity >= 60 && humidity <= 80) count++;
  if (moistureSens >= 30 && moistureSens <= 70) count++;
  if (rainSens >= 40 && rainSens <= 70) count++;
  if (ph >= 5.5 && ph <= 6.5) count++;

  return count;
}
