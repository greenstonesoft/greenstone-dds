# Greenstone SWIFT DDS 3.0 <img src="https://nwzimg.wezhan.cn/contents/sitefiles2049/10245019/images/37839368.png" width="29" height="25" >

<div style="text-align: center;">
<a href="https://www.greenstonesoft.com/en_homepage"><img src="https://nwzimg.wezhan.cn/contents/sitefiles2049/10245019/images/37867159.png" style="display: inline-block;" hspace="8" vspace="2" width="142" height="40" ></a>
</div>


*SWIFT DDS* is a C++ implementation of the Data Distribution Service (DDS) standard, specified by the Object Management Group (OMG), and developed by Greenstone Technology Co., Ltd. Beijing China. With its reliability and high performance, SWIFT DDS is suitable for critical systems in industries such as autonomous vehicles, aerospace, robotics, and the industrial internet of things.

This repository provides the community version of SWIFT DDS. It is specifically offered for users to facilitate rapid software validation for constructing distributed systems on various hardware platforms and operating systems. 

## Features

### Remarkable Performance & High reliability
- Commercial DDS product with 6 years of R&D and verifications by projects from OEMs and Tier1’s
- Proprietary deterministic execution/communication technology, guarantee the real-time data communication
- Low overhead and high throughput
- Efficient resource utilization
### Industry-Leading Safety Guarantees
- ISO 26262 ASIL-D functional safety product certification
- Suitable for safety-critical applications in autonomous driving
- Compliant with MISRA C/C++ coding standards and pass static code analysis in QAC
- Comprehensive tests (unit, integration, embedded, and fault injection) achieving 100% safety requirements coverage and mandatory MC/DC code coverage, as required by ISO 26262 ASIL-D certification
### Minimum Dependency
- No third-party codes included
- Can be easily customized/extended according to users’ needs
- Support a wide range of SoC/OS and MCU/RTOS. Easy for cross-platform porting
### Full DDS Standard Compliance and performance-enhancing extensions
- Full compliance with DDS standard specifications
- Support for all DDS QoS policies
- Seamless interoperability with other DDS implementations
- Supported Customized Features:
  - ZeroCopy: Enables direct data transfer mechanisms to eliminate unnecessary memory copying operations
  - Inter-core communication: Support direct inter-core communication on heterogeneous chips (Horizon Robotics Journal 6, TDA4, S32G, etc.) such as arm A Core with R Core and arm A Core with M Core
  - UDP_FlowControl: Supports configuring DataWriter transmission and DataReader reception bandwidth at the process level, with flexible options to set either individually or simultaneously—the most restrictive flow limit will take effect
  - PreferTransportOrder: Dynamically selects the optimal communication channel based on the configured channel priority order
  - NetworkPortRangeQoSPolicy: Restricts processes to operate within a specified UDP port range
  - ThreadInstanceConfigQoSPolicy: When enabled, elevates thread resources from the participant level to the process level, reducing the number of threads created for nodes
### Comprehensive toolchains that further accelerate system integration
- Developers only need to focus on the intelligent driving logic and algorithms. Compatible with common intelligent driving chips, help fast integration and verification of intelligent driving products


## Cross-Platform

The repository offers a variety of dynamic libraries to support various platforms, which are accessible in their respective folders.

|  Operating System   |  CPU  |  Compiler  |  Hardware  |
|  ----  | ---- |  ----  | ---- |
| Ubuntu 18.04 LTS  | x86-64 |  gcc 7.5.0  |  X64 machine  |
| Ubuntu 20.04 LTS  | x86-64 |  gcc 9.4.0  |  X64 machine  |
| Ubuntu 22.04 LTS  | x86-64 |  gcc 11.4.0  |  X64 machine  |
| Ubuntu 24.04 LTS  | x86-64 |  gcc 13.2.0  |  X64 machine  |
| ARM Linux  | aarch64 |  aarch64-linux-gnu-gcc 9.3.0  | TDA4, J3/J5, ZU5, S32G, Orin, RPi4B |

## Repo structure 
#### demo folder
Five demos are included. This can be the start point for developing DDS applications.  
#### include folder
This folder contains header files for Greenstone implementations of DCPS(Data-Centric Publish-Subscribe) and RTPS(Real Time Publish Subscribe protocol), completely in accordance with OMG standards. How to include the header files are illustrated in demo applications.  
#### lib folder
This folder contains greenstone-DCPS dynamic-link libraries which need to be linked when building excutables of SWIFT DDS based applications. Various cpu architectures are supported.  
#### package folder
This folder contains the deb installation package of SWIFT DDS and can be installed using the sudo dpkg -i *.deb command. Various cpu architectures are supported.  
#### tools folder
This folder contains idlparser that is used to generate type related files. Please refer to the readme in the folder.  
#### utils folder
This folder contains various utility classes and interfaces. It provides basic functional classes such as 'ConfigParser' to ease the development.


## Usage
1. For the data_type to be used in communication, write a corresponding data_type.idl file to define the data type. It should be a 'struct' for the outmost type. Please refer to idl files in demos as examples. For standard idl languages and the full data types in idl, please refer to https://www.omg.org/spec/IDL/4.2.
2. Use idlparser to generate type related files. For the usage of idlparser, please refer to the readme in tools folder. Currently we provide command line parsers for both linux and windows. For the usage of idlparser generated files, please refer to the source files and cmake files of the demos.
3. Write application codes and use SWIFT DDS api's to send and receive data. Write a config.json file to configurate DDS Qos. Please refer to the demo applications for details. 
4. Write cmake file to compile the files in step 2&3, link to the DDS library for the specific platform. Please refer to the demo applications for details.

## Disclaimer

The community version of SWIFT DDS is licensed solely for the purpose of internal evaluation and testing. Users are strictly prohibited from transferring, distributing, sub-licensing, or deploying it outside the testing environment. Under no circumstances may the users use the evaluation version of SWIFT DDS for commercial, development, or production purposes. Failure to comply with this disclaimer may result in legal actions.

## Support

Please feel free to leave any feedbacks or ask for software supports. Users can either raise issues in this repo or contact gitsupport@greenstonesoft.com for support.

For MCUs or ARM R/M architectures, greenstone also provides SWIFT DDS-RT, which is specifically designed to run on resource-limited hardware. Unlike some MCU implementations that adopt DDS-XRCE protocol, DDS-RT is a full DDS protocol implementation with all the standard API's and Qos.

For the commercial version of SWIFT DDS/SWIFT DDS-RT, or any commercial cooperating inquiries, please contact bd@greenstonesoft.com.
