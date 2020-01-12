//
// Created by eden on 12/01/2020.
//

#include "FileCacheManager.h"
#include <fstream>
template <class T>

// Constructor
FileCacheManager<T>::FileCacheManager(int capacity) {
    mCapacity = capacity;
}

template <class T>
FileCacheManager<T>::~FileCacheManager() {

}

template <class T>
void FileCacheManager<T>::insert(string key, T obj) {
    cacheInsert(key, obj);
    fileInsert(key, obj);
}

template <class T>
T FileCacheManager<T>::get(string key) {
    ifstream file_obj;
    T obj;

    // Search in cache
    if (mCache.find(key) != mCache.end()) {
        // Move the element to the head of the list
        cacheInsert(key, mCache[key].first);
        return mCache[key].first;
    }

    // Not found in cache, search in file
    // Opening file in input mode
    file_obj.open(obj.class_name + key, ios::in|ios::binary);
    // File not found, throw an exception
    if (!file_obj)
        throw "key not found";
    file_obj.read((char*)&obj, sizeof(obj));
    file_obj.close();
    // Add object to cache
    cacheInsert(key, obj);
    return obj;
}

template <class T>
void FileCacheManager<T>::cacheInsert(string key, T obj) {
    // Insert it into map if not present already
    if (mCache.find(key) == mCache.end()) {
        // Check if the map can hold more objects
        if (mCache.size() == (size_t)mCapacity) {
            // delete least recently used element
            string last = mObjectsList.back();
            // Pops the last element
            mObjectsList.pop_back();
            // Erase the last
            mCache.erase(last);
        }
    }
    // present in cache
    else
        mObjectsList.erase(mCache[key].second);

    // update reference
    mObjectsList.push_front(key);
    mCache[key] = {obj, mObjectsList.begin()};
}

template <class T>
void fileInsert(string key, T obj) {
    ofstream file_obj;

    // Opening file in output mode
    file_obj.open(obj.class_name + key, ios::out|ios::trunc|ios::binary);
    if (!file_obj)
        throw "Failed in creating file";

    // Writing the object's data in file
    file_obj.write((char*)&obj, sizeof(obj));

    file_obj.close();
}