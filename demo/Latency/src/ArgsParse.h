/**************************************************************
* @file ArgsParse.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef ARGS_PARSE_H
#define ARGS_PARSE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

//arguments parse result
enum ParseResult 
{
    SUCCESS,
    FAILURE
};

//the type of node
enum NodeType 
{
    UNDEFINED,
	PUBLISHER,
	SUBSCRIBER
};

//all arguments of node
struct ParsedArguments 
{
    NodeType nodeType;
    std::string cfgPath;
    std::string payloadPath;
    uint32_t sleepTime;
    std::string topicName;
    bool verbose;
    bool printDetails;
    ParseResult parseResult;
};

//check if file exists
bool exists (const std::string& name) 
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

//convert string to number
uint32_t convert_to_number(std::string str)
{
    int lastPosition = -1;
    int nextPosition;
    uint32_t result = 1;

    while ((nextPosition = str.find('*', lastPosition + 1)) != std::string::npos)
    {
        result *= std::stoi(str.substr(lastPosition + 1, nextPosition));
        lastPosition = nextPosition;
    }
    result *= std::stoi(str.substr(lastPosition + 1, str.size()));
    return result;
}

//get payloads from file
void get_test_payloads(
    const std::string& path,
    std::vector<std::pair<uint32_t, uint32_t>>& testPayloads)
{
    std::ifstream input(path);
    std::string line;
    std::string delimiter = ",";
    uint16_t delimiterIndex;
    uint32_t payload;
    uint32_t count;

    for (;getline(input, line);)
    {   
        if (line.size() >= 2 && (line.substr(0, 2) == "**" || line.substr(0, 2) == "//"))
        {
            continue; 
        }
        if (std::all_of(line.begin(), line.end(), isspace))
        {
            continue;
        }
        delimiterIndex = line.find(delimiter);
        payload = convert_to_number(line.substr(0, delimiterIndex));
        count = convert_to_number(line.substr(delimiterIndex + 1, line.size()));
        testPayloads.push_back(std::make_pair(payload, count));
    }
}

//get all input arguments of node
ParsedArguments parse_arguments(int argc, char* argv[])
{
    ParsedArguments parsedArguments;
    parsedArguments.nodeType = NodeType::UNDEFINED;
    parsedArguments.cfgPath = "config.json";
    parsedArguments.payloadPath = "payload.txt";
    parsedArguments.sleepTime = 0;
    parsedArguments.topicName = "Latency";
    parsedArguments.verbose = false;
    parsedArguments.printDetails = false;
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
        } 
        else if (strcmp(argv[argCount], "-p") == 0 || strcmp(argv[argCount], "--payload-path") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "Payload file is missed" << std::endl;
                parsedArguments.parseResult = ParseResult::FAILURE;
                break;
            } 
            else 
            {
                parsedArguments.payloadPath = argv[argCount + 1];
                if (!exists(parsedArguments.payloadPath)) 
                {
                    std::cout << "Payload file does not exist or the path is wrong" << std::endl;
                    parsedArguments.parseResult = ParseResult::FAILURE;
                    break;
                }
            }
            argCount += 2;
        } 
        else if (strcmp(argv[argCount], "-s") == 0 || strcmp(argv[argCount], "--sleep-time") == 0) 
        {
            parsedArguments.sleepTime = atoi(argv[argCount + 1]);
            argCount += 2;

        } 
        else if (strcmp(argv[argCount], "-t") == 0 || strcmp(argv[argCount], "--topic-name") == 0) 
        {
            if (argCount + 1 == argc) 
            {
                std::cout << "topic type is missed. Default value (Latency) will be used." << std::endl;
            } else 
            {
                parsedArguments.topicName = argv[argCount + 1];
            }
            argCount += 2;

        } 
        else if (strcmp(argv[argCount], "-v") == 0 || strcmp(argv[argCount], "--verbose") == 0) 
        {
            parsedArguments.verbose = true;
            argCount += 1;

        } 
        else if (strcmp(argv[argCount], "-d") == 0 || strcmp(argv[argCount], "--details") == 0) 
        {
            parsedArguments.printDetails = true;
            argCount += 1;

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
                    "                                         Values: publisher, pub, subscriber, sub\n"
                    "                                         Default: undefined\n"
                    "    -c, --config-path      <string>      Path of configuration file\n"
                    "                                         Default: ./config.json\n" 
                    "    -p, --payload-path     <string>      Path of payload file\n"
                    "                                         Default: ./payload.txt, sweep from 16 B to 32 MB\n"
                    "    -s, --sleep-time       <int>         Sleep time between sending data (unit: ms)\n"
                    "                                         Default: 0\n"
                    "    -t, --topic-name       <string>      Topic of data\n"
                    "                                         Default: Latency\n"
                    "    -v, --verbose          <bool>        Verbose mode\n"
                    "                                         Default: false\n"
                    "    -d, --details          <bool>        Print details for whole record of testing results\n"
                    "                                         Default: false"
		<< std::endl;
    }

    return parsedArguments;
}
#endif // ARGS_PARSE_H
