#ifndef LOG_H
#define LOG_H

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

extern std::shared_ptr<spdlog::logger> console;

#endif