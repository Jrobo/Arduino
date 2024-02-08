/*---------------------Assignment 5 -----------------*/
 int sensor_pin=A0; //  analog pin connected to sensor
  int sensor_val=0;
 const int signalPin = 4;   // digital pin number

/*---------------------Part (a)-----------------*/
/*a filter routine for a signal being read on an Arduino.
Install and set Arduino Nano->*/
/*---------------------Part (b)-----------------*/
// the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// // the loop function runs over and over again forever
// void loop() {
//   digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(1000);     //delay(200);               // wait for a second //
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(1000);     //delay(200);                 // wait for a second
// }
/*---------------------Part (c)-----------------*/
/*read a heart rate sensor (KY-039 Heartbeat Sensor)
black(signal)-->pin A0 |  gray-->GND  |  white-->5V */

/*---------------------Part (d)-----------------*/
// /*read the sensor and display the signal on the computer using the SSerial Plotter*/
//  void setup() {

// // pinMode(signalPin, OUTPUT);
// Serial.begin(9600); /*-----(1) setup() function with 9600 baud,----*/
// pinMode(sensor_pin, INPUT); //initialize ldr sensor as INPUT
// }
//  void loop() {
//      int sensor_val = analogRead(sensor_pin);   /*-----(2) read value --> stored in a sensor_val(variable) --->A0*/
//      Serial.println(sensor_val); /*-----(3)display : the Serial Monitor-->numbers | graphically-->Serial Plotter*/
//      delay(1000);  // delay
// }
/*---------------------Part (e)-----------------*/
/*Arduino’s ADC provides a 10-bit value,
discard the last two bits
division by 2^n ---->as y = x >> n
multiplication by 2^n --->as y = x << n
Observe the values on the Serial Plotter*/

//  void setup() {
// Serial.begin(9600); 
// pinMode(sensor_pin, INPUT); //INPUT
// // pinMode(signalPin, OUTPUT);//OUTPUT
// }

//  void loop() {

// int y = 2;  
// int binaryData = 10;  // binary data
// int shiftedData = binaryData >> y; 
//      int sensor_val = analogRead(sensor_pin);   //read value
//      Serial.println(sensor_val); //display
//      delay(1000);  // delay
// // digitalWrite(signalPin, LOW);
// // //delay(1000); // delay
// }

/*---------------------Part (f)-----------------*/
//  void setup() {
// Serial.begin(9600); 
// pinMode(sensor_pin, INPUT); //INPUT
// // pinMode(signalPin, OUTPUT);//OUTPUT
//  }
//  void loop() {
// int y = 2;  
// int binaryData = 10;  // binary data
// int shiftedData = binaryData >> y; 
//      int sensor_val = analogRead(sensor_pin); // read data
//      Serial.println(sensor_val); //display
//      //digitalWrite(signalPin, !digitalRead(signalPin)); // oscilloscope measurement
//      delay(1000);  // delay
//  }

/*---------------------Part (g)-----------------*/
 /*---------------------(i)-----------------*/
/* filter length (BL), fraction length (FL), 
and a static array for filter coefficients (B).*/
// Global variables 
const int BL = 4;  // Filter length
const int FL = 2;  // Fraction length

// Fixed-Point representation
const int scale = 1 << FL;  // Scaling factor by 2^2 (which is 4) multiplication
// Floating-point coefficients ---> fixed-point
// const int BL = 21;
// const int B[BL] = {
//    -0.09052875617128, 0.009722747694745,  0.01838996686929,  0.03195431491574,
//     0.04915884133571,  0.06837674373478,  0.08774872525134,   0.1053566360378,
//      0.1194195945823,   0.1284901981234,   0.1316232562652,   0.1284901981234,
//      0.1194195945823,   0.1053566360378,  0.08774872525134,  0.06837674373478,
//     0.04915884133571,  0.03195431491574,  0.01838996686929, 0.009722747694745,
//    -0.09052875617128
// };

const int B[BL] = {0.25 * scale, 0.25 * scale, 0.25 * scale, 0.25 * scale};  // Global array with fixed-point coefficients
 /*---------------------(ii)-----------------*/
 /*Define a static array (sensor_buf) to store the last N + 1 preceding values of the input signal.
 Also, use a global counting variable n to keep track of the current index.*/ 
// Global array for storing preceding sensor values
int sensor_buf[BL];

// Global counting variable
int n = 0;
int sensor_filt = 0;
/*---------------------(iii)-----------------*/
/*Implement the filter routine to calculate the filtered output using the FIR filter equation*/
// Function to apply the Running-Average-FIR filter
// Declare sensor_filt only once at the beginning of the function
int runningAverageFIR(int sensor_val) {
  //int sensor_filt = 0;  // Declaration at the beginning

  // Update buffer with current sensor value
  sensor_buf[n] = sensor_val;
  n = (n + 1) % BL;  // Update index with modulo

  // Running-Average-FIR filter
  for (int k = 0; k < BL; k++) {
    int correct_index = (n - k + BL) % BL;  // indexing as a ring buffer
    sensor_filt += B[k] * sensor_buf[correct_index];
  }

  // Shift by the fraction length
  sensor_filt >>= FL;

  return sensor_filt;
}


/*---------------------(iv)-----------------*/
/*Consider the fraction length and shift the result accordingly*/
// Inside the filter routine after the for loop
 void setup() {
Serial.begin(9600); 
pinMode(sensor_pin, INPUT); //INPUT
}
/*---------------------(v)-----------------*/

void loop() {
  // Example usage:
  int sensor_val = analogRead(sensor_pin);  // Read sensor value

  // Apply the filter
  int result = runningAverageFIR(sensor_val);

  // Print the filtered result
  //Serial.print("Filtered Result: ");
  Serial.println(result);

  // Use the filtered result as needed

  delay(1000);  // Adjust delay as needed
}


