// ReadAnalogAverage
// Prints average to the serial monitor
// Typically the input is biased at Vcc/2 for a reading of ~512 with no signal
// Reads input A0

// sensor offset
const float SensorOffset = 38.0;
// digital pin 26 has a mosfet controlling a solenoid attached to it. Give it a name:
const int solenoid = 26;
const float pressure= 8.0;


// Global variables
int Analog;
float Sum;
float Average;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(solenoid, OUTPUT);
   delay(100);       //"Stabilization time".   Probably not necessary
   Serial.print("Hiya, I'm a pressure sensor \n");

}

void loop() {
  // put your main code here, to run repeatedly:
Sum = 0;        //Initialize/reset

//Take 1000 readings, find min, max, and average.  This loop takes about 100ms.
for (int i = 0; i < 1000; i++)
{
  Analog = analogRead(A0);

  Sum = Sum + Analog;   //Sum for averaging     
}

Average = (Sum/1000);

//Calibration
float Average_calib= (Average-SensorOffset)/10.0;


if (Average_calib >= pressure) {
  delay(100);
  digitalWrite(solenoid,LOW);
// if the gauged pressure is higher than the pressure cutoff, send a LOW V signal to the mosfet (ie Valve closed!)
} else {
  delay(20);
  digitalWrite(solenoid,HIGH);
// if the gauged pressure is lower than the pressure cutoff, send a HIGH V signal to the mosfet (ie Valve open)
}

Serial.print (" Average = ");
Serial.println (Average_calib);
}
