#ifndef DAEMON_HPP_
#define DAEMON_HPP_

#include <csignal>
#include <functional>

class Daemon {
   public:
    static Daemon& instance() {
        static Daemon instance;
        return instance;
    }

    void setReloadFunction(std::function<void()> func);

    bool IsRunning();

   private:
    std::function<void()> m_reloadFunc;
    bool m_isRunning;
    bool m_reload;

    Daemon();
    Daemon(Daemon const&) = delete;
    void operator=(Daemon const&) = delete;

    void Reload();

    static void signalHandler(int signal);
};

#endif  // DAEMON_HPP_
