cmake_minimum_required(VERSION 3.8) 

project(PDFWriterTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

enable_testing()

set(Tests
  PDFParserFuzzSanity.cpp
  main.cpp 
)

add_executable(PDFWriterTesting ${Tests}
    testing/FileURL.cpp
    testing/PosixPath.cpp
    testing/WindowsPath.cpp
    PDFComment.cpp
    PDFCommentWriter.cpp
    AnnotationsWriter.cpp
)

target_link_libraries(PDFWriterTesting PDFWriter)

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif()
