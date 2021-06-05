/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Arduino.h>
#include <EthernetClient.h>
#include "Dns.h"
#include <SPI.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

const char * host = "http://www.google.com";
EthernetClient client;

void setup() {

  Serial.begin(115200);
  while (!Serial) {
	; // wait for serial port to connect. Needed for native USB port only
  }
  //pinMode(0, OUTPUT);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
	Serial.print("Failed to configure Ethernet using DHCP");
    Serial.print(" ");
	Serial.print(int(Ethernet.linkStatus()));
    Serial.print(" ");
    Serial.println(int(Ethernet.hardwareStatus()));
	if (Ethernet.hardwareStatus() == EthernetNoHardware) {
	  Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
	} else if (Ethernet.linkStatus() == LinkOFF) {
	  Serial.println("Ethernet cable is not connected.");
	}
	// no point in carrying on, so do nothing forevermore:
	while (true) {
	  delay(1);

	}
  }
    // print your local IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.println(Ethernet.dnsServerIP() );
    Serial.println(Ethernet.gatewayIP());
    
}

void loop() {
    switch (Ethernet.maintain()) {
        case 1:
        //renewed fail
        Serial.println("Error: renewed fail");
        break;

        case 2:
        //renewed success
        Serial.println("Renewed success");
        //print your local IP address:
        Serial.print("My IP address: ");
        Serial.println(Ethernet.localIP());
        break;

        case 3:
        //rebind fail
        Serial.println("Error: rebind fail");
        break;

        case 4:
        //rebind success
        Serial.println("Rebind success");
        //print your local IP address:
        Serial.print("My IP address: ");
        Serial.println(Ethernet.localIP());
        break;

        default:
        //nothing happened
        break;
    }
    IPAddress addr;
    DNSClient dns;
    dns.begin(Ethernet.dnsServerIP());
    Serial.println(dns.getHostByName("www.google.com", addr));
    Serial.println(addr);
    // Serial.println(client.connect(addr, 80));
    
}

extern "C" int main(void)
{
	setup();
	while (1) {
		loop();
		delay(10000);
	}
}


