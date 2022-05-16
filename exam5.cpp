#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include<random>

using namespace cv;
using namespace std;
//Roberts����
Mat Roberts(Mat srcImage)
{
	Mat dstImage = srcImage.clone();
	int nRows = dstImage.rows;
	int nCols = dstImage.cols;
	for (int i = 0; i < nRows - 1; i++) {
		for (int j = 0; j < nCols - 1; j++) {
			//���ݹ�ʽ����
			int t1 = (srcImage.at<uchar>(i, j) -
				srcImage.at<uchar>(i + 1, j + 1))*
				(srcImage.at<uchar>(i, j) -
					srcImage.at<uchar>(i + 1, j + 1));
			int t2 = (srcImage.at<uchar>(i + 1, j) -
				srcImage.at<uchar>(i, j + 1))*
				(srcImage.at<uchar>(i + 1, j) -
					srcImage.at<uchar>(i, j + 1));
			//����g��x,y��
			dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}
	}
	return dstImage;
}

int main()
{
	Mat img_gray, src,sobel_img,robert_img,laplace_img,canny_img;
	img_gray = imread("E://gray_lena.png", -1);
	cout<<"ͨ������"<<img_gray.channels() << endl;
	if (!img_gray.data)
	{
		cout << "δ��ȡ����ͼƬ��" << endl;
		return 0;
	}
	else
	{
		imshow("gray_lena", img_gray); 
		//���б�Ե��⣺��������sobel,canny,robert,laplace
		//�Ƚ��и�˹�˲����ټ��ͼ���������� GaussianBlur(input img,output arc,Size(X,X),x���׼ƫ��,y���׼ƫ��)
		GaussianBlur(img_gray, src, Size(3, 3), 5, 5);
		imshow("Gauss�˲����ͼ��", src);
		//�ٽ������Ӵ�����ȡͼ���Ե
		//Sobel(InputArray src,OutputArray dst,int ddepth// ���ͼ�����, x���ֽ���, y���ֽ���,int ksize = 3,double scale = 1,double delta = 0,int borderType = BORDER_DEFAULT );
		//Laplacian(InputArray src,OutputArray dst,int ddepth//���ͼ�����,int ksize = 1,double scale = 1,double delta = 0,int borderType = BORDER_DEFAULT);
		//Canny(InputArray image,OutputArray edges, ����ֵ, ����ֵ, size, L2gradient = false // �Ƿ��һ��);
		//Roberts����ʵ�֣�Roberts(Mat srcImage) //ѭ��
		robert_img=Roberts(src);
		imshow("use roberts ��Ե���", robert_img);
	    Canny(src, canny_img, 100, 200, 3);
		imshow("use canny ��Ե���", canny_img);
		Sobel(src, sobel_img, CV_8U, 1, 1, 3, 1, 0);
		imshow("use sobel ��Ե���", sobel_img);
		Laplacian(src, laplace_img, CV_8U, 1, 1, 0);
		imshow("use laplace ��Ե���", laplace_img);
	


	}














	waitKey(0);
	return 0;
}