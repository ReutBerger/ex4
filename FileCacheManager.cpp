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

void FileCacheManager::insert(string& key, string& obj) {
    cacheInsert(key, obj);
    fileInsert(key, obj);
}

bool FileCacheManager::find(string& key) {
    ifstream file_obj;
    string obj;

    // Search in cache
    if (mCache.find(key) != mCache.end()) {
        return true;
    }

    // Not found in cache, search in file
    // Opening file in input mode
    file_obj.open("Matrix" + key + ".txt", ios::in|ios::binary);
    // File not found, throw an exception
    if (!file_obj) {
        return false;
    }
    return true;
}

string FileCacheManager::get(string& key) {
    ifstream file_obj;
    string obj = "";

    // Search in cache
    if (mCache.find(key) != mCache.end()) {
        // Move the element to the head of the list
        cacheInsert(key, mCache[key].first);
        return mCache[key].first;
    }

    // Not found in cache, search in file
    // Opening file in input mode
    file_obj.open("Matrix" + key + ".txt", ios::in|ios::binary);
    // File not found, throw an exception
    if (!file_obj)
        throw "key not found";
    getline(file_obj, obj);
//    file_obj.read((char*)&obj, sizeof(obj));
    file_obj.close();
    // Add object to cache
    cacheInsert(key, obj);
    return obj;
}

void FileCacheManager::cacheInsert(string& key, string& obj) {
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

void FileCacheManager::fileInsert(string& key, string& obj) {
    ofstream file_obj;

    // Opening file in output mode
    file_obj.open("Matrix" + key + ".txt", ios::out|ios::trunc|ios::binary);
    if (!file_obj)
        throw "Failed in creating file";

    // Writing the object's data in file
//    file_obj.write((char*)&obj, sizeof(obj));
    file_obj << obj << endl;

    file_obj.close();
}