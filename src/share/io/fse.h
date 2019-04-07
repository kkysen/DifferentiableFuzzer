//
// Created by Khyber on 3/18/2019.
//

#pragma once

#include "src/share/io/fs.h"
#include "src/share/common/numbers.h"
#include "src/share/common/math.h"

#include <cstddef>
#include <cstring>

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace fse {
    
    namespace page {
        
        constexpr size_t constSize = 4096; // only usually correct, but sometimes I need it as a constexpr
        const size_t dynamicSize = static_cast<const size_t>(sysconf(_SC_PAGESIZE));
        
    }
    
    constexpr size_t bufferSize(size_t elementSize) noexcept {
        return math::lcm(page::constSize, elementSize) / elementSize;
    }
    
    template <typename T>
    constexpr size_t bufferSize() noexcept {
        return bufferSize(sizeof(T));
    }
    
    fs::filesystem_error error(const std::string& what);
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1);
    
    fs::filesystem_error error(const std::string& what, const fs::path& path1, const fs::path& path2);
    
    void* mmapRaw(int fd, int protection, int flags, size_t length, size_t offset = 0);
    
    template <typename T = u8>
    T* mmap(int fd, int protection, int flags, size_t length, size_t offset = 0) {
        return static_cast<T*>(mmapRaw(fd, protection, flags, length, offset));
    }
    
    // return if created
    bool ensureDir(const fs::path& path);
    
}
