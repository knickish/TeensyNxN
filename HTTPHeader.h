#pragma once

// #define __DEBUG__

#ifdef __DEBUG__
    #include <Arduino.h>
#endif

#include "WebForms.h"


class HTTPHeaderFactory
{
    public:                                                     // PUBLIC

    enum HTTPResponse : unsigned
    {
        HTTP_200,
        HTTP_400,
        HTTP_500
    };

    enum ContentType : unsigned
    {
        TEXT_HTML = 1,
        TEXT_PLAIN = 1<<1,
        IMAGE_JPEG = 1<<2,
        IMAGE_PNG = 1<<3,
        VIDEO_MP4 = 1<<4
    };

    enum ConnectionMode : unsigned
    {
        CLOSE,
        KEEP_ALIVE
    };
    typedef unsigned ContentTypeFlags;

    HTTPResponse HTTPResponseFromReturnCode(int response)
    {
        switch(response)
        {
            case 200:
                return HTTP_200;
            case 400:
                return HTTP_400;
            default:
                return HTTP_500;
        }
    }

    //CONSTRUCTOR
    HTTPHeaderFactory(
        ContentTypeFlags content_flags_arg, 
        ConnectionMode connection_mode_arg, 
        HTTPResponse http_response_arg
        )
        :content_flags(content_flags_arg)
        ,connection_mode(connection_mode_arg)
        ,http_response(http_response_arg)
        ,flags_changed(true)
    {
    }

    void changeFlags(
        ContentTypeFlags content_flags_arg, 
        ConnectionMode connection_mode_arg, 
        HTTPResponse http_response_arg
        )
    {
        content_flags=content_flags_arg;
        connection_mode=connection_mode_arg;
        http_response=http_response_arg;
        flags_changed=true;
    }

    char* get_header()
    {
        #ifdef __DEBUG__
            Serial.println("Forming header");
        #endif
        
        //init
        if (flags_changed==false)
            return header;
        else    
        {
            #ifdef __DEBUG__
            Serial.print("Forming header");
            #endif
            for (int i = 0 ; i<1000;i++)
            {
                header[i] = '\0';
            }
        }
        int index = 0;
        char linebreak_arr[2] = {'\n','\0'};
        char* linebreak = &linebreak_arr[0];
        //Protocol and response
        index += strncpy(header+index, (char*) HTTPResponseStr(http_response), 1000-index);
        index += strncpy(header+index, linebreak, 1000-index);

        #ifdef __DEBUG__
            Serial.println(header_arr);
        #endif

        //content-type flags
        index += strncpy(header+index, (char*) ContentTypeStrKey(), 1000-index);
        ContentTypeFlags content_flags_tmp = content_flags;
        while(content_flags_tmp)
        {
            #ifdef __DEBUG__
            Serial.println("Adding Content Type flag");
            #endif
            index += strncpy(header+index, (char*) ContentTypeStrVal(&content_flags_tmp), 1000-index);
        }
        index += strncpy(header+index, linebreak, 1000-index);

        index += strncpy(header+index, (char*) ConnectionModeStr(connection_mode), 1000-index);
        index += strncpy(header+index, linebreak, 1000-index);

        flags_changed=false;

        #ifdef __DEBUG__
            Serial.print(header_arr);
        #endif
        return header;
    }

    

    protected:                                                    // PROTECTED
    ContentTypeFlags    content_flags;
    ConnectionMode      connection_mode;
    HTTPResponse        http_response;
    bool                flags_changed;

    char header_arr[1000] = {0};
    char * header = &header_arr[0];

    const char* HTTPResponseStr(HTTPResponse code)
    {
        switch(code)
        {
            case HTTP_200:
                return "HTTP/1.1 200 OK";
            case HTTP_400:
                return "HTTP/1.1 400 Bad Request";
            default:
                return "HTTP/1.1 500 Internal Server Error";
        }
        return "";
    }

    inline ContentTypeFlags ContentTypeFlagClear(ContentTypeFlags * code, ContentType flag)
    {
        return (ContentTypeFlags)(*code & ~flag);
    }

    const char* ContentTypeStrKey()
    {
        return "Content-Type: ";
    }

    const char* ContentTypeStrVal(ContentTypeFlags * code)
    {
        if (TEXT_HTML & *code)
        {
            #ifdef __DEBUG__
            Serial.println("text/html;charset=UTF-8");
            #endif
            *code = ContentTypeFlagClear(code, TEXT_HTML);
            return "text/html;charset=UTF-8";
        }
        if (TEXT_PLAIN & *code)
        {
            #ifdef __DEBUG__
            Serial.println("text/plain;charset=UTF-8");
            #endif
            *code = ContentTypeFlagClear(code, TEXT_PLAIN);
            return "text/plain;charset=UTF-8";
        }
        return nullptr;
    }

    const char* ConnectionModeStr(ConnectionMode code)
    {
        switch(code)
        {
            case CLOSE:
                return "Connection: close";
            case KEEP_ALIVE:
                return "Connection: keep-alive";
            default:
                return "Connection: close";
        }
    }
};