#ifndef DICE_RECOGNITION_MY_DICE_RECOGNIZER_H
#define DICE_RECOGNITION_MY_DICE_RECOGNIZER_H

#include "IDiceRecognizer.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include <opencv2/opencv.hpp>
#include <list>

using namespace std;
using namespace cv;

class Hole
{
public:
    int x;
    int y;
    int index;
    Hole(){}
    Hole(int _x,int _y, int _i){
        x = _x;
        y = _y;
        index = _i;
    }
    Hole(int _x, int _y){
        x = _x;
        y = _y;
    }
    ~Hole(){}
    
};

class MyDiceRecognizer : public IDiceRecognizer
{
public:
	virtual std::multiset<int> readNumbers(const cv::Mat& img);
    void countForImproperDice(bool & flag, vector<vector<Point> >::iterator it, list<Hole> &holes,  int & indexBlack);
    void addNumberOfImproperDice(bool flag, int &indexBlack, list<Hole> &holes, multiset<int> & numbers);
};

#endif // DICE_RECOGNITION_MY_DICE_RECOGNIZER_H
