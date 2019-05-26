//
// Created by Khyber on 5/23/2019.
//

#include "src/share/aio/signal/Handler.h"

namespace {
    
    void registerSigAction(int signal, const struct sigaction* action, struct sigaction* oldAction) noexcept {
        assert(::sigaction(signal, action, oldAction) == 0);
        // only possible errors can't happen:
        // EFAULT: action or oldAction or not part of address space, but they obviously are
        // EINVAL: invalid signal specified, incl. SIGKILL and SIGSTOP,
        //      but I go through a list of all the signals (dispositions) and skip SIGKILL and SIGSTOP
    }
    
}

namespace aio::signal {
    
    void Handler::old(const Signal& signal) noexcept {
        oldHandlers[signal.signal](signal);
    }
    
    void Handler::operator()(const Signal& signal) noexcept {
        for (const auto& handler : stde::reversed(handlers)) {
            handler(signal);
        }
        old(signal);
    }
    
    void Handler::operator()(int signal, siginfo_t* sigInfo, void* context) noexcept {
        (*this)(Signal(signal, sigInfo, context));
    }
    
    // must be a pure function pointer, so no closures allowed
    // instance is a singleton, no other instances allowed
    void Handler::handle(int signal, siginfo_t* sigInfo, void* context) noexcept {
        instance(signal, sigInfo, context);
    }
    
    void Handler::add(HandlerFunc&& handler) {
        handlers.push_back(std::move(handler));
    }
    
    void Handler::addExisting(int signal, const UnMaskedAction& action) {
        oldHandlers[signal] = action;
    }
    
    bool Handler::tryAddExisting(int signal, struct sigaction& oldAction) noexcept {
        registerSigAction(signal, nullptr, &oldAction);
        const auto unMasked = UnMaskedAction(oldAction);
        if (!unMasked.ignore()) {
            if (unMasked.hasAction(handle)) {
                // don't want to add our own main handler as one of the handlers
                return false;
            }
            addExisting(signal, unMasked);
        }
        return !unMasked.ignore();
    }
    
    void Handler::registerFor(int signal, struct sigaction& oldAction) noexcept {
        // re-use oldAction ref to re-use mask and flags
        auto& action = oldAction;
        action.sa_sigaction = handle;
        auto& flags = action.sa_flags;
        // altStack.flag() needs to | directly w/ flags b/c it's overloaded (also does a &~)
        flags = ((altStack.flag() | flags) | isAction) & ~UnMaskedAction::handledFlags;
        registerSigAction(signal, &action, nullptr);
        handledSignals[signal] = true;
    }
    
    bool Handler::tryRegisterFor(const disposition::Default& disposition) noexcept {
        // if the disposition is Ign or Cont, don't need to do anything
        // even if there's a signal handler, it won't terminate b/c of it
        // only if the signal handler calls exit(), which calls destructors
        // if the disposition is Term or Core, then we need to register the signal handler
        // if the disposition is Stop, then we don't need to register the signal handler,
        // b/c the process could be continued,
        // but it might be stopped for a while,
        // so instead of calling destructors, we can just flush data
        // in general, the actual signal handler can decide specifically what to do
        // based on what signal it is
        if (!disposition.atLeastStops) {
            return false;
        }
        const int signal = disposition.signal;
        struct sigaction action = {}; // share action across both calls to reuse mask and flags
        const bool shouldRegister = tryAddExisting(signal, action);
        if (!shouldRegister) {
            return false;
        }
        registerFor(signal, action);
    }
    
    void Handler::register_() {
        // use sigaltstack for sigsegv handler if possible
        for (const auto& disposition : disposition::defaults) {
            tryRegisterFor(disposition); // TODO do I need to use bool return value?
        }
    }
    
    Handler::Handler() {
        register_();
    }
    
}