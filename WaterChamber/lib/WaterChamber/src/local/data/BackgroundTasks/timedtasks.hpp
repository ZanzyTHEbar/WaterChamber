#pragma once
#ifndef TIMEDTASKS_HPP
#define TIMEDTASKS_HPP
#include <timeObj.h>
#include <idlers.h>
#include <lists.h>

#include "local/data/AccumulateData/accumulatedata.hpp"
#include "local/network/ntp/ntp.hpp"

class TimedTasks : public timeObj
{
public:
  TimedTasks(AccumulateData *accumulateData);
  virtual ~TimedTasks(void);
  
#if ENABLE_I2C_SCANNER
  void ScanI2CBus(void);
#endif // ENABLE_I2C_SCANNER
  void accumulateSensorData(void);
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

  NetworkNTP *ntp;
  AccumulateData *accumulateData;
};

#endif
