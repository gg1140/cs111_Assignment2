#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

template <typename T>
void printMat(Mat& img) {
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.rows; j++) {
            cout << "\t|" << img.at<T>(i, j);
        }
        cout << endl;
    }
}

Mat CreateGaussianFilter() {
	// This is your empty kernel
	// Every entry is a float value
	Mat I(5, 5, CV_32FC1);

	// This is 1D Gaussian kernel values
	float g[] = { 0.05, 0.25, 0.4, 0.25, 0.05 };

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// Fill in the kernel values
			I.at<float>(i, j) = g[i] * g[j];
		}
	}
	return I;
}

Mat ApplyFilter(Mat input, Mat filter) {
	
	// This is your empty output Mat
	Mat result(input.rows, input.cols, CV_8UC1);

//	for (int i = 0; i < output.rows; i++) {
//		for (int j = 0; j < output.cols; j++) {
			
			/*

			// Perform convolution for this pixel
			for (...){
				for (...){

					// Checking boundary condition
					if (...){
	
					}
				}
			}

			// Assign the output value for pixel
			result.at<uchar>(i, j) = ...

			*/
//		}
//	}

	return result;
}

Mat Reduce(Mat input) {

	// THis is your empty output image
	Mat output(input.rows / 2, input.cols / 2, CV_8UC1);

	// Calculate each pixel of output image
	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			
			/*
			output.at<uchar>(i, j) = ...
			*/
		}
	}
	return output;
}

Mat Deduct(Mat I, Mat J) {
	
	// Intermediate pixel to keep the differences
	// Each entry is int
	Mat intermediate(I.rows, I.cols, CV_32SC1);
	int minVal = 256;
	int maxVal = -256;
	for (int i = 0; i < intermediate.rows; i++) {
		for (int j = 0; j < intermediate.cols; j++) {
			/*
				Calculate the intermediate pixel values
			*/
		}
	}
	float dynamicRange = maxVal - minVal;

	// The output image of type unsigned char for each pixel
	Mat result(I.rows, I.cols, CV_8UC1);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			/*
			// Calculate the output pixels
			result.at<uchar>(i, j) = ...
			*/
		}
	}

	return result;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("specify image path\n");
        return -1;
    }

    Mat og_img = imread(argv[1], IMREAD_GRAYSCALE);

    if (!og_img.data) {
        printf("No image data \n");
        return -1;
    }

    CreateGaussianFilter();
/*    Mat new_img =;

    if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }*/
    return 0;
}
