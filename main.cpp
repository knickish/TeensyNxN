#include "WebServer.H"

APIServer server(IPAddress(192, 168, 137, 177));

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the server
  if (server.begin())
  {
      Serial.print("Server initialized at address ");
      Serial.println(server.ip);
  }
  else{
      Serial.println("Server failed to initialize");
  }
    
}


void loop() {
    if (server.get_client())
    {
        server.process_client();
        server.finish_client();
    }
    else
    {
        delay(1000);
    }
}

extern "C" int main(void)
{
    setup();
    while (1) {
        loop();
    }
}