#ifndef A_MULTIPLICATIVE_HASHING_H
#define A_MULTIPLICATIVE_HASHING_H

#include <cmath>

#include "hash_function.h"


/**
 * @class hash multiplicative function
     *        referencing
     *        D.E. Knuth
     *        The art of computer programming
     *        volume 3[516]
 * */
class MultiplicativeHashing : public HashFunction{

    /**
    * @brief basic constructor, define the name
    * */
    MultiplicativeHashing();

    /**
     * @brief hash function operator
     * @pre true
     * @post true
     * @param value is the key to be hashed
     * @param tableSize is the size of the hash table
     * @returns the hashed value of the key
     * */
    virtual unsigned int operator()(int key, unsigned int tableSize) const override ;

private:

    /**
     * @brief the word size of the computer
     * */
    int wordSize;

    /**
     * @brief constant relative prime to wordSize
     * */
    int A;

    /**
     * @brief the fraction of A div wordSize
     * */
    int fractionADivWord;

};


#endif //A_MULTIPLICATIVE_HASHING_H
