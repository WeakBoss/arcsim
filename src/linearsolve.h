#pragma once
#include "sparse.hpp"
#include "vectors.hpp"

std::vector<double> linear_solve(const SpMat<double>& A, const std::vector<double>& b);

template <int m> std::vector< Vec<m> > linear_solve
    (const SpMat< Mat<m, m> >& A, const std::vector< Vec<m> >& b);