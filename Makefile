# variable definition
OPT = -O3
STD = -std=c++17
COMPILER = g++ $(OPT)
OUTNAME = -o experimenter

# directory definition
DATA = data/data_manager.cpp
CSV = data/csv_file.cpp
DICTIONARY_BLOOM = dictionary/bloom_filters/bloom_filters.cpp
DICTIONARY_CHAINING_LISTS = dictionary/separate_chaining/separate_chaining_lists.cpp
DICTIONARY_CHAINING_VECTOR = dictionary/separate_chaining/separate_chaining_vector.cpp
DICTIONARY_DOUBLE_HASHING = dictionary/open_hashing/double_hashing/double_hashing.cpp
DICTIONARY_CUCKOO_HASHING = dictionary/open_hashing/cuckoo_hashing/cuckoo_hashing.cpp
DICTIONARY_LINEAR_PROBING = dictionary/open_hashing/linear_probing/linear_probing.cpp
DICTIONARY_QUADRATIC_PROBING = dictionary/open_hashing/quadratic_probing/quadratic_probing.cpp
EXPERIMENT = experiment/experiment.cpp
HASH_FUNCTIONS = hash/hash_functions/division_hash.cpp \
				 hash/hash_functions/fibonacci_hash.cpp \
				 hash/hash_functions/random_hash.cpp
RANDOM = random/rand_generator.cpp
MAIN = experimenter.cpp

TARGET = $(RANDOM) $(DATA) $(HASH_FUNCTIONS) $(DICTIONARY_BLOOM) $(CSV)\
		 $(DICTIONARY_CHAINING_LISTS) $(DICTIONARY_CHAINING_VECTOR) \
		 $(DICTIONARY_DOUBLE_HASHING) $(DICTIONARY_LINEAR_PROBING) $(DICTIONARY_QUADRATIC_PROBING) $(DICTIONARY_CUCKOO_HASHING) \
		 $(EXPERIMENT)

# rule definition
experimenter: $(TARGET) $(MAIN)
	$(COMPILER) $(STD) $(TARGET) $(MAIN) $(OUTNAME)

clean:
		rm experimenter
