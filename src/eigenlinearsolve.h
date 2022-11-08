#pragma once
#include <Eigen/Sparse>
#include <Eigen/src/SparseCore/SparseUtil.h>
#include <Eigen/Dense>
#include <Eigen/src/Core/Map.h>
#include "sparse.hpp"
#include "vectors.hpp"
#include "MethodsDef.h"

typedef Eigen::SparseMatrix<double, Eigen::ColMajor> EigenSpMat;
typedef Eigen::VectorXd EigenVector;
typedef Eigen::Triplet<double> Triplet;

EigenSpMat* sparse_to_eigen(const SpMat<double>& As)
{
    // assumption: A is square and symmetric
    int n = As.n;
    EigenSpMat* pLowerMat = new EigenSpMat(n, n);
    std::vector<Triplet> TripletList;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < As.rows[i].indices.size(); k++) {
            int j = As.rows[i].indices[k]; //columnIndex
            if (j < i) continue;
            TripletList.push_back(Triplet(j, i, As.rows[i].entries[k]));  ////转为下三角矩阵  columnIndex变为roeIndex
        }
    }
    pLowerMat->setFromTriplets(TripletList.begin(), TripletList.end());
    return pLowerMat;
}

template <int m> EigenSpMat* sparse_to_eigen(const SpMat< Mat<m, m> >& As)
{
    // assumption: A is square and symmetric
    int n = As.n;
    EigenSpMat* pLowerMat = new EigenSpMat(n * m, n * m);
    std::vector<Triplet> TripletList;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)  //m是block的size
        {
            for (int jj = 0; jj < As.rows[i].indices.size(); jj++)
            {
                int j = As.rows[i].indices[jj];//block的列
                if (j < i) continue;
                const Mat<m, m>& Aij = As.rows[i].entries[jj];
                for (int l = (i == j) ? k : 0; l < m; l++)
                {
                    TripletList.push_back(Triplet(j * m + l, i * m + k, Aij(k, l)));
                }
            }
        }
    }
    pLowerMat->setFromTriplets(TripletList.begin(), TripletList.end());
    return pLowerMat;
}

template <int m>
void blockVecDumpEigen(EigenVector& voEigenV, const std::vector< Vec<m> >& vBlockV)
{
    voEigenV.resize(vBlockV.size() * m);
    for (int i = 0; i < vBlockV.size(); i++)
    {
        EigenVector V(m);
        for (int k = 0; k < m; k++) V(k) = vBlockV[i][k];
        voEigenV.segment<m>(i * m) = V;
    }
}

template <int m>
void EigenDumpblockVec(std::vector< Vec<m> >& voBlockV, const EigenVector& vEigenV)
{
    voBlockV.resize(vEigenV.rows() / m);
    for (int i = 0; i < voBlockV.size(); i++)
    {
        EigenVector V(m);
        V = vEigenV.segment<m>(i * m);
        Vec<m> Block;
        for (int k = 0; k < m; k++)
        {
            Block[k] = V[k];
        }
        voBlockV[i] = Block;
    }
}

EigenVector simplicialLDLT_solve(const EigenSpMat* vMatA, const EigenVector& vVecB)
{
    if (vMatA == NULL)
    {
        //log("empty_pointer");
        exit(EXIT_FAILURE);
    }
    Eigen::SimplicialLDLT<EigenSpMat, Eigen::Lower> Solver;
    Solver.compute(*vMatA);
    if (Solver.info() != Eigen::Success) {
        //log("eigen_linear_solve_decomposition_fail");
        exit(EXIT_FAILURE);
    }
    EigenVector VecX = Solver.solve(vVecB);
    if (Solver.info() != Eigen::Success) {
        //log("eigen_linear_solve_fail");
        exit(EXIT_FAILURE);
    }
    delete vMatA;
    return VecX;
}

EigenVector conjugate_gradient_solve(const EigenSpMat* vMatA, const EigenVector& vVecB)
{
    if (vMatA == NULL)
    {
        //log("empty_pointer");
        exit(EXIT_FAILURE);
    }
    Eigen::ConjugateGradient<EigenSpMat, Eigen::Lower> Solver;
    Solver.compute(*vMatA);
    if (Solver.info() != Eigen::Success) {
        //log("eigen_linear_solve_decomposition_fail");
        exit(EXIT_FAILURE);
    }
    EigenVector VecX = Solver.solve(vVecB);
    if (Solver.info() != Eigen::Success) {
        //log("eigen_linear_solve_fail");
        exit(EXIT_FAILURE);
    }
    delete vMatA;
    return VecX;
}

std::vector<double> eigen_linear_solve(const SpMat<double>& A, const std::vector<double>& b)
{
    EigenSpMat* MatA = sparse_to_eigen(A);
    EigenVector VecB = Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(b.data(), b.size());
#ifdef Eigen_SimplicialLLT
    EigenVector VecX = simplicialLDLT_solve(MatA, VecB);
#elif defined EIGEN_CONJUGATE_GRADIENT
    EigenVector VecX = conjugate_gradient_solve(MatA, VecB);
#endif
    return std::vector<double>(VecX.data(), VecX.data() + VecX.rows());
}

template <int m> std::vector< Vec<m> > eigen_linear_solve
(const SpMat< Mat<m, m> >& A, const std::vector< Vec<m> >& b)
{
    EigenSpMat* MatA = sparse_to_eigen(A);
    EigenVector VecB;
    blockVecDumpEigen(VecB, b);
#ifdef Eigen_SimplicialLLT
    EigenVector VecX = simplicialLDLT_solve(MatA, VecB);
#elif defined EIGEN_CONJUGATE_GRADIENT
    EigenVector VecX = conjugate_gradient_solve(MatA, VecB);
#endif
    std::vector< Vec<m> > BlockVec;
    EigenDumpblockVec(BlockVec, VecX);
    return BlockVec;
}