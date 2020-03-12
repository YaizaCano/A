#ifndef A_EXPERIMENT_H
#define A_EXPERIMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <chrono>
#include <limits>

#include "../dictionary/dictionary.h"


/**
  * @typedef type definition for a really big double
  * */
typedef long double BigDouble;

/**
 * @class Experiment
 * @brief The experiment class receives some parameters and a dictionary
 *        and tests them, the results are saved in a data structure
 *        and finally they can be written into a file
 *
 * */
class Experiment {

public:

    /**
     * @brief Generate a basic experiment with a defined dictionary
     * @param dict is the dictionary to test
     * */
    explicit Experiment(Dictionary  &dict);

    /**
     * @brief This functions tests the dictionary with the specified
     *        parameters and saves the results
     * */
    void test(std::vector<int> const& keys, std::vector<int> const& text);


    /**
     * @brief getter for the succesful probes in lookup
     * */
    double getSuccessProbes() const;

    /**
     * @brief getter for the fail probes in lookup
     * */
    double getFailProbes() const;

    /**
     * @brief getter for the build time in microseconds
     * */
    BigDouble getBuildTime() const;

    /**
     * @brief getter for the success lookup time in microseconds
     * */
    BigDouble getSuccessMeanTime()const;

    /**
     * @brief getter for the failed lookup time in microseconds
     * */
    BigDouble getFailMeanTime()const;

    /**
     * @brief getter the number of false positives, returns negative if
     *        false negatives
     * @pre there cannot be false positives and false negatives at the same time
     * */
    int getFalsePositives() const;


    /**
     * @brief getter for the max successful lookup in microseconds
     * */
    double getSuccessMaxTime() const;


    /**
     * @brief getter for the max failed lookup in microseconds
     * */
    double getFailMaxTime() const;

    /**
     * @brief getter for the min successful lookup in microseconds
     * */
    double getSuccessMinTime() const;

    /**
     * @brief getter for the min successful lookup in microseconds
     * */
    double getFailMinTime() const;

    /**
     * @brief getter for the succesful theorical value,
     *        avg probes for hash tables and false positives for bf
     * */
    double getSuccessTheoricalValue(float loadFactor) const;

    /**
     * @brief getter for the fail theorical value,
     *        avg probes for hash tables and false positives for bf
     * */
    double getFailTheoricalValue(float loadFactor) const;

private:

    /**
     * @brief represents the initial time for a task
     * */
    std::chrono::steady_clock::time_point startPoint;

    /**
     * @brief represents the final time for a task
     * */
    std::chrono::steady_clock::time_point endPoint;

    /**
     * @brief contains the number of the successful lookups of the experiment
     * */
    unsigned int successLookupTimes;

    /**
    * @brief contains the number of the failed lookups of the experiment
    * */
    unsigned int failLookupTimes;

    /**
     * @brief contains the mean time for successful lookups
     * */
    BigDouble successLookupTimeMean;

    /**
     * @brief contains the mean time for unsuccessful lookups
     * */
    BigDouble failLookupTimeMean;

    /**
     * @brief contains the maxLookupTime for succesful lookup
     * */
     BigDouble successMaxLookupTime;

    /**
    * @brief contains the minLookupTime for succesful lookup
    * */
    BigDouble successMinLookupTime;

    /**
    * @brief contains the maxLookupTime for fail lookup
    * */
    BigDouble failMaxLookupTime;

    /**
    * @brief contains the min LookupTime for fail lookup
    * */
    BigDouble failMinLookupTime;

    /**
     * @brief contains the time to build the dictionary (insert all the keys)
     * */
    BigDouble  buildTime;

    /**
     * @brief contains the number of false positives that happened during lookups,
     *        if it is negative then that means that false negatives where found
     * */
    int falsePositives;


    /**
     * @brief contains the number of probes in a successful search
     * */
    double successProbes;

    /**
     * @brief contains the number of probes in an unsuccessful search
     */
    double failProbes;

    /**
     * @brief is the current dictionary
     * */
    Dictionary* dictionary;

    /**
     * @brief sets the initial starting time  to now
     * */
    void startTimer();

    /**
     * @brief sets the end time to now
     * */
    void endTimer();

    /**
     * @brief gets the difference between the initial time point and the end time point
     * */
    double getElapsedTime() const;

    /**
     * @brief test to build a table with the specified keys
     * @param vector keys to insert into the dictionary
     * */
    void buildTable(const std::vector<int> &vector);

    /**
     * @brief test to search n elements in the dictionary and save the results
     * @param vector contains the elements to search
     * */
    void searchElements(const std::vector<int> &vector);
};


#endif //A_EXPERIMENT_H
