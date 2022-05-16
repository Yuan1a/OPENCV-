#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include<random>

using namespace cv;
using namespace std;

  //������������
   void addSaltNoise(const Mat &srcImage, Mat &dstImage, int n)
   {
	dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//���ȡֵ����
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//ͼ��ͨ���ж�
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//������
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
		//���ȡֵ����
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//ͼ��ͨ���ж�
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//������
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
   }

	//���ɸ�˹����
	double generateGaussianNoise(double mu, double sigma)
	{
		//����Сֵ
		const double epsilon = numeric_limits<double>::min();
		static double z0, z1;
		static bool flag = false;
		flag = !flag;
		//flagΪ�ٹ����˹�������X
		if (!flag)
			return z1 * sigma + mu;
		double u1, u2;
		//�����������
		do
		{
			u1 = rand() * (1.0 / RAND_MAX);
			u2 = rand() * (1.0 / RAND_MAX);
		} while (u1 <= epsilon);
		//flagΪ�湹���˹�������
		z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
		z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
		return z0 * sigma + mu;
	}

	//Ϊͼ������˹����
	void addGaussianNoise(Mat &srcImag, Mat &dstImage, double mu, double sigma)
	{
		dstImage = srcImag.clone();
		int channels = dstImage.channels();
		int rowsNumber = dstImage.rows;
		int colsNumber = dstImage.cols*channels;
		//�ƶ�ͼ���������
		if (dstImage.isContinuous())
		{
			colsNumber *= rowsNumber;
			rowsNumber = 1;
		}
		for (int i = 0; i < rowsNumber; i++)
		{
			for (int j = 0; j < colsNumber; j++)
			{
				//�����˹����
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
		cout << "δ��ȡ����ͼƬ��" << endl;
		return 0;
	}
    else
	{
		//��������:��˹����,��������;
		addSaltNoise(img_gray, addsalt_img, 30000); //���ӽ�������
		imshow("Add salt noise image", addsalt_img);
		addGaussianNoise(img_gray, addgauss_img, 0, 1);
		imshow("Add Gaussina noise image", addgauss_img);
		
		//�˲�����ֵ,��ֵ
		// blur(InputArray src, OutputArray dst, Size(X,X)���˲��˴�С, Point(-1, -1)��ê��, int borderType = BORDER_DEFAULT����ʡ��); //��ֵ�˲�����
		// medianBlur(InputArray src, OutputArray dst, int ksize��3Ϊ3��3���˲���)//��ֵ�˲�����
		//��g��
		blur(addsalt_img, filter_img1, Size(8,8), Point(5, 5));//���ӽ���������ͼ����о�ֵ�˲�
		medianBlur(addsalt_img, filter_img2, 5);//���ӽ���������ͼ�������ֵ�˲�
		blur(addgauss_img, filter_img3, Size(8,8), Point(5, 5));//���Ӹ�˹������ͼ����о�ֵ�˲�
		medianBlur(addgauss_img, filter_img4, 5);//���Ӹ�˹������ͼ�������ֵ�˲�
		imshow("filter salt noise image����ֵ�˲���", filter_img1);
		imshow("filter salt noise image����ֵ�˲���", filter_img2);
		imshow("filter gauss noise image����ֵ�˲���", filter_img3);
		imshow("filter gauss noise image����ֵ�˲���", filter_img4);
	}
	waitKey(0);
	return 0;
}
