#include <iostream>


#include "data/data_manager.h"
#include "experiment/experiment.h"
#include "dictionary/bloom_filters/bloom_filters.h"
#include "dictionary/open_hashing/double_hashing/double_hashing.h"
#include "dictionary/open_hashing/cockoo_hashing/cockoo_hashing.h"
#include "dictionary/open_hashing/linear_probing/linear_probing.h"
#include "dictionary/open_hashing/quadratic_probing/quadratic_probing.h"
#include "hash/hash_functions/division_hash.h"
#include "hash/hash_functions/multiplicative_hash.h"
#include "data/csv_file.h"


int main(){

    // PARAMETER DEFINITION
    int tableSize = 10000;
    int n = 4000;
    int nHashFunctions = 5;
    int seed = 165516;
    float keyPercentage = 0.5;

    // RANDOM DATA GENERATION

    DataManager data{};
    data.setSeed(seed);
    data.setSize(n);
    // creates the files if they do not exist already
    std::string path = "data/data/";
    data.generateIntegerData(path, keyPercentage);

    // DICTIONARIES DEFINITION
    auto h1 = DivisionHash();
    auto h2 = MultiplicativeHash();
    std::list<Dictionary*> dictionaries;
    DoubleHashing dh(tableSize, h1, h2);
    dictionaries.push_back(&dh);
    LinearProbing lp(tableSize, h1);
    dictionaries.push_back(&lp);
    QuadraticProbing qp(tableSize, h1);
    dictionaries.push_back(&qp);
    BloomFilters bf(tableSize, nHashFunctions, h1, h2);
    dictionaries.push_back(&bf);


    // DEFINE EXPERIMENT FILE
    std::string experimentsDir = "data/experiments/";
    CsvFile experimentFile(experimentsDir);

    // DEFINE AND RUN EXPERIMENT
    auto keys = data.getIntegerKeys(path);
    auto text = data.getIntegerText(path);
    for(auto const& dictionary : dictionaries){
        std::cout << "=================================" << std::endl;
        Experiment experiment(*dictionary);
        experiment.test(keys, text);
    }

    CsvRow row;
    row.push_back("new value");
    row.push_back("new vcalue 2");
    experimentFile.addRow(row);
    // SAVE DATA TO FILE
    experimentFile.write();

    return 0;
}
