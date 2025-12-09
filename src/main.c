#define LOGCAT
#include "log.h"
#include <android/sensor.h>
#include <stdio.h>

#include "sensor_helper.h"

#define PORT 9000
#define DEFAULT_SENSOR_COUNT 50

static ASensorList sensorList = NULL;
static ASensorManager *sensorManager = NULL;

static int sensor_count = 0;
static sensor_info_t sensors_info[DEFAULT_SENSOR_COUNT];

int main(void) {
  sensorManager = ASensorManager_getInstanceForPackage(NULL);
  if (!sensorManager) {
    LOGE("Failed to get sensor manager");
    return 1;
  }

  sensor_count = ASensorManager_getSensorList(sensorManager, &sensorList);
  if (sensor_count < 0) {
    LOGE("Could not get device sensors list");
    return 1;
  }

  if (load_sensors_info(sensorList, sensors_info, sensor_count) != 0) {
    LOGE("Could not retrieve sensors infos");
    return 1;
  }

  printf("Count: %d\n\n", sensor_count);
  for (int i = 0; i < sensor_count; i++) {
    printf("Name: %s\n", sensors_info[i].name);
    printf("Vendor: %s\n\n", sensors_info[i].vendor);
  }

  return 0;
}
