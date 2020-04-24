#ifndef GENOMES_H
#define GENOMES_H

// includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "common.h"
#include "fastareader.h"
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include "options.h"

using namespace std;

class MapResult{

public:
    MapResult(){
        mapped = false;
        start = 0;
        len = 0;
        ed = 0x7FFFFFFF; // initialized with a very large ED
    }
public:
    bool mapped;
    uint32 start;
    uint32 len;
    uint32 ed; // edit distance
};

class Genomes
{
public:
    Genomes(string fastaFile, Options* opt);
    ~Genomes();
    void run();
    void report();
    void reportJSON(ofstream& ofs);
    void reportHtml(ofstream& ofs);

private:
    void buildKmerTable();
    void addKmer(uint64 key, int id);
    void makeUniqueKMER();

private:
    int mGenomeNum;
    FastaReader* mFastaReader;
    vector<string> mSequences;
    vector<string> mNames;
    vector<vector<string>> mUniqueKmers;
    // KMER: value
    // If value is negative, means more than one contig hit this KMER
    unordered_map<uint64, int> mKmerTable;
    Options* mOptions;
    long mHitCount;
    long mMissedCount;
    char* mBloomFilterArray;
};


#endif