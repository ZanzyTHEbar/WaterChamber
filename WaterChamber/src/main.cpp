#include <Arduino.h>
#include <secrets.h>  // WiFi credentials - not included in repo you need to create this file in the /includes directory

//* Network
//! Optional header files
#include <network/mDNS/MDNSManager.hpp>
#include <network/ota/OTA.hpp>
#include <utilities/network_utilities.hpp>  // various network utilities

//! Required header files
#include <EasyNetworkManager.h>  // (*)
#if USE_GOOGLE_SHEETS
#    include "local/network/HTTPClient/http.hpp"
#endif  // USE_GOOGLE_SHEETS
//* Data
#include <local/data/AccumulateData/accumulatedata.hpp>

//* Sensors
//* Temp local/io/Sensors
#include "local/io/sensors/temperature/towertemp.hpp"
//* Humidity local/io/Sensors
#include "local/io/sensors/humidity/Humidity.hpp"
//* Water Level local/io/Sensors
#include "local/io/sensors/water_level/waterlevelsensor.hpp"
//* Time stamp
#include "local/network/ntp/ntp.hpp"
//* Background tasks
#include "local/data/BackgroundTasks/timedtasks.hpp"

//* Objects
ProjectConfig configManager("easynetwork", DEFAULT_HOSTNAME);
WiFiHandler network(configManager, WIFI_SSID, WIFI_PASS, 1);
APIServer server(80, configManager, "/control", "/wifimanager",
                 "/userCommands");
OTA ota(configManager);
MDNSHandler mDNS(configManager, "_waterchamber", "data", "_tcp", "api_port",
                 "80");

NetworkNTP ntp;
#if USE_GOOGLE_SHEETS
NetworkHTTP http(GOOGLE_SCRIPT_ID);
#endif  // USE_GOOGLE_SHEETS
TowerTemp tower_temp;
Humidity humidity;
WaterLevelSensor waterLevelSensor(&tower_temp);

#if USE_GOOGLE_SHEETS
AccumulateData data(configManager, ntp, http, tower_temp, humidity,
                    waterLevelSensor);
#else
AccumulateData data(configManager, ntp, tower_temp, humidity, waterLevelSensor);
#endif  // USE_GOOGLE_SHEETS
TimedTasks timedTasks(data);

const int led1 = 4;

void setup() {
    pinMode(led1, OUTPUT);
    Serial.begin(115200);

    Serial.setDebugOutput(true);
    configManager.attach(&mDNS);
    configManager.load();  // load the config from flash
    network.begin();
    mDNS.begin();

    // handle the WiFi connection state changes
    switch (wifiStateManager.getCurrentState()) {
        case WiFiState_e::WiFiState_Disconnected: {
            break;
        }
        case WiFiState_e::WiFiState_Disconnecting: {
            break;
        }
        case WiFiState_e::WiFiState_ADHOC: {
            server.begin();
            log_d("[SETUP]: Starting API Server");
            break;
        }
        case WiFiState_e::WiFiState_Connected: {
            server.begin();
            log_d("[SETUP]: Starting API Server");
            break;
        }
        case WiFiState_e::WiFiState_Connecting: {
            break;
        }
        case WiFiState_e::WiFiState_Error: {
            break;
        }
    }
    ntp.begin();
#if USE_GOOGLE_SHEETS
    http.begin();
#endif  // USE_GOOGLE_SHEETS
    ota.begin();
    humidity.begin();
    tower_temp.begin();
    waterLevelSensor.begin();
}

void loop() {
    ota.handleOTAUpdate();
    data.loop();
    timedTasks.accumulateSensorData();
}