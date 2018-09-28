/*
Tencent is pleased to support the open source community by making PhxQueue available.
Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

<https://opensource.org/licenses/BSD-3-Clause>

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/



#include "phxqueue/comm/logger.h"

#include <cstdarg>
#include <iostream>
#include <mutex>
#include <string>
#include <cstring>


using namespace std;


namespace phxqueue {

namespace comm {


class Logger::LoggerImpl {
  public:
    LoggerImpl() = default;
    virtual ~LoggerImpl() = default;

    mutex lock;
    LogLevel log_level{LogLevel::Verbose};
    LogFunc log_func{nullptr};
};

Logger::Logger() : impl_(new LoggerImpl()) {}

Logger *Logger::GetInstance() {
    static Logger logger;

    return &logger;
}

void Logger::LogError(const char *format, ...) {
    string newFormat("\033[41;37m " + string(format) + " \033[0m");

    if (impl_->log_func != nullptr) {
        va_list args;
        va_start(args, format);
        impl_->log_func(static_cast<int>(LogLevel::Error), newFormat.c_str(), args);
        va_end(args);

        return;
    }
}

void Logger::LogStatus(const char *format, ...) {
    if (impl_->log_func != nullptr) {
        va_list args;
        va_start(args, format);
        impl_->log_func(static_cast<int>(LogLevel::Error), format, args);
        va_end(args);

        return;
    }
}

void Logger::LogWarning(const char *format, ...) {
    string newFormat("\033[44;37m " + string(format) + " \033[0m");

    if (impl_->log_func != nullptr) {
        va_list args;
        va_start(args, format);
        impl_->log_func(static_cast<int>(LogLevel::Warning), newFormat.c_str(), args);
        va_end(args);

        return;
    }
}

void Logger::LogInfo(const char *format, ...) {
    string newFormat("\033[45;37m " + string(format) + " \033[0m");

    if (impl_->log_func != nullptr) {
        va_list args;
        va_start(args, format);
        impl_->log_func(static_cast<int>(LogLevel::Info), newFormat.c_str(), args);
        va_end(args);

        return;
    }
}

void Logger::LogVerbose(const char *format, ...) {
    string newFormat("\033[45;37m " + string(format) + " \033[0m");

    if (impl_->log_func != nullptr) {
        va_list args;
        va_start(args, format);
        impl_->log_func(static_cast<int>(LogLevel::Verbose), newFormat.c_str(), args);
        va_end(args);

        return;
    }
}

void Logger::SetLogFunc(LogFunc log_func) {
    impl_->log_func = log_func;
}

void Logger::Log(const int log_level, const char *format, va_list args) {
	if (impl_->log_func != nullptr) {
		impl_->log_func(log_level, format, args);
	}
}

enum PhxPaxosLogLevel {
    PhxPaxosLogLevel_None = 0,
    PhxPaxosLogLevel_Error = 1,
    PhxPaxosLogLevel_Warning = 2,
    PhxPaxosLogLevel_Info = 3,
    PhxPaxosLogLevel_Verbose = 4,
};

void LogFuncForPhxPaxos(const int log_level, const char *format, va_list args) {
    auto phxqueue_log_level = LogLevel::None;
    switch (log_level) {
        case PhxPaxosLogLevel::PhxPaxosLogLevel_None:
            phxqueue_log_level = LogLevel::Error;
            break;
        case PhxPaxosLogLevel::PhxPaxosLogLevel_Error:
            phxqueue_log_level = LogLevel::Error;
            break;
        case PhxPaxosLogLevel::PhxPaxosLogLevel_Warning:
            phxqueue_log_level = LogLevel::Verbose;
            break;
        case PhxPaxosLogLevel::PhxPaxosLogLevel_Info:
            phxqueue_log_level = LogLevel::Verbose;
            break;
        case PhxPaxosLogLevel::PhxPaxosLogLevel_Verbose:
            phxqueue_log_level = LogLevel::Verbose;
            break;
    }

    if (phxqueue_log_level != LogLevel::None) {
        if (strstr(format, "STATUS")) return;
        if (strstr(format, "Lag msg")) return;
        phxqueue::comm::Logger::GetInstance()->Log(static_cast<int>(phxqueue_log_level), format, args);
    }
}

void LogFuncForPhxRpc(const int log_level, const char *format, va_list args) {
    phxqueue::comm::Logger::GetInstance()->Log(static_cast<int>(LogLevel::Info), format, args);
}


}  // namespace comm

}  // namespace phxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

