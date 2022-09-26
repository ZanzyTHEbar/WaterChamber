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

    switch (*config)
    {
    case Configs::IOConfig:
    { /* IO Config */
        std::string relay = "relay";
        std::string relay_pin = "relay_pin";
        for (int i = 0; i < sizeof(this->configLocal.ioConfig.relays_pin) / sizeof(this->configLocal.ioConfig.relays_pin[0]); i++)
        {
            char buffer[2];
            std::string iter_str = Helpers::itoa(i, buffer, 10);
            relay.append(iter_str);
            relay_pin.append(iter_str);

            putBool(relay.c_str(), this->configLocal.ioConfig.relays[i]);
            putInt(relay_pin.c_str(), this->configLocal.ioConfig.relays_pin[i]);
        }
        putInt("numTempSensors", this->configLocal.ioConfig.numTempSensors);
        break;
    }
    case Configs::MQTTConfig:
    { /* MQTT Config */
        putString("MQTTClientID", this->configLocal.mqttConfig.MQTTClientID.c_str());
        putString("MQTTUser", this->configLocal.mqttConfig.MQTTUser.c_str());
        putString("MQTTPass", this->configLocal.mqttConfig.MQTTPass.c_str());
        putString("MQTTTopic", this->configLocal.mqttConfig.MQTTTopic.c_str());
        putString("MQTTSetTopic", this->configLocal.mqttConfig.MQTTSetTopic.c_str());
        putString("MQTTDeviceName", this->configLocal.mqttConfig.MQTTDeviceName.c_str());
        putString("MQTTBroker", this->configLocal.mqttConfig.MQTTBroker.c_str());
        putBool("MQTTSecure", this->configLocal.mqttConfig.MQTTSecureState);
        putBool("MQTTConnected", this->configLocal.mqttConfig.MQTTConnectedState);
        putInt("MQTTPort", this->configLocal.mqttConfig.MQTTPort);
        putInt("MQTTPort_Secure", this->configLocal.mqttConfig.MQTTPort_Secure);
        break;
    }
    default:
        break;
    }

    ProjectConfig::save();
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

    this->configLocal.mqttConfig = {
        getString("MQTTClientID", "").c_str(),
        getString("MQTTUser", "").c_str(),
        getString("MQTTPass", "").c_str(),
        getString("MQTTTopic", "").c_str(),
        getString("MQTTSetTopic", "").c_str(),
        getString("MQTTDeviceName", "").c_str(),
        getString("MQTTBroker", "").c_str(),
        getBool("MQTTSecure", false),
        getBool("MQTTConnected", false),
        getInt("MQTTPort", 1883),
        getInt("MQTTPort_Secure", 8883),
    };

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
void Config::setMQTTConfig(const std::string &MQTTClientID,
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
                           bool *shouldNotify)
{
    log_d("Updating MQTT config");
    this->configLocal.mqttConfig.MQTTClientID.assign(MQTTClientID);
    this->configLocal.mqttConfig.MQTTUser.assign(MQTTUser);
    this->configLocal.mqttConfig.MQTTPass.assign(MQTTPass);
    this->configLocal.mqttConfig.MQTTTopic.assign(MQTTTopic);
    this->configLocal.mqttConfig.MQTTSetTopic.assign(MQTTSetTopic);
    this->configLocal.mqttConfig.MQTTDeviceName.assign(MQTTDeviceName);
    this->configLocal.mqttConfig.MQTTBroker.assign(MQTTBroker);
    this->configLocal.mqttConfig.MQTTSecureState = MQTTSecureState;
    this->configLocal.mqttConfig.MQTTConnectedState = *MQTTConnectedState;
    this->configLocal.mqttConfig.MQTTPort = *MQTTPort;
    this->configLocal.mqttConfig.MQTTPort_Secure = *MQTTPort_Secure;

    if (shouldNotify)
    {
        this->notify(_event. Config_Events::MQTTConfigChanged);
    }
}

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
