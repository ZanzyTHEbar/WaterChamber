#include <Arduino.h>
#include <secrets.h> // WiFi credentials - not included in repo you need to create this file in the /includes directory
// Config
#include <data/config/project_config.hpp>
#include <data/StateManager/StateManager.hpp>

// Network
#include <mDNS/MDNSManager.hpp>
#include <ota/OTA.hpp>
#include <wifihandler/wifiHandler.hpp>
#include <api/webserverHandler.hpp>
#if USE_GOOGLE_SHEETS
#include "local/network/HTTPClient/http.hpp"
#endif // USE_GOOGLE_SHEETS
// Data
#include <local/data/AccumulateData/accumulatedata.hpp>

// Sensors
// Temp local/io/Sensors
#include "local/io/sensors/temperature/towertemp.hpp"
// Humidity local/io/Sensors
#include "local/io/sensors/humidity/Humidity.hpp"
// Water Level local/io/Sensors
#include "local/io/sensors/water_level/waterlevelsensor.hpp"
// Time stamp
#include "local/network/ntp/ntp.hpp"
// Background tasks
#include "local/data/BackgroundTasks/timedtasks.hpp"

// Objects
ProjectConfig configManager(std::string(), "waterchamber");
WiFiHandler network(&configManager, &wifiStateManager, WIFI_SSID, WIFI_PASS, "waterchamber", 1);

APIServer server(80, &configManager, NULL, "/api/v1", "/wifimanager", "/userCommands");
OTA ota(&configManager);
MDNSHandler mDNS(&mdnsStateManager, &configManager, "_waterchamber", "data", "_tcp", "api_port", "80");

NetworkNTP ntp;
#if USE_GOOGLE_SHEETS
NetworkHTTP http(GOOGLE_SCRIPT_ID);
#endif // USE_GOOGLE_SHEETS
TowerTemp tower_temp;
Humidity humidity;
WaterLevelSensor waterLevelSensor(&tower_temp);

#if USE_GOOGLE_SHEETS
AccumulateData data(&configManager, &ntp, &http, &tower_temp, &humidity, &waterLevelSensor);
#else
AccumulateData data(&configManager, &ntp, &tower_temp, &humidity, &waterLevelSensor);
#endif // USE_GOOGLE_SHEETS
TimedTasks timedTasks(&data);

void setup()
{
	Serial.begin(115200);

	Serial.setDebugOutput(true);
	configManager.initConfig(); // call before load to initialise the structs
	configManager.load();		// load the config from flash

	network.setupWifi();
	mDNS.startMDNS();

	// handle the WiFi connection state changes
	switch (wifiStateManager.getCurrentState())
	{
	case WiFiState_e::WiFiState_Disconnected:
	{
		break;
	}
	case WiFiState_e::WiFiState_Disconnecting:
	{
		break;
	}
	case WiFiState_e::WiFiState_ADHOC:
	{
		// only start the API server if we have wifi connection
		// server.updateCommandHandlers("blink", blink);                // add a command handler to the API server - you can add as many as you want - you can also add methods.
		// server.updateCommandHandlers("helloWorld", printHelloWorld); // add a command handler to the API server - you can add as many as you want - you can also add methods.
		server.begin();
		log_d("[SETUP]: Starting API Server");
		break;
	}
	case WiFiState_e::WiFiState_Connected:
	{
		// only start the API server if we have wifi connection
		// server.updateCommandHandlers("blink", blink);                // add a command handler to the API server - you can add as many as you want - you can also add methods.
		// server.updateCommandHandlers("helloWorld", printHelloWorld); // add a command handler to the API server - you can add as many as you want - you can also add methods.
		server.begin();
		log_d("[SETUP]: Starting API Server");
		break;
	}
	case WiFiState_e::WiFiState_Connecting:
	{
		break;
	}
	case WiFiState_e::WiFiState_Error:
	{
		break;
	}
	}
	ntp.begin();
#if USE_GOOGLE_SHEETS
	http.begin();
#endif // USE_GOOGLE_SHEETS
	ota.SetupOTA();
	humidity.begin();
	tower_temp.begin();
	waterLevelSensor.begin();
}

void loop()
{
	ota.HandleOTAUpdate();
	data.loop();
	timedTasks.accumulateSensorData();
}