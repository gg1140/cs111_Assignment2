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

/* Return a Point type containing row and col position
 * obtained from reflecting a position outside of the img boundary
 * with its closest img boundary row & col position
 * Point(col, row), Point.x = col, Point.y = row
 */
Point reflect(int x, int y, int height, int width) {
    auto below_bound = [](int x) {return x < 0;};
    auto over_bound = [](int x, int upper) {return x > upper;};
    auto reflect_index = [] (int x, int edge_val) {return (2 * edge_val) - 1 - x;};

    int new_x = x;
    int new_y = y;

    if (below_bound(x)) {
        new_x = reflect_index(x, 0);
    } else if (over_bound(x, height - 1)) {
        new_x = reflect_index(x, height);
    }

    if (below_bound(y)) {
        new_y = reflect_index(y, 0);
    } else if (over_bound(y, width - 1)) {
        new_y = reflect_index(y, width);
    }

    return Point(new_y, new_x);
}

Mat ApplyFilter(Mat input, Mat filter) {
    auto out_bound = [c=input.cols-1, r=input.rows-1](int x, int y) {
        return (x < 0 || x > r || y < 0 || y > c);
    };

	// This is your empty output Mat
	Mat result(input.rows, input.cols, CV_8UC1);
    int ker_width = filter.rows / 2;

	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			// Perform convolution for this pixel
            float convol_sum = 0;
            // Position of kernal's first element in terms of input image
            int ker_start_row = i - ker_width;
            int ker_start_col = j - ker_width;

            for (int s = 0; s < filter.rows; s++){
                for (int t = 0; t < filter.cols; t++){
                    int ofset_row = ker_start_row + s;
                    int ofset_col = ker_start_col + t;

                    float pixel = 0.0;
					if (out_bound(ofset_row, ofset_col)){ // Checking boundary condition
                        pixel = (float) input.at<uchar>(reflect(ofset_row, ofset_col, input.rows, input.cols));
					} else {
                        pixel = (float) input.at<uchar>(ofset_row, ofset_col);
                    }

                    convol_sum += pixel * filter.at<float>(s, t);
				}
			}
			result.at<uchar>(i, j) = (uchar) convol_sum; // Assign the output value for pixel
		}
	}
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

    float filter_val[9] = {1/9.0f, 1/9.0f, 1/9.0f,
                            1/9.0f, 1/9.0f, 1/9.0f,
                            1/9.0f, 1/9.0f, 1/9.0f};
    Mat filter = Mat_<float>(3, 3, filter_val);
    Mat gau_filter = CreateGaussianFilter();
    Mat new_img = ApplyFilter(og_img, filter);

    if (argc = 3) {
        imwrite(argv[2], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }
    return 0;
}
