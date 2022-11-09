#pragma once
#include<string>
#define EIGEN_LINEAR_SOLVE

#define Eigen_SimplicialLDLT  
//#define EIGEN_CONJUGATE_GRADIENT

//#define SIMULATE
//#define SIMULATEWITHOUTSAVE
//#define SIMULATEOFFLINE
#define REPLAY


const std::string ConfPath = "../conf/karate.json";
const std::string OutPath = "../karateSimulateOutput";

#ifdef SIMULATE
const std::string ArcsimMethod = "simulate";
const std::vector<std::string> ArcsimPara = { ConfPath, OutPath };
#elif defined SIMULATEWITHOUTSAVE
const std::string ArcsimMethod = "simulate";
const std::vector<std::string> ArcsimPara = { ConfPath };
#elif defined SIMULATEOFFLINE
const std::string ArcsimMethod = "simulateoffline";
const std::vector<std::string> ArcsimPara = { ConfPath, OutPath };
#elif defined REPLAY
const std::string ArcsimMethod = "replay";
const std::vector<std::string> ArcsimPara = { OutPath };
#endif  