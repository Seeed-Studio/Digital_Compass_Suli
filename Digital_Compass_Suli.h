/*
  Digital_Compass_Suli.h

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
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __DIGITAL_COMPASS_SULI_H__
#define __DIGITAL_COMPASS_SULI_H__

#include "Suli.h"


#define HMC5883L_ADDRESS            0x1E
#define CONFIGURATION_REGISTERA     0x00
#define CONFIGURATION_REGISTERB     0x01
#define MODE_REGISTER               0x02
#define DATA_REGISTER_BEGIN         0x03


#define MEASUREMENT_CONTINUOUS      0x00
#define MEASUREMENT_SINGLE_SHOT     0x01
#define MEASUREMENT_IDLE            0x03


#define ERRORCODE_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ERRORCODE_1_NUM 1


struct MagnetometerScaled
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

struct MagnetometerRaw
{
	int XAxis;
	int YAxis;
	int ZAxis;
};

static void digital_compass_write_reg(int address, int data);
static uint8 digital_compass_read_reg(int address, uint8 *buff, int length);

void digital_compass_init(void *i2c_dev);
MagnetometerRaw digital_compass_read_axis();
MagnetometerScaled digital_compass_read_scale();
int digital_compass_set_scale(float gauss);
int digital_compass_set_measure_mode(uint8 mode);



#endif