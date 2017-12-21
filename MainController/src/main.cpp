#include <mbed.h>
#include <mbed_events.h>

// Classes
#include "Classes/Analog_Sensor.h"
#include "Classes/Fan.h"
#include "Classes/DigitalOut_Ext.h"
#include "Classes/Integrator.h"

// Defs
#include "Def/constants.h"
#include "Def/pin_def.h"
#include "Def/object_def.h"
#include "Def/thread_def.h"
#include "Def/semaphore_def.h"

// Thread src
#include "controller_event_queue.h"
#include "controller_states.h"
#include "monitoring.h"
#include "error_event_queue.h"
#include "main.h"

#include "fc_status.h"
/*
Initilaize Objects
  -These are used by the Threads
    -want the I/O to be global, local objects are defined locally
*/

// Interrupt Objects
InterruptIn h2(H2_OK);
InterruptIn err(ERROR_ISR);

// AnalogIn_Ext Objects
Analog_Sensor capvolt(CAPVOLT);
Analog_Sensor fccurr(FCCURR);
Analog_Sensor fcvolt(FCVOLT);
Analog_Sensor capcurr(CAPCURR);
Analog_Sensor motorvolt(MOTORVOLT);
Analog_Sensor motorcurr(MOTORCURR);
Analog_Sensor press1(PRESS1);
Analog_Sensor press2(PRESS2);
Analog_Sensor press3(PRESS3);
Analog_Sensor press4(PRESS4);
Analog_Sensor fctemp1(FCTEMP1);
Analog_Sensor fctemp2(FCTEMP2);
Analog_Sensor temp1(TEMP1);
Analog_Sensor temp2(TEMP2);
Analog_Sensor temp3(TEMP3);
Analog_Sensor temp4(TEMP4);
Analog_Sensor temp5(TEMP5);

// DigitalOut_Ext objects
DigitalOut_Ext supply_v(SUPPLY_V);
DigitalOut_Ext purge_v(PURGE_V);
DigitalOut_Ext other1_v(VALVE3);
DigitalOut_Ext other2_v(VALVE4);
DigitalOut_Ext start_r(START_R);
DigitalOut_Ext motor_r(MOTOR_R);
DigitalOut_Ext charge_r(CHARGE_R);
DigitalOut_Ext cap_r(CAP_R);
DigitalOut_Ext fcc_r(FCC_R);
DigitalOut_Ext error_throw(ERROR_ISR_THROW);
DigitalOut_Ext alarm_led(ALARM_LED);
DigitalOut_Ext debug_led(DEBUG_LED);
DigitalOut_Ext shut_led(SHUT_LED);
DigitalOut_Ext run_led(RUN_LED);
DigitalOut_Ext start_led(START_LED);
DigitalOut_Ext ol_rst(OL_RST);
DigitalOut_Ext hum_rst(HUM_RST);

// Fan objects
Fan fan1(PWM_1,TACH_1);
Fan fan2(PWM_2,TACH_2);
Fan fan3(PWM_3,TACH_3);

// Integrator objects
Integrator fc_coulumbs;
Integrator fc_joules;
Integrator cap_coulumbs;
Integrator cap_joules;


// Initilaize threads
Thread controller_event_thread;
Thread error_event_thread;
Thread data_event_thread;
Thread FTDI_event_thread;
Thread monitor;

void error_isr(){
  controller_event_thread.terminate();
  set_fc_status(ALARM_STATE);
  error_cleanup();
}

int main() {




  // Attach Interrupts (Should be the first thing to do)
  //h2.fall(&error_isr);
  //err.rise(&error_isr);


  // Threads from lowest -> highest priority
  monitor.set_priority(osPriorityIdle); // Will be running 90% of the time, since other threads are quick
  data_event_thread.set_priority(osPriorityLow);
  controller_event_thread.set_priority(osPriorityBelowNormal);
  FTDI_event_thread.set_priority(osPriorityNormal);
  error_event_thread.set_priority(osPriorityHigh);

  // Start threads
  error_event_thread.start(&error_event_queue);
  controller_event_thread.start(&contoller_event_queue_thread);
  monitor.start(&monitoring_thread);


  while(1){Thread::wait(1000000);};
  return 0;
}
