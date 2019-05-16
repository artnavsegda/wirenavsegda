// NAME: PN5180-Library.ino
//
// DESC: Example usage of the PN5180 library for the PN5180-NFC Module
//       from NXP Semiconductors.
//
// Copyright (c) 2018 by Andreas Trappmann. All rights reserved.
//
// This file is part of the PN5180 library for the Arduino environment.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// BEWARE: SPI with an Arduino to a PN5180 module has to be at a level of 3.3V
// use of logic-level converters from 5V->3.3V is absolutly neccessary
// on most Arduinos for all input pins of PN5180!
// If used with an ESP-32, there is no need for a logic-level converter, since
// it operates on 3.3V already.
//
// Arduino <-> Level Converter <-> PN5180 pin mapping:
// 5V             <-->             5V
// 3.3V           <-->             3.3V
// GND            <-->             GND
// 5V      <-> HV
// GND     <-> GND (HV)
//             LV              <-> 3.3V
//             GND (LV)        <-> GND
// SCLK,13 <-> HV1 - LV1       --> SCLK
// MISO,12        <---         <-- MISO
// MOSI,11 <-> HV3 - LV3       --> MOSI
// SS,10   <-> HV4 - LV4       --> NSS (=Not SS -> active LOW)
// BUSY,9         <---             BUSY
// Reset,7 <-> HV2 - LV2       --> RST
//
// ESP-32    <--> PN5180 pin mapping:
// 3.3V      <--> 3.3V
// GND       <--> GND
// SCLK, 18   --> SCLK
// MISO, 19  <--  MISO
// MOSI, 23   --> MOSI
// SS, 16     --> NSS (=Not SS -> active LOW)
// BUSY, 5   <--  BUSY
// Reset, 17  --> RST
//

#define DEBUG 1

/*
 * Pins on ICODE2 Reader Writer:
 *
 *   ICODE2   |     PN5180
 * pin  label | pin  I/O  name
 * 1    +5V
 * 2    +3,3V
 * 3    RST     10   I    RESET_N (low active)
 * 4    NSS     1    I    SPI NSS
 * 5    MOSI    3    I    SPI MOSI
 * 6    MISO    5    O    SPI MISO
 * 7    SCK     7    I    SPI Clock
 * 8    BUSY    8    O    Busy Signal
 * 9    GND     9  Supply VSS - Ground
 * 10   GPIO    38   O    GPO1 - Control for external DC/DC
 * 11   IRQ     39   O    IRQ
 * 12   AUX     40   O    AUX1 - Analog/Digital test signal
 * 13   REQ     2?  I/O   AUX2 - Analog test bus or download
 *
 */

//#define WRITE_ENABLED 1

#include <PN5180.h>
#include <PN5180ISO15693.h>

#define PN5180_NSS  10
#define PN5180_BUSY 6
#define PN5180_RST  7

PN5180 nfc(PN5180_NSS, PN5180_BUSY, PN5180_RST);

static char hexBuffer[9];
static const char hexChar[] = "0123456789ABCDEF";

bool setupRF() {
  Serial.println(F("Loading RF-Configuration...\n"));
  if (nfc.loadRFConfig(0x00, 0x80)) {  // ISO14443 parameters
    Serial.println(F("done.\n"));
  }
  else return false;

  Serial.println(F("Turning ON RF field...\n"));
  if (nfc.setRF_on()) {
    Serial.println(F("done.\n"));
  }
  else return false;

  nfc.writeRegisterWithAndMask(SYSTEM_CONFIG, 0xfffffff8);  // Idle/StopCom Command
  nfc.writeRegisterWithOrMask(SYSTEM_CONFIG, 0x00000003);   // Transceive Command

  return true;
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("=================================="));
  Serial.println(F("Uploaded: " __DATE__ " " __TIME__));
  Serial.println(F("PN5180 ISO15693 Demo Sketch"));

  nfc.begin();

  Serial.println(F("----------------------------------"));
  Serial.println(F("PN5180 Hard-Reset..."));
  nfc.reset();

  Serial.println(F("----------------------------------"));
  Serial.println(F("Reading product version..."));
  uint8_t productVersion[2];
  nfc.readEEprom(PRODUCT_VERSION, productVersion, sizeof(productVersion));
  Serial.print(F("Product version="));
  Serial.print(productVersion[1]);
  Serial.print(".");
  Serial.println(productVersion[0]);

  if (0xff == productVersion[1]) { // if product version 255, the initialization failed
    Serial.println(F("Initialization failed!?"));
    Serial.println(F("Press reset to restart..."));
    Serial.flush();
    exit(-1); // halt
  }
  
  Serial.println(F("----------------------------------"));
  Serial.println(F("Reading firmware version..."));
  uint8_t firmwareVersion[2];
  nfc.readEEprom(FIRMWARE_VERSION, firmwareVersion, sizeof(firmwareVersion));
  Serial.print(F("Firmware version="));
  Serial.print(firmwareVersion[1]);
  Serial.print(".");
  Serial.println(firmwareVersion[0]);

  Serial.println(F("----------------------------------"));
  Serial.println(F("Reading EEPROM version..."));
  uint8_t eepromVersion[2];
  nfc.readEEprom(EEPROM_VERSION, eepromVersion, sizeof(eepromVersion));
  Serial.print(F("EEPROM version="));
  Serial.print(eepromVersion[1]);
  Serial.print(".");
  Serial.println(eepromVersion[0]);

  /*
  Serial.println(F("----------------------------------"));
  Serial.println(F("Reading IRQ pin config..."));
  uint8_t irqConfig;
  nfc.readEEprom(IRQ_PIN_CONFIG, &irqConfig, 1));
  Serial.print(F("IRQ_PIN_CONFIG=0x"));
  Serial.println(irqConfig, HEX);

  Serial.println(F("----------------------------------"));
  Serial.println(F("Reading IRQ_ENABLE register..."));
  uint32_t irqEnable;
  nfc.readRegister(IRQ_ENABLE, &irqEnable));
  Serial.print(F("IRQ_ENABLE=0x"));
  Serial.println(irqConfig, HEX);
  */

  Serial.println(F("----------------------------------"));
  Serial.println(F("Enable RF field..."));
  setupRF();
}

uint32_t loopCnt = 0;
bool errorFlag = false;

ISO15693ErrorCode issueISO14443Command(uint8_t *cmd, uint8_t cmdLen, uint8_t **resultPtr) {
#ifdef DEBUG
  Serial.print(F("Issue Command 0x"));
  Serial.print(cmd[1], HEX);
  Serial.print("...\n");
#endif

  nfc.sendData(cmd, cmdLen);
  delay(10);

  if (0 == (nfc.getIRQStatus() & RX_SOF_DET_IRQ_STAT)) {
    return EC_NO_CARD;
  }

  uint32_t rxStatus;
  nfc.readRegister(RX_STATUS, &rxStatus);

  Serial.println(F("RX-Status="));

  uint16_t len = (uint16_t)(rxStatus & 0x000001ff);

  Serial.println(", len=");
  Serial.println(len);
  Serial.println("\n");

 *resultPtr = nfc.readData(len);
  if (0L == *resultPtr) {
    Serial.println(F("*** ERROR in readData!\n"));
    return ISO15693_EC_UNKNOWN_ERROR;
  }

#ifdef DEBUG
  Serial.print("Read=");
  for (int i=0; i<len; i++) {
    if (i<len-1) Serial.print(":");
  }
  Serial.println();
#endif

  uint32_t irqStatus = nfc.getIRQStatus();
  if (0 == (RX_SOF_DET_IRQ_STAT & irqStatus)) { // no card detected
     nfc.clearIRQStatus(TX_IRQ_STAT | IDLE_IRQ_STAT);
     return EC_NO_CARD;
  }

  uint8_t responseFlags = (*resultPtr)[0];
  if (responseFlags & (1<<0)) { // error flag
    uint8_t errorCode = (*resultPtr)[1];

    Serial.println("ERROR code=");
    Serial.println(" - ");
    Serial.println("\n");

    if (errorCode >= 0xA0) { // custom command error codes
      return ISO15693_EC_CUSTOM_CMD_ERROR;
    }
    else return (ISO15693ErrorCode)errorCode;
  }

#ifdef DEBUG
  if (responseFlags & (1<<3)) { // extendsion flag
    Serial.println("Extension flag is set!\n");
  }
#endif

  nfc.clearIRQStatus(RX_SOF_DET_IRQ_STAT | IDLE_IRQ_STAT | TX_IRQ_STAT | RX_IRQ_STAT);
  return ISO15693_EC_OK;
}

ISO15693ErrorCode getUID(uint8_t *uid) {
  //                     Flags,  CMD, maskLen
  uint8_t inventory[] = { 0x26, 0x01, 0x00 };
  //                        |\- inventory flag + high data rate
  //                        \-- 1 slot: only one card, no AFI field present
  Serial.println(F("Get UID...\n"));

  for (int i=0; i<8; i++) {
    uid[i] = 0;
  }

  uint8_t *readBuffer;
  ISO15693ErrorCode rc = issueISO14443Command(inventory, sizeof(inventory), &readBuffer);
  if (ISO15693_EC_OK != rc) {
    return rc;
  }

  Serial.println(F("Response flags: "));
  Serial.println(F(", Data Storage Format ID: "));
  Serial.println(F(", UID: "));

  for (int i=0; i<8; i++) {
    uid[i] = readBuffer[2+i];
#ifdef DEBUG
    if (i<2) Serial.println(":");
#endif
  }

  Serial.println("\n");

  return ISO15693_EC_OK;
}

ISO15693ErrorCode getSystemInfo(uint8_t *uid, uint8_t *blockSize, uint8_t *numBlocks) {
  uint8_t sysInfo[] = { 0x22, 0x2b, 1,2,3,4,5,6,7,8 };  // UID has LSB first!
  for (int i=0; i<8; i++) {
    sysInfo[2+i] = uid[i];
  }

#ifdef DEBUG
  Serial.println("Get System Information");
  for (int i=0; i<sizeof(sysInfo); i++) {
    Serial.println(" ");
  }
  Serial.println("\n");
#endif

  uint8_t *readBuffer;
  ISO15693ErrorCode rc = issueISO14443Command(sysInfo, sizeof(sysInfo), &readBuffer);
  if (ISO15693_EC_OK != rc) {
    return rc;
  }

  for (int i=0; i<8; i++) {
    uid[i] = readBuffer[2+i];
  }

#ifdef DEBUG
  Serial.println("UID=");
  for (int i=0; i<8; i++) {
    if (i<2) Serial.println(":");
  }
  Serial.println("\n");
#endif

  uint8_t *p = &readBuffer[10];

  uint8_t infoFlags = readBuffer[1];
  if (infoFlags & 0x01) { // DSFID flag
    uint8_t dsfid = *p++;
    Serial.println("DSFID=");  // Data storage format identifier
    Serial.println("\n");
  }
#ifdef DEBUG
  else Serial.println(F("No DSFID\n"));
#endif

  if (infoFlags & 0x02) { // AFI flag
    uint8_t afi = *p++;
    Serial.println(F("AFI="));  // Application family identifier
    Serial.println(F(" - "));
    switch (afi >> 4) {
      case 0: Serial.println(F("All families")); break;
      case 1: Serial.println(F("Transport")); break;
      case 2: Serial.println(F("Financial")); break;
      case 3: Serial.println(F("Identification")); break;
      case 4: Serial.println(F("Telecommunication")); break;
      case 5: Serial.println(F("Medical")); break;
      case 6: Serial.println(F("Multimedia")); break;
      case 7: Serial.println(F("Gaming")); break;
      case 8: Serial.println(F("Data storage")); break;
      case 9: Serial.println(F("Item management")); break;
      case 10: Serial.println(F("Express parcels")); break;
      case 11: Serial.println(F("Postal services")); break;
      case 12: Serial.println(F("Airline bags")); break;
      default: Serial.println(F("Unknown")); break;
    }
    Serial.println("\n");
  }
#ifdef DEBUG
  else Serial.println(F("No AFI\n"));
#endif

  if (infoFlags & 0x04) { // VICC Memory size
    *numBlocks = *p++;
    *blockSize = *p++;
    *blockSize = (*blockSize) & 0x1f;

    *blockSize = *blockSize + 1; // range: 1-32
    *numBlocks = *numBlocks + 1; // range: 1-256
    uint16_t viccMemSize = (*blockSize) * (*numBlocks);

    Serial.println("VICC MemSize=");
    Serial.println(viccMemSize);
    Serial.println(" BlockSize=");
    Serial.println(*blockSize);
    Serial.println(" NumBlocks=");
    Serial.println(*numBlocks);
    Serial.println("\n");
  }
#ifdef DEBUG
  else Serial.println(F("No VICC memory size\n"));
#endif

  if (infoFlags & 0x08) { // IC reference
    uint8_t icRef = *p++;
    Serial.println("IC Ref=");
    Serial.println("\n");
  }
#ifdef DEBUG
  else Serial.println(F("No IC ref\n"));
#endif

  return ISO15693_EC_OK;
}

ISO15693ErrorCode readSingleBlock(uint8_t *uid, uint8_t blockNo, uint8_t *blockData, uint8_t blockSize) {
  //                            flags, cmd, uid,             blockNo
  uint8_t readSingleBlock[] = { 0x22, 0x20, 1,2,3,4,5,6,7,8, blockNo }; // UID has LSB first!
  //                              |\- high data rate
  //                              \-- no options, addressed by UID
  for (int i=0; i<8; i++) {
    readSingleBlock[2+i] = uid[i];
  }

#ifdef DEBUG
  Serial.println("Read Single Block #");
  Serial.println(blockNo);
  Serial.println(", size=");
  Serial.println(blockSize);
  Serial.println(": ");
  for (int i=0; i<sizeof(readSingleBlock); i++) {
    Serial.println(" ");
  }
  Serial.println("\n");
#endif

  uint8_t *resultPtr;
  ISO15693ErrorCode rc = issueISO14443Command(readSingleBlock, sizeof(readSingleBlock), &resultPtr);
  if (ISO15693_EC_OK != rc) {
    return rc;
  }

  Serial.println("Value=");

  for (int i=0; i<blockSize; i++) {
    blockData[i] = resultPtr[2+i];
#ifdef DEBUG
    Serial.println(" ");
#endif
  }

#ifdef DEBUG
  Serial.println(" ");
  for (int i=0; i<blockSize; i++) {
    char c = blockData[i];
    if (isPrintable(c)) {
      Serial.println(c);
    }
    else Serial.println(".");
  }
  Serial.println("\n");
#endif

  return ISO15693_EC_OK;
}

void loop() {
  delay(1000);
  
  if (errorFlag) {
    uint32_t irqStatus = nfc.getIRQStatus();
    showIRQStatus(irqStatus);

    if (0 == (RX_SOF_DET_IRQ_STAT & irqStatus)) { // no card detected
      Serial.println(F("*** No card detected!"));
    }

    //nfc.reset();
    //nfc.setupRF();

    errorFlag = false;
  }

  Serial.println(F("----------------------------------"));
  Serial.print(F("Loop #"));
  Serial.println(loopCnt++);

  uint8_t uid[8];
  ISO15693ErrorCode rc = getUID(uid);
  if (ISO15693_EC_OK != rc) {
    Serial.print(F("Error in getUID: "));
    Serial.println(rc, HEX);
    errorFlag = true;
    return;
  }
  Serial.print(F("getUID successful, UID="));
  for (int i=0; i<8; i++) {
    Serial.print(uid[7-i], HEX); // LSB is first
    if (i < 2) Serial.print(":");
  }
  Serial.println();

  Serial.println(F("----------------------------------"));
  uint8_t blockSize, numBlocks;
  rc = getSystemInfo(uid, &blockSize, &numBlocks);
  if (ISO15693_EC_OK != rc) {
    Serial.print(F("Error in getSystemInfo: "));
    errorFlag = true;
    return;
  }
  Serial.print(F("System Info retrieved: blockSize="));
  Serial.print(blockSize);
  Serial.print(F(", numBlocks="));
  Serial.println(numBlocks);

  Serial.println(F("----------------------------------"));
  uint8_t readBuffer[blockSize];
  for (int no=0; no<numBlocks; no++) {
    rc = readSingleBlock(uid, no, readBuffer, blockSize);
    if (ISO15693_EC_OK != rc) {
      Serial.print(F("Error in readSingleBlock #"));
      Serial.print(no);
      Serial.print(": ");
      errorFlag = true;
      return;
    }
    Serial.print(F("Read block #"));
    Serial.print(no);
    Serial.print(": ");
    for (int i=0; i<blockSize; i++) {
      if (readBuffer[i] < 16) Serial.print("0");
      Serial.print(readBuffer[i], HEX);
      Serial.print(" ");
    }
    Serial.print(" ");
    for (int i=0; i<blockSize; i++) {
      if (isprint(readBuffer[i])) {
        Serial.print((char)readBuffer[i]);
      }
      else Serial.print(".");
    }
    Serial.println();
  }

#ifdef WRITE_ENABLED
  Serial.println(F("----------------------------------"));
  uint8_t *writeBuffer = malloc(blockSize);
  for (int i=0; i<blockSize; i++) {
    writeBuffer[i] = 0x80 + i;
  }
  for (int no=0; no<numBlocks; no++) {
    rc = nfc.writeSingleBlock(uid, no, writeBuffer, blockSize);
    if (ISO15693_EC_OK == rc) {
      Serial.print(F("Wrote block #"));
      Serial.println(no);
    }
    else {
      Serial.print(F("Error in writeSingleBlock #"));
      Serial.print(no);
      Serial.print(": ");
      errorFlag = true;
      return;
    }
  }
#endif /* WRITE_ENABLED */
}

void showIRQStatus(uint32_t irqStatus) {
  Serial.print(F("IRQ-Status 0x"));
  Serial.print(irqStatus, HEX);
  Serial.print(": [ ");
  if (irqStatus & (1<< 0)) Serial.print(F("RQ "));
  if (irqStatus & (1<< 1)) Serial.print(F("TX "));
  if (irqStatus & (1<< 2)) Serial.print(F("IDLE "));
  if (irqStatus & (1<< 3)) Serial.print(F("MODE_DETECTED "));
  if (irqStatus & (1<< 4)) Serial.print(F("CARD_ACTIVATED "));
  if (irqStatus & (1<< 5)) Serial.print(F("STATE_CHANGE "));
  if (irqStatus & (1<< 6)) Serial.print(F("RFOFF_DET "));
  if (irqStatus & (1<< 7)) Serial.print(F("RFON_DET "));
  if (irqStatus & (1<< 8)) Serial.print(F("TX_RFOFF "));
  if (irqStatus & (1<< 9)) Serial.print(F("TX_RFON "));
  if (irqStatus & (1<<10)) Serial.print(F("RF_ACTIVE_ERROR "));
  if (irqStatus & (1<<11)) Serial.print(F("TIMER0 "));
  if (irqStatus & (1<<12)) Serial.print(F("TIMER1 "));
  if (irqStatus & (1<<13)) Serial.print(F("TIMER2 "));
  if (irqStatus & (1<<14)) Serial.print(F("RX_SOF_DET "));
  if (irqStatus & (1<<15)) Serial.print(F("RX_SC_DET "));
  if (irqStatus & (1<<16)) Serial.print(F("TEMPSENS_ERROR "));
  if (irqStatus & (1<<17)) Serial.print(F("GENERAL_ERROR "));
  if (irqStatus & (1<<18)) Serial.print(F("HV_ERROR "));
  if (irqStatus & (1<<19)) Serial.print(F("LPCD "));
  Serial.println("]");
}
