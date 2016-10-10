#include "MyDiceRecognizer.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "KMeans.h"
#include <math.h>

#include <opencv2/opencv.hpp>

using std::multiset;
using namespace cv;
using namespace std;

multiset<int> MyDiceRecognizer::readNumbers(const cv::Mat& img)
{
	multiset<int> numbers;
	KMeans *kmeans = new KMeans(img);
	Mat thresholdedImage = kmeans->run();
	Mat tempThresholdedImage;
	thresholdedImage.copyTo(tempThresholdedImage);

	//find blobs
	vector< vector<Point> > contours;
	findContours(tempThresholdedImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	bool isBlackDiceExist = false;
	int indexBlack = 1;
	int whiteContour = 0;
	list<Hole> holesBlack;
	list<Hole> holesWhite;

	//foreach blobs
	for (vector<vector<Point> >::iterator it = contours.begin(); it != contours.end();)
	{
		double a = contourArea(*it);
        //noise => 6-16
		if (a <= 10) it = contours.erase(it);
		else if (a<50){
            //black dice update for more than one black dice
            //AND instead of contour size opencv using every hole is counted
			double ratio = boundingRect(*it).area() / a;
			if (ratio < 3) countForImproperDice(isBlackDiceExist, it, holesBlack, indexBlack);
            it = contours.erase(it);
			
		} // endif -- blackdice
		else if(a<1200) {
            //white dice: using contour function of opencv in order to count hole of white dice
            Mat mask;
			thresholdedImage.copyTo(mask);
            mask = Scalar(0);
			drawContours(mask, contours, whiteContour, Scalar(255), CV_FILLED);
			mask = (mask & thresholdedImage) ^ mask;

			vector<vector<Point>> cntrs;
            //find holes on white dice
			findContours(mask, cntrs, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			if (cntrs.size() > 0 && cntrs.size() <7)
				numbers.insert(cntrs.size());
			++it;
			whiteContour++;
		} // endif -- white dice
		else if (a<2000) {
            //stucked white dice: not to use contour function of opencv in order to hole of white dice
			bool isWhiteStuck = false;
			int indexWhiteStuck = 1;
			int whiteStuckContour = 0;
			Mat mask;
			thresholdedImage.copyTo(mask);
			mask = Scalar(0);
			drawContours(mask, contours, whiteStuckContour, Scalar(255), CV_FILLED);
			mask = (mask & thresholdedImage) ^ mask;

			vector<vector<Point>> cntrs;
			findContours(mask, cntrs, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //find holes on white dice
			for (vector<vector<Point> >::iterator iter = cntrs.begin(); iter != cntrs.end();){
                countForImproperDice(isWhiteStuck, iter, holesWhite, indexWhiteStuck);
				iter = cntrs.erase(iter);
			}
			
            addNumberOfImproperDice(true, indexWhiteStuck,holesWhite, numbers);
			++it;
		} //endif -- stucked white dice
		else it = contours.erase(it);
	}
	//number of black dices are added to prediction
    addNumberOfImproperDice(isBlackDiceExist, indexBlack, holesBlack, numbers);

	contours.clear();
	cv::imshow("x", img);
	cv::waitKey(20);
	delete kmeans;
	
	return numbers;
}


//calculate hole of stuck white dice or blackdice
void MyDiceRecognizer::countForImproperDice(bool & flag, vector<vector<Point> >::iterator it, list<Hole>& holes, int &index){
     flag = true;
     int x = (*it)[0].x;
     int y = (*it)[0].y;;
     Hole hole = Hole(x, y);
     
     if (holes.empty()){
         //first black or stuck white dice
         hole.index = index;
     }
     else { //Next black or stuck white dice
         bool existSameDice = false;
         for (list<Hole >::iterator iterator = holes.begin(); iterator != holes.end();){
             int deltaX = abs(x - (*iterator).x);
             int deltaY = abs(y - (*iterator).y);
             if (deltaX < 25 && deltaY< 25){
                 // exist hole on same black or stuck white dice
                 existSameDice = true;
                 index = (*iterator).index;
             }
             ++iterator;
         }
         if (!existSameDice) index++;
         hole.index = index;
     }
     holes.push_back(hole);
}

//number of black or stuck dices are added to prediction
void MyDiceRecognizer::addNumberOfImproperDice(bool flag, int &index, list<Hole> &holes, multiset<int> & numbers ){
    if(!flag) return;
    int *numberOfImproperDice = new int[index];
    for (int i = 0; i < index; i++){
        numberOfImproperDice[i] = 0;
    }
    for (list<Hole >::iterator it = holes.begin(); it != holes.end();)
    {
        numberOfImproperDice[(*it).index-1] = 1 + numberOfImproperDice[(*it).index-1];
        ++it;
    }
    for (int i = 0; i < index; i++){
        numbers.insert(numberOfImproperDice[i]);
    }
    delete[] numberOfImproperDice;
}
