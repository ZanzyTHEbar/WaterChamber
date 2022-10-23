/*
 config.hpp - ESP32GreenHouseDIY library
 Copyright (c) 2021 ZanzyTHEbar
*/

#pragma once
#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <data/config/project_config.hpp>
#include <data/utilities/enuminheritance.hpp>

class Config : public ProjectConfig
{
public:
    Config();
    virtual ~Config();

    struct IOConfig_t
    {
        bool relays[5];
        int relays_pin[5];
        int numTempSensors;
    };

    struct Config_t
    {
        // Variables
        IOConfig_t ioConfig;
    };

    void load();
    void save();
    bool reset();
    void initConfig();

    // trigger a config write/commit
    bool setConfigChanged();
    bool updateCurrentData();

private:
    // save last "timestamp" the config has been saved
    Config_t configLocal;
};

extern Config cfg;
#endif
// EOF