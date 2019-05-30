//
// Created by Khyber on 5/29/2019.
//

#pragma once

#include "src/share/hooks/lifecycle/LifeCycle.h"
#include "src/share/aio/signal/Handler.h"

namespace hooks::lifecycle {
    
    LifeCycle& add(std::unique_ptr<LifeCycle>&& object);
    
    // these 3 methods must be idempotent
    
    void reconstruct();
    
    void flush() noexcept;
    
    void destruct() noexcept;
    
    void handleSignal(const aio::signal::Signal& signal) noexcept;
    
}