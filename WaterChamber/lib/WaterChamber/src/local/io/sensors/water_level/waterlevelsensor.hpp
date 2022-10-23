/*
 WaterlevelSensor.h - ESP32GreenHouseDIY Distance Sensor library
 Copyright (c) 2021 ZanzyTHEbar
 */
#pragma once
#ifndef WATERLEVELSENSOR_HPP
#define WATERLEVELSENSOR_HPP
#include <memory>
#include <functional>
#include <HCSR04.h>
#if USE_CAP
#include "calibrationbutton.hpp"
#endif // USE_CAP

#include "local/io/sensors/temperature/towertemp.hpp"

class WaterLevelSensor
{
public:
    // Constructor
#if USE_CAP
    WaterLevelSensor(CalibrationButton *_calibrationButton, 
                     TowerTemp *_towerTemp);
#else
    WaterLevelSensor(TowerTemp *_towerTemp);
#endif // USE_CAP

    virtual ~WaterLevelSensor();
    void begin();
    double readSensor();
    // Read the water level

    int getWaterLevel();
    int getPercentage();

private:
    // Private variables
    double _radius;
    double _height;
    bool _activateCalibration;
    byte _depth;
    byte _depthRange;
    int _depthArray[100];
    int _qNumberReadings[100];
    int _qNumberDepth[100];
    struct Calibration_t
    {
        int _min;
        int _max;
    };
    Calibration_t _calibration;

    // Private functions
    int readWaterLevelUltraSonic();
    int readWaterLevelCapacitive();
    void calibrateSensor();
    void setCapSensorRange();
    int convertToQNumber(int readings);
    void convertToQNumber(int *readings, int *depth);

    void holdCallback(void);
    void quickCallback(void);
    void longholdCallback(void);

    std::shared_ptr<UltraSonicDistanceSensor> _distanceSensor; // Initialize sensor that uses digital pins 13 and 12.
#if USE_CAP
    CalibrationButton *_calibrationButton;
#endif // USE_CAP
    TowerTemp *_towerTemp;
};
#endif
