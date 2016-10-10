#include "PerformanceMeter.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "Util.h"

using std::back_inserter;
using std::getline;
using std::ifstream;
using std::ios;
using std::map;
using std::multiset;
using std::set_intersection;
using std::set_union;
using std::string;
using std::vector;


using cv::imread;
using cv::Mat;

PerformanceMeter::PerformanceMeter(IDiceRecognizer* recognizer)
{
	this->recognizer = recognizer;

	readLabels("data/data.txt");
}


void PerformanceMeter::readLabels(const string& filePath)
{
	ifstream dataFile(filePath, ios::in);
	if (!dataFile.is_open())
		Util::error("Cannot open " + filePath);

	string line;
	while (dataFile.good())
	{
		getline(dataFile, line);
		parseLine(line);
	}
}

// Line format is:
// image_name comma_separated_numbers
// e.g: "27 3,6,4"
void PerformanceMeter::parseLine(const string& line)
{
	if (line == "")
		return;

	size_t pos = line.find(' ');
	string imageName = line.substr(0, pos);

	string numbersStr = line.substr(pos);
	multiset<int> numbers = splitAsNumbers(numbersStr);

	labels[imageName] = numbers;
}

multiset<int> PerformanceMeter::splitAsNumbers(const string& numbersStr)
{
	vector<string> strings = Util::split(numbersStr, ',');

	multiset<int> numbers;
	for (int i = 0; i<strings.size(); i++)
		numbers.insert(Util::toInt(strings[i]));

	return numbers;
}

size_t PerformanceMeter::intersectionCount(const multiset<int>& set1, const multiset<int>& set2)
{
	vector<int> temp;
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(temp));
	return temp.size();
}

size_t PerformanceMeter::unionCount(const multiset<int>& set1, const multiset<int>& set2)
{
	vector<int> temp;
	set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(temp));
	return temp.size();
}

void PerformanceMeter::evaluate()
{
	int count = 0;
	double accumulatedPerformance = 0;

	map<string, multiset<int>>::iterator it;
	for (it = labels.begin(); it != labels.end(); it++)
	{
		string imageName = it->first;
		Mat img = imread("data/" + imageName + ".jpg");

		multiset<int> truth = it->second;
		multiset<int> prediction = recognizer->readNumbers(img);

		int truePositive = intersectionCount(truth, prediction);


		accumulatedPerformance += (double)truePositive / unionCount(truth, prediction);
		count++;
	}

	std::cout << "Performance: " << 100.0 * accumulatedPerformance / count << "%\n";
}


