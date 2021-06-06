#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "WebForms.h"

class APIServer
{
    public:

    EthernetServer server;
    IPAddress ip;
    EthernetClient curr_client;
    HTTPHeaderFactory header_factory;
    byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

    //CONSTRUCTOR
    APIServer(IPAddress ip_arg)
        : server(80)
        , ip(ip_arg) 
        , header_factory(
            (HTTPHeaderFactory::ContentTypeFlags) HTTPHeaderFactory::ContentType::TEXT_HTML,
            HTTPHeaderFactory::ConnectionMode::CLOSE,
            HTTPHeaderFactory::HTTPResponse::HTTP_200
            )
    {
    }

    bool begin()
    {
        // start the Ethernet connection and the server:
        Ethernet.begin(mac, ip);

        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
            return false;
        }
        if (Ethernet.linkStatus() == LinkOFF) {
            Serial.println("Ethernet cable is not connected.");
            return false;
        }
        server.begin();
        Serial.print("server is at ");
        Serial.println(Ethernet.localIP());
        return true;
    }

    bool get_client()
    {
        curr_client = server.available();

        if (curr_client)
        {
            Serial.println("new client");
            return true;
        }
        else
            return false;
    }

    bool process_client()
    {
        EthernetClient client = curr_client;
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n' && currentLineIsBlank) {
                // send a standard http response header
                Serial.println("\nResponse Header Goes Here");
                Serial.println(header_factory.get_header());
                client.println(header_factory.get_header());
                client.println();
                client.println("<!DOCTYPE HTML>");
                client.println("<html>");
                // output the value of each analog input pin
                for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
                    int sensorReading = analogRead(analogChannel);
                    client.print("analog input ");
                    client.print(analogChannel);
                    client.print(" is ");
                    client.print(sensorReading);
                    client.println("<br />");
                }
                client.println("</html>");
                break;
                }
                if (c == '\n') {
                // you're starting a new line
                currentLineIsBlank = true;
                } else if (c != '\r') {
                // you've gotten a character on the current line
                currentLineIsBlank = false;
                }
            }
        }
        
        return true;
    }

    void finish_client()
    {
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        curr_client.stop();
        Serial.println("client disconnected\n");
    }
};