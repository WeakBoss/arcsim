#include <vector>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/src/Core/Map.h>
#include "gtest/gtest.h"
typedef Eigen::VectorXd EigenVector;
template <int n, typename T = double> class Vec {
private:
	T c[n];
public:
	Vec() { for (int i = 0; i < n; i++) c[i] = 0; }
	explicit Vec(T x) { for (int i = 0; i < n; i++) c[i] = x; }
	explicit Vec(T x, T y) { static_assert(n == 2); c[0] = x; c[1] = y; }
	explicit Vec(T x, T y, T z) { static_assert(n == 3); c[0] = x; c[1] = y; c[2] = z; }
	explicit Vec(T x, T y, T z, T w) { static_assert(n == 4); c[0] = x; c[1] = y; c[2] = z; c[3] = w; }
	T& operator[] (int i) { return c[i]; }
	const T& operator[] (int i) const { return c[i]; }
};

class TestEigen :public ::testing::Test
{
public:
protected:
	void SetUp() override
	{
		
	}
};

TEST_F(TestEigen, sparse_to_eigen)
{
	//todo
}

TEST_F(TestEigen, EigenMap)
{
	//std::vector< Vec<3> > BlockVector = { Vec<3>(0.0,0.1,0.2),Vec<3>(1.0,1.1,1.2) };
	//EigenVector VecB = Eigen::Map< Eigen::VectorXd, Eigen::Unaligned>(BlockVector.data(), BlockVector.size());
}