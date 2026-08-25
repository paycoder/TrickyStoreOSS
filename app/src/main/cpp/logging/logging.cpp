// Copyright 2026 Dakkshesh <beakthoven@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <android/log.h>

#include <cstdarg>
#include <cstring>
#include <sys/system_properties.h>

#include "logging.hpp"

namespace logging {
namespace {

bool logd_running() {
    static const bool ready = [] {
        char value[PROP_VALUE_MAX] = {};
        return __system_property_get("init.svc.logd", value) > 0 && strcmp(value, "running") == 0;
    }();
    return ready;
}
} // namespace

void log(int prio, const char *tag, const char *fmt, ...) {
    if (!logd_running()) {
        return;
    }
    va_list ap;
    va_start(ap, fmt);
    __android_log_vprint(prio, tag, fmt, ap);
    va_end(ap);
}
} // namespace logging
