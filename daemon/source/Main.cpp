#include <iostream>
#include <thread>
#include <chrono>
#include <libconfig.h++>

#include "Log.hpp"
#include "CommandLineParser.hpp"
#include "Daemon.hpp"

// This function will be called when the daemon receive a SIGHUP signal.
void reload() {
    LOG_INFO("Reload function called.");
}

int main(int argc, char **argv) {

    CommandLineParser commandLine(argc, argv);

    // TODO 
    //libconfig::Config config;
    //config.readFile("resource/config/daemon-template.conf");
    //std::string name = config.lookup("name");

    // The Daemon class is a singleton to avoid be instantiate more than once
    Daemon& daemon = Daemon::instance();
    
    // Set the reload function to be called in case of receiving a SIGHUP signal
    daemon.setReloadFunction(reload);
    
    // Daemon main loop
    int count = 0;
    while(daemon.IsRunning()) {
        LOG_DEBUG("Count: ", count++);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    LOG_INFO("The daemon process ended gracefully.");
}
