#pragma once
#include <Arduino.h>
#include "Wire.h"

class I2C_Multiplexer {
    TwoWire* _pWire;
    uint8_t _I2CMultiplexer_addr;

   public:
    I2C_Multiplexer(TwoWire* pWire, uint8_t addr);
    ~I2C_Multiplexer();

    /**
     * @fn begin
     * @brief IIC initialize
     */
    void begin(void);

    /**
     * @fn scan
     * @brief Scan all I2C devices connected to the I2C cascade module
     * @param port   Specify the port for scanning
     * @return uint8_t* Return the I2C address of all devices
     */
    uint8_t* scan(uint8_t port);

    /**
     * @fn selectPort
     * @brief Enable a specific channel on the I2C multiplexer or disable all
     * channels
     * @param port - Select channel, range: 0- 8
     * @n 0-7 for enabling the corresponding channel separately, 8 for disabling
     * all channels
     * @note When“multiple multiplexer modules” are used on one I2C bus to
     * connect “sensors with same I2C address”, to avoid conflicts,
     * @n it is necessary to ensure that “the currently used channel”is the only
     * enabled one among “all channels in all multiplexers”
     * @n For instance, when one of the channels in the first multiplexer is
     * enabled, in order to use any channel in the second multiplexer,
     * @n please make sure that the channels in the first multiplexer are all
     * disabled.
     */
    void selectPort(uint8_t port);

    /**
     * @fn read
     * @brief   Read the data of the target I2C device
     * @param port    The I2C port that the target device is connected to
     * @param addr    I2C address of the target device
     * @param reg     Register of the target device to be read
     * @param data    Data of the target device to be stored
     * @param len     Data length of the target device to be read
     * @return uint8_t read status
     */
    uint8_t read(uint8_t port, uint8_t addr, uint8_t reg, uint8_t* data,
                 uint8_t len);

    /**
     * @fn write
     * @brief    Write the data into the target I2C device
     * @param port    The I2C port that the target device is connected to
     * @param addr    I2C address of the target device
     * @param reg     Register of the target device to be written
     * @param buf     Data of the target device to be written
     * @param len     Data length of the target device to be written
     */
    void write(uint8_t port, uint8_t addr, uint8_t reg, uint8_t* buf,
               uint8_t len);
};