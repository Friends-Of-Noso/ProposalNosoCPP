#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <csignal>
#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>  // Include spdlog for logging
#include <string>

class Application {
public:
    // Method to get the singleton instance of Application
    static Application& getInstance();

    // Public method to check local data integrity
    void checkLocalIntegrity();

    // Public method to initialize the application with command-line arguments
    void initialise(int argc, char* argv[]);

    // Public method to run the application
    void run();

    // Public method to handle graceful shutdown
    void shutdown();

private:
    // Private constructor to enforce singleton pattern
    Application();

    // Delete copy constructor and assignment operator
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Static signal handler function
    static void signalHandler(int signal);

    // Static pointer to hold the singleton instance
    static Application* instance;

    // Method to set log level based on a string
    void setLogLevel(const std::string& logLevel);
};

#endif  // APPLICATION_HPP
