#ifndef RELAYS_HPP
#define RELAYS_HPP
#include <Arduino.h>
#include <vector>
//#include <PID_v1.h>

class Relays
{
public:
    Relays();
    virtual ~Relays();
    bool begin();
    void relayOnOff(int relay, bool state);
    void setupPID();

    struct Pins_t
    {
        std::vector<uint8_t> relay_pins;
    };

    Pins_t pins;

#if USE_SHT31_SENSOR
    void humRelayOnOff();
#endif // USE_SHT31_SENSOR

private:
#if USE_PID
    double _Setpoint, _Input, _Output;
    int _WindowSize;
    unsigned long _windowStartTime;
    PID myPID;
#endif // USE_PID
};
extern Relays Relay;
#endif