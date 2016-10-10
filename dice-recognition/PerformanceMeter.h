#ifndef DICE_RECOGNITION_PERFORMANCE_METER_H
#define DICE_RECOGNITION_PERFORMANCE_METER_H

#include <map>
#include <string>

#include "IDiceRecognizer.h"

class PerformanceMeter
{
public:
	PerformanceMeter(IDiceRecognizer* recognizer);
	void evaluate();

private:
	IDiceRecognizer* recognizer;

	std::map<std::string, std::multiset<int>> labels;

	void readLabels(const std::string& filePath);
	void parseLine(const std::string& line);
	std::multiset<int> splitAsNumbers(const std::string& numbersStr);

	size_t intersectionCount(const std::multiset<int>& set1, const std::multiset<int>& set2);
	size_t unionCount(const std::multiset<int>& set1, const std::multiset<int>& set2);
};

#endif // DICE_RECOGNITION_PERFORMANCE_METER_H
