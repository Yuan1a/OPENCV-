#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include<random>

using namespace cv;
using namespace std;

int main()
{
	Mat gray_img, src1, src2, src_open,src_close, element,morph_grad;
	gray_img = imread("E://word.png", 0);
	if (!gray_img.data)
	{
		cout << "未能够读出图片" << endl;
		return -1;
	}
	else
		imshow("文字灰度图", gray_img);
		//腐蚀与膨胀 erode函数和dilate函数
	//先使用getStructuringElement获得内核矩阵
	element = getStructuringElement(MORPH_RECT, Size(8, 8));
	//腐蚀和膨胀：
	erode(gray_img, src1, element); //腐蚀
	dilate(gray_img, src2,element); //膨胀
	imshow("erode", src1);
	imshow("dilate", src2);
	 //函数morphologyEx(input,output,MORPH_XX：运算类型,内核采用getStructuringElement函数配合获取,Point,迭代次数)
	//开运算(先腐蚀后膨胀)
	morphologyEx(gray_img, src_open, MORPH_OPEN, element,Point(-1,1),1);
	imshow("open_img", src_open);
	//闭运算(先膨胀后腐蚀)
	morphologyEx(gray_img, src_close, MORPH_CLOSE, element,Point(-1,1),1);
	imshow("close_img", src_close);

	//形态学梯度//边缘提取 膨胀—腐蚀
	morphologyEx(gray_img, morph_grad, MORPH_GRADIENT, element, Point(-1, 1), 1);
	imshow("morph_grad_img", morph_grad);






	 
		
	waitKey(0);
	return 0;

}