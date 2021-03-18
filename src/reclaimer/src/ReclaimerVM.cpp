#include <ReclaimerVM.h>
#include <string>
#include <iostream>


ReclaimerVM::ReclaimerVM()
{
    {
        using sol::lib;
        m_state.open_libraries(
            lib::base,
            lib::package,
            lib::os,
            lib::math,
            lib::io
        );
    }
}


// For the threading stuff
unsigned long ReclaimerVM::ThreadEntry(void* param)
{
    reinterpret_cast<ReclaimerVM*>(param)->REPLLoop();
}
THREAD_DECLARE(ReclaimerVM::ThreadEntry);

void ReclaimerVM::StartREPL()
{
    m_thread = Ogre::Threads::CreateThread(THREAD_GET(ReclaimerVM::ThreadEntry), 0, this);
}

void ReclaimerVM::REPLLoop()
{
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "[ -- LUA REPL Initialized -- ]" << endl;

    std::string query;
    while (1) {
        cout << ">> ";
        cin >> query;
        auto result = m_state.safe_script(query);
    }
}