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
    virtual bool find(string& key) = 0;
    virtual void insert(string& key, T& obj) = 0;
    virtual T get(string& key) = 0;

};
#endif //EX4_CACHEMANAGER_H
