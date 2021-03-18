#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>




class ReclaimerVM
{
public:

    ReclaimerVM();

// Threading is just for a temporary way to get a REPL going in console.
// Will be looking to integrate the VM more naturally into the games main loop + events.
public:
    void StartREPL();
private:

    static unsigned long ThreadEntry(void* param);

    // Ogre wants the entry to be wrapped in their stuff, so be it
    static unsigned long ThreadEntry_internal(void* param);

    void REPLLoop();

private:
    sol::state m_state;
    void* m_thread;
};