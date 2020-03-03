#ifndef A_EXPERIMENT_H
#define A_EXPERIMENT_H


#include <string>

#include "../dictionary/dictionary.h"


/**
 * @class The experiment class receives some parameters and a dictionary
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
    explicit Experiment(Dictionary const& dict);

    /**
     * @brief This functions tests the dictionary with the specified
     *        parameters and saves the results
     * */
    void test();

    /**
     * @brief This function writes the results of the test into a file
     * @param fileName is the name of the file to write into
     * */
    void write(std::string const& fileName) const;

private:

    /**
     * @brief is the current dictionary
     * */
    Dictionary dictionary;


};


#endif //A_EXPERIMENT_H
