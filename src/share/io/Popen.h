//
// Created by Khyber on 5/21/2019.
//

#pragma once

#include "src/share/stde/getline.h"
#include "src/share/common/deleteCopy.h"

#include <string>
#include <atomic>

#include <cstdio>

namespace io {
    
    class Popen {
    
    private:
        
        std::atomic<FILE*> _file;
    
    public:
        
        static constexpr auto defaultMode = "r";
        
        constexpr FILE& file() const noexcept {
            return *_file;
        }
        
        explicit Popen(const char* command, const char* mode = defaultMode);
        
        explicit Popen(const std::string& string, const char* mode = defaultMode);
        
        void close() noexcept;
        
        ~Popen();
    
        deleteCopy(Popen);
        
        constexpr Popen(Popen&& other) noexcept : _file(other._file.exchange(nullptr)) {}
        
        template <class F>
        bool forEachLine(F f, char delimiter = '\n') {
            return stde::forEachLine(f, file(), delimiter);
        }
        
        std::string read();
        
    };
    
}
