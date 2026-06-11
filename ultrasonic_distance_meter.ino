#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "RIYA";
const char* password = "riya1234";

WebServer server(80);

/* ================= MOTOR PINS ================= */
#define IN1 D0
#define IN2 D1
#define IN3 D2
#define IN4 D3
#define ENA D4
#define ENB D5

/* ================= ULTRASONIC ================= */
#define TRIG D6
#define ECHO D7

int distanceCM = 0;
String robotStatus = "Stopped";

/* ================= MOTOR FUNCTIONS ================= */

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  robotStatus = "Stopped";
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  robotStatus = "Moving Forward";
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  robotStatus = "Moving Backward";
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  robotStatus = "Turning Left";
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  robotStatus = "Turning Right";
}

/* ================= DISTANCE ================= */

int getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2;
}

/* ================= WEB PAGE ================= */

void handleRoot() {

  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>ESP32 Distance Robot</title>

<style>

body{
font-family:Arial;
text-align:center;
background:#f5f5f5;
margin-top:20px;
}

.card{
background:white;
width:350px;
margin:auto;
padding:20px;
border-radius:15px;
box-shadow:0px 0px 10px gray;
}

button{
width:120px;
height:70px;
font-size:20px;
margin:5px;
}

.distance{
font-size:40px;
font-weight:bold;
color:blue;
}

.status{
font-size:22px;
font-weight:bold;
color:green;
}

</style>

<meta http-equiv="refresh" content="1">

</head>

<body>

<div class="card">

<h2>WiFi Distance Robot</h2>

<p>Distance</p>
<p class="distance">DISTANCE cm</p>

<p class="status">STATUS</p>

<p>
<a href="/forward"><button>Forward</button></a>
</p>

<p>
<a href="/left"><button>Left</button></a>
<a href="/stop"><button>Stop</button></a>
<a href="/right"><button>Right</button></a>
</p>

<p>
<a href="/backward"><button>Backward</button></a>
</p>

</div>

</body>
</html>
)rawliteral";

  page.replace("DISTANCE", String(distanceCM));
  page.replace("STATUS", robotStatus);

  server.send(200, "text/html", page);
}

/* ================= SETUP ================= */

void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  stopMotors();

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("WiFi Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);

  server.on("/forward", []() {
    forward();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/backward", []() {
    backward();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/left", []() {
    left();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/right", []() {
    right();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/stop", []() {
    stopMotors();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();

  Serial.println("Web Server Started");
}

/* ================= LOOP ================= */

void loop() {

  server.handleClient();

  static unsigned long lastRead = 0;

  if (millis() - lastRead > 200) {

    distanceCM = getDistance();

    Serial.print("Distance: ");

    if (distanceCM > 0)
      Serial.print(distanceCM);
    else
      Serial.print("Out of Range");

    Serial.println(" cm");

    lastRead = millis();
  }
}