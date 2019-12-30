#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <csignal>
#include <functional>

class Daemon {

    public:

    static Daemon& instance() {
        static Daemon instance;
        return instance;
    }

    void setReloadFunction(std::function<void()> func) {
        m_reloadFunc = func;
    }

    bool IsRunning();
    
    private:

    std::function<void()> m_reloadFunc;
    static bool m_isRunning;
    static bool m_reload;

    Daemon();
    Daemon(Daemon const&) = delete;
    void operator=(Daemon const&) = delete;

    void Reload();

    static void signalHandler(int signal);

};


#endif // DAEMON_HPP
