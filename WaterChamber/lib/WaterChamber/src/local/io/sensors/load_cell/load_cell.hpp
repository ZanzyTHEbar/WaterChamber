#ifndef LOAD_CELL_HPP
#define LOAD_CELL_HPP

#include <Arduino.h>
#include <Wire.h>
#include <local/data/config/config.hpp>
#include <vector>

#define HX711_I2C_ADDR (0x64)  ///< sensor IIC address

class LoadCell {
   public:
#define REG_CLEAR_REG_STATE 0x65       ///< Get sensor raw data
#define REG_DATA_GET_RAM_DATA 0x66     ///< Get sensor raw data
#define REG_DATA_GET_CALIBRATION 0x67  ///< Gets the automatic calibration value
#define REG_DATA_GET_PEEL_FLAG 0x69    ///< Obtain peeling position
#define REG_DATA_INIT_SENSOR 0x70      ///< Module initialization
#define REG_SET_CAL_THRESHOLD 0x71   ///< Set the calibration trigger threshold
#define REG_SET_TRIGGER_WEIGHT 0x72  ///< Set calibration weight

#define REG_CLICK_RST 0x73  ///< Simulation of RST
#define REG_CLICK_CAL 0x74  ///< Simulation of CAL
    /**
     * @fn LoadCell
     * @brief Constructor
     * @param pWire I2c controller
     * @param addr  I2C address(0x64/0x65/0x660x67)
     */
    LoadCell(WaterConfig& waterConfig, TwoWire* pWire = &Wire,
             uint8_t addr = HX711_I2C_ADDR);

    /**
     * @fn ~LoadCell
     * @brief De-Constructor
     */
    virtual ~LoadCell();

    /*!
     * @fn begin
     * @brief init function
     * @return return 1 if initialization succeeds, otherwise return non-zero
     * and error code.
     */
    bool begin(void);

    /*!
     * @fn readWeight
     * @brief Get the weight of the object
     * @param times Take the average several times
     * @return return the read weight value, unit: g
     */
    float readWeight(uint8_t times = 12);

    /*!
     * @fn getCalibration
     * @brief get calibration value
     * @return return the read calibration value
     */
    float getCalibration();

    /*!
     * @fn setCalibration
     * @brief Set calibration value
     * @param value the calibration value
     */
    void setCalibration(float value);

    /*!
     * @fn setThreshold
     * @brief Set the trigger threshold when the weight sensor module is
     * automatically calibrated(g)
     * @param threshold threshold
     */
    void setThreshold(uint16_t threshold);

    /*!
     * @fn setCalWeight
     * @brief Set the calibration weight when the weight sensor module is
     * automatically calibrated(g)
     * @param triWeight   Weight
     */
    void setCalWeight(uint16_t triWeight);

    /*!
     * @fn enableCal
     * @brief Start sensor calibration
     */
    void enableCal();

    /*!
     * @fn peel
     * @brief remove the peel
     */
    void peel();

    /*!
     * @fn getCalFlag
     * @brief Wait for sensor calibration to complete
     * @return Result
     * @retval true The calibration completed
     * @retval false The calibration is not complete
     */
    bool getCalFlag();

   private:
    long getValue();
    uint8_t peelFlag();
    long average(uint8_t times = 10);

    int readReg(uint8_t reg, uint8_t* data, size_t size);

    uint8_t writeReg(uint8_t reg, const void* data, size_t size);
    uint8_t _address;
    uint8_t _pFlag = 0;
    long _offset;
    TwoWire* _pWire;
    float _calibration;
    std::vector<long> _readings;
    long _total;
    long _average;
    uint8_t _index;
    WaterConfig& waterConfig;
};
#endif