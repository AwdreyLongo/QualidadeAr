Objetivo do Projeto

Este projeto implementa um sistema IoT para monitorar a qualidade do ar em ambientes internos, utilizando um ESP32, o sensor MQ-135 e comunicação em nuvem via protocolo MQTT.
O sistema envia leituras em tempo real para um broker MQTT e aciona atuadores (LEDs e buzzer) quando a qualidade do ar se torna prejudicial à saúde, contribuindo diretamente ao ODS 3 – Saúde e Bem-estar.

Índice

Descrição Geral


Demonstração

Hardware Utilizado

Diagrama do Circuito

Arquitetura do Sistema

Fluxograma de Funcionamento

MQTT – Tópicos e Comunicação

Instalação e Execução

Medições de Tempo de Resposta

Resultados Obtidos

Estrutura do Repositório

Licença


Descrição Geral


O sistema realiza as seguintes atividades:

Lê continuamente valores do sensor MQ-135

Publica leituras no broker MQTT (saude/ar)

Envia alertas automáticos (saude/alerta)

Aciona LED verde quando o ar está bom

Acende LED vermelho + buzzer quando o ar está ruim

Permite visualização de dados no MQTT Explorer, HiveMQ Web ou Node-RED


Demonstração


vídeo exigido pelo professor.


Hardware Utilizado


Componente	Função

ESP32 DevKit v1	Processamento e conexão Wi-Fi

MQ-135	Sensor de qualidade do ar (gases e poluentes)

LED Verde	Indica ar saudável

LED Vermelho	Indica ar ruim

Buzzer	Alerta sonoro

Resistores 220Ω	Limitar corrente dos LEDs

Protoboard e jumpers	Montagem do circuito


Diagrama do Circuito


 [3.3V] ---- [Potenciômetro] ---- [GND]
                   |
                [GPIO34]

 [ESP32 GPIO2] ---- [LED] ---- [Resistor] ---- [GND]

 [ESP32 GPIO4] ---- [Buzzer] ---- [GND]


Esquemático de montagem do sistema no Wokwi. Fonte: Wokwi.


Arquitetura do Sistema


MQ-135 → ESP32 → Broker MQTT (Mosquitto)
                 ↓
              Dashboards
        (MQTT Explorer / Node-RED)
                 ↓
           Atuadores locais
      (LED verde, LED vermelho, buzzer)


  <img width="636" height="587" alt="image" src="https://github.com/user-attachments/assets/2094ad45-bc1f-4059-a817-b5d3cd0c9013" />


Fluxograma de Funcionamento


<img width="899" height="403" alt="image" src="https://github.com/user-attachments/assets/dcd8b68c-4376-4200-8481-6e7811adf31a" />


MQTT – Tópicos e Comunicação


Publicação



saude/ar	Valor da qualidade do ar	"Qualidade do Ar: 150 ppm"

saude/alerta	Alerta de risco	"⚠️ ALERTA: qualidade ruim!"


Instalação e Execução


Pré-requisitos


Arduino IDE ou PlatformIO

Biblioteca PubSubClient

Biblioteca WiFi.h


Acesso ao broker público (Mosquitto)


Clonar o repositório


git clone https://github.com/AwdreyLongo/QualidadeAr


Abrir o arquivo

/main/scketch.ino


Configurar Wi-Fi no código:

const char* ssid = "Wokwi-GUEST";

const char* password = "";


Enviar para o ESP32

Visualizar dados no MQTT Explorer


Medições de Tempo de Resposta


Foram feitas três medições do tempo entre:

(a) Sensor → MQTT


Usando suas medições:


ppm	Tempo (s)


416 ppm	8.96 s

116 ppm	2.99 s

150 ppm	12.02 s


Média ≈ 8.96 s


Resultados Obtidos


Núm. medida	Sensor/atuador	Tempo de resposta

416 ppm	 MQ-135 → MQTT / Comando MQTT → LED vermelhor/Buzzer	 8.96 segundos

116 ppm	 MQ-135 → MQTT / Comando MQTT → LED verde	 2.99 segundos

150 ppm	 MQ-135 → MQTT / Comando MQTT → LED vermelhor/Buzzer	12.02 segundos


<img width="886" height="443" alt="image" src="https://github.com/user-attachments/assets/81461f90-a775-4197-8aef-2a2aec40290f" />


<img width="886" height="446" alt="image" src="https://github.com/user-attachments/assets/8665ed76-7d1a-47de-92b1-bdade61a89c2" />


<img width="886" height="434" alt="image" src="https://github.com/user-attachments/assets/0d8e7539-b270-41ea-8ab9-48009f2a46d7" />
✔ Console serial exibindo valores
✔ Dashboard no Node-RED (opcional)
✔ Gráficos gerados no Python
✔ Tabela de medições
