/*
 HTTP.h - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
*/
#pragma once
#ifndef NETWORKHTTP_hpp
#define NETWORKHTTP_hpp
#include <memory>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <strTools.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <local/network/ntp/ntp.hpp>

class NetworkHTTP
{
public:
    // constructors
    NetworkHTTP(const std::string &google_script_id);
    virtual ~NetworkHTTP();
    // Functions
    void begin();
    void loop(const JsonDocument &local_doc);

    // Private variables
private:
    // HTTP Servers:
    std::unique_ptr<HTTPClient> http;
    std::string _google_script_id;
    std::string _url;
    int httpCode;
    struct Data {
        std::string id;
        std::string timestamp;
        std::string max_temp;
        std::string num_temp_sensors;
        std::string water_level_liters;
        std::string water_level_percentage;
        std::string humidity;
        std::string humidity_temp;
        std::string temp_sensors[10];
    };
    Data data;
};
#endif