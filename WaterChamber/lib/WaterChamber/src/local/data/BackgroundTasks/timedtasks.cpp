
#include "timedtasks.hpp"

TimedTasks::TimedTasks(AccumulateData *accumulateData) : _Timer_1s(1000),
                                                         _Timer_5s(5000),
                                                         _Timer_5s_2(5000),
                                                         _Timer_10s(10000),
                                                         _Timer_10s_2(10000),
                                                         _Timer_30s(30000),
                                                         _Timer_1m(60000),
                                                         _Timer_5m(300000),
                                                         ntp(ntp),
                                                         accumulateData(accumulateData) {}

TimedTasks::~TimedTasks(void) {}

#if ENABLE_I2C_SCANNER
void TimedTasks::ScanI2CBus(void)
{
  if (ENABLE_I2C_SCANNER)
  {
    if (_Timer_5s.ding())
    {
      Scan.SetupScan();
      Scan.BeginScan();
      _Timer_5s_2.start();
    }
  }
  else
  {
    return;
  }
}
#endif // ENABLE_I2C_SCANNER

void TimedTasks::accumulateSensorData(void)
{
  if (_Timer_5s.ding())
  {
    accumulateData->accumulateData();
    _Timer_5s.start();
  }
}
