// C++ code
//

String ssid = "Simulator Wifi";     // SSID to connect to
String password = "";               // Our virtual wifi has no password
String host = "api.thingspeak.com"; // Open Weather Map API
const int httpPort = 80;
String uri = "/update?api_key=5SXNU1Q3CXE33SAD&field1=";
void setup()
{
    Serial.begin(115200); // Serial connection over USB to computer
    Serial.println("AT"); // Serial connection on Tx /Rx porto to ESP8266
    delay(10);            // Wait for ESP response

    if (!Serial.find("OK"))
        Serial.println("9 OK");

    // Connect to 123D Circuits Simulator Wifi
    Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
    if (!Serial.find("OK"))
        Serial.println("14 OK");

    // Open TPC connection to the host:
    Serial.println("AT+CIPSTART=\"TCP\", \"" + host + "\"," + httpPort);
    if (!Serial.find("OK"))
        Serial.println("18 OK");

    pinMode(A2, INPUT);
    pinMode(A0, INPUT);

    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
}

void temperatureSensor(void)
{
    int temp = map(analogRead(A0), 20, 358, -40, 125);
    // Construct our HTTP call
    String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    int length = httpPacket.length();

    // Send our message length
    Serial.print("AT+CIPSEND=");
    Serial.println(length);
    delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

    // Send our http request
    Serial.print(httpPacket);
    delay(10); // Wait a little for the ESP to respond
    if (!Serial.find("SEND OK\r\n"))
        return;
}

void loop()
{

    int SensorTempTensao = analogRead(A0);

    // Converte a tensao lida
    float Tensao = SensorTempTensao * 5;
    Tensao /= 1024;

    // Converte a tensao lida em Graus Celsius
    float TemperaturaC = (Tensao - 0.5) * 100;

    if (TemperaturaC > 70)
    {
        digitalWrite(8, HIGH);
    }
    else
    {
        digitalWrite(8, LOW);
    }

    if (analogRead(A2) > 600)
    {
        digitalWrite(7, HIGH);
        digitalWrite(6, HIGH);
        delay(1000); // Wait for 1000 millisecond(s)
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        delay(500); // Wait for 500 millisecond(s)
    }
    else
    {
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
    }

    temperatureSensor();
}