
#include "linearsolve.h"
#include "eigenlinearsolve.h"
#include "timer.hpp"
#include "MethodsDef.h"

std::vector<double> linear_solve(const SpMat<double>& A, const std::vector<double>& b)
{
#ifdef EIGEN_LINEAR_SOLVE
    return eigen_linear_solve(A, b);
#endif // EIGEN_LINEAR_SOLVE
}

template <int m> std::vector< Vec<m> > linear_solve
    (const SpMat< Mat<m, m> >& A, const std::vector< Vec<m> >& b)
{
#ifdef EIGEN_LINEAR_SOLVE
    return eigen_linear_solve(A, b);
#endif // EIGEN_LINEAR_SOLVE
}

template  std::vector<Vec3> linear_solve
    (const SpMat<Mat3x3>& A, const std::vector<Vec3>& b);