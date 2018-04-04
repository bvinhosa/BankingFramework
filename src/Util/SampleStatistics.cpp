#include "SampleStatistics.hpp"

#include <cmath>
#include <sstream>

double SampleStatistics::sampleMean(std::vector<double> sample){

    int numMembers = sample.size();

    if (numMembers > 0){

        double runningTotal = 0.0;

        for (int i = 0; i < numMembers; i++)
            runningTotal += sample[i];

        return (runningTotal / numMembers);
    }

    else
        return (double)NAN;
}

double SampleStatistics::sampleVariance(std::vector<double> sample){

    int numMembers = sample.size();

    if (numMembers > 1){

        double runningTotal = 0.0;
        double deviation = 0.0;
        double thisSampleMean = sampleMean(sample);

        for (int i = 0; i < numMembers; i++){
            deviation = sample[i] - thisSampleMean;
            runningTotal += (deviation * deviation);
        }

        return (runningTotal / (numMembers - 1));
    }

    else if (numMembers == 1)
        return 0.0;

    else
        return (double)NAN;

}

double SampleStatistics::sampleStdDeviation(std::vector<double> sample){
    return std::sqrt(sampleVariance(sample));
}

std::string SampleStatistics::sampleMetricsString(std::vector<double> sample) {

    std::stringstream strStream;

    strStream << "count: " << sample.size() <<
              "; mean: " << SampleStatistics::sampleMean(sample) <<
              "; st. dev.: " << SampleStatistics::sampleStdDeviation(sample);

    return strStream.str();
}