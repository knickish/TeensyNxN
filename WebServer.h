#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "WebForms.h"


#define ENDPOINT_COUNT 3
class APIServer
{
    public:

    EthernetServer server;
    IPAddress ip;
    EthernetClient curr_client;
    HTTPHeaderFactory header_factory;
    const byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    const char * endpoints[ENDPOINT_COUNT] = {"/","/matrix_size/","/matrix_invert/"};

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
        Ethernet.begin((uint8_t*) &mac[0], ip);

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
            Serial.print("new client ");
            Serial.println(curr_client.remoteIP());
            return true;
        }
        else
            return false;
    }

    bool process_client()
    {
        EthernetClient client = curr_client;
        char endpoint_str[100] = {0};
        int index = 0;
        bool passed_slash = false;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                
                if (c=='/')
                    passed_slash = true;

                if((c==' ' || c=='?') && passed_slash)
                {
                    Serial.println(endpoint_str);
                    endpoint_switch(&endpoint_str[0]);
                    return true;
                }
                if(index<100)
                {
                    endpoint_str[index] = c;
                    index++;
                }
            }
        }
        return false;
    }

    bool endpoint_switch(char* endpoint)
    {
        int space_pointer = 0;
        while(endpoint[space_pointer]!=' ')
            space_pointer++;
        space_pointer++;
        

        int endpoint_index = ENDPOINT_COUNT-1;
        for (; endpoint_index>=0 ; endpoint_index--)
        {
            if(!strcmp_template<const char, char>(&endpoints[endpoint_index][0], &endpoint[space_pointer]))
            {
                Serial.println("Matched Endpoint");
                Serial.println(strcmp_template<const char, char>(&endpoints[endpoint_index][0], &endpoint[space_pointer]));
                Serial.println();
                break;
            }
        }

        switch(endpoint_index)
        {
            case 0:
            {
                initial_endpoint();
                break;
            }
            case 1:
            {
                matrix_size_endpoint();
                break;
            }
            case 2:
            {
                matrix_invert_endpoint();
                break;
            }
                

        }
        return true;
    }
    void initial_endpoint()
    {
        Serial.println("Using Initial Endpoint");
        EthernetClient client =  curr_client;
        while (client.connected()) {
            while (client.available()) {
                client.read();
            }
            Serial.println(header_factory.get_header());
            client.println(header_factory.get_header());
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println(" <form action=\"/matrix_size/\" method=\"get\">"
            "<label for=\"size_select\">Input Matrix Size</label><br>"
            "<input type=\"text\" id=\"size_select\" name=\"size_select\"><br>"
            "</form>");
            client.println("</html>");
            break;
        }
    }

    void matrix_size_endpoint()
    {
        Serial.println("Using Matrix Size Endpoint");
        EthernetClient client =  curr_client;
        const int char_buf_size = 10;
        char char_buf[char_buf_size+1] = {0};
        int char_index = 0;
        while (client.connected()) {
            char c;
            bool passed_equal = false;
            while (client.available()) {
                c = client.read();
                if (passed_equal && c && char_index<char_buf_size)
                {
                    char_buf[char_index] = c;
                    char_index++;
                }
                if (c=='='){
                    passed_equal= true;
                }
            }
            int matrix_size = stou(&char_buf[0]);
            Serial.println(&char_buf[0]);
            Serial.print("Matrix Size: ");
            Serial.println(matrix_size);
            if (matrix_size>4)
                matrix_size = 4;
            Serial.println(header_factory.get_header());
            client.println(header_factory.get_header());
            client.println();
            Serial.println("<!DOCTYPE HTML>");
            Serial.println("<html>");
            Serial.print(" <form action=\"/matrix_invert/\" method=\"POST\"><br>");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.print(" <form action=\"/matrix_invert/\" method=\"POST\"><br>");
            client.println("<h3>Input Matrix Values</h3><br>");
            for (int i = 0 ; i< matrix_size ; i++)
            {
                for (int j = 0; j<matrix_size; j++)
                {
                    Serial.print("<input type=\"text\" id=\"matrix_val");
                    Serial.print(j);
                    Serial.print(i);
                    Serial.print("\" name=\"matrix_val");
                    Serial.print(j);
                    Serial.print(i);
                    Serial.print("\">");
                    client.print("<input type=\"text\" id=\"matrix_val");
                    client.print(j);
                    client.print(i);
                    client.print("\" name=\"matrix_val");
                    client.print(j);
                    client.print(i);
                    client.print("\">");
                }
                Serial.println("<br>");
                client.println("<br>");
            }
            client.println("<input type=\"submit\" value=\"Submit\">");
            client.println("</form>");
            client.println("</html>");
            break;
        }
        return;
    }

    void matrix_invert_endpoint()
    {
        return;
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