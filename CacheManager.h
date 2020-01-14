//
// Created by eden on 12/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <iostream>

using namespace std;

template <class T>

class CacheManager {
public:
    bool find(string key);
    void insert(string key, T obj);
    T get(string key);

};
#endif //EX4_CACHEMANAGER_H
