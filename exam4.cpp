#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include<random>

using namespace cv;
using namespace std;

  //椒盐噪声函数
   void addSaltNoise(const Mat &srcImage, Mat &dstImage, int n)
   {
	dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//盐噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//椒噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
   }

	//生成高斯噪声
	double generateGaussianNoise(double mu, double sigma)
	{
		//定义小值
		const double epsilon = numeric_limits<double>::min();
		static double z0, z1;
		static bool flag = false;
		flag = !flag;
		//flag为假构造高斯随机变量X
		if (!flag)
			return z1 * sigma + mu;
		double u1, u2;
		//构造随机变量
		do
		{
			u1 = rand() * (1.0 / RAND_MAX);
			u2 = rand() * (1.0 / RAND_MAX);
		} while (u1 <= epsilon);
		//flag为真构造高斯随机变量
		z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
		z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
		return z0 * sigma + mu;
	}

	//为图像加入高斯噪声
	void addGaussianNoise(Mat &srcImag, Mat &dstImage, double mu, double sigma)
	{
		dstImage = srcImag.clone();
		int channels = dstImage.channels();
		int rowsNumber = dstImage.rows;
		int colsNumber = dstImage.cols*channels;
		//推断图像的连续性
		if (dstImage.isContinuous())
		{
			colsNumber *= rowsNumber;
			rowsNumber = 1;
		}
		for (int i = 0; i < rowsNumber; i++)
		{
			for (int j = 0; j < colsNumber; j++)
			{
				//加入高斯噪声
				int val = dstImage.ptr<uchar>(i)[j] +generateGaussianNoise(mu, sigma) * 32;
				if (val < 0)
					val = 0;
				if (val > 255)
					val = 255;
				dstImage.ptr<uchar>(i)[j] = (uchar)val;
			}
		}
	}


int main()
{
	Mat img_gray, src, addsalt_img,addgauss_img,filter_img1,filter_img2, filter_img3, filter_img4;
	img_gray = imread("E://gray_lena.png",-1);
	if (!img_gray.data)
	{
		cout << "未读取到该图片！" << endl;
		return 0;
	}
    else
	{
		//噪声生成:高斯噪声,椒盐噪声;
		addSaltNoise(img_gray, addsalt_img, 30000); //叠加椒盐噪声
		imshow("Add salt noise image", addsalt_img);
		addGaussianNoise(img_gray, addgauss_img, 0, 1);
		imshow("Add Gaussina noise image", addgauss_img);
		
		//滤波：中值,均值
		// blur(InputArray src, OutputArray dst, Size(X,X)：滤波核大小, Point(-1, -1)：锚点, int borderType = BORDER_DEFAULT：可省略); //均值滤波函数
		// medianBlur(InputArray src, OutputArray dst, int ksize：3为3乘3的滤波核)//中值滤波函数
		//ｅg：
		blur(addsalt_img, filter_img1, Size(8,8), Point(5, 5));//叠加椒盐噪声的图像进行均值滤波
		medianBlur(addsalt_img, filter_img2, 5);//叠加椒盐噪声的图像进行中值滤波
		blur(addgauss_img, filter_img3, Size(8,8), Point(5, 5));//叠加高斯噪声的图像进行均值滤波
		medianBlur(addgauss_img, filter_img4, 5);//叠加高斯噪声的图像进行中值滤波
		imshow("filter salt noise image（均值滤波）", filter_img1);
		imshow("filter salt noise image（中值滤波）", filter_img2);
		imshow("filter gauss noise image（均值滤波）", filter_img3);
		imshow("filter gauss noise image（中值滤波）", filter_img4);
	}
	waitKey(0);
	return 0;
}
