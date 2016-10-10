#pragma once
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class Cluster
{
private:
	double center_value;
public:
	Cluster(){}
	~Cluster(){}
	double getCenterValue() const{
		return this->center_value;
	}
	void setCenterValue(double centerValue){
		this->center_value = centerValue;
	}
};

class KMeans
{
private:
	Mat img;
	Cluster blackCluster;
	Cluster whiteCluster;
public:
	KMeans(const Mat& image);
	~KMeans();
	Mat run();
};

