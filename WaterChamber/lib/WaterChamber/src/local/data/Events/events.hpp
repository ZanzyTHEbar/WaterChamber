#pragma once

#include <Arduino.h>
#include "secrets.h"  // WiFi credentials - not included in repo you need to create this file in the /includes directory

#include "local/io/multiplexer/multiplexer.hpp"

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
//* Load Cell
#include "local/io/sensors/load_cell/load_cell.hpp"

//* Time stamp
#include "local/network/ntp/ntp.hpp"
//* Background tasks
#include "local/data/BackgroundTasks/timedtasks.hpp"

//* Scanner
#include "local/io/i2cscanner/i2cscan.hpp"

#define WIRE_OBJECT &Wire

class EventHandler {
   private:
    //! Objects

    ProjectConfig configManager;

    //* Network
    WiFiHandler network;
    APIServer server;
    OTA ota;
    MDNSHandler mDNS;
    NetworkNTP ntp;

    //* Sensors
    TowerTemp tower_temp;
    Humidity humidity;
    WaterLevelSensor waterLevelSensor;
    LoadCell loadCell;

//* Data
#if USE_GOOGLE_SHEETS
    NetworkHTTP http;
    AccumulateData data;
#else   // USE_GOOGLE_SHEETS
    AccumulateData data;
#endif  // USE_GOOGLE_SHEETS
    TimedTasks timedTasks;

    I2C_Multiplexer multiplexer;

   public:
    EventHandler();
    ~EventHandler();

    void begin(void);
    void loop(void);
};