#include "events.hpp"

EventHandler::EventHandler(void)
    : projectConfig("easynetwork", DEFAULT_HOSTNAME),
      configHandler(projectConfig),
      waterConfig(projectConfig),
      network(projectConfig, WIFI_SSID, WIFI_PASS, 1),
      server(80, projectConfig, "/control", "/wifimanager", "/userCommands"),
      ota(projectConfig),
      mDNS(projectConfig, "_waterchamber", "data", "_tcp", "api_port", "80"),
      tower_temp(),
      humidity(),
      waterLevelSensor(tower_temp),
      loadCell(waterConfig),
#if USE_GOOGLE_SHEETS
      http(GOOGLE_SCRIPT_ID),
      data(projectConfig, ntp, http, tower_temp, humidity, waterLevelSensor),
#else
      data(projectConfig, ntp, tower_temp, humidity, waterLevelSensor,
           loadCell),
#endif
      timedTasks(data),
      multiplexer(WIRE_OBJECT, 0x70),
      load_cell_success(false) {
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

    projectConfig.attach(configHandler);
    projectConfig.registerUserConfig(&waterConfig);
    projectConfig.attach(network);
    projectConfig.attach(mDNS);
    configHandler.begin();  // load the projectConfig from flash
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
    load_cell_success = loadCell.begin();
    log_d("[EventHandler]: Initializing Load Cell %s",
          load_cell_success ? "Success" : "Failed");
}

void EventHandler::loop(void) {
    ota.handleOTAUpdate();
    data.loop();
    timedTasks.accumulateSensorData();
    //if (load_cell_success) {
    //    log_d("[EventHandler]: %0.3f", loadCell.readWeight());
    //}
}