#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <Arduino.h>
#include <string>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif

class Display : public LiquidCrystal_I2C
{
public:
    Display();
    virtual ~Display();
    void init();
    void printStr(std::string text);
    void displayKeyCodes(void);

private:
    uint8_t bell[8];
    uint8_t note[8];
    uint8_t clock[8];
    uint8_t heart[8];
    uint8_t duck[8];
    uint8_t check[8];
    uint8_t cross[8];
    uint8_t retarrow[8];
};

#endif // DISPLAY_HPP