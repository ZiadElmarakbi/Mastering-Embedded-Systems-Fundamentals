
#include "Alarm_Indicator_Driver.h"

void (*Alarm_Indicator_ptr2Fun)(Indicator_status);

void Alarm_Indicator_init(){

	Alarm_Indicator_ptr2Fun = AlarmIdle_State;
	SET_BIT(GPIOA_ODR,10);
	SET_BIT(GPIOA_ODR,11);
	SET_BIT(GPIOA_ODR,12);
//	 DPRINTF("Initializing Alarm Indicator...\n");
//	 DPRINTF("...Alarm Indicator Initialized Successfully !!\n\n");
}

void AlarmIndicatorOFF(Indicator_status LEDstatus){
	Alarm_Indicator_ptr2Fun = AlarmIdle_State;
	Alarm_Indicator_ptr2Fun(LEDstatus);
}

void AlarmIndicatorON(Indicator_status LEDstatus){
	Alarm_Indicator_ptr2Fun = AlarmIndication_State;
	Alarm_Indicator_ptr2Fun(LEDstatus);
}

// States
void AlarmIndication_State(Indicator_status LEDstatus){

	Alarm_Indicator_Status = IndicatorAlarm;

	if(LEDstatus == Green_On)
		Set_Alarm_Indicator(Green_On);

	else if(LEDstatus == Red_On)
		Set_Alarm_Indicator(Red_On);

	else if(LEDstatus == Yellow_On)
		Set_Alarm_Indicator(Yellow_On);
}

void AlarmIdle_State(Indicator_status LEDstatus){

	Alarm_Indicator_Status = IndicatorIdle;

	if(LEDstatus == Green_Off)
		Set_Alarm_Indicator(Green_Off);

	else if(LEDstatus == Red_Off)
		Set_Alarm_Indicator(Red_Off);

	else if(LEDstatus == Yellow_Off)
		Set_Alarm_Indicator(Yellow_Off);
}



