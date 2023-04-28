/**************************************************************
* @file ConfigParser.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <vector>
#include <list>
#include <fstream>
#include "json.hpp"
#include "dcps/SwiftDdsExport.h"

using json = nlohmann::json;

#define DECLARE_CONFIG_SINGLETON(classname) \
public:                                     \
    ~classname()                            \
    {                                       \
    }                                       \
    static classname* get_instance()        \
    {                                       \
        static classname instance;          \
        return &instance;                   \
    }                                       \
                                            \
private:                                    \
    classname()                             \
    {                                       \
    }

typedef std::shared_ptr<greenstone::dds::DomainParticipantQos> ParticipantQosPtr;
typedef std::shared_ptr<greenstone::dds::PublisherQos> PublisherQosPtr;
typedef std::shared_ptr<greenstone::dds::SubscriberQos> SubscriberQosPtr;
typedef std::shared_ptr<greenstone::dds::DataWriterQos> WriterQosPtr;
typedef std::shared_ptr<greenstone::dds::DataReaderQos> ReaderQosPtr;
typedef std::shared_ptr<greenstone::dds::TopicQos> TopicQosPtr;

/**
* @class ConfigParser
* @brief This class is used to parse configurations while creating DDS entities.
* @note
*/

class ConfigParser
{
public:
    // Load configuration json file by name
    gbool_t load_config_file(const std::string& configPath);

    // Get participant qos from json  
    ParticipantQosPtr get_participant_qos_from_json(const char* participantConfigName);

    // Get publisher qos from json  
    PublisherQosPtr get_publisher_qos_from_json(const char* publisherConfigName);

    // Get subscriber qos from json  
    SubscriberQosPtr get_subscriber_qos_from_json(const char* subscriberConfigName);

    // Get writer qos from json  
    WriterQosPtr get_writer_qos_from_json(const char* writerConfigName);

    // Get reader qos from json  
    ReaderQosPtr get_reader_qos_from_json(const char* readerConfigName);

    // Get topic qos from json  
    TopicQosPtr get_topic_qos_from_json(const char* topicConfigName);

    // Create a participant with configuration 
    greenstone::dds::DomainParticipant* get_participant_from_json(
        const char* participantConfigName,
        greenstone::dds::DomainParticipantListener* listener,
        const greenstone::dds::StatusMask& mask,
        const gbool_t& autoenableParticipant=true);

    // Create a publisher with configuration 
    greenstone::dds::Publisher* get_publisher_from_json(
        const char* publisherConfigName,
        greenstone::dds::DomainParticipant* domainParticipant,
        greenstone::dds::PublisherListener* listener,
        const greenstone::dds::StatusMask& mask);

    // Create a subscriber with configuration 
    greenstone::dds::Subscriber* get_subscriber_from_json(
        const char* subscriberConfigName,
        greenstone::dds::DomainParticipant* domainParticipant,
        greenstone::dds::SubscriberListener* listener,
        const greenstone::dds::StatusMask& mask);

    // Create a writer with configuration 
    greenstone::dds::DataWriter* get_writer_from_json(
        const char* writerConfigName,
        greenstone::dds::Publisher* publisher,
        greenstone::dds::Topic* topic,
        greenstone::dds::DataWriterListener* listener,
        const greenstone::dds::StatusMask& mask);

    // Create a reader with configuration 
    greenstone::dds::DataReader* get_reader_from_json(
        const char* readerConfigName,
        greenstone::dds::Subscriber* subscriber,
        greenstone::dds::Topic* topic,
        greenstone::dds::DataReaderListener* listener,
        const greenstone::dds::StatusMask& mask);

    // Create a topic with configuration 
    greenstone::dds::Topic* get_topic_from_json(
        const char* topicConfigName,
        greenstone::dds::DomainParticipant* domainParticipant,
        const std::string &topicName,
        const std::string &topicTypeName,
        greenstone::dds::TopicListener* listener,
        const greenstone::dds::StatusMask& mask);

private:
    // Get an ipv4 locator from an address string
    greenstone::dds::Locator_t get_locator_from_address(const std::string& address);

    // Get locator list from json 
    greenstone::dds::LocatorList_t get_locator_list(
        greenstone::dds::LocatorList_t defaultValue, 
        json& jLocator, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get duration value from json 
    greenstone::dds::Duration_t get_duration(
        greenstone::dds::Duration_t defaultValue, 
        json& jDuration, 
        const std::string& key1,
        const std::string& key2 = "");

    // Get bool value from json 
    gbool_t get_bool(
        gbool_t defaultValue, 
        json& jBool, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get qos data value from json
    std::vector<octet> get_qos_data(
        std::vector<octet> defaultValue, 
        json& jData, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get string value from json
    std::string get_string(
        std::string defaultValue, 
        json& jSeq, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get string sequence from json
    std::vector<std::string> get_string_sequence(
        std::vector<std::string> defaultValue, 
        json& jSeq, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get number value from json
    template <typename T>
    T get_number(
        T defaultValue, 
        json& jNumber, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Get enum value from json
    template <typename T>
    T get_enum(
        T defaultValue, 
        json& jEnum, 
        std::map<std::string, T> policyMap, 
        const std::string& policyName, 
        const std::string& key1, 
        const std::string& key2 = "");

    // Set DDS Security from json
    void set_security_qos(ParticipantQosPtr qos);

private:
    json m_j;
    bool m_initialized {false};

    DECLARE_CONFIG_SINGLETON(ConfigParser)
};

template <typename T>
T ConfigParser::get_number(T defaultValue, json& jNumber, const std::string& key1, const std::string& key2)
{
    json jValue;
    if (jNumber.contains(key1) && (key2 == ""))
    {
        jValue = jNumber[key1];
    }
    else if (jNumber.contains(key1) && jNumber[key1].contains(key2))
    {
        jValue = jNumber[key1][key2];
    } 
    else 
    {
        return defaultValue;
    }
    return jValue.get<T>();
}

template <typename T>
T ConfigParser::get_enum(T defaultValue, json& jEnum, std::map<std::string, T> policyMap, 
    const std::string& policyName, const std::string& key1, const std::string& key2)
{
    json jValue;
    if (jEnum.contains(key1) && (key2 == ""))
    {
        jValue = jEnum[key1];
    }
    else if (jEnum.contains(key1) && jEnum[key1].contains(key2))
    {
        jValue = jEnum[key1][key2];
    } 
    else 
    {
        return defaultValue;
    }
    std::string policy;
    if (jValue.is_string())
    {
        policy = jValue.get<std::string>();
    }
    else if (jValue.is_boolean())
    {
        policy = jValue.get<gbool_t>() ? "true" : "false";
    }

    if (policyMap.find(policy) != policyMap.end())
    {
        return policyMap[policy];
    }
    else
    {
        std::cout << "Please configure a valid " << policyName << " Kind QoS" << std::endl;
        return defaultValue;
    }
}

#endif // CONFIG_PARSER_H
