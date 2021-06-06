#pragma once

#include "HTTPHeader.h"

class HTTPHeader
{
    public: // PUBLIC
    enum HTTPResponseEnum : unsigned
    {
        HTTP_200,
        HTTP_400,
        HTTP_500
    };

    enum ContentTypeEnum : unsigned
    {
        TEXT_HTML = 1,
        TEXT_PLAIN = 1<<1,
        IMAGE_JPEG = 1<<2,
        IMAGE_PNG = 1<<3,
        VIDEO_MP4 = 1<<4
    };

    enum ConnectionModeEnum : unsigned
    {
        CLOSE,
        KEEP_ALIVE
    };

    private: // PRIVATE
    char header[1000] = {0};

    

    HTTPResponseEnum HTTPResponseEnumFromCode(int response)
    {
        switch(response)
        {
            case 200:
                return HTTP_200;
            case 404:
                return HTTP_400;
            default:
                return HTTP_500;
        }
    }

    const char* HTTPResponseStr(HTTPResponseEnum code)
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
    }

    inline ContentTypeEnum ContentTypeFlagClear(ContentTypeEnum code, ContentTypeEnum flag)
    {
        return ContentTypeEnum(code & ~flag);
    }

    const char* ContentTypeStrKey()
    {
        return "Content-Type:";
    }

    const char* ContentTypeStrVal(ContentTypeEnum &code)
    {
        if (TEXT_HTML & code)
        {
            code = ContentTypeFlagClear(code, TEXT_HTML);
            return "text/html;charset=UTF-8";
        }
        if (TEXT_PLAIN & code)
        {
            code = ContentTypeFlagClear(code, TEXT_PLAIN);
            return "text/html;charset=UTF-8";
        }
        return nullptr;
    }

    const char* ConnectionModeStr(ContentTypeEnum code)
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