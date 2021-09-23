#ifndef _I2C_LINUX_H
#define _I2C_LINUX_H



void init_i2c();
void set_i2c_slave_address(int addr);
void i2c_read(char* buf, int size);
void i2c_write(char* buf, int size);














#endif