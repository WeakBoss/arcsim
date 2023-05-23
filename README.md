# ARCSim

#### 介绍
ArcSim是一个模拟引擎，用于为布料、纸张、塑料和金属等可变形材料的板材设置动画。它使用自适应优化的三角形网格来有效地解析模拟对象的几何和动态细节。
http://graphics.berkeley.edu/resources/ARCSim/index.html
本项目将arcsim-0.2.1-windows在win10,vs2019上配置
由于win环境上没有该项目之前使用的矩阵运算库taus，故使用eigen进行替代，并使用LDLT方法求解线性方程。
#### 环境配置
需要依赖第三方库：boost, boost_date_time, boost_filesystem, boost_system, boost_timer, freeglut, eigen3，jsoncpp，alglib，imgui
#### 运行示例：arcSim是一个离线的模拟库，此暂时为录帧重播
 

 