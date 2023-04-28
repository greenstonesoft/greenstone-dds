/**************************************************************
* @file LatencyPubBase.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef LATENCY_PUB_BASE_H
#define LATENCY_PUB_BASE_H

#include "Statistics.h"

#include <iomanip>
#include <condition_variable>
#include <algorithm>
#include <numeric>
#include <math.h>

/**
* @class LatencyPubBase
* @brief This class is a base class of LatencyPub, define a print function.
* @note
*/

class LatencyPubBase
{
public:
    
    explicit LatencyPubBase(bool verbose) : 
        m_verbose(verbose), 
        m_ack(false), 
        m_sampleCnt(0) {}

    virtual ~LatencyPubBase() {};

    // virtual function publish data
    virtual void publish() = 0;

    // virtual function publish data and calculate latency
    virtual void test(
        const std::vector<std::pair<uint32_t, uint32_t>>& payloads, 
        int sleepTime, 
        bool printDetails) = 0;
    
    // print latency result
    void print_latency_result()
    {   
        uint32_t latencyAvg = static_cast<uint32_t>(m_result.avg + 0.5);
        uint32_t latencyStd = static_cast<uint32_t>(m_result.std + 0.5);
        uint32_t latencyMax = static_cast<uint32_t>(m_result.max + 0.5);
        uint32_t latencyMin = static_cast<uint32_t>(m_result.min + 0.5);
        uint32_t latencyMed = static_cast<uint32_t>(m_result.med + 0.5);
        uint32_t payloadSize = m_payloadSize;
        std::string latencyUnit("us");
        std::string payloadUnit(" B");
        double lossRate = (1 - sqrt(m_sampleCnt / m_payloadCount)) * 100;

        if ( latencyAvg >= 10000000 )
        {
            latencyAvg /= 1000000;
            latencyStd /= 1000000;
            latencyMax /= 1000000;
            latencyMin /= 1000000;
            latencyMed /= 1000000;
            latencyUnit = " s";
        }
        else if ( latencyAvg >= 10000 )
        {
            latencyAvg /= 1000; 
            latencyStd /= 1000;
            latencyMax /= 1000;
            latencyMin /= 1000;
            latencyMed /= 1000;
            latencyUnit = "ms";
        }

        if ( payloadSize >= 1024 * 1024 ) 
        {
            payloadSize = payloadSize >> 20;
            payloadUnit = "MB";
        } 
        else if ( payloadSize >= 1024 ) 
        {
            payloadSize = payloadSize >> 10;
            payloadUnit = "KB";
        }

        std::cout << " Payload: "    << std::setw(10) << payloadSize << " " << payloadUnit  << " |"\
                  << " Received: "   << std::setw(10) << m_sampleCnt << " |"\
                  << " Loss Rate: "  << std::setw(10) << std::fixed  << std::setprecision(2) << lossRate    << " % |"\
                  << " latencyAvg: " << std::setw(10) << latencyAvg  << " "                  << latencyUnit << " |"\
                  << " latencyMax: " << std::setw(10) << latencyMax  << " "                  << latencyUnit << " |"\
                  << " latencyMin: " << std::setw(10) << latencyMin  << " "                  << latencyUnit << " |"\
                  << " latencyMed: " << std::setw(10) << latencyMed  << " "                  << latencyUnit << " |"\
                  << " latencyStd: " << std::setw(10) << latencyStd  << " "                  << latencyUnit << " |"\
                  << std::endl;
    }

public:

    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_ack;
    bool m_verbose;

    uint32_t m_payloadSize;
	uint32_t m_payloadCount;
		
    std::chrono::steady_clock::time_point m_t1, m_t2;
    uint64_t m_deltaT;
    uint32_t m_sampleCnt;
    TestResult m_result;
};

#endif // LATENCY_PUB_BASE_H
