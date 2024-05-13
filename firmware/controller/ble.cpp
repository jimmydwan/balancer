
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "BLEDevice.h"
#include "driver/uart.h"
#include "ble.h"
unsigned char BLEBUF[13];
extern HardwareSerial serial1;

bool deviceConnected = false;
extern char lyValue, lxValue, ryValue, rxValue;

// Humidity Characteristic and Descriptor
BLECharacteristic txCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor txDescriptor(BLEUUID((uint16_t)0x2903));

// Setup callbacks onConnect and onDisconnect
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    pServer->getAdvertising()->start();
  }
};

BLECharacteristic *pTxCharacteristic;

void bleInit() {
  // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *bmeService = pServer->createService(SERVICE_UUID);

  bmeService->addCharacteristic(&txCharacteristics);
  txDescriptor.setValue("joyStick");
  txCharacteristics.addDescriptor(new BLE2902());

  // Start the service
  bmeService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  serial1.println("Waiting a client connection to notify...");
}

void blePolling() {
  if (deviceConnected) {
    serial1.printf("connected\n");

    BLEBUF[0] = 0xA5;     // 包头
    BLEBUF[1] = lxValue;  //
    BLEBUF[2] = lyValue;  //
    BLEBUF[3] = rxValue;  //
    BLEBUF[4] = ryValue;  //

    BLEBUF[5] = 0x5A;  // 包尾

    txCharacteristics.setValue(BLEBUF, 6);
    txCharacteristics.notify();
  }
}