#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include<random>

using namespace cv;
using namespace std;
//Roberts算子
Mat Roberts(Mat srcImage)
{
	Mat dstImage = srcImage.clone();
	int nRows = dstImage.rows;
	int nCols = dstImage.cols;
	for (int i = 0; i < nRows - 1; i++) {
		for (int j = 0; j < nCols - 1; j++) {
			//根据公式计算
			int t1 = (srcImage.at<uchar>(i, j) -
				srcImage.at<uchar>(i + 1, j + 1))*
				(srcImage.at<uchar>(i, j) -
					srcImage.at<uchar>(i + 1, j + 1));
			int t2 = (srcImage.at<uchar>(i + 1, j) -
				srcImage.at<uchar>(i, j + 1))*
				(srcImage.at<uchar>(i + 1, j) -
					srcImage.at<uchar>(i, j + 1));
			//计算g（x,y）
			dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}
	}
	return dstImage;
}

int main()
{
	Mat img_gray, src,sobel_img,robert_img,laplace_img,canny_img;
	img_gray = imread("E://gray_lena.png", -1);
	cout<<"通道数："<<img_gray.channels() << endl;
	if (!img_gray.data)
	{
		cout << "未读取到该图片！" << endl;
		return 0;
	}
	else
	{
		imshow("gray_lena", img_gray); 
		//进行边缘检测：四种算子sobel,canny,robert,laplace
		//先进行高斯滤波减少检测图像噪声敏感 GaussianBlur(input img,output arc,Size(X,X),x轴标准偏差,y轴标准偏差)
		GaussianBlur(img_gray, src, Size(3, 3), 5, 5);
		imshow("Gauss滤波后的图像", src);
		//再进行算子处理提取图像边缘
		//Sobel(InputArray src,OutputArray dst,int ddepth// 输出图像深度, x轴差分阶数, y轴差分阶数,int ksize = 3,double scale = 1,double delta = 0,int borderType = BORDER_DEFAULT );
		//Laplacian(InputArray src,OutputArray dst,int ddepth//输出图像深度,int ksize = 1,double scale = 1,double delta = 0,int borderType = BORDER_DEFAULT);
		//Canny(InputArray image,OutputArray edges, 低阈值, 高阈值, size, L2gradient = false // 是否规一化);
		//Roberts算子实现：Roberts(Mat srcImage) //循环
		robert_img=Roberts(src);
		imshow("use roberts 边缘检测", robert_img);
	    Canny(src, canny_img, 100, 200, 3);
		imshow("use canny 边缘检测", canny_img);
		Sobel(src, sobel_img, CV_8U, 1, 1, 3, 1, 0);
		imshow("use sobel 边缘检测", sobel_img);
		Laplacian(src, laplace_img, CV_8U, 1, 1, 0);
		imshow("use laplace 边缘检测", laplace_img);
	


	}














	waitKey(0);
	return 0;
}