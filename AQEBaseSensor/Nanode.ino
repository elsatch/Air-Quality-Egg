#include <EtherCard.h>
#include <NanodeMAC.h>
#include <StackPaint.h>

#define ETHERNET_BUFFER_LENGTH 450
static uint8_t mymac[6] = { 
  0,0,0,0,0,0 };

NanodeMAC mac( mymac );
char website[] PROGMEM = "api.cosm.com";

byte Ethernet::buffer[ETHERNET_BUFFER_LENGTH];

void setupNanode(){
  char serial_number[18] = {0};
  for(uint8_t ii = 0; ii < 6; ii++){
    convertByteArrayToAsciiHex(mymac + ii, serial_number + 3*ii, 1);
    if(ii == 5) serial_number[3*ii+2] = '\0';
    else serial_number[3*ii+2] = ':';
  }  
  Serial.println();
  Serial.print(F("Egg Serial #:  "));
  Serial.println(serial_number);  
  Serial.println();
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
    
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
  
  Serial.print(F("IP: "));
  ether.printIp(ether.myip);
  Serial.println();
  
  Serial.print(F("GW: "));
  ether.printIp(ether.gwip);  
  Serial.println();  
  
  Serial.print(F("DNS: "));
  ether.printIp(ether.dnsip);  
  Serial.println();

  PRINT_STACK_SPACE;
  
  if (!ether.dnsLookup(website))
    Serial.println(F("DNS failed"));
  Serial.print(F("SRV: "));
  ether.printIp(ether.hisip);
  Serial.println();
  
  ether.disableBroadcast();
}

