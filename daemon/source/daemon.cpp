
#include "daemon.hpp"
#include "log.hpp"

Daemon::Daemon() {
    m_isRunning = true;
    m_reload = false;
    signal(SIGINT, Daemon::signalHandler);
    signal(SIGTERM, Daemon::signalHandler);
    signal(SIGHUP, Daemon::signalHandler);
}

void Daemon::setReloadFunction(std::function<void()> func) {
    m_reloadFunc = func;
}

bool Daemon::IsRunning() {
    if (m_reload) {
        m_reload = false;
        m_reloadFunc();
    }
    return m_isRunning;
}

void Daemon::signalHandler(int signal) {
    LOG_INFO("Interrup signal number [", signal, "] recived.");
    switch (signal) {
        case SIGINT:
        case SIGTERM: {
            Daemon::instance().m_isRunning = false;
            break;
        }
        case SIGHUP: {
            Daemon::instance().m_reload = true;
            break;
        }
    }
}
