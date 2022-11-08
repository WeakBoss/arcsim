#pragma once
#include<string>
const std::string ArcsimMethod = "simulate";
const std::string ConfPath = "../conf/sphere.json";
const std::string OutPath = "../output";
const std::vector<std::string> ArcsimPara = { ConfPath, OutPath };

#define EIGEN_LINEAR_SOLVE

#define Eigen_SimplicialLLT  
//#define EIGEN_CONJUGATE_GRADIENT