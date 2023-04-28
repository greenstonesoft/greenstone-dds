/**************************************************************
* @file LatencySubBase.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef LATENCY_SUB_BASE_H
#define LATENCY_SUB_BASE_H

/**
* @class LatencySubBase
* @brief This class is a base class of LatencySub
* @note
*/

class LatencySubBase
{
public:

    explicit LatencySubBase(bool verbose)
        : m_verbose(verbose) {}

    virtual ~LatencySubBase() {};

    virtual void test() = 0;

public:

    bool m_verbose;
};

#endif // LATENCY_SUB_BASE_H
