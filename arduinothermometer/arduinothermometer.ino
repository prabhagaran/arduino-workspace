const int ntcPin = A0;

// Your circuit:
const float R_FIXED = 10000.0;
const float R0 = 10000.0;
const float T0 = 25.0 + 273.15;
const float BETA = 3950.0;
const float VREF = 3.3;
const float ADC_MAX = 1023.0;

// ----- FILTER SETTINGS -----
const int FILTER_SIZE = 20;    // average of 20 samples
float filterBuffer[FILTER_SIZE];
int filterIndex = 0;

float smoothADC(float newValue) {
  filterBuffer[filterIndex] = newValue;
  filterIndex = (filterIndex + 1) % FILTER_SIZE;

  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) sum += filterBuffer[i];

  return sum / FILTER_SIZE;
}

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);

  // Initialize buffer
  for (int i = 0; i < FILTER_SIZE; i++) filterBuffer[i] = 0;
}

void loop() {

  // Read raw ADC
  float adcRaw = analogRead(ntcPin);

  // Smooth ADC
  float adcValue = smoothADC(adcRaw);

  float vOut = adcValue * (VREF / ADC_MAX);

  // Correct formula for your wiring
  float rNtc = (vOut * R_FIXED) / (VREF - vOut);

  // Beta equation
  float steinhart = rNtc / R0;
  steinhart = log(steinhart);
  steinhart /= BETA;
  steinhart += 1.0 / T0;
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  Serial.print("Temp = ");
  Serial.print(steinhart);
  Serial.println(" °C");

  delay(50);  // fast sampling, filtering handles stability
}
