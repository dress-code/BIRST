/*
Copyright (C) 2016 Arturo Guadalupi. All right reserved.

This example is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This example is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

created 09 May 2016
by Arturo Guadalupi
*/

#include <GoPRO.h>
#include <ESP8266HTTPClient.h> 

#define CONNECT_PRESSED 1
#define ON_PRESSED  2
#define CAPTURE_PRESSED 3

char ssid[] = "GP56253952";      //  your network SSID (name)
char pass[] = "travel8415";     // your network password

const int buttonConnect = A1;
const int buttonOn = A2;
const int buttonCapture = A3;

const int connectLED = 3;
const int onLED = 4;
const int captureLED = 5;

bool onStatus = true;
bool captureStatus = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonConnect, INPUT_PULLUP);
  pinMode(buttonOn, INPUT_PULLUP);
  pinMode(buttonCapture, INPUT_PULLUP);

  pinMode(connectLED, OUTPUT);
  pinMode(onLED, OUTPUT);
  pinMode(captureLED, OUTPUT);

  digitalWrite(connectLED, LOW);
  digitalWrite(onLED, HIGH);
  digitalWrite(captureLED, LOW);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("hi!");
}

void loop() {

  if (!GoPRO.checkConnection()) {
    if (GoPRO.begin(ssid, pass)) {
      Serial.println("beginning!");
    }
    else {
      Serial.println("couldn't begin!");
    }
  }
  else {
    Serial.println("couldn't connect!");
  }

  //should be conneced here!
  delay(1000);

  if (GoPRO.setVideoMode(true)){
    Serial.println("We are in the video conditional statement.");
    GoPRO.startCapture();
    Serial.println("Capturing video.");
    delay(5000);
    Serial.println("Finished capturing video.");
    GoPRO.stopCapture();  
  } else {
    Serial.println("Could not set the video mode.");  
  }
}

int isButtonPressed() {
  if (digitalRead(buttonConnect) == LOW) return 1;

  else if (digitalRead(buttonOn) == LOW) return 2;

  else if (digitalRead(buttonCapture) == LOW) return 3;

  else return 0;
}

