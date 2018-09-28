#include "skphxqueue/plugin/sklogger.h"

#include <cassert>
#include <stdarg.h>
#include <string>

#include "iLog.h"


namespace skphxqueue {

namespace plugin {


using namespace Comm;
using namespace std;


phxqueue::comm::LogFunc SKLogger::GetLogger() {
    return SKLogger::Log;
}

void SKLogger::Log(const int iLogLevel, const char *pcFormat, va_list args) {
    char sBuf[1024] = {0};
    vsnprintf(sBuf, sizeof(sBuf), pcFormat, args);

    auto log_level = static_cast<phxqueue::comm::LogLevel>(iLogLevel);
    switch (log_level) {
    case phxqueue::comm::LogLevel::Info:
        LogInfo("%s", sBuf);
    case phxqueue::comm::LogLevel::Error:
    case phxqueue::comm::LogLevel::Warning:
        LogErr("%s", sBuf);
        break;
    case phxqueue::comm::LogLevel::Verbose:
        LogDebug("%s", sBuf);
        break;
    default:
        break;
    };
}


}  // namespace plugin

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL: http://scm-gy.tencent.com/gzrd/gzrd_mail_rep/phoenix_proj/trunk/phxpaxos/skplugin/logger_sk/logger_sk.cpp $ $Id: logger_sk.cpp 1689032 2016-07-27 08:48:13Z lynncui $ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

