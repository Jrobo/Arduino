int led_pin=13;
int sensor_pin=A0;

void setup() {

pinMode(led_pin,OUTPUT);

Serial.begin(9600);
  pinMode(sensor_pin, INPUT); //initialize ldr sensor as INPUT
    Serial.begin(9600);
}

void loop()

{
int A = 10;          // binary
int y = 1;
int res = A >> y;
  // Displaying 
  

int data=analogRead(sensor_pin);
    Serial.println(data);
    delay(30);

}