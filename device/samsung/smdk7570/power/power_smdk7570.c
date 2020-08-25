/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define LOG_TAG "UNIVERSAL7870_PowerHAL"
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/power.h>
// We only support clang and g++.
#define UNUSED_ARGUMENT __attribute((unused))

static void sysfs_write(const char *path, char *s)
{
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }

    close(fd);
}

static void power_init(struct power_module *module)
{

    /*
     * called when system initialize
     */

  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/timer_rate", "20000");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/timer_slack", "20000");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/min_sample_time", "40000");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/hispeed_freq", "902000");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/go_hispeed_load", "89");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/target_loads", "75 1248000:85");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/above_hispeed_delay", "39000 1248000:19000");
  sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/interactive/boostpulse_duration", "40000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/timer_rate", "20000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/timer_slack", "20000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/min_sample_time", "40000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/hispeed_freq", "902000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/go_hispeed_load", "89");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/target_loads", "75 1248000:85");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/above_hispeed_delay", "39000 1248000:19000");
  sysfs_write("/sys/devices/system/cpu/cpu4/cpufreq/interactive/boostpulse_duration", "40000");
}
static void power_set_interactive(struct power_module *module UNUSED_ARGUMENT,
                                  int on UNUSED_ARGUMENT)
{
}
static void power_hint(struct power_module *module UNUSED_ARGUMENT,
                       power_hint_t hint,
                       void *data UNUSED_ARGUMENT) {
    switch (hint) {
    default:
        break;
    }
}
static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};
struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "UNIVERSAL7870 Power HAL",
        .author = "The Android Open Source Project",
        .methods = &power_module_methods,
    },
    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
};
