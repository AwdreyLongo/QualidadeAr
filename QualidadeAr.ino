#include <WiFi.h>
#include <PubSubClient.h>

// Config Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Config MQTT
const char* mqtt_server = "test.mosquitto.org"; 
WiFiClient espClient;
PubSubClient client(espClient);

// Pinos
#define MQ135_PIN 34   // Potenciômetro simula o MQ-135
#define LED_RED 2      // LED vermelho (ar ruim)
#define LED_GREEN 5    // LED verde (ar bom)
#define BUZZER_PIN 4   // Buzzer

int valorSensor = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Conectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Conectar MQTT
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    if (client.connect("ESP32_QualidadeAr")) {
      Serial.println("Conectado ao MQTT!");
    } else {
      delay(2000);
    }
  }
}

void loop() {
  valorSensor = analogRead(MQ135_PIN); 
  int qualidadeAr = map(valorSensor, 0, 4095, 0, 500); // escala ppm simulada

  // Publica no broker
  char msg[50];
  sprintf(msg, "Qualidade do Ar: %d ppm", qualidadeAr);
  client.publish("saude/ar", msg);
  Serial.println(msg);

  // Se a qualidade for ruim
  if (qualidadeAr > 150) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_GREEN, LOW);
    client.publish("saude/alerta", "⚠️ ALERTA: Qualidade do ar ruim!");
  } else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_GREEN, HIGH); // Ar bom → LED verde aceso
  }

  delay(3000);
}
