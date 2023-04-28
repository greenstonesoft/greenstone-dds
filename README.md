# Greenstone SWIFT DDS 2.0 <img src="https://nwzimg.wezhan.cn/contents/sitefiles2049/10245019/images/37839368.png" width="29" height="25" >

<div style="text-align: center;">
<a href="https://www.greenstonesoft.com/"><img src="https://nwzimg.wezhan.cn/contents/sitefiles2049/10245019/images/37867159.png" style="display: inline-block;" hspace="8" vspace="2" width="142" height="40" ></a>
</div>


*SWIFT DDS* is a C++ implementation of the Data Distribution Service (DDS) standard, specified by the Object Management Group (OMG), and developed by Greenstone Soft Co., Ltd. Beijing China. With its reliability and high performance, SWIFT DDS is suitable for critical systems in industries such as autonomous vehicles, aerospace, robotics, and the industrial internet of things.

This repository provides an evaluation version of SWIFT DDS with a time limit of 4 hours. It is specifically offered for users to facilitate rapid software validation for constructing distributed systems on various hardware platforms and operating systems. 

## Features

SWIFT DDS offers a broad range of essential capabilities, including:
- Full compliance with the DCPS and RTPS standards
- Decoupling between the application layer and operating system layer
- Support for various transport modes, such as UDP, TCP, Shared Memory, Zero Copy, and Inter-processor communication (IPC)
- Real-time data transmission with low latency
- Abundant Quality-of-Service (QoS) policies for service customization
- Support for both synchronous and asynchronous interaction modes
- Plug-and-Play connectivity 
- Scalability to facilitate systems scaling to large networks
- A distributed framework that avoids a single point of failure

## Cross-Platform

The repository offers a variety of dynamic libraries to support various platforms, which are accessible in their respective folders.

|  Operating System   |  CPU  |  Compiler  |  Hardware  |
|  ----  | ---- |  ----  | ---- |
| Ubuntu 18.04.1 LTS  | x86-64 |  gcc 7.5.0  |  X64 machine  |
| ARM Linux  | aarch64 |  aarch64-linux-gnu-gcc 7.5.0  | J3/J5, ZU5, S32G, Orin, RPi4B |
| ARM Linux  | aarch64 |  aarch64-none-linux-gnu-gcc 9.2  | TDA4 |
| QNX 7.1.0  | aarch64 |  gcc_ntoaarch64le 8.3.0  | Orin, RPi4B |

## Repo structure 
#### demo folder
Five demos are included. This can be the start point for developing DDS applications.  
#### include folder
This folder contains header files for Greenstone implementations of DCPS(Data-Centric Publish-Subscribe) and RTPS(Real Time Publish Subscribe protocol), completely in accordance with OMG standards. How to include the header files are illustrated in demo applications.  
#### lib folder
This folder contains greenstone-DCPS dynamic-link libraries which need to be linked when building excutables of SWIFT DDS based applications. Various cpu architectures are supported.  
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

The evaluation version of SWIFT DDS is licensed solely for the purpose of internal evaluation and testing. Users are strictly prohibited from transferring, distributing, sub-licensing, or deploying it outside the testing environment. Under no circumstances may the users use the evaluation version of SWIFT DDS for commercial, development, or production purposes. Failure to comply with this disclaimer may result in legal actions.

## Support

Please feel free to leave any feedbacks or ask for software supports. Users can either raise issues in this repo or contact gitsupport@greenstonesoft.com for support.

Apart from SWIFT DDS, greenstone also provides SWIFT DDS-RT, which is specifically designed to run on resource-limited hardware, such as embedded MCUs. SWIFT DDS-RT has received the ISO 26262 ASIL-D Functional Safety certification, making it well suited for application scenarios that have high functional safety requirements. 

For the full version of SWIFT DDS/SWIFT DDS-RT, or any commercial cooperating inquiries, please contact bd@greenstonesoft.com.

