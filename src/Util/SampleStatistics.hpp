#ifndef SAMPLESTATISTICS_HPP
#define SAMPLESTATISTICS_HPP

#include <vector>
#include <string>

class SampleStatistics {
public:
    static double sampleMean(std::vector<double> sample);

    //maybe the median???

    static double sampleVariance(std::vector<double> sample);

    static double sampleStdDeviation(std::vector<double> sample);

    static std::string sampleMetricsString(std::vector<double> sample);
};

#endif //SAMPLESTATISTICS_HPP
