/**************************************************************
* @file HelloworldMain.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
* All rights reserved
**************************************************************/

#include <iostream>
#include <string>

#include "HelloworldWriter.h"
#include "HelloworldReader.h"
#include "ConfigParser.h"

enum ParseResult 
{
    SUCCESS,
    FAILURE
};

enum NodeType 
{
    UNDEFINED,
    PUBLISHER,
    SUBSCRIBER
};

struct ParsedArguments 
{
    NodeType nodeType;
    std::string cfgPath;
    uint32_t sensorId;
    uint32_t numOfInstances;
    std::string topicName;
    uint32_t dataByte;
    uint32_t sampleCount;
    uint32_t sleepTime;
    uint32_t finalSleep;
    bool wait;
    uint32_t recvLimit;
    ParseResult parseResult;
};

inline bool exists (const std::string& name) 
{
    if (FILE* file = fopen(name.c_str(), "r")) 
    {
        fclose(file);
        return true;
    } 
    else 
    {
        return false;
    }   
}

inline ParsedArguments parse_arguments(int argc, char* argv[])
{
    ParsedArguments parsedArguments;
    parsedArguments.nodeType = NodeType::UNDEFINED;
    parsedArguments.cfgPath = "config.json";
    parsedArguments.sensorId = 0;
    parsedArguments.numOfInstances = 1;
    parsedArguments.topicName = "HelloWorld";
    parsedArguments.dataByte = 60000;
    parsedArguments.sampleCount = (std::numeric_limits<uint32_t>::max)();
    parsedArguments.sleepTime = 1000;
    parsedArguments.finalSleep = 0;
    parsedArguments.wait = false;
    parsedArguments.recvLimit = (std::numeric_limits<uint32_t>::max)();
    parsedArguments.parseResult = ParseResult::SUCCESS;

    int argCount = 1;
    bool printHelp = false;

    while (argCount < argc) 
    {
        if (strcmp(argv[argCount], "-h") == 0 || strcmp(argv[argCount], "--help") == 0) 
        {
            std::cout << "List of arguments.\n" << std::endl;
            printHelp = true;
            parsedArguments.parseResult = ParseResult::FAILURE;
            break;
        } 
        else if (strcmp(argv[argCount], "-n") == 0 || strcmp(argv[argCount], "--node-type") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Node type is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else if (strcmp(argv[argCount + 1], "pub") == 0 || strcmp(argv[argCount + 1], "publisher") == 0) 
            {
                parsedArguments.nodeType = NodeType::PUBLISHER;
            } 
            else if (strcmp(argv[argCount + 1], "sub") == 0 || strcmp(argv[argCount + 1], "subscriber") == 0) 
            {
                parsedArguments.nodeType = NodeType::SUBSCRIBER;
            } 
            else 
            {
                std::cout << "Node type needs to be assigned as a 'publisher' or 'subscriber'" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-c") == 0 || strcmp(argv[argCount], "--config-path") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Configuration file is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.cfgPath = argv[argCount + 1];
                if (!exists(parsedArguments.cfgPath)) 
                {
                    std::cout << "Configuration file does not exist or the path is wrong" << std::endl;
                    parsedArguments.parseResult = ParseResult::FAILURE;
                    break;
                }
            }
            argCount += 2;

        } else if (strcmp(argv[argCount], "-id") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Sensor id is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.sensorId = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-k") == 0 || strcmp(argv[argCount], "--number-of-keys") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Number of instances is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.numOfInstances = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-t") == 0 || strcmp(argv[argCount], "--topic-name") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Topic name is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.topicName = argv[argCount + 1];
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-b") == 0 || strcmp(argv[argCount], "--data-byte") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Data byte is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.dataByte = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-s") == 0 || strcmp(argv[argCount], "--sample-count") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Sample count is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.sampleCount = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-d") == 0 || strcmp(argv[argCount], "--sleep-duration") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Sleep time is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.sleepTime = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-f") == 0 || strcmp(argv[argCount], "--final-sleep") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Final sleep time is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.finalSleep = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-w") == 0 || strcmp(argv[argCount], "--wait") == 0) 
        {
            parsedArguments.wait = true;
            argCount += 1;
        } 
        else if (strcmp(argv[argCount], "-l") == 0 || strcmp(argv[argCount], "--rec-limit") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Number of samples to be received is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.recvLimit = atoi(argv[argCount + 1]);
            }
            argCount += 2;
        } 
        else 
        {
            std::cout << "Wrong arguments. Please check optional arguments as below.\n" << std::endl;
            printHelp = true;
            parsedArguments.parseResult = ParseResult::FAILURE;
            break;
        }
    }

    if (printHelp)
    {
        std::cout << "Usage:\n"\
                    "    -n, --node-type        <string>      Type of application node\n"
                    "                                         Values: publisher, pub, subscriber, sub\n"\
                    "                                         Default: undefined\n"\
                    "    -c, --config-path      <string>      Path of configuration file\n"\
                    "                                         Default: ./config.json\n" 
                    "    -t, --topic-name       <string>      Topic name that is used to match writer and reader\n"\
                    "                                         Default: HelloWorld\n"
                    "    -id                    <int>         Sensor id that will be used as the key of datatype\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: 0\n"
                    "    -k, --number-of-keys   <int>         Number of keys (instances) that are sent by writer\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: 1\n"
                    "    -b, --data-byte        <int>         The size of data to be sent (byte)\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: 60000\n"
                    "    -s, --sample-count     <int>         Number of samples to be sent\n"
                    "                                         ONLY effective on Writer"
                    "                                         Default: infinite\n"
                    "    -d, --sleep-duration   <int>         The interval between two samples to be sent (millisecond)\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: 1000\n"\
                    "    -f, --final-sleep      <int>         The duration to be spent after all data samples have been sent (millisecond)\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: 0\n"\
                    "    -w, --wait             <bool>        Whether to wait for matched endpoints before sending data\n"\
                    "                                         ONLY effective on Writer"
                    "                                         Default: false\n"\
                    "    -l, --rec-limit        <int>         Total number of samples to be received\n"
                    "                                         ONLY effective on Reader"
                    "                                         Default: infinite\n"
        << std::endl;
    }

    return parsedArguments;
}


int main(int argc, char *argv[])
{
    ParsedArguments arguments = parse_arguments(argc, argv);

    if (arguments.parseResult == ParseResult::FAILURE)
    {
        return 0;
    }

    ConfigParser::get_instance()->load_config_file(arguments.cfgPath);

    try
    {
        switch (arguments.nodeType)
        {
            case NodeType::PUBLISHER:
            {
                // Create an instance of DataWriter to send data
                HelloworldWriter dataWriter;
                if (dataWriter.init(arguments.topicName))
                {
                    dataWriter.run(arguments.sensorId, arguments.numOfInstances, arguments.dataByte, 
                        arguments.sampleCount, arguments.sleepTime, arguments.finalSleep, arguments.wait);
                }
                break;
            }
            case NodeType::SUBSCRIBER:
            {
                // Create an instance of DataReader to receive data
                HelloworldReader dataReader;
                if (dataReader.init(arguments.topicName))
                {
                    dataReader.run(arguments.recvLimit);
                }
                break;
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception in run(): " << ex.what() << std::endl;
        return 0;
    }
    return 0;
}
