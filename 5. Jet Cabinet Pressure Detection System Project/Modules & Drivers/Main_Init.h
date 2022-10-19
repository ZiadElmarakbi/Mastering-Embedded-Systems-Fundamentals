
#ifndef MAIN_INIT_H_
#define MAIN_INIT_H_

#include "Flash_Memory_Driver.h"

// Functions and Pointer to Functions Used in Main
extern void Pressure_Sensor_init();
extern void Alarm_Indicator_init();
extern void Alarm_Buzzer_init();
extern void Alarm_Manager_init();

extern fifo_flash* flashptr;
extern uint32_t flashArr[flashSpace];

extern void (*Alarm_Manager_ptr2Fun)();
extern void (*Pressure_Sensor_ptr2Fun)();

#endif /* MAIN_INIT_H_ */
