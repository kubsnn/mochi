#pragma once
#ifndef MOCHI_LOGGER_HPP
#define MOCHI_LOGGER_HPP

#include "globals.hpp"
#include "color.hpp"
#include <iostream>
#include <string_view>
#include <chrono>
#include <mutex>

namespace mochi {

    class logger {
    public:
        class log_entry;
        class log_entry_debug;
        
        inline logger(const logger&) = delete;
        inline logger(logger&&) noexcept = delete;

        inline logger& operator=(const logger&) = delete;
        inline logger& operator=(logger&&) noexcept = delete;

        inline explicit logger(std::ostream& os) noexcept
            : os_(os)
        { }

        inline log_entry info() {
            return {*this, "info", cc::darkgreen};
        }

        inline log_entry warning() {
            return {*this, "warn", cc::darkyellow};
        }

        inline log_entry error() {
            return {*this, "fatal", cc::red};
        }

        inline log_entry_debug debug() {
            return log_entry_debug{*this};
        }

    private:
        std::ostream& os_;
        std::mutex mutex_;

    public:
        class log_entry {
        public:
            inline log_entry(logger& logger, const std::string& prefix, const jaszyk::ConsoleColor& color)
                : logger_(logger), lock_(logger.mutex_)
            {
                logger_.os_ << cc::white << '[' << color << prefix << cc::white << "] " << cc::reset;
            }

            inline log_entry(const log_entry&) = delete;

            inline log_entry& operator=(const log_entry&) = delete;

            inline ~log_entry() {
                logger_.os_ << std::endl;
            }

            template <typename T>
            inline log_entry& operator<<(const T& value) {
                logger_.os_ << value;
                return *this;
            }

            inline log_entry& operator<<(std::ostream& (*fn)(std::ostream&)) {
                logger_.os_ << fn;
                return *this;
            }


        private:
            logger& logger_;
            std::lock_guard<std::mutex> lock_;
        };

        class log_entry_debug {
        public:
            inline explicit log_entry_debug(logger& logger)
                : logger_(logger), lock_(logger.mutex_)
            {
                if (globals::debug) logger_.os_ << cc::white << '[' << cc::blue << "debug" << cc::white << "] " << cc::reset;
            }

            inline log_entry_debug(const log_entry_debug&) = delete;

            inline log_entry_debug& operator=(const log_entry_debug&) = delete;

            inline ~log_entry_debug() {
                if (globals::debug) logger_.os_ << std::endl;
            }

            template <typename T>
            inline log_entry_debug& operator<<(const T& value) {
                if (globals::debug) logger_.os_ << value;
                return *this;
            }

            inline log_entry_debug& operator<<(std::ostream&(*fn)(std::ostream&)) {
                if (globals::debug) logger_.os_ << fn;
                return *this;
            }
        private:
            logger& logger_;
            std::lock_guard<std::mutex> lock_;
        };
    };

#if LOG_TO_FILE == 1
    #include <fstream>

    inline std::ofstream _log_file("log.txt", std::ios::app);
    inline log log{_log_file};
#else
    inline logger log{std::cout};
#endif

} // namespace app

#endif //!MOCHI_LOGGER_HPP