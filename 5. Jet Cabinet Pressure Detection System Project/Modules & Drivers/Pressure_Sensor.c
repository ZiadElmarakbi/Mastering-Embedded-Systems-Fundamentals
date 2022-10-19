
#include "Pressure_Sensor.h"

// Pointer to function to alternate between the states
void (*Pressure_Sensor_ptr2Fun)();

// To Store the pressure sensor values
uint32_t pval;

// Initializing the Pressure Sensor
void Pressure_Sensor_init(){

	Pressure_Sensor_ptr2Fun = State(WaitingPressureVal);
  //DPRINTF("Initializing Pressure Sensor...\n");
  //DPRINTF("...Pressure Sensor Initialized Successfully !!\n\n");
}

// Defining the Reading Pressure State
Define_State(ReadingPressureVal){

	Pressure_sensor_state = ReadingPressureVal;
    pval = getPressureVal(); // Get pressure Value from Sensor
  //pval = generate_random(21,50,1);
  //DPRINTF("...Reading Pressure @ %d bars/s\n",pval);
  //Flash_Memory_ptr2Fun(pval);
	Delay(1000);
	Pressure_Sensor_ptr2Fun = State(WaitingPressureVal);
}

// Defining the Waiting Pressure State
Define_State(WaitingPressureVal){

	Pressure_sensor_state =  WaitingPressureVal;
	Pressure_Sensor_ptr2Fun = State(ReadingPressureVal);
	Pressure_Sensor_ptr2Fun();
}
