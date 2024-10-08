#include "application.hpp"
#include <cstring>  // For strcmp
#include <ini.h>  // Include inih header

// Platform-specific includes
#ifdef _WIN32
#include <windows.h>  // Windows API for console control handling
#endif

// Initialize the static instance pointer to nullptr
Application* Application::instance = nullptr;

// Private constructor
Application::Application() {
#ifndef _WIN32
    // Register signal handlers for SIGINT and SIGTERM
    std::signal(SIGINT, Application::signalHandler);
    std::signal(SIGTERM, Application::signalHandler);
#else
    // Register a console control handler on Windows
    SetConsoleCtrlHandler([](DWORD event) -> BOOL {
        switch (event) {
            case CTRL_C_EVENT:  // CTRL-C pressed
            case CTRL_BREAK_EVENT:  // CTRL-Break pressed
            case CTRL_CLOSE_EVENT:  // Console window is closed
            case CTRL_LOGOFF_EVENT:  // User logs off
            case CTRL_SHUTDOWN_EVENT:  // System shutting down
                spdlog::info("Windows console event received. Shutting down gracefully...");
                if (Application::instance != nullptr) {
                    Application::instance->shutdown();
                }
                return TRUE;
            default:
                return FALSE;
        }
    }, TRUE);
#endif
}

// Method to get the singleton instance
Application& Application::getInstance() {
    if (instance == nullptr) {
        instance = new Application();  // Create the instance if it doesn't exist
    }
    return *instance;
}

// Method to set log level based on a string
void Application::setLogLevel(const std::string& logLevel) {
    if (logLevel == "trace") {
        spdlog::set_level(spdlog::level::trace);
    } else if (logLevel == "debug") {
        spdlog::set_level(spdlog::level::debug);
    } else if (logLevel == "info") {
        spdlog::set_level(spdlog::level::info);
    } else if (logLevel == "warn") {
        spdlog::set_level(spdlog::level::warn);
    } else if (logLevel == "error") {
        spdlog::set_level(spdlog::level::err);
    } else if (logLevel == "critical") {
        spdlog::set_level(spdlog::level::critical);
    } else if (logLevel == "off") {
        spdlog::set_level(spdlog::level::off);
    } else {
        spdlog::warn("Invalid log level: {}. Using default 'info' level.", logLevel);
        spdlog::set_level(spdlog::level::info);
    }
}

// Static signal handler function
void Application::signalHandler(int signal) {
    if ((signal == SIGINT || signal == SIGTERM) && instance != nullptr) {
        spdlog::info("Termination signal received. Shutting down gracefully...");
        instance->shutdown();
    }
}

// INI handler function
 int Application::iniHandler(void* user, const char* section, const char* name, const char* value) {
    Application* app = static_cast<Application*>(user);

    if (strcmp(section, "Logging") == 0 && strcmp(name, "log_level") == 0) {
        app->setLogLevel(value);
    } else if (strcmp(section, "Noso") == 0) {
        if (strcmp(name, "run_mode") == 0) {
            spdlog::info("Run mode set to: {}", value);
            // Store the run_mode in your application state if needed
        } else if (strcmp(name, "max_connections") == 0) {
            int maxCon = std::atoi(value);
            spdlog::info("Max connections set to: {}", maxCon);
            // Store max_connections in your application state if needed
        }
    }

    return 1;
}


// Method to initialize the application with command-line arguments
void Application::initialise(int argc, char* argv[]) {
    std::string logLevel = "info"; // Default log level

    // Loop through command-line arguments
    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--log-level") == 0 || strcmp(argv[i], "-l") == 0) && i + 1 < argc) {
            // If --log-level or -l is found, the next argument should be the log level
            logLevel = argv[i + 1];
            i++;  // Skip the next argument since it is consumed as log level
        }
    }

    // Set the log level for spdlog
    setLogLevel(logLevel);

    // Load the config file using inih
    const char* config_file = "config.ini";
    if (ini_parse(config_file, Application::iniHandler, this) < 0) {
        spdlog::error("Can't load configuration file: {}", config_file);
    } else {
        spdlog::info("Configuration file '{}' loaded successfully.", config_file);
    }}

// Method to check the integrity of local data
void Application::checkLocalIntegrity() {
    // Checking the blocks
    spdlog::info("Checking blocks");

    // More checks can be made
}

// Method to run the application
void Application::run() {
    spdlog::info("Application is running. Press CTRL-C or stop the service to terminate...");
    
    // This infinite loop should be replaced with the start of all the
    // other threads that will compose the full node
    while (true) {
        // Simulate some work
        spdlog::debug("Running some periodic tasks...");
        
        // Sleep for 5 seconds to yield CPU
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

// Method to handle graceful shutdown
void Application::shutdown() {
    spdlog::info("Performing cleanup tasks...");
    // Add your cleanup code here
    std::exit(0);  // Terminate the program after cleanup
}
