#include <SPI.h>
#include <Ethernet.h>

const unsigned int BAUD_RATE = 9600;

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xBD, 0x16 };
char* eway_server = "constitution.com.ua";
EthernetClient client;

void setup() {
  Serial.begin(BAUD_RATE);
  if (Ethernet.begin(mac) == 0) {
    for (;;) {
      Serial.println("Could not obtain an IP address using DHCP.");
      delay(1000);
    }
  } else {
    print_ip_address(Ethernet.localIP());
  }
}

void loop() {
  delay(20000);
  
  Serial.print("Connecting...");
  
  if (client.connect(eway_server, 80) <= 0) {
    Serial.println("connection failed.");
  } else {
    Serial.println("connected.");
    delay(300);

    client.println("GET /eway HTTP/1.1\nHost: constitution.com.ua");
    client.println();
    delay(1500);
    
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    Serial.println("Disconnecting.");
    client.stop();
  }
}

void print_ip_address(IPAddress ip) {
  const unsigned int OCTETS = 4;
  Serial.print("We've got the following IP address: ");
  for (unsigned int i = 0; i < OCTETS; i++) {
    Serial.print(ip[i]);
    if (i != OCTETS - 1)
    Serial.print(".");
  }
  Serial.println();
}
