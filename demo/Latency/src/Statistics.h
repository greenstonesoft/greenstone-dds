/**************************************************************
* @file Statistics.h
* @copyright GREENSTONE TECHNOLOGY CO.,LTD. 2020-2023
*  All rights reserved
**************************************************************/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <string>

struct TestResult
{
    double avg; // average
    double std;
    double max; // 90%
    double min; // 10%
    double med;
};

/**
* @class TestStatistics
* @brief This class is a class which calculate latency result
* @note
*/

class TestStatistics
{
public:

    //calculate latency
    template <typename T>
    static TestResult cal_result(std::vector<T>& data)
    {
        TestResult result;
        std::sort(data.begin(), data.end());
        double sum = std::accumulate(data.begin(), data.end(), 0);
        uint32_t count = data.size();
        result.avg = sum / count;
        result.min = data[count / 10];
        result.max = data[count - count / 10]; // 10%
        result.med = (data[count / 2] + data[count / 2 + 1]) / 2.0; // even
        result.std = cal_std_dev(data, result.avg);

        return result;
    }

private:

    // calculate Standard Deviation
    template <typename T>
    static double cal_std_dev(const std::vector<T>& data, const double& avg) 
    { 
        T sum;
        for (auto& perData : data)
        {
            sum += std::pow(perData - avg, 2);
        }
        
        return std::sqrt(sum / data.size());
    }

};

#endif // STATISTICS_H
