//
// Created by eden on 12/01/2020.
//

#include "FileCacheManager.h"
#include <stdio.h>
#include <fstream>

// Constructor
FileCacheManager::FileCacheManager(int capacity) {
    mCapacity = capacity;
}

FileCacheManager::~FileCacheManager() {

}


string FileCacheManager::makeStrHash(string &key) {
    size_t str = hashStr(key);
    string hashStr = to_string(str);
    return hashStr;
}

void FileCacheManager::insert(string& key, string& obj) {
    hashKey = makeStrHash(key);
    cacheInsert(hashKey, obj);
    fileInsert(hashKey, obj);
}

bool FileCacheManager::find(string& key) {
    ifstream file_obj;
    string obj;

    hashKey = makeStrHash(key);
    // Search in cache
    if (mCache.find(hashKey) != mCache.end()) {
        return true;
    }

    // Not found in cache, search in file
    // Opening file in input mode
    file_obj.open("Matrix" + hashKey + ".txt", ios::in|ios::binary);
    // File not found, throw an exception
    if (!file_obj) {
        return false;
    }
    return true;
}

string FileCacheManager::get(string& key) {
    ifstream file_obj;
    string obj = "";
    hashKey = makeStrHash(key);

    // Search in cache
    if (mCache.find(hashKey) != mCache.end()) {
        // Move the element to the head of the list
        cacheInsert(hashKey, mCache[hashKey].first);
        return mCache[hashKey].first;
    }

    // Not found in cache, search in file
    // Opening file in input mode
    file_obj.open("Matrix" + hashKey + ".txt", ios::in|ios::binary);
    // File not found, throw an exception
    if (!file_obj)
        throw "key not found";
    getline(file_obj, obj);
//    file_obj.read((char*)&obj, sizeof(obj));
    file_obj.close();
    // Add object to cache
    cacheInsert(hashKey, obj);
    return obj;
}

void FileCacheManager::cacheInsert(string& key, string& obj) {
    // Insert it into map if not present already
    if (mCache.find(hashKey) == mCache.end()) {
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
        mObjectsList.erase(mCache[hashKey].second);

    // update reference
    mObjectsList.push_front(hashKey);
    mCache[hashKey] = {obj, mObjectsList.begin()};
}

void FileCacheManager::fileInsert(string& hashKey, string& obj) {
    ofstream file_obj;

    // Opening file in output mode
    file_obj.open("Matrix" + hashKey + ".txt", ios::out|ios::trunc|ios::binary);
    if (!file_obj)
        throw "Failed in creating file";

    // Writing the object's data in file
//    file_obj.write((char*)&obj, sizeof(obj));
    file_obj << obj << endl;

    file_obj.close();
}
