#include "config.hpp"

Config::Config() : ProjectConfig("config"),
                   _last_config_change(false) {}

Config::~Config() {}

/**
 *@brief Initializes the structures with blank data to prevent empty memory sectors and nullptr errors.
 *@brief This is to be called in setup() before loading the config.
 */
void Config::initConfig()
{
    ProjectConfig::initConfig();

    this->configLocal.mqttConfig = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        false,
        false,
        1883,
        8883,
    };

    this->configLocal.ioConfig = {
        {false, false, false, false, false},
        {0, 0, 0, 0, 0},
        0,
    };
}

void Config::save(Configs *config)
{
    log_d("Saving config");
}

bool Config::reset()
{
    log_w("Resetting config");
    return clear();
}

void Config::load()
{
    log_d("Loading  config");
    if (this->_already_loaded)
    {
        log_w(" config already loaded");
        return;
    }

    std::string relay = "relay";
    std::string relay_pin = "relay_pin";
    for (int i = 0; i < sizeof(this->configLocal.ioConfig.relays_pin) / sizeof(this->configLocal.ioConfig.relays_pin[0]); i++)
    {
        char buffer[2];
        std::string iter_str = Helpers::itoa(i, buffer, 10);
        relay.append(iter_str);
        relay_pin.append(iter_str);

        this->configLocal.ioConfig.relays[i] = getBool(relay.c_str(), false);
        this->configLocal.ioConfig.relays_pin[i] = getInt(relay_pin.c_str(), 0);
    }
    this->configLocal.ioConfig.numTempSensors = getInt("numTempSensors", 0);

    ProjectConfig::load();
}

//**********************************************************************************************************************
//*
//!                                                LocalConfig
//*
//**********************************************************************************************************************

void Config::setIOConfig(bool *relays,
                         int *relays_pin,
                         int *numTempSensors,
                         bool *shouldNotify)
{
    log_d("Updating IO config");
    for (int i = 0; i < sizeof(this->configLocal.ioConfig.relays_pin) / sizeof(this->configLocal.ioConfig.relays_pin[0]); i++)
    {
        this->configLocal.ioConfig.relays[i] = relays[i];
        this->configLocal.ioConfig.relays_pin[i] = relays_pin[i];
    }
    this->configLocal.ioConfig.numTempSensors = *numTempSensors;

    if (shouldNotify)
    {
        this->notify(ObserverEvent::ioConfigUpdated);
    }
}
