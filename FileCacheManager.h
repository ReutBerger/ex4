//
// Created by eden on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class FileCacheManager : public CacheManager<string> {
private:
    hash<string> hashStr;
    int mCapacity;
    string hashKey;
    unordered_map<string, typename std::pair<string, list<string>::iterator>> mCache;
    list<string> mObjectsList;

    string makeStrHash(string& key);
    void cacheInsert(string& key, string& obj);
    void fileInsert(string& key, string& obj);

public:

    bool find(string& key);
    void insert(string& key, string& obj);
    string get(string& key);
    FileCacheManager(int capacity);
    ~FileCacheManager();
};


#endif //EX4_FILECACHEMANAGER_H
