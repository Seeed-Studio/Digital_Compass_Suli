/*
  Digital_Compass_Arduino.h

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

#ifndef __DIGITAL_COMPASS_ARDUINO_H__
#define __DIGITAL_COMPASS_ARDUINO_H__

#include <Arduino.h>
#include <Wire.h>
#include "Digital_Compass_Suli.h"

class digital_compass{

public:

    void begin()
    {
        Wire.begin();
        digital_compass_init(&Wire);
    }
    
    void setScale(float scale)
    {
        digital_compass_set_scale(scale);
    }
    
    MagnetometerRaw readRawAxis()
    {
        return digital_compass_read_axis();
    }
    
    MagnetometerScaled readScaledAxis()
    {
        return digital_compass_read_scale();
    }

};

#endif