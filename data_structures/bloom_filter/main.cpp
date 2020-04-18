#include <iostream>
#include "bloom_filter.h"


int main() {
    std::vector<std::pair<int, int>> experiments = { {10, 1}, {10, 3}, {50, 3}, {100, 3}};
    for(auto pr: experiments) {
        std::cout << "####################################" << std::endl;
        int buckets = pr.first;
        int hashes = pr.second;
        std::vector<std::string> vocabulary {
            "Bloom", "filter", "test", "vocabulary", "cats", "dogs", "and", "other", "stuff" 
        }; 

        std::cout << "Creating a bloom filter with " << buckets << " buckets and " << hashes << " hash functions..." << std::endl;
        BloomFilter bl(buckets, hashes);
        std::cout << "Probability of a false positive is " << bl.getFalsePositiveProbability(vocabulary.size()) << std::endl;
    
        std::vector<std::string> oov {
            "This", "words", "are", "not", "in", "the", "dictionary" 
        };

        std::cout << "Adding words..." << std::endl;
        for(auto word: vocabulary) {
            bl.add(word);
        }
        std::cout << "Testing words in vocabulary..." << std::endl;
        // All of this words should give a positive result
        for(auto word: vocabulary) {
            std::cout << word << ": " << (bl.search(word) ? "Word is in vocabulary" : "Something is wrong here") << std::endl;
        }
        std::cout << "Testing out of vocabulary words..." << std::endl;
        // All of this words should give a positive result
        for(auto word: oov) {
            std::cout << word << ": " << (bl.search(word) ? "True. This is a false positive!" : "False") << std::endl;
        }

    }
}


