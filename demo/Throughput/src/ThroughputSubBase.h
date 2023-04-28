/**************************************************************
* @file ThroughputSubBase.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef THROUGHPUT_SUB_BASE_H
#define THROUGHPUT_SUB_BASE_H

#include <iomanip>
#include <chrono>
#include <atomic>
#include <iostream>

/**
* @class ThroughputSubBase
* @brief This class is a base class of ThroughputSub
* @note
*/

class ThroughputSubBase
{
public:

    explicit ThroughputSubBase(bool verbose) : 
        m_verbose(verbose), 
        m_sampleCnt(0) {}

    virtual ~ThroughputSubBase() {};

    virtual void test() = 0;

    // print the result of throughput
    void print_throughput_result()
    {
        uint32_t payloadSize = m_payloadSize;
        std::string throughputUnit("us");
        std::string payloadUnit(" B");
        double lossRate = (m_payloadCount - m_sampleCnt + 1) * 100.0 / m_payloadCount;
    
        if ( m_deltaT >= 10000000 )
        {
            m_deltaT /= 1000000;
            throughputUnit = " s";
        }
        else if ( m_deltaT >= 10000 )
        {
            m_deltaT /= 1000;
            throughputUnit = "ms";
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

        std::cout << " Payload: "    << std::setw(10) << payloadSize  << " " << payloadUnit << " |"\
                  << " Received: "   << std::setw(10) << m_sampleCnt - 1 << " |"\
                  << " Loss Rate: "  << std::setw(10) << std::fixed << std::setprecision(2) << lossRate << " % |"\
                  << " Time Spent: " << std::setw(10) << m_deltaT   << " " << throughputUnit << " |"\
                  << " Throughput: " << std::setw(10) << std::fixed << std::setprecision(2) << m_throughput << " Mbps" << std::endl;
    }  

public:

    bool m_verbose;

    uint32_t m_payloadSize;
	uint32_t m_payloadCount;

    std::chrono::steady_clock::time_point m_t1, m_t2;
    uint64_t m_deltaT;
    uint32_t m_sampleCnt;
    double m_throughput;
};

#endif  // THROUGHPUT_SUB_BASE_H
