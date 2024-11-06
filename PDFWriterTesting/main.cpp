#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

extern void PDFParserFuzzSanity(const std::string& inputFile, const std::string& outputFile);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_directory> <output_directory>" << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::string outputDir = argv[2];

    std::cout << "Running fuzz tests from " << inputDir << "..." << std::endl;


    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.is_regular_file()) {
            std::string inputFile = entry.path().string();
            std::string outputFile = outputDir + "/" + entry.path().filename().string() + ".txt";
            
            std::cout << "Running test for " << inputFile << std::endl;
            PDFParserFuzzSanity(inputFile, outputFile);
        }
    }

    std::cout << "All fuzz tests completed." << std::endl;
    return 0;
}
