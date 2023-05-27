#include "multiplexer.hpp"

I2C_Multiplexer::I2C_Multiplexer(TwoWire* pWire, uint8_t addr)
    : _pWire(pWire), _I2CMultiplexer_addr(addr) {}

I2C_Multiplexer::~I2C_Multiplexer() {}

void I2C_Multiplexer::begin(void) {
    _pWire->begin();
}

uint8_t* I2C_Multiplexer::scan(uint8_t port) {
    static uint8_t dev[127] = {0};
    memset(dev, 0, sizeof(dev));
    uint8_t i = 0;
    selectPort(port);
    byte error, address;
    for (address = 1; address < 127; address++) {
        if (address == _I2CMultiplexer_addr)
            continue;
        _pWire->beginTransmission(address);
        error = _pWire->endTransmission();
        if (error == 0) {
            dev[i] = address;
            i++;
        }
    }
    return dev;
}

void I2C_Multiplexer::selectPort(uint8_t port) {
    // To prevent multiple expansion modules from colliding, add a parameter to
    // close all channels
    if (port > 8)
        return;
    _pWire->beginTransmission(_I2CMultiplexer_addr);
    _pWire->write((1 << port) & 0xFF);
    _pWire->endTransmission();
}

void I2C_Multiplexer::write(uint8_t port, uint8_t addr, uint8_t reg,
                            uint8_t* buf, uint8_t len) {
    selectPort(port);
    _pWire->beginTransmission(addr);
    _pWire->write(reg);
    uint8_t i = 0;
    for (i = 0; i < len; i++) {
        _pWire->write(*buf);
        buf++;
    }
    _pWire->endTransmission();
}

uint8_t I2C_Multiplexer::read(uint8_t port, uint8_t addr, uint8_t reg,
                              uint8_t* data, uint8_t len) {
    selectPort(port);
    int i = 0;
    _pWire->beginTransmission(addr);
    _pWire->write(reg);
    _pWire->endTransmission();
    _pWire->requestFrom(addr, len);
    while (_pWire->available()) {
        data[i++] = _pWire->read();
    }
    return i;
}