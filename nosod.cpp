#include "application.hpp"  // Include the header file for the Application class

int main(int argc, char* argv[]) {
    // Get the singleton instance of the Application class
    Application& app = Application::getInstance();

    // Initialize the application with command-line arguments
    app.initialise(argc, argv);

    // Check local data integrity
    app.checkLocalIntegrity();

    // Run the application
    app.run();
    return 0;
}
