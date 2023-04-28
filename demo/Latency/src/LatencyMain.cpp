/**************************************************************
* @file LatencyMain.cpp
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#include "LatencyPub.h"
#include "LatencySub.h"
#include "ConfigParser.h"
#include "ArgsParse.h"

int main(int argc, char* argv[])
{
    ParsedArguments arguments = parse_arguments(argc, argv);

    if (arguments.parseResult == ParseResult::FAILURE) 
    {
        return 0;
    }

    try 
    {
        ConfigParser::get_instance()->load_config_file(arguments.cfgPath);
    } 
    catch(const std::exception& ex)
    {
        std::cerr << "Exception in loading configuration file: " << ex.what() << '\n';
        return 0;
    }
    
    std::vector<std::pair<uint32_t, uint32_t>> payloads = {};
    try
    {
        get_test_payloads(arguments.payloadPath, payloads);
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Exception in loading payload file: " << ex.what() << '\n';
        return 0;
    }

    try 
    {
        switch (arguments.nodeType)
        {
            case NodeType::PUBLISHER:
            {
                LatencyPub dataWriter(arguments.verbose, arguments.topicName);
                
                dataWriter.test(payloads, arguments.sleepTime, arguments.printDetails);
                
                break;
            }
            case NodeType::SUBSCRIBER:
            {
                LatencySub dataReader(arguments.verbose, arguments.topicName);

                dataReader.test();

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
