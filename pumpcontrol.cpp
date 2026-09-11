// ============================================
// 12V DC Water Pump PWM Speed Control - ESP32
// ============================================

const int PUMP_PIN = 25;      // GPIO connected to MOSFET gate

const int PWM_FREQ = 5000;    // 5 kHz PWM frequency
const int PWM_RESOLUTION = 8; // 8-bit: 0-255

void setup()
{
    Serial.begin(115200);

    // Configure PWM output
    ledcAttach(PUMP_PIN, PWM_FREQ, PWM_RESOLUTION);

    // Pump initially OFF
    ledcWrite(PUMP_PIN, 0);
}

void loop()
{
    // Example: gradually increase pump voltage from 0V to 12V

    for (int voltage = 0; voltage <= 12; voltage++)
    {
        setPumpVoltage(voltage);

        Serial.print("Pump voltage: ");
        Serial.print(voltage);
        Serial.println(" V");

        delay(1000);
    }

    // Turn pump off
    setPumpVoltage(0);

    delay(3000);
}


// ------------------------------------------------
// Set desired effective pump voltage from 0 to 12V
// ------------------------------------------------
void setPumpVoltage(float voltage)
{
    // Limit input
    voltage = constrain(voltage, 0.0, 12.0);

    // Convert voltage to PWM duty cycle
    // 0V  -> 0
    // 6V  -> ~128
    // 12V -> 255

    int pwmValue = (voltage / 12.0) * 255;

    ledcWrite(PUMP_PIN, pwmValue);
}
