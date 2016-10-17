// **********************************************************************************
// Copyright Autonomii.com
// **********************************************************************************
// DESCRIPTION
// **********************************************************************************
// This Arduino Sketch will switch Open and Close your NODii Relay
// **********************************************************************************
// License
// **********************************************************************************
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General 
// Public License as published by the Free Software 
// Foundation; either version 3 of the License, or 
// (at your option) any later version. 

// RELAY Signal Pin setup through Extender board on Pin 8
#define RELAY 8     // Pin 8

void setup()
{ 

 // Initialize the Arduino data pins for OUTPUT
 pinMode(RELAY, OUTPUT); 

}

void loop()
{

 // Turns ON RELAY 
 digitalWrite(RELAY,HIGH); 

 // Delay by 5000 milliseconds / 5 seconds
 delay(5000);

 // Turns OFF RELAY
 digitalWrite(RELAY,LOW);

 // Delay by 5000 milliseconds / 5 seconds
 delay(5000);
}
