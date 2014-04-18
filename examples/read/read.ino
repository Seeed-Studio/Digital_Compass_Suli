// demo of digital compass

#include <Wire.h>
#include <SoftwareSerial.h>

#include "Suli.h"
#include "Digital_Compass_Arduino.h"

digital_compass compass;

void setup()
{
    Serial.begin(115200);
    compass.begin();
    compass.setScale(1.3);
}

void loop()
{
    // Retrive the raw values from the compass (not scaled).
    MagnetometerRaw raw = compass.readRawAxis();
    // Retrived the scaled values from the compass (scaled to the configured scale).
    MagnetometerScaled scaled = compass.readScaledAxis();

    // Values are accessed like so:
    int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(scaled.YAxis, scaled.XAxis);

    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -2??37' which is -2.617 Degrees, or (which we need) -0.0456752665 radians, I will use -0.0457
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = -0.0457;
    heading += declinationAngle;
    
    // Correct for when signs are reversed.
    if(heading < 0)
    heading += 2*PI;
    
    // Check for wrap due to addition of declination.
    if(heading > 2*PI)
    heading -= 2*PI;
    
    // Convert radians to degrees for readability.
    float headingDegrees = heading * 180/M_PI;
    
    // Output the data via the serial port.
    Output(raw, scaled, heading, headingDegrees);
    
    // Normally we would delay the application by 66ms to allow the loop
    // to run at 15Hz (default bandwidth for the HMC5883L).
    // However since we have a long serial out (104ms at 9600) we will let
    // it run at its natural speed.
    delay(100);//of course it can be delayed longer.
}


// Output the data down the serial port.
void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
{
    Serial.print("Raw:\t");
    Serial.print(raw.XAxis);
    Serial.print("   ");
    Serial.print(raw.YAxis);
    Serial.print("   ");
    Serial.print(raw.ZAxis);
    Serial.print("   \tScaled:\t");
    
    Serial.print(scaled.XAxis);
    Serial.print("   ");
    Serial.print(scaled.YAxis);
    Serial.print("   ");
    Serial.print(scaled.ZAxis);
    
    Serial.print("   \tHeading:\t");
    Serial.print(heading);
    Serial.print(" Radians   \t");
    Serial.print(headingDegrees);
    Serial.println(" Degrees   \t");
}