#include "RandomDiceRecognizer.h"

#include <opencv2\opencv.hpp>

using std::multiset;

multiset<int> RandomDiceRecognizer::readNumbers(const cv::Mat& img)
{
	multiset<int> numbers;

	int diceCount = rand() % 3 + 1;
	for (int i = 0; i<diceCount; i++)
		numbers.insert(rand() % 6 + 1);

	cv::imshow("x", img);
	cv::waitKey(20);

	return numbers;
}
