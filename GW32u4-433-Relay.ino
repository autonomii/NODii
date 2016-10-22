// *********************************************************************************************
// Copyright Autonomii.com
// Author : Dennis Huang dennis@autonomii.com
// Sketches based on library and code from LowPowerLab.com's wonderful RFM69 libraries
// for the HopeRF RFM69 radios.
// *********************************************************************************************
// License
// *********************************************************************************************
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General    
// Public License as published by the Free Software       
// Foundation; either version 3 of the License, or        
// (at your option) any later version.                    
//                                                        
// This program is distributed in the hope that it will   
// be useful, but WITHOUT ANY WARRANTY; without even the  
// implied warranty of MERCHANTABILITY or FITNESS FOR A   
// PARTICULAR PURPOSE. See the GNU General Public        
// License for more details.                              
//                                                        
// You should have received a copy of the GNU General    
// Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//                                                        
// Licence can be viewed at                               
// http://www.gnu.org/licenses/gpl-3.0.txt
//
// Please maintain this license information along with authorship
// and copyright notices in any redistribution of this code
//
// Copyright Felix Rusu, LowPowerLab.com
// RFM69 Library by Felix Rusu - felix@lowpowerlab.com


// *********************************************************************************************
// ************ IMPORTANT SETTINGS - YOU MUST CHANGE/ONFIGURE TO FIT YOUR HARDWARE *************
// *********************************************************************************************
#define NETWORKID     100                   // The same on all nodes that talk to each other
#define NODEID        1                     // The unique identifier of this node
#define RECEIVER      2                     // The recipient of packets
#define FREQUENCY     RF69_433MHZ           // change to RF69_868MHZ or RF69_915MHZ depending on radio
#define ENCRYPTKEY    "NODiiIsAwesome!!"    //exactly the same 16 characters/bytes on all nodes!
#define IS_RFM69HCW   false                 // set to 'true' if you are using an RFM69HCW module
#define RFM69_CS      SS                    // NSS PB0(SS)/RX 
#define RFM69_IRQ     7                     // DIO0 Pin / GPIO0 Pin / IRQ (interrupt request) pin.
#define RFM69_IRQN    4                     // IRQ Num Pin
#define RFM69_RST     4                     // RFM69 radio reset pin
#define LED           13                    // onboard LED
#define SERIAL_BAUD   115200
// *********************************************************************************************

#include <RFM69.h>    //get it here: https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>

int16_t packetnum = 0;  // packet counter, we increment per xmission

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

void setup() {
//  while (!Serial); // wait until Serial Monitor is open. Comment out if not connecting to computer.
  Serial.begin(SERIAL_BAUD);

  Serial.println("NODii Gateway");
  
  // Hard Reset the RFM module
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);

  // Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31);   // power output ranges from 0 (W -18dBm /HW 5dBm) to 31 (W 13dBm /HW 20dBm)
  
  radio.encrypt(ENCRYPTKEY);
  
  pinMode(LED, OUTPUT);
  Serial.print("\nTransmitting at ");
  Serial.print(FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(" MHz");
}

void loop() {

  // Send OPEN command to Relay node 
  delay(5000);
  char* radiopacket = "OPEN";
  Serial.print("Sending "); Serial.println(radiopacket);
  if (radio.sendWithRetry(RECEIVER, radiopacket, strlen(radiopacket))) { 
    Serial.println("OK");
  }

  // Send CLOSE command to Relay node
  delay(5000);
  radiopacket = "CLOSE";
  Serial.print("Sending "); Serial.println(radiopacket);
  if (radio.sendWithRetry(RECEIVER, radiopacket, strlen(radiopacket))) { 
    Serial.println("OK");
  }
  
  radio.receiveDone(); //put radio in RX mode
  Serial.flush(); //make sure all serial data is clocked out before sleeping the MCU
}
