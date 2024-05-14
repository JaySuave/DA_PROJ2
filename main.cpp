#include <iostream> // Input/output stream library
#include <iomanip> // Input/output manipulation library
#include <vector> // Vector container library
#include "Graph.h"

/**
 * @brief Prints the program menu options.
 */
void printMenuOptions() {
    std::cout << "Flow Optimization Menu:" << std::endl;
    std::cout << "1. Reservoir Reports" << std::endl;
    std::cout << "2. Cities Reports" << std::endl;
    std::cout << "3. Pipes Reports" << std::endl;
    std::cout << "4. Pumping Stations Reports" << std::endl;
    std::cout << "5. Execute Edmonds-Karp Algorithm" << std::endl;
    std::cout << "6. Reliability and Sensitivity to Failures" << std::endl;
    std::cout << "7. Restore Original Settings" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

void menu(Graph* graph) {
    printMenuOptions();

    bool menuOpen = true;

    while(menuOpen) {
        char choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case '1':

                break;
            case '2':

                break;
            case '3':
                std::cout << "Exiting..." << std::endl;
                menuOpen = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

int main() {
    auto* graph = new Graph;

    menu(graph); // Call the menu function

    delete graph; // Clean up dynamically allocated memory

    return 0;
}


