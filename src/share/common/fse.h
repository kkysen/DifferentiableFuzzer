//
// Created by Khyber on 3/18/2019.
//

#pragma once

// fs-extra
#include "src/share/common/numbers.h"

#include <cstddef>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

namespace fse {
    
    const size_t pageSize = static_cast<const size_t>(sysconf(_SC_PAGESIZE));
    
    template <typename T = u8>
    T* mmap(int fd, int protection, int flags, size_t length, size_t offset = 0) {
        void* memory = ::mmap(nullptr, length, protection, flags, fd, offset);
        if (!memory) {
            throw fs::filesystem_error("mmap failed for fd = " + std::to_string(fd), std::error_code());
        }
        return static_cast<T*>(memory);
    }
    
}
