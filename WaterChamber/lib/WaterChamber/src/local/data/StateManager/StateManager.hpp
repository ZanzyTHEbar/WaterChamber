#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <Arduino.h>

/*
 * StateManager
 * All Project States are managed here
 */
struct DeviceStates
{

    enum SensorStates_e
    {
        SensorStates_None,
        SensorStates_Starting,
        SensorStates_Started,
        SensorStates_Stopping,
        SensorStates_Stopped,
        SensorStates_Error
    };

    enum LEDStates_e
    {
        _LEDOff,
        _LEDOn,
        _LEDBlink,
        _LEDBlinkFast,
        _WiFiState_None,
        _WiFiState_Connecting,
        _WiFiState_Connected,
        _WiFiState_Disconnected,
        _WiFiState_Disconnecting,
        _WiFiState_ADHOC,
        _WiFiState_Error,
        _SensorStates_None,
        _SensorStates_Starting,
        _SensorStates_Started,
        _SensorStates_Stopping,
        _SensorStates_Stopped,
        _SensorStates_Error,
    };
};

/*
 * EventManager
 * All Project Events are managed here
 */
template <class T>
class StateManager
{
public:
    StateManager() {}

    virtual ~StateManager() {}

    void setState(T state)
    {
        _current_state = state;
    }

    /*
     * Get States
     * Returns the current state of the device
     */
    T getCurrentState()
    {
        return _current_state;
    }

private:
    T _current_state;
};

typedef DeviceStates::SensorStates_e SensorStates_e;
typedef DeviceStates::LEDStates_e LEDStates_e;

extern StateManager<SensorStates_e> SensorStatesManager;
extern StateManager<LEDStates_e> ledStateManager;

#endif // STATEMANAGER_HPP