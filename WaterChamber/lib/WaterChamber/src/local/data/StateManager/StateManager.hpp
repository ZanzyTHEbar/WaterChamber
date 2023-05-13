#ifndef LOCAL_STATEMANAGER_HPP
#define LOCAL_STATEMANAGER_HPP
#include <data/statemanager/StateManager.hpp>

/*
 * StateManager
 * All Project States are managed here
 */
struct WaterChamberStates {
    enum SensorStates_e {
        SensorStates_None,
        SensorStates_Starting,
        SensorStates_Started,
        SensorStates_Stopping,
        SensorStates_Stopped,
        SensorStates_Error
    };
};

typedef WaterChamberStates::SensorStates_e SensorStates_e;
extern StateManager<SensorStates_e> sensorStatesManager;

#endif  // STATEMANAGER_HPP