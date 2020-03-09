#include <iostream>


#include "data/data_manager.h"
#include "experiment/experiment.h"
#include "dictionary/bloom_filters/bloom_filters.h"
#include "dictionary/open_hashing/double_hashing/double_hashing.h"
#include "dictionary/open_hashing/cuckoo_hashing/cuckoo_hashing.h"
#include "dictionary/open_hashing/linear_probing/linear_probing.h"
#include "dictionary/separate_chaining/separate_chaining_lists.h"
#include "dictionary/separate_chaining/separate_chaining_vector.h"
#include "dictionary/open_hashing/quadratic_probing/quadratic_probing.h"
#include "hash/hash_functions/division_hash.h"
#include "hash/hash_functions/fibonacci_hash.h"
#include "hash/hash_functions/random_hash.h"
#include "data/csv_file.h"


void usage(){
    std::cerr << "Usage: ./experimenter n load nHashFunctions seed nRounds keyPercentage inputDir outputDir" << std::endl << std::endl;
    std::cerr << "    n: the number of keys to insert to the dictionary " << std::endl;
    std::cerr << "    load: the load factor of the table, size of the table = n / loadFactor" << std::endl;
    std::cerr << "    nHashFunctions: the number of hash functions used by the bloom filters" << std::endl;
    std::cerr << "    seed: the random seed for the data generation" << std::endl;
    std::cerr << "    nRounds: the number of repetitions per dictionary per experiment" << std::endl;
    std::cerr << "    keyPercentage: the minimum percentage of keys that appear in the data text files" << std::endl;
    std::cerr << "    inputDir: the directory where the generated data must be placed, the directory must exist" << std::endl;
    std::cerr << "    outputDir: the directory where the experiment must be placed, the directory must exist" << std::endl << std::endl;
}

int main(int argc, char* argv[]){

    if(argc < 8){
        usage();
        return 1;
    }

    // PARAMETER DEFINITION
    int n = std::stoi(argv[1]);
    int tableSize = float(n) / std::stof(argv[2]);
    int nHashFunctions = std::stoi(argv[3]);
    int seed = std::stoi(argv[4]);
    int nRounds = std::stoi(argv[5]);
    float keyPercentage = std::stof(argv[6]);
    std::string inputPath = argv[7];
    if(inputPath[inputPath.size() - 1] != '/')inputPath += '/';
    std::string outputPath = argv[8];
    if(inputPath[outputPath.size() - 1] != '/')outputPath += '/';

    // RANDOM DATA GENERATION

    DataManager data{};
    data.setSeed(seed);
    data.setSize(n);
    // creates the files if they do not exist already

    data.generateIntegerData(inputPath, keyPercentage);

    // DICTIONARIES DEFINITION
    auto h1 = DivisionHash();
    auto h2 = FibonacciHash();
    auto h3 = RandomHash();

    DoubleHashing dh(tableSize, h1, h2);
    LinearProbing lp(tableSize, h2);
    QuadraticProbing qp(tableSize, h1);
    BloomFilters bf(tableSize, nHashFunctions, h1, h2);
    CuckooHashing ck(tableSize, h1, h2, 10);
    SeparateChainingLists spl(tableSize, h2);
    SeparateChainingVector spv(tableSize, h2);

    std::list<Dictionary*> dictionaries{&dh, &lp, &qp, &ck, &spl, &spv, &bf};
    std::vector<std::string> names{"DH", "LP", "QP", "CK", "SPL", "SPV", "BF"};

    // DEFINE EXPERIMENT FILE

    CsvFile experimentFile(outputPath);

    // DEFINE COL NAMES
    CsvRow colNames{"dictionaryType", "n", "tableSize", "nHashFunctions",
                    "seed", "keyPercentage", "nCollisions",
                    "buildTime", "successMeanTime", "failMeanTime", "successMaxTime",
                    "successMinTime", "failMaxTime", "failMinTime", "falsePositives"};

    experimentFile.addRow(colNames);


    // DEFINE AND RUN EXPERIMENT
    int i = 0;
    auto keys = data.getIntegerKeys(inputPath);
    auto text = data.getIntegerText(inputPath);
    for(auto const& dictionary : dictionaries){
        std::cout << "=================================" << std::endl;
        std::cout << "Testing " << names[i] << std::endl;

        Experiment experiment(*dictionary);
        experiment.test(keys, text);
        CsvRow row{names[i++],
                   std::to_string(n), std::to_string(tableSize), std::to_string(nHashFunctions),
                   std::to_string(seed), std::to_string(keyPercentage), std::to_string(experiment.getCollisions()),
                   std::to_string(experiment.getBuildTime()), std::to_string(experiment.getSuccessMeanTime()),
                   std::to_string(experiment.getFailMeanTime()), std::to_string(experiment.getSuccessMaxTime()),
                   std::to_string(experiment.getSuccessMinTime()), std::to_string(experiment.getFailMaxTime()),
                   std::to_string(experiment.getFailMinTime()),
                   std::to_string(experiment.getFalsePositives())};
        experimentFile.addRow(row);
    }


    // SAVE DATA TO FILE
    experimentFile.write();

    return 0;
}
