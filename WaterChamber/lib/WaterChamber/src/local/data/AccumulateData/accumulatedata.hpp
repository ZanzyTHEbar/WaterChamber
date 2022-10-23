#ifndef ACCUMULATEDATA_HPP
#define ACCUMULATEDATA_HPP
#include <ArduinoJson.h>
#include <lists.h>
#include <vector>

// data Struct
#include "local/data/Config/config.hpp"
#include "data/StateManager/StateManager.hpp"

// Temp local/io/Sensors
#include "local/io/sensors/temperature/towertemp.hpp"

// Humidity local/io/Sensors
#include "local/io/sensors/humidity/Humidity.hpp"

// Water Level local/io/Sensors
#include "local/io/sensors/water_level/waterlevelsensor.hpp"

#include "local/io/Relays/relays.hpp"
#include "local/io/Pump/pump.hpp"

class AccumulateData
{
public:
    AccumulateData(TowerTemp *tower_temp, Humidity *humidity, LDR *ldr, WaterLevelSensor *waterLevelSensor, PHSENSOR *phsensor, PUMP *pump, Relays *relays);
    virtual ~AccumulateData();

    void begin();

    void InitAccumulateData();
    bool SendData();

private:
    // Stack Data to send
    int _maxTemp;
    int _numTempSensors;
    TowerTemp *tower_temp;
    Humidity *humidity;
    WaterLevelSensor *waterLevelSensor;
    PHSENSOR *phsensor;
    PUMP *pump;
    Relays *relays;
};
#endif
