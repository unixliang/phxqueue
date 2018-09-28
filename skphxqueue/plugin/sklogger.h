#pragma once

#include <cstdio>
#include <string>

#include "phxqueue/comm.h"


namespace skphxqueue {

namespace plugin {


class SKLogger {
  public:
    static phxqueue::comm::LogFunc GetLogger();

    static void Log(const int iLogLevel, const char *pcFormat, va_list args);
};


}  // namespace plugin

}  // namespace skphxqueue

