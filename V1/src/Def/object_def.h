#ifndef OBJECT_DEF_H
#define OBJECT_DEF_H

#include <vector>
#include <mbed.h>
#include "./Classes/FuelCell.h"
#include "./Classes/Analog_Sensor.h"
#include "./Classes/Fan.h"
#include "./Classes/FuelCell.h"
#include "./Classes/Integrator.h"
#include "./Classes/FanControl.h"
#include "./Classes/RTC.h"
#include "./Classes/SHT31.h"
#include "./Classes/DigitalOut_Ext.h"

// SHT31
extern SHT31 sht31;
// RTC
extern RealTimeClock rtc;
// DigitalOut_Ext Objects
extern DigitalOut_Ext supply_v;
extern DigitalOut_Ext purge_v;
extern DigitalOut_Ext start_r;
extern DigitalOut_Ext motor_r;
extern DigitalOut_Ext charge_r;
extern DigitalOut_Ext cap_r;
extern DigitalOut_Ext fcc_r;
extern DigitalOut_Ext error_throw;
extern DigitalOut_Ext alarm_led;
extern DigitalOut_Ext debug_led;
extern DigitalOut_Ext shut_led;
extern DigitalOut_Ext run_led;
extern DigitalOut_Ext start_led;

// Analog_Sensor Objects
extern Analog_Sensor<LinearScalable<float> > capvolt;
extern Analog_Sensor<LinearScalable<float> > fccurr;
extern Analog_Sensor<LinearScalable<float> > fcvolt;
extern Analog_Sensor<LinearScalable<float> > capcurr;
extern Analog_Sensor<LinearScalable<float> > motorvolt;
extern Analog_Sensor<LinearScalable<float> > motorcurr;
extern Analog_Sensor<LinearScalable<float> > press1;

#ifdef ADD_PRESS
extern Analog_Sensor<LinearScalable<float> > press2;
extern Analog_Sensor<LinearScalable<float> > press3;
extern Analog_Sensor<LinearScalable<float> > press4;
#endif

extern Analog_Sensor<PolyScalable<float> > fctemp1;
extern Analog_Sensor<PolyScalable<float> > fctemp2;

#ifdef EXT_TEMP
extern Analog_Sensor<LinearScalable<float> > temp1;
extern Analog_Sensor<LinearScalable<float> > temp2;
extern Analog_Sensor<LinearScalable<float> > temp3;
extern Analog_Sensor<LinearScalable<float> > temp4;
extern Analog_Sensor<LinearScalable<float> > temp5;
#endif

//Fans
extern Fan fan1;

#ifdef ALICE_CONFIGURATION
extern Fan fan2;
extern Fan fan3;
#endif


// Intergrators
extern Integrator fc_coulumbs;
extern Integrator fc_joules;
extern Integrator cap_coulumbs;
extern Integrator cap_joules;

extern FuelCell fc;

extern FanControl<PolyScalable<float>, LinearScalable<float> > fan_cont;

//Vectors
extern vector<Sensor*> sensor_vec;
extern vector<Integrator*> int_vec;
extern vector<DigitalOut_Ext*> dig_out_vec;
extern vector<Fan*> fan_vec;
extern vector<Analog_Sensor<PolyScalable<float> >* > temp_vec;

//Iterators
extern vector<Sensor*>::iterator sensor_iter;
extern vector<Integrator*>::iterator int_iter;
extern vector<DigitalOut_Ext*>::iterator dig_out_iter;
extern vector<Fan*>::iterator fan_iter;

#endif
