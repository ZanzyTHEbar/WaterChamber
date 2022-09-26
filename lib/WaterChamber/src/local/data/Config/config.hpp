/*
 config.hpp - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
*/

#pragma once
#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <defines.hpp>
#include <observer.hpp>
#include <data/config/project_config.hpp>
#include <data/utilities/enuminheritance.hpp>

namespace ObserverEvent
{
    enum Config_Events
    {
        ConfigChanged,
        MQTTConfigChanged,
        IOConfigChanged,
    };
}

typedef InheritEnum<ObserverEvent::Event, ObserverEvent::Config_Events> Events;

class Config : public ProjectConfig
{
public:
    Config();
    virtual ~Config();

    enum Configs
    {
        MQTTConfig,
        IOConfig,
    };

    struct MQTTConfig_t
    {
        std::string MQTTClientID;
        std::string MQTTUser;
        std::string MQTTPass;
        std::string MQTTTopic;
        std::string MQTTSetTopic;
        std::string MQTTDeviceName;
        std::string MQTTBroker;
        bool MQTTSecureState;
        bool MQTTConnectedState;
        int MQTTPort;        // Port to use for unsecured MQTT
        int MQTTPort_Secure; // port to use if Secured MQTT is enabled
    };

    struct IOConfig_t
    {
        bool relays[5];
        int relays_pin[5];
        int numTempSensors;
    };

    struct Config_t
    {
        // Variables
        MQTTConfig_t mqttConfig;
        IOConfig_t ioConfig;
    };

    // Config_t *getConfig() { return &this->config; }
    MQTTConfig_t *getMQTTConfig() { return &this->configLocal.mqttConfig; }
    IOConfig_t *getIOConfig() { return &this->configLocal.ioConfig; }

    void setMQTTConfig(const std::string &MQTTClientID,
                       const std::string &MQTTUser,
                       const std::string &MQTTPass,
                       const std::string &MQTTTopic,
                       const std::string &MQTTSetTopic,
                       const std::string &MQTTDeviceName,
                       const std::string &MQTTBroker,
                       bool *MQTTSecureState,
                       bool *MQTTConnectedState,
                       int *MQTTPort,
                       int *MQTTPort_Secure,
                       bool *shouldNotify);

    void setIOConfig(bool *relays, int *relays_pin, int *numTempSensors, bool *shouldNotify);

    void load();
    void save(Configs *config);
    bool reset();
    void initConfig();

    // trigger a config write/commit
    bool setConfigChanged();
    bool updateCurrentData();
    bool isValidHostname(const std::string &hostname_to_check, long size);
    // parse and set a new hostname to config
    void setHostname(const std::string &new_hostname);
    void CreateDefaultConfig();

private:
    // save last "timestamp" the config has been saved
    bool _last_config_change;
    Config_t configLocal;
    Events _event;
};

extern Config cfg;
#endif
// EOF