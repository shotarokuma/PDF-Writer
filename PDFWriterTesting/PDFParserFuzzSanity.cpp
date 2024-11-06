#include "PDFParser.h"
#include "InputFile.h"
#include "Trace.h"

#include <iostream>
#include <string>

using namespace std;
using namespace PDFHummus;

int PDFParserFuzzSanity(const std::string& inputPath, const std::string& outputPath) {
    PDFParser parser;
    InputFile pdfFile;

    EStatusCode status = pdfFile.OpenFile(inputPath);
    if (status != PDFHummus::eSuccess) {
        cout << "Unable to open file for reading, Path: " << inputPath << "\n";
        return 1;
    }

    // Set trace settings with the output file path
    Trace::DefaultTrace().SetLogSettings(outputPath, true, true);

    // Start parsing the PDF file
    parser.StartPDFParsing(pdfFile.GetInputStream());

    pdfFile.CloseFile();
    return status;
}
