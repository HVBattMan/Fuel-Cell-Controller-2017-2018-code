#ifndef RTC_H
#define RTC_H

#include "IO.h"

#define DS3231_ADDRESS 0b1101000

#define SECONDS         0x00
#define MINUTES         0x01
#define HOURS           0x02
#define DAY             0x03
#define DATE            0x04
#define MONTH           0x05
#define YEAR            0x06
#define MODE_12HOUR_AM  0x40
#define MODE_12HOUR_PM  0X60

#define DS3231_BUFFERSIZE 19

class RealTimeClock: public IO{
// Class is specific to the DS3231 Real Time Clock
//      -Communicates via I2C
private:

    I2C *master;
    struct{
        int sec;
        int min;
        int hour;
    }time;

protected:
    // Device getters
    void read_device();



public:
    // Constructor
    RealTimeClock(string name, I2C *master);

    // Class getters
    int get_sec(bool update=0);
    int get_min(bool update=0);
    int get_hour(bool update=0);

    // To class to string...
    string toString(bool json_format = 0);
    string toStringInfo(bool json_format = 0);

};

#endif