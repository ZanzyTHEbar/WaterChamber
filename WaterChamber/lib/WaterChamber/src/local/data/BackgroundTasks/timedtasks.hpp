#pragma once
#ifndef TIMEDTASKS_HPP
#define TIMEDTASKS_HPP
#include <timeObj.h>
#include <idlers.h>
#include <lists.h>

#include "local/data/Config/config.hpp"
#include "local/data/AccumulateData/accumulatedata.hpp"
#include "local/network/ntp/ntp.hpp"


class TimedTasks : public timeObj //, public linkList
{
public:
  TimedTasks(void);
  virtual ~TimedTasks(void);
  bool begin(void);
  /* void execute(void); */

  void updateCurrentData(void);
  void checkMQTTState(void);
#if ENABLE_I2C_SCANNER
  void ScanI2CBus(void);
#endif // ENABLE_I2C_SCANNER
  void accumulateSensorData(void);
  void NTPService(void);
  void checkNetwork(void);

private:
  // Timers
  timeObj _Timer_1s;
  timeObj _Timer_5s;
  timeObj _Timer_5s_2;
  timeObj _Timer_10s;
  timeObj _Timer_10s_2;
  timeObj _Timer_30s;
  timeObj _Timer_1m;
  timeObj _Timer_5m;
};

extern TimedTasks timedTasks;

#endif

/*

AccumulateData data1;

void setup(void) {
   data1.begin(&sensorMgr);
   data1.addSelf();
}

void loop() {
   sensorMgr.checkStuff();
   theList.execute();
}

 */