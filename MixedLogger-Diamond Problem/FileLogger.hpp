#pragma once
#include "BaseLogger.hpp"
#include <fstream>

class FileLogger : public virtual BaseLogger {
public:
    FileLogger() : filename("default.txt"), out(filename, std::ios::app) {
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    FileLogger(const std::string& filename) : filename(filename), out(this->filename, std::ios::app) {
        if (this->filename.find(".txt") == std::string::npos || this->filename.size() < 5) {
            throw std::invalid_argument("Invalid filename");
        }
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    FileLogger(const FileLogger& other) noexcept : filename(other.filename), out(other.filename, std::ios::app) {
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    FileLogger(FileLogger&& other) noexcept : filename(std::move(other.filename)), out(std::move(other.out)){}

    FileLogger& operator=(const FileLogger& other) noexcept {
        if (this != &other) {
            filename = other.filename;
            out.close();
            out.open(filename, std::ios::app);
            if (!out.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
        }
        return *this;
    }

    FileLogger& operator=(FileLogger&& other) noexcept {
        if (this != &other) {
            filename = std::move(other.filename);
            out = std::move(other.out);
        }
        return *this;
    }

    ~FileLogger() {
        if (out.is_open()) {
            out.close();
        }
    }

    void log(const std::string& message) override {
        if (out.is_open()) {
            out << prefix << ' ';
            for (char ch : message) {
                out.put(ch);
            }
            out.put('\n');
            this->out.flush();
            this->out.clear();
            if (!this->out.is_open()) {
                this->out.open(this->filename, std::ios::app);
            }
        }
        else {
            out.open(filename, std::ios::app);
            if (!out.is_open()) {
                throw std::runtime_error("Failed to reopen file: " + filename);
            }
        }
    }

protected:
    std::string filename;
    std::ofstream out;
};
