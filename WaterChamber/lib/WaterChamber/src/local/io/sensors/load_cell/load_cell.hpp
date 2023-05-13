/*
 WaterlevelSensor.h - ESP32GreenHouseDIY Distance Sensor library
 Copyright (c) 2021 ZanzyTHEbar
 */
#pragma once
#ifndef LOAD_CELL_HPP
#    define LOAD_CELL_HPP

#    include <Wire.h>
#    include "Arduino.h"

#    define HX711_I2C_ADDR (0x64)  ///< sensor IIC address

#    define REG_CLEAR_REG_STATE 0x65    ///< Get sensor raw data
#    define REG_DATA_GET_RAM_DATA 0x66  ///< Get sensor raw data
#    define REG_DATA_GET_CALIBRATION \
        0x67  ///< Gets the automatic calibration value
#    define REG_DATA_GET_PEEL_FLAG 0x69  ///< Obtain peeling position
#    define REG_DATA_INIT_SENSOR 0x70    ///< Module initialization
#    define REG_SET_CAL_THRESHOLD \
        0x71  ///< Set the calibration trigger threshold
#    define REG_SET_TRIGGER_WEIGHT 0x72  ///< Set calibration weight

#    define REG_CLICK_RST 0x73  ///< Simulation of RST
#    define REG_CLICK_CAL 0x74  ///< Simulation of CAL

class LoadCell {
    //* Private variables

    TwoWire& _pWire;
    uint8_t _address;
    uint8_t pFlag;
    long _offset;
    float _calibration;

    //* Private functions
    double readSensor(uint8_t times = 12);

    long getValue();
    uint8_t peelFlag();
    long average(uint8_t times = 10);

    int readReg(uint8_t reg, uint8_t* data, size_t size);

    uint8_t writeReg(uint8_t reg, const void* data, size_t size);

   public:
    //* Constructor
    LoadCell(TwoWire& pWire = Wire, uint8_t addr = HX711_I2C_ADDR);
    virtual ~LoadCell(void);
    bool begin(void);

    //* Calibration
    float getCalibrationValue(void);
    void setCalibration(float value);
    void setCalWeight(uint16_t triWeight);
    void setThreshold(uint16_t threshold);
    void enableCalibration(void);
    void peel(void);
    bool getCalFlag();
};
#endif