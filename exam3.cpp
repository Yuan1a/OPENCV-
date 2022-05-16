///////////////////////////实验3///////////////////////////////
#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img,src,gray,smallimg,bigimg,rotate,res,result;
	img = imread("E://lena.jpg");
	src = imread("E://lena2.jpg");
	
	if (!img.data)
	{
		cout << "未读取到该图片！" << endl;
		return -1;
	}
	else
	{
		cvtColor(img, gray, CV_RGB2GRAY);
		imshow("灰度图", gray);
		//验证单通道
		cout << "该图像通道数为：" << gray.channels() << endl;
		
		//放缩图像使用不同插值方式 采用resize() 格式：resize(input,output,output image Size(X,X),x axis比例,y axis比例,插值方式：7种自行查看代码清单)
		//eg：
		resize(gray, smallimg, Size(256, 256), 0, 0, 3);//缩小图片首选inter_area 简打3 这里缩0.5倍
		resize(gray, bigimg, Size(768, 768), 0, 0, 0);//放大1.5倍
		imshow("缩小图", smallimg);
		imshow("放大图", bigimg);

		//旋转图像（任意角度）：getRotationMatrix2D(center,+逆/-顺时针+角度,缩放比例) 得到2*3矩阵再用warpAffine()函数绘制
		Point2f center((float)gray.rows*0.5, (float)gray.cols*0.5);
		rotate = getRotationMatrix2D(center,-45, 1);
		warpAffine(gray, res, rotate, gray.size());
		imshow("顺时针旋转45度", res);

		//两张图片的代数运算 采用absdiff()函数 差值进行绝对值
		//格式absdiff(input img1,input img2,output image)
		absdiff(img, src, result);
		namedWindow("两图减法 负数取绝对值");
		imshow("原图1", img);
		imshow("原图2", src);
		imshow("两图减法 负数取绝对值", result);


	}
	waitKey(0);
	return 0;



}