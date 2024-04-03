//conversion
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Function to process CSV data
void processCsv(const std::string& inputFileName, const std::string& outputFileName) {
    // Open the input CSV file
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input CSV file: " << inputFileName << std::endl;
        return;
    }

    // Open the output CSV file
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output CSV file: " << outputFileName << std::endl;
        inputFile.close();
        return;
    }

    // Define categories and URLs
    std::vector<std::string> categories = {"Overview", "Campus", "Courses", "Scholarships", "Admission", "Placements", "Results"};
    std::vector<std::string> urls = {
        "https://example.com/data/ai",
        "https://example.com/data/php",
        "https://example.com/data/python"
    };

    // Initialize data map
    std::unordered_map<std::string, std::vector<std::string>> dataMap;

    // Read and process each line of the CSV file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string url, description;
        if (std::getline(ss, url, '\t') && std::getline(ss, description, '\t')) {
            // Get category from the URL
            size_t pos = url.find_last_of('/');
            std::string category = url.substr(pos + 1);

            // Update data map
            dataMap[category].push_back(description);
        }
    }

    // Write headers to the output CSV file
    outputFile << "URL";
    for (const auto& category : categories) {
        outputFile << "," << category;
    }
    outputFile << std::endl;

    // Write data to the output CSV file
    for (const auto& url : urls) {
        outputFile << url;
        for (const auto& category : categories) {
            if (dataMap.count(category) && dataMap[category].size() >= 3) {
                outputFile << "," << dataMap[category].at(&url - &urls[0]);
            } else {
                outputFile << ",";
            }
        }
        outputFile << std::endl;
    }

    // Close the input and output files
    inputFile.close();
    outputFile.close();
}

int main() {
    processCsv("input.csv", "output.csv");
    std::cout << "Conversion complete." << std::endl;
    return 0;
}