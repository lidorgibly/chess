#include "contact_sensor.h"
#ifdef LINUX
#include "PCF8575_linux.h"
#else 
#include "PCF8575.h"
#endif




_IOsDevice device4;
_IOsDevice device5;
_IOsDevice device6;
_IOsDevice device7;






void init_contact_sensors(){

	device4.address = 0x20;


}




