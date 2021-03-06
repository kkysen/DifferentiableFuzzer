//
// Created by Khyber on 4/7/2019.
//

#pragma once

#include "src/share/io/Dir.h"
#include "src/share/io/fs.h"
#include "src/share/io/fse.h"

#include <string_view>
#include <sys/stat.h>
#include <unistd.h>

namespace runtime {
    
    class RuntimeOutput {
    
    public:
        
        const std::string_view name;
        const fse::Dir dir;
        
        explicit RuntimeOutput(std::string_view name) noexcept;
        
    };
    
}
