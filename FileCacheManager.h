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

template <class T>

class FileCacheManager : public CacheManager<T> {
private:
    int mCapacity;
    unordered_map<string, typename std::pair<T, list<string>::iterator>> mCache;
    list<string> mObjectsList;

    void cacheInsert(string key, T obj);
    void fileInsert(string key, T obj);

public:

    void insert(string key, T obj);
    T get(string key);
    FileCacheManager(int capacity);
    ~FileCacheManager();
};


#endif //EX4_FILECACHEMANAGER_H
