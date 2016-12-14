/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/time.h"

#include "drivers/compass.h"

#include "sensors/sensors.h"

// Type of magnetometer used/detected
typedef enum {
    MAG_NONE = 0,
    MAG_HMC5883 = 1,
    MAG_AK8975 = 2,
    MAG_GPS = 3,
    MAG_MAG3110 = 4,
    MAG_AK8963 = 5,
    MAG_FAKE = 6,
    MAG_MAX = MAG_FAKE
} magSensor_e;

typedef struct mag_s {
    magDev_t dev;
    float magneticDeclination;
    int32_t magADC[XYZ_AXIS_COUNT];
} mag_t;

extern mag_t mag;

typedef struct compassConfig_s {
    int16_t mag_declination;                // Get your magnetic decliniation from here : http://magnetic-declination.com/
                                            // For example, -6deg 37min, = -637 Japan, format is [sign]dddmm (degreesminutes) default is zero.
    sensor_align_e mag_align;               // mag alignment
    uint8_t mag_hardware;                   // Which mag hardware to use on boards with more than one device
} compassConfig_t;

bool compassDetect(magDev_t *dev, magSensor_e magHardwareToUse);
bool compassInit(const compassConfig_t *compassConfig);
union flightDynamicsTrims_u;
void compassUpdate(timeUs_t currentTimeUs, union flightDynamicsTrims_u *magZero);
bool isCompassReady(void);
bool isCompassHealthy(void);
