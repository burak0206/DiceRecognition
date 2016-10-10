#ifndef DICE_RECOGNITION_RANDOM_DICE_RECOGNIZER_H
#define DICE_RECOGNITION_RANDOM_DICE_RECOGNIZER_H

#include "IDiceRecognizer.h"

class RandomDiceRecognizer : public IDiceRecognizer
{
public:
	virtual std::multiset<int> readNumbers(const cv::Mat& img);
};

#endif // DICE_RECOGNITION_RANDOM_DICE_RECOGNIZER_H
