#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <libconfig.h++>

#include "Log.hpp"
#include "CommandLineParser.hpp"

bool gExitDaemon = false;

void signalHandler(int signal) {
    LOG_INFO("Interrup signal number [", signal,"] recived.");
    switch(signal) {
        case SIGINT:
        case SIGTERM: {
            gExitDaemon = true;
            break;
        }
    }
}

int main(int argc, char **argv) {

    LOG_DEBUG("You have entered ", argc, " arguments."); 
  
    for (int i = 0; i < argc; ++i) {
        LOG_DEBUG("Argument ", i, ": ", argv[i]); 
    }

    // Register the signal function to treat external events
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    //libconfig::Config config;
    //config.readFile("resource/config/daemon-template.conf");
    //std::string name = config.lookup("name");

    LOG_INFO("Daemon started.");

    int count = 0;
    while (!gExitDaemon) {
        //std::clog << "Count: " << count << std::endl;
        LOG_DEBUG("Count: ", count);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count++;
        if (count == 10) {
            gExitDaemon = true;
        }
    }

    LOG_INFO("The daemon ended gracefully.");
}
