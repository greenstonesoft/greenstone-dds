/**************************************************************
* @file ThroughputPubBase.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef THROUGHPUT_PUB_BASE_H
#define THROUGHPUT_PUB_BASE_H

#include <condition_variable>
#include <vector>

/**
* @class ThroughputPubBase
* @brief This class is a base class of ThroughputPub.
* @note
*/

class ThroughputPubBase
{
public:
    
    explicit ThroughputPubBase(bool verbose) : 
        m_verbose(verbose), 
        m_ack(false) {}

    virtual ~ThroughputPubBase() {};

    // virtual function publish data
    virtual void publish() = 0;

    // virtual main function of test throughput
    virtual void test(const std::vector<std::pair<uint32_t, uint32_t>>& payloads, int sleepTime) = 0;

public:

    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_ack;

    bool m_verbose;

    uint32_t m_payloadSize;
	uint32_t m_payloadCount;
};

#endif  // THROUGHPUT_PUB_BASE_H
