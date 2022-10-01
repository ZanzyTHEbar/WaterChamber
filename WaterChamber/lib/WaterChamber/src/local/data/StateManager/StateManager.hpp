#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include <Arduino.h>

/*
 * StateManager
 * All Project States are managed here
 */
struct DeviceStates
{
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
        _WebServerState_None,
        _WebServerState_Starting,
        _WebServerState_Started,
        _WebServerState_Stopping,
        _WebServerState_Stopped,
        _WebServerState_Error,
        _MDNSState_None,
        _MDNSState_Starting,
        _MDNSState_Started,
        _MDNSState_Stopping,
        _MDNSState_Stopped,
        _MDNSState_Error,
        _PumpState_None,
        _PumpState_Starting,
        _PumpState_Started,
        _PumpState_Stopping,
        _PumpState_Stopped,
        _PumpState_Error,
    };

    enum PumpState_e
    {
        PumpState_None,
        PumpState_Starting,
        PumpState_Started,
        PumpState_Stopping,
        PumpState_Stopped,
        PumpState_Error
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

typedef DeviceStates::PumpState_e PumpState_e;
typedef DeviceStates::LEDStates_e LEDStates_e;

extern StateManager<PumpState_e> PumpStateManager;
extern StateManager<LEDStates_e> ledStateManager;

#endif // STATEMANAGER_HPP