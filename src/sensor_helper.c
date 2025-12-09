#include "sensor_helper.h"
#include <android/sensor.h>
#include <string.h>
#include <sys/param.h>

// #include "log.h"

static uint16_t sensor_id_from_type_vendor(const ASensor *s) {
  const char *vendor = ASensor_getVendor(s);
  uint16_t type = (uint16_t)ASensor_getType(s);
  uint32_t hash = 5381;
  while (*vendor)
    hash = ((hash << 5) + hash) + (uint8_t)(*vendor++);
  return (uint16_t)((hash + type) & 0xFFFF);
}

int load_sensors_info(ASensorList list, sensor_info_t *ilist, int count) {
  if (!list || !ilist)
    return -1;

  for (int i = 0; i < count; i++) {
    const ASensor *sensor = list[i];
    sensor_info_t info = {0};
    if (get_sensor_info(sensor, &info) != 0)
      return -1;
    ilist[i] = info;
  }

  return 0;
}

int get_sensor_info(const ASensor *s, sensor_info_t *i) {
  if (!s)
    return -1;

  i->id = sensor_id_from_type_vendor(s);
  i->type = ASensor_getType(s);
  i->min_delay = ASensor_getMinDelay(s);
  i->resolution = ASensor_getResolution(s);

  const char *name = ASensor_getName(s);
  size_t name_len = strlen(name);
  i->name_len = (uint8_t)MIN(name_len, MAX_SENSOR_NAME_LEN);
  memcpy(i->name, name, i->name_len);

  const char *strtype = ASensor_getStringType(s);
  size_t strtype_len = strlen(strtype);
  i->strtype_len = (uint8_t)MIN(strtype_len, MAX_SENSOR_STRING_TYPE);
  memcpy(i->string_type, strtype, i->strtype_len);

  const char *vendor = ASensor_getVendor(s);
  size_t vendor_len = strlen(vendor);
  i->vendor_len = (uint8_t)MIN(vendor_len, MAX_SENSOR_VENDOR_LEN);
  memcpy(i->vendor, vendor, i->vendor_len);

  return 0;
}
