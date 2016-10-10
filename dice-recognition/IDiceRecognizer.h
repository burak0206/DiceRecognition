#ifndef DICE_RECOGNITION_I_DICE_RECOGNIZER_H
#define DICE_RECOGNITION_I_DICE_RECOGNIZER_H

#include <set>

#include <opencv2/opencv.hpp>

class IDiceRecognizer
{
public:
	virtual ~IDiceRecognizer() {}
	virtual std::multiset<int> readNumbers(const cv::Mat& img) = 0;
};


#endif // DICE_RECOGNITION_I_DICE_RECOGNIZER_H
