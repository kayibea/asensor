#pragma once

#include <stdarg.h>
#include <stdio.h>

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#ifdef LOGCAT
#include <android/log.h>
#define LOG_TAG "ASensor"
#endif

__attribute__((unused)) static void log_message(int level, const char *fmt,
                                                ...) {
  if (level < LOG_LEVEL)
    return;

  va_list args1, args2;
  va_start(args1, fmt);
  va_copy(args2, args1);

  const char *prefix;
  switch (level) {
  case LOG_LEVEL_DEBUG:
    prefix = "DEBUG";
    break;
  case LOG_LEVEL_INFO:
    prefix = "INFO";
    break;
  case LOG_LEVEL_WARN:
    prefix = "WARN";
    break;
  case LOG_LEVEL_ERROR:
    prefix = "ERROR";
    break;
  default:
    prefix = "LOG";
    break;
  }

  FILE *stream = ((level >= LOG_LEVEL_WARN) ? stderr : stdout);
  fprintf(stream, "[%s] ", prefix);
  vfprintf(stream, fmt, args1);
  fprintf(stream, "\n");

#ifdef LOGCAT
  int android_level;
  switch (level) {
  case LOG_LEVEL_DEBUG:
    android_level = ANDROID_LOG_DEBUG;
    break;
  case LOG_LEVEL_INFO:
    android_level = ANDROID_LOG_INFO;
    break;
  case LOG_LEVEL_WARN:
    android_level = ANDROID_LOG_WARN;
    break;
  case LOG_LEVEL_ERROR:
    android_level = ANDROID_LOG_ERROR;
    break;
  default:
    android_level = ANDROID_LOG_UNKNOWN;
    break;
  }
  __android_log_vprint(android_level, LOG_TAG, fmt, args2);
#endif

  va_end(args1);
  va_end(args2);
}

#define LOGD(...) log_message(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOGI(...) log_message(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOGW(...) log_message(LOG_LEVEL_WARN, __VA_ARGS__)
#define LOGE(...) log_message(LOG_LEVEL_ERROR, __VA_ARGS__)
