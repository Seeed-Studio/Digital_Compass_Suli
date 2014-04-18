/*
  Digital_Compass_Suli.cpp

  This is a Suly compatible Library

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.

  Loovee
  2014-4-17

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, digital_compass_write_reg to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Digital_Compass_Suli.h"


uint8 __Scale = 1;

void *__I2C_Device;

void digital_compass_init(void *i2c_dev)
{
    __I2C_Device = i2c_dev;
}

MagnetometerRaw digital_compass_read_axis()
{

    uint8 buffer[6];
    digital_compass_read_reg(DATA_REGISTER_BEGIN, buffer, 6);
    MagnetometerRaw raw = MagnetometerRaw();
    
    raw.XAxis = (buffer[0] << 8) | buffer[1];
    raw.ZAxis = (buffer[2] << 8) | buffer[3];
    raw.YAxis = (buffer[4] << 8) | buffer[5];
    
    return raw;
}

MagnetometerScaled digital_compass_read_scale()
{
    MagnetometerRaw raw = digital_compass_read_axis();
    MagnetometerScaled scaled = MagnetometerScaled();
    scaled.XAxis = raw.XAxis * __Scale;
    scaled.ZAxis = raw.ZAxis * __Scale;
    scaled.YAxis = raw.YAxis * __Scale;
    return scaled;
}

int digital_compass_set_scale(float gauss)
{
    uint8 regValue = 0x00;
    if(gauss == 0.88)
    {
        regValue = 0x00;
        __Scale = 0.73;
    }
    else if(gauss == 1.3)
    {
        regValue = 0x01;
        __Scale = 0.92;
    }
    else if(gauss == 1.9)
    {
        regValue = 0x02;
        __Scale = 1.22;
    }
    else if(gauss == 2.5)
    {
        regValue = 0x03;
        __Scale = 1.52;
    }
    else if(gauss == 4.0)
    {
        regValue = 0x04;
        __Scale = 2.27;
    }
    else if(gauss == 4.7)
    {
        regValue = 0x05;
        __Scale = 2.56;
    }
    else if(gauss == 5.6)
    {
        regValue = 0x06;
        __Scale = 3.03;
    }
    else if(gauss == 8.1)
    {
        regValue = 0x07;
        __Scale = 4.35;
    }
    else
    return ERRORCODE_1_NUM;

    // Setting is in the top 3 bits of the register.
    regValue = regValue << 5;
    digital_compass_write_reg(CONFIGURATION_REGISTERB, regValue);
}

int digital_compass_set_measure_mode(uint8 mode)
{
    digital_compass_write_reg(MODE_REGISTER, mode);
}

void digital_compass_write_reg(int address, int data)
{
    uint8 dta[3] = {address, data};
    suli_i2c_write(__I2C_Device, HMC5883L_ADDRESS, dta, 2);
}

uint8 digital_compass_read_reg(int address, uint8 *buff, int length)
{
    uint8 dta[1] = {address};
    suli_i2c_write(__I2C_Device, HMC5883L_ADDRESS, dta, 1);
    suli_i2c_read(__I2C_Device, HMC5883L_ADDRESS, buff, length);
    return 1;
}
