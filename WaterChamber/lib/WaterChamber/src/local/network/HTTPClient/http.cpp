#include "http.hpp"

NetworkHTTP::NetworkHTTP(const std::string &google_script_id) : http(new HTTPClient),
                                                                _google_script_id(google_script_id),
                                                                _url(""),
                                                                httpCode(0) {}

NetworkHTTP::~NetworkHTTP() {}

void NetworkHTTP::begin()
{
    data = {
        .id = "",
        .timestamp = "",
        .max_temp = "",
        .num_temp_sensors = "",
        .water_level_liters = "",
        .water_level_percentage = "",
        .humidity = "",
        .humidity_temp = "",
        .temp_sensors = {"", "", "", "", "", "", "", "", "", ""}};
}

void NetworkHTTP::loop(const JsonDocument &local_doc)
{
    if (httpCode == HTTP_CODE_NOT_FOUND)
    {
        log_w("Google Script HTTP Code 404: Not Found");
        return;
    }
    data.id.assign(local_doc["id"].as<std::string>());
    data.timestamp.assign(local_doc["timestamp"].as<std::string>());
    data.max_temp.assign(local_doc["max_temp"].as<std::string>());
    data.num_temp_sensors.assign(local_doc["num_temp_sensors"].as<std::string>());
    data.water_level_liters.assign(local_doc["water_level_liters"].as<std::string>());
    data.water_level_percentage.assign(local_doc["water_level_percentage"].as<std::string>());
    data.humidity.assign(local_doc["humidity_dht"].as<std::string>());
    data.humidity_temp.assign(local_doc["humidity_temp_dht"].as<std::string>());
    for (int i = 0; i < sizeof(local_doc["temp_sensors"]) / sizeof(local_doc["temp_sensors"][0]); i++)
    {
        data.temp_sensors[i].assign(local_doc["temp_sensors"][i].as<std::string>());
    }
    // Create the URL
    _url = "https://script.google.com/macros/s/" + _google_script_id + "/exec?";
    _url += "id=" + data.id;
    _url += "&timestamp=" + data.timestamp;
    _url += "&max_temp=" + data.max_temp;
    _url += "&num_temp_sensors=" + data.num_temp_sensors;
    _url += "&water_level_liters=" + data.water_level_liters;
    _url += "&water_level_percentage=" + data.water_level_percentage;
    _url += "&humidity=" + data.humidity;
    _url += "&humidity_temp=" + data.humidity_temp;
    for (int i = 0; i < sizeof(data.temp_sensors) / sizeof(data.temp_sensors[0]); i++)
    {
        _url += "&temp_sensors=" + data.temp_sensors[i];
    }
    // Send the data
    http->begin(_url.c_str());
    httpCode = http->GET();
    if (httpCode > 0)
    {
        log_i("HTTP GET code: %d", httpCode);
        if (httpCode == HTTP_CODE_OK)
        {
            std::string payload = http->getString().c_str();
            log_i("HTTP GET payload: %s", payload.c_str());
        }

        http->end();
    }
}