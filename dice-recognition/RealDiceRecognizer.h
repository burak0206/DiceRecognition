#pragma once
#include "IDiceRecognizer.h"

class RealDiceRecognizer : public IDiceRecognizer
{
public:
	virtual std::multiset<int> readNumbers(const cv::Mat& img);
};
