#include "KMeans.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include <opencv2/opencv.hpp>


KMeans::KMeans(const Mat& image)
{
	cvtColor(image, this->img, COLOR_RGB2GRAY);
	//initial center values
	blackCluster.setCenterValue(50);
	whiteCluster.setCenterValue(230);
}


KMeans::~KMeans()
{
}

Mat KMeans::run(){
	bool isAnyCenterValueChanged = true;
	while (isAnyCenterValueChanged){
		double sumBlackCluster = 0; 
		int	counterBlackClusterItem = 0 ; 
		double sumWhiteCluster = 0;
		int counterWhiteClusterItem = 0;

		//for each pixel find the closest one center value of clusters
		for (int nRow = 0; nRow < img.rows; nRow++){
			for (int nCol = 0; nCol < img.cols; nCol++){
				int intensity = (int)img.at<uchar>(nRow, nCol);
				double deltaWithBlackClusterCenter = abs(blackCluster.getCenterValue() - intensity);
				double deltaWithWhiteClusterCenter = abs(whiteCluster.getCenterValue() - intensity);
				if (deltaWithBlackClusterCenter < deltaWithWhiteClusterCenter){
					//more closer to black cluster
					sumBlackCluster += intensity;
					counterBlackClusterItem++;
				}
				else {
					//more closer to white cluster
					sumWhiteCluster += intensity;
					counterWhiteClusterItem++;
				}
			}
		}

		//calculate new mean of clusters
		double newCenterValueForBlackCluster = sumBlackCluster / counterBlackClusterItem;
		double newCenterValueForWhiteCluster = sumWhiteCluster / counterWhiteClusterItem;
		
		if (newCenterValueForBlackCluster == blackCluster.getCenterValue() && newCenterValueForWhiteCluster == whiteCluster.getCenterValue()) {
			//algorithm converges to local minumum of error function so loop is going to finish
			isAnyCenterValueChanged = false;
		}
		else {
			//at least one center value changed so assign new center values
			blackCluster.setCenterValue(newCenterValueForBlackCluster);
			whiteCluster.setCenterValue(newCenterValueForWhiteCluster);
		}

	}

	//for each pixel will segment and change black or white
	for (int nRow = 0; nRow < img.rows; nRow++){
		for (int nCol = 0; nCol < img.cols; nCol++){
			int intensity = (int)img.at<uchar>(nRow, nCol);
			double deltaWithBlackClusterCenter = abs(blackCluster.getCenterValue() - intensity);
			double deltaWithWhiteClusterCenter = abs(whiteCluster.getCenterValue() - intensity);
			if (deltaWithBlackClusterCenter < deltaWithWhiteClusterCenter){
				img.at<uchar>(nRow, nCol) = (uchar)0;
			}
			else {
				img.at<uchar>(nRow, nCol) = (uchar)255;
			}
		}
	}

	//return updated image according to segmentation
	return img;
}
