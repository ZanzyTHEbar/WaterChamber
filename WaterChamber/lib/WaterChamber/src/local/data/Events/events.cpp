#include "events.hpp"

EventHandler::EventHandler(void)
    : configManager("easynetwork", DEFAULT_HOSTNAME),
      network(configManager, WIFI_SSID, WIFI_PASS, 1),
      server(80, configManager, "/control", "/wifimanager", "/userCommands"),
      ota(configManager),
      mDNS(configManager, "_waterchamber", "data", "_tcp", "api_port", "80"),
      tower_temp(),
      humidity(),
      waterLevelSensor(tower_temp),
      loadCell(),
#if USE_GOOGLE_SHEETS
      http(GOOGLE_SCRIPT_ID),
      data(configManager, ntp, http, tower_temp, humidity, waterLevelSensor),
#else
      data(configManager, ntp, tower_temp, humidity, waterLevelSensor),
#endif
      timedTasks(data),
      multiplexer(WIRE_OBJECT, 0x70) {
}

EventHandler::~EventHandler(void) {}

void EventHandler::begin(void) {
    Serial.begin(115200);
    multiplexer.begin();

    log_d("[EventHandler]: Multiplexer Initialized");
    /*log_d("[EventHandler]: Scanning for connected devices");
     for (uint8_t port = 0; port <= 8; port++) {
        log_i("[EventHandler]: Scanning multiplexer channel %d", port);
        uint8_t* devices = multiplexer.scan(port);
        while (*devices) {
            log_i("[EventHandler]: Found device at address 0x%02x", *devices);
            devices++;
        }
    } */

    Serial.setDebugOutput(PRODUCTION);
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

    log_d("[EventHandler]: Scanning multiplexer for Load Cell");
    multiplexer.selectPort(0);
    log_d("[EventHandler]: Initializing Load Cell %s",
          loadCell.begin() ? "Success" : "Failed");
    // Manually set the calibration values
    //loadCell.setCalibration(2236.f);
    //// remove the peel
    //loadCell.peel();
    // Set the calibration weight when the weight sensor module is automatically
    // calibrated (g)
    loadCell.setCalWeight(50);
    // Set the trigger threshold (G) for automatic calibration of the weight
    // sensor module. When only the weight of the object on the scale is greater
    // than this value, the module will start the calibration process This value
    // cannot be greater than the calibration weight of the setCalWeight()
    // setting
    loadCell.setThreshold(50);

    delay(2000);
    // Start sensor calibration
    loadCell.enableCal();
    long time1 = millis();
    // Wait for sensor calibration to complete
    while (!loadCell.getCalFlag()) {
        delay(1000);
        if ((millis() - time1) > 7000) {
            Serial.println(
                "Calibration failed, no weight was detected on the scale");
            Serial.println(
                "Please check whether the weight sensor module is placed "
                "correctly on the scale");
            Serial.println(
                "Restarting calibration after 2 seconds, please wait.");
            delay(2000);
        }
    }

    // Obtain the calibration value. The accurate calibration value can be
    // obtained after the calibration operation is completed
    Serial.print("the calibration value of the sensor is: ");
    Serial.println(loadCell.getCalibration());
    loadCell.setCalibration(loadCell.getCalibration());
    delay(1000);
}

void EventHandler::loop(void) {
    Serial.print("weight is: ");
    Serial.print(loadCell.readWeight(), 1);
    Serial.println(" g");
    delay(1500);
    ota.handleOTAUpdate();
    data.loop();
    timedTasks.accumulateSensorData();
}