#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
//String knownBLEAddresses[] = {"6E:bc:55:18:cf:7b", "53:3c:cb:56:36:02", "40:99:4b:75:7d:2f", "5c:5b:68:6f:34:96"};
String knownBLEAddresses[] = {"0c:b8:15:ec:a5:8e"};
int RSSI_THRESHOLD = -55;
bool device_found;
int scanTime = 1;
BLEScan* pBLEScan;
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      for (int i = 0; i < (sizeof(knownBLEAddresses) / sizeof(knownBLEAddresses[0])); i++)
      {
        //Uncomment to Enable Debug Information
        //Serial.println("*************Start**************");
        //Serial.println(sizeof(knownBLEAddresses));
        //Serial.println(sizeof(knownBLEAddresses[0]));
        //Serial.println(sizeof(knownBLEAddresses)/sizeof(knownBLEAddresses[0]));
        //Serial.println(advertisedDevice.getAddress().toString().c_str());
        //Serial.println(knownBLEAddresses[i].c_str());
        //Serial.println("*************End**************");
        if (strcmp(advertisedDevice.getAddress().toString().c_str(), knownBLEAddresses[i].c_str()) == 0)
                        {
          device_found = true;
                          Serial.print("RSSI :");//debug
                          Serial.print(advertisedDevice.getRSSI());//debug
                          Serial.printf("-----Advertised Device********: %s \n", advertisedDevice.toString().c_str());//debug

                          break;
                        }
        else
          device_found = false;
      }
      //Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};
void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  //pinMode(LED_BUILTIN, OUTPUT);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}
void loop() {
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
//  for (int i = 0; i < foundDevices.getCount(); i++)
//  {
//    BLEAdvertisedDevice device = foundDevices.getDevice(i);
//    int rssi = device.getRSSI();
//    Serial.print(device.getAddress().toString().c_str());
//    Serial.print("-----");
//    Serial.print("RSSI: ");
//    Serial.println(rssi);
//    if (rssi > RSSI_THRESHOLD && device_found == true)
//      digitalWrite(LED_BUILTIN, HIGH);
//    else
//      digitalWrite(LED_BUILTIN, LOW);
//  }
  pBLEScan->clearResults();
  
}
