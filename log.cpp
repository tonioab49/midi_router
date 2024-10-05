#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");