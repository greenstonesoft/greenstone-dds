# CMake Minumum Version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# Set operating system for compilation. 
# Available values: LINUX_X86_18, LINUX_X86_20, LINUX_X86_22, LINUX_X86_24, LINUX_ARM
SET(TARGET_OS LINUX_X86_18 CACHE STRING "os ")

# Set compiler
IF (${TARGET_OS} STREQUAL "LINUX_ARM")
    SET(CMAKE_SYSTEM_NAME Linux)
    SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
    SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
ENDIF()

# Set project name and executable name
PROJECT(DEMO_Throughput)
SET(EXE_NAME Throughput)

# Specify the c++ standard
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

SET(GS_DDS_DIR "${PROJECT_SOURCE_DIR}/../../")

# Add directories of header files
INCLUDE_DIRECTORIES("${GS_DDS_DIR}/include"
                    "${GS_DDS_DIR}/utils"
                    "${PROJECT_SOURCE_DIR}/datatype")

# Look up source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/datatype DATATYPE_SRCS)
AUX_SOURCE_DIRECTORY(${GS_DDS_DIR}/utils UTILS_SRCS)


SET(PROJECT_SRCS
    ${DIR_SRCS}
    ${DATATYPE_SRCS}
    ${UTILS_SRCS})

# Add link directories including .so libraries
IF (${TARGET_OS} STREQUAL "LINUX_X86_18")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/x86_64-linux_gnu_gcc_7.5.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_X86_20")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/x86_64-linux_gnu_gcc_9.4.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_X86_22")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/x86_64-linux_gnu_gcc_11.4.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_X86_24")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/x86_64-linux_gnu_gcc_13.2.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_ARM")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/aarch64_linux_gnu_gcc_9.3.0)
ENDIF()

# Set executable
ADD_EXECUTABLE(${EXE_NAME} ${PROJECT_SRCS})

# Target link libraries
TARGET_LINK_LIBRARIES(${EXE_NAME} greenstone-DCPS pthread)

SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")