# CMake Minumum Version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# Set operating system for compilation. 
# Available values: LINUX_X86, LINUX_ARM, LINUX_TDA4, QNX_ARM
SET(TARGET_OS LINUX_X86 CACHE STRING "os ")

# Set compiler
IF (${TARGET_OS} STREQUAL "LINUX_X86")
    SET(CMAKE_SYSTEM_NAME Linux)
    SET(CMAKE_C_COMPILER gcc)
    SET(CMAKE_CXX_COMPILER g++)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_ARM")
    SET(CMAKE_SYSTEM_NAME Linux)
    SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
    SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_TDA4")
    SET(CMAKE_SYSTEM_NAME Linux)
    SET(CMAKE_C_COMPILER aarch64-none-linux-gnu-gcc)
    SET(CMAKE_CXX_COMPILER aarch64-none-linux-gnu-g++)
ELSEIF (${TARGET_OS} STREQUAL "QNX_ARM")
    SET(CMAKE_SYSTEM_NAME QNX)
    SET(CMAKE_C_COMPILER qcc)
    SET(CMAKE_C_COMPILER_TARGET gcc_ntoaarch64le)
    SET(CMAKE_CXX_COMPILER q++)
    SET(CMAKE_CXX_COMPILER_TARGET gcc_ntoaarch64le)
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
                    "${GS_DDS_DIR}/include/dcps"
                    "${GS_DDS_DIR}/include/rtps"
                    "${GS_DDS_DIR}/utils"
                    "${PROJECT_SOURCE_DIR}/datatype")

# Look up source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/datatype DTATTYPE_SRCS)
AUX_SOURCE_DIRECTORY(${GS_DDS_DIR}/utils UTILS_SRCS)


SET(PROJECT_SRCS
    ${DIR_SRCS}
    ${DTATTYPE_SRCS}
    ${UTILS_SRCS})

# Add link directories including .so libraries
IF (${TARGET_OS} STREQUAL "LINUX_X86")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/x86-64_gcc7.5.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_ARM")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/aarch64_aarch64-linux-gnu-gcc7.5.0)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_TDA4")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/aarch64_aarch64-none-linux-gnu-gcc9.2)
ELSEIF (${TARGET_OS} STREQUAL "QNX_ARM")
    LINK_DIRECTORIES(${GS_DDS_DIR}/lib/aarch64_qcc)
ENDIF()

# Set executable
ADD_EXECUTABLE(${EXE_NAME} ${PROJECT_SRCS})

# Target link libraries
IF (${TARGET_OS} STREQUAL "LINUX_X86" OR ${TARGET_OS} STREQUAL "LINUX_ARM")
    TARGET_LINK_LIBRARIES(${EXE_NAME} greenstone-DCPS pthread)
ELSEIF (${TARGET_OS} STREQUAL "LINUX_TDA4")
    TARGET_LINK_LIBRARIES(${EXE_NAME} greenstone-DCPS pthread rt)
ELSEIF (${TARGET_OS} STREQUAL "QNX_ARM")
    TARGET_LINK_LIBRARIES(${EXE_NAME} greenstone-DCPS socket)
ENDIF()

SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")