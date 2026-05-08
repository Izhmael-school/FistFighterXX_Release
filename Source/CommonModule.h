#pragma once
#include <vector>
#include "Data/json.hpp"
#include <DxLib.h>
#include <fstream>
#include <iostream>
#include <list>

// 汎用的に使える関数をまとめたファイル



template <class T>
inline std::vector<T> MergeVector(std::vector<T> vec1, std::vector<T> vec2) {
    std::vector<T> vec3;

    for (T d : vec1) {
        vec3.push_back(d);
    }

    for (T d : vec2) {
        vec3.push_back(d);
    }

    return vec3;
}