#pragma once

#include <chrono>
#include <format>
#include <fstream>
#include <ios>
#include <optional>
#include <print>
#include <string>

namespace jello {
    enum class Level {
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    namespace internal {
        static auto min_log_level = Level::Debug;
        static std::optional<std::ofstream> log_file = {};

        inline std::string level_to_str(Level level) {
            switch (level) {
            case Level::Debug:
                return "DEBUG";
            case Level::Info:
                return "INFO";
            case Level::Warning:
                return "WARN";
            case Level::Error:
                return "ERROR";
            case Level::Fatal:
                return "FATAL";
            }

            std::abort();
        }

        static const auto color_reset = "\033[0m";
        static const auto color_debug = "\033[1;34m";
        static const auto color_info = "\033[1;32m";
        static const auto color_warning = "\033[1;33m";
        static const auto color_error = "\033[1;31m";
        static const auto color_fatal = "\033[1;35m";

        inline std::string level_to_color(Level level) {
            switch (level) {
            case Level::Debug:
                return color_debug;
            case Level::Info:
                return color_info;
            case Level::Warning:
                return color_warning;
            case Level::Error:
                return color_error;
            case Level::Fatal:
                return color_fatal;
            }

            std::abort();
        }

        void log(Level level, const std::string& format, auto&&... args) {
            if (level < min_log_level) {
                return;
            }

            auto now = std::chrono::system_clock::now();

            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::tm* now_tm = std::localtime(&now_c);

            auto log_str = std::format(
                "{}[{}]\t[{}-{:02}-{:02} {:02}:{:02}:{:02}]{}\t{}",
                level_to_color(level),
                level_to_str(level),
                now_tm->tm_year + 1900,
                now_tm->tm_mon + 1,
                now_tm->tm_mday,
                now_tm->tm_hour,
                now_tm->tm_min,
                now_tm->tm_sec,
                color_reset,
                std::vformat(format, std::make_format_args(args...))
            );

            std::println(level >= Level::Error ? stderr : stdout, "{}", log_str);

            if (log_file.has_value()) {
                log_file.value() << log_str << std::endl;
            }
        }
    }

    void debug(const std::string& format, auto&&... args) {
        internal::log(Level::Debug, format, std::forward<decltype(args)>(args)...);
    }

    void info(const std::string& format, auto&&... args) {
        internal::log(Level::Info, format, std::forward<decltype(args)>(args)...);
    }

    void warning(const std::string& format, auto&&... args) {
        internal::log(Level::Warning, format, std::forward<decltype(args)>(args)...);
    }

    void error(const std::string& format, auto&&... args) {
        internal::log(Level::Error, format, std::forward<decltype(args)>(args)...);
    }

    void fatal(const std::string& format, auto&&... args) {
        internal::log(Level::Fatal, format, std::forward<decltype(args)>(args)...);
        std::abort();
    }

    inline void configure(Level min_level = Level::Debug, std::optional<std::string> log_file_path = {}) {
        internal::min_log_level = min_level;

        if (log_file_path.has_value()) {
            internal::log_file.emplace(log_file_path.value(), std::ios_base::app);

            if (!internal::log_file->is_open()) {
                internal::log_file.reset();
                error("Could not open file at: {}", log_file_path.value());
                return;
            }
        }
    }
}
