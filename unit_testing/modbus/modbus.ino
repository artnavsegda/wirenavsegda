#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

//ModbusIP object
ModbusIP mb;

void setup() {
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    // The IP address for the shield
    byte ip[] = { 192, 168, 1, 120 };
    //Config Modbus IP
    mb.config(mac, ip);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
}
