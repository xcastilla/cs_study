#include <functional>
#include <vector>
#include <math.h>
#include "thirdparty/MurmurHash3.h"

typedef void (*pfHash) ( const void * blob, const int len, const uint32_t seed, void * out );

class BloomFilter {
public:
    BloomFilter(int nBuckets, int nHashes);
    ~BloomFilter();
    void add(std::string& key);
    bool search(std::string& key) const;
    float getFalsePositiveProbability(int expected_elements) const;
private:
    // Vector of hash functions initialized with different seeds
    // https://stackoverflow.com/a/30906150
    using bindFnType = decltype(std::bind(MurmurHash3_x64_128, std::placeholders::_1, std::placeholders::_2, uint32_t(), std::placeholders::_3));
    std::vector<bindFnType> hashFuncs_;

    // Buckets
    std::vector<bool> buckets_;
    int nBuckets_;
};

BloomFilter::BloomFilter(int nBuckets, int nHashes) {
    using namespace std::placeholders;
    // Initialize pointers to murmur hash with different random seeds
    for(int i = 0; i < nHashes; i++) {
        int rnd = rand();
        auto fn = std::bind(MurmurHash3_x86_32, _1, _2, (uint32_t)rnd, _3);
        hashFuncs_.push_back(fn);
    }
    // Initialize bucket vector
    nBuckets_ = nBuckets;
    buckets_ = std::vector<bool>(nBuckets_, false);
}

BloomFilter::~BloomFilter() {
    
}

uint32_t bytes2uint32(const char* b) {
    uint32_t ret;
    ret = (b[0] << 24) & 0xFF000000;
    ret |= (b[1] << 16) & 0x00FF0000;
    ret |= (b[2] << 8) & 0x0000FF00;
    ret |= (b[3] << 0) & 0x000000FF;
    return ret;
}

void BloomFilter::add(std::string& key) {
    for(auto fn: hashFuncs_) {
        char hash[4];
        fn(key.c_str(), key.length(), hash);
        uint32_t pos = bytes2uint32(hash);
        buckets_[pos%nBuckets_] = true;
    }
}

bool BloomFilter::search(std::string& key) const {
    for(auto fn: hashFuncs_) {
        char hash[4];
        fn(key.c_str(), key.length(), hash);
        uint32_t pos = bytes2uint32(hash);
        if(!buckets_[pos%nBuckets_]) {
            return false;
        }
    }
    return true;
}

float BloomFilter::getFalsePositiveProbability(int expected_elements) const {
    return pow(1.0 - pow(1.0 - 1.0 / nBuckets_, hashFuncs_.size() * expected_elements), hashFuncs_.size()); 
}

