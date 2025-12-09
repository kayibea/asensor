#include <android/sensor.h>

#define MAX_SENSOR_NAME_LEN 64
#define MAX_SENSOR_STRING_TYPE 64
#define MAX_SENSOR_VENDOR_LEN 64

typedef struct {
  uint16_t id;
  uint16_t type;
  float resolution;
  int min_delay;
  uint8_t name_len;
  char name[MAX_SENSOR_NAME_LEN];
  uint8_t strtype_len;
  char string_type[MAX_SENSOR_STRING_TYPE];
  uint8_t vendor_len;
  char vendor[MAX_SENSOR_VENDOR_LEN];
} sensor_info_t;

int get_sensor_info(const ASensor *s, sensor_info_t *i);
int load_sensors_info(ASensorList list, sensor_info_t *ilist, int count);
