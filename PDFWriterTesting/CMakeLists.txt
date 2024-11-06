## testing
enable_testing()

# Test files (add new tests here)
create_test_sourcelist (Tests
  PDFParserFuzzSanity.cpp
)

# add the testing executable
add_executable (PDFWriterTesting     
    ${Tests}

)

target_link_libraries (PDFWriterTesting PDFWriter)

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif(APPLE)

# fuzz test errors specific
file(GLOB fuzztestfiles ${CMAKE_CURRENT_SOURCE_DIR}/Materials/fuzzing/*)
foreach (fuzztestfile ${fuzztestfiles})
    get_filename_component (TName ${fuzztestfile} NAME)
    add_test (NAME FuzzTest_${TName} COMMAND PDFWriterTesting PDFParserFuzzSanity ${CMAKE_CURRENT_SOURCE_DIR}/Materials ${CMAKE_BINARY_DIR}/Testing/Output ${fuzztestfile} FuzzTest_${TName}.txt)
endforeach ()


# create temp dir for output files
set (TmpOutputDir ${CMAKE_BINARY_DIR}/Testing/Output)

file(MAKE_DIRECTORY  ${TmpOutputDir})

# pdfWriterCheck: target for running the tests via ctest. using depends to make sure project+deps are build, and also that the tmp output folder is clear of
# materials from previous runs by recreating it. [note that the two CMAKE_COMMAND steps are ran using COMMAND. this is done to make sure they run 
# sequentially]
add_custom_target(pdfWriterCheck
  COMMAND ${CMAKE_COMMAND} -E rm -r -f ${TmpOutputDir}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${TmpOutputDir}
  COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
  DEPENDS PDFWriterTesting
)