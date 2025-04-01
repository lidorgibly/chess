#include "sensors.h"
#ifdef LINUX
#include "PCF8575_linux.h"
#else 
#include "PCF8575.h"
#endif




_IOsDevice device4;
_IOsDevice device5;
_IOsDevice device6;
_IOsDevice device7;






void init_contact_sensors()
{

	device4.address = I2C_DEVICE4_ADDRESS;
	device5.address = I2C_DEVICE5_ADDRESS;
	device6.address = I2C_DEVICE6_ADDRESS;
	device7.address = I2C_DEVICE7_ADDRESS;


}



