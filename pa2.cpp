#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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

    Mat result(input.rows, input.cols, CV_8UC1);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            // Perform convolution for this input sample pixel
            float convol_sum = 0;
            // Position the central element of the kernal at i, j
            int ker_start_row = i - filter.rows / 2;
            int ker_start_col = j - filter.cols / 2;

            for (int s = 0; s < filter.rows; s++) {
                for (int t = 0; t < filter.cols; t++) {
                    int pix_row = ker_start_row + s;
                    int pix_col = ker_start_col + t;

                    float pixel = 0.0;
                    // Checking boundary condition & retrive appropriate pixel
                    if (out_bound(pix_row, pix_col)) {
                        pixel = (float) input.at<uchar>(reflect(pix_row, pix_col,
                                                                input.rows, input.cols));
                    } else {
                        pixel = (float) input.at<uchar>(pix_row, pix_col);
                    }
                    //Access filter elements as if it is a flipped kernal
                    convol_sum += pixel * filter.at<float>(filter.rows - s - 1,
                                                            filter.cols - t - 1);
                }
            }
            // Assign the output value for pixel
            result.at<uchar>(i, j) = (uchar) convol_sum;
        }
    }

    return result;
}

Mat Reduce(Mat input) {
    // THis is your empty output image
    Mat output(input.rows / 2, input.cols / 2, CV_8UC1);
    // Calculate each pixel of output image
    for (int i = 0; i < output.rows; i++) {
        int input_row = i * 2;
        for (int j = 0; j < output.cols; j++) {
            int input_col = j * 2;
            int top_left = (int) input.at<uchar>(input_row, input_col);
            int top_right = (int) input.at<uchar>(input_row, input_col + 1);
            int bottom_left = (int) input.at<uchar>(input_row + 1, input_col);
            int bottom_right = (int) input.at<uchar>(input_row + 1, input_col + 1);
            output.at<uchar>(i, j) = (uchar) ((top_left + top_right + bottom_left + bottom_left) / 4);
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
            //	Calculate the intermediate pixel values
            int diff = (int) I.at<uchar>(i, j) - (int) J.at<uchar>(i, j);
            intermediate.at<int>(i, j) = diff;

            if (diff < minVal) {
                minVal = diff;
            }
            if (diff > maxVal) {
                maxVal = diff;
            }
		}
	}
	// The output image of type unsigned char for each pixel
	Mat result(I.rows, I.cols, CV_8UC1);
	float dynamicRange = maxVal - minVal;

	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			// Calculate the output pixels
			result.at<uchar>(i, j) = 255 * (intermediate.at<int>(i, j) - minVal) / dynamicRange;
		}
	}

	return result;
}

Mat read_img(int argc, char** argv, int i) {
    if (argc < (i + 1)) {
        printf("specify image path\n");
        exit(-1);
    }

    Mat img = imread(argv[i], IMREAD_GRAYSCALE);

    if (!img.data) {
        printf("No image data \n");
        exit(-1);
    }
    return img;
}

void write_img(int argc, char** argv, int i, Mat new_img) {
    if (argc <= i + 1 ) {
        imwrite(argv[i], new_img);
    } else {
        imwrite("new.jpg", new_img);
    }
    return;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("specify function\n");
        return -1;
    }

    if (strcmp(argv[1], "-g") == 0) {
        Mat og_img = read_img(argc, argv, 2);
        Mat gau_filter = CreateGaussianFilter();
        Mat new_img = ApplyFilter(og_img, gau_filter);
        write_img(argc, argv, 3, new_img);

    } else if (strcmp(argv[1], "-gr") == 0) {
        Mat og_img = read_img(argc, argv, 2);
        Mat gau_filter = CreateGaussianFilter();
        Mat new_img = Reduce(ApplyFilter(og_img, gau_filter));
        write_img(argc, argv, 3, new_img);

    } else if (strcmp(argv[1], "-r") == 0) {
        Mat og_img = read_img(argc, argv, 2);
        Mat new_img = Reduce(og_img);
        write_img(argc, argv, 3, new_img);

    } else if (strcmp(argv[1], "-d") == 0) {
        Mat img_1 = read_img(argc, argv, 2);
        Mat img_2 = read_img(argc, argv, 3);
        Mat new_img = Deduct(img_1, img_2);
        write_img(argc, argv, 4, new_img);

    } else if (strcmp(argv[1], "--resize") == 0) {
        Mat og_img = read_img(argc, argv, 2);
        Mat new_img;

        if (argc < 5) {
            printf("specify width, height");
            exit(-1);
        }

        resize(og_img, new_img, Size(atoi(argv[3]), atoi(argv[4])));
        write_img(argc, argv, 5, new_img);

    } else {
        printf("unknown function \"%s\"\n", argv[1]);
        return -1;
    }

    return 0;
}
