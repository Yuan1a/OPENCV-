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
		cout << "δ�ܹ�����ͼƬ" << endl;
		return -1;
	}
	else
		imshow("���ֻҶ�ͼ", gray_img);
		//��ʴ������ erode������dilate����
	//��ʹ��getStructuringElement����ں˾���
	element = getStructuringElement(MORPH_RECT, Size(8, 8));
	//��ʴ�����ͣ�
	erode(gray_img, src1, element); //��ʴ
	dilate(gray_img, src2,element); //����
	imshow("erode", src1);
	imshow("dilate", src2);
	 //����morphologyEx(input,output,MORPH_XX����������,�ں˲���getStructuringElement������ϻ�ȡ,Point,��������)
	//������(�ȸ�ʴ������)
	morphologyEx(gray_img, src_open, MORPH_OPEN, element,Point(-1,1),1);
	imshow("open_img", src_open);
	//������(�����ͺ�ʴ)
	morphologyEx(gray_img, src_close, MORPH_CLOSE, element,Point(-1,1),1);
	imshow("close_img", src_close);

	//��̬ѧ�ݶ�//��Ե��ȡ ���͡���ʴ
	morphologyEx(gray_img, morph_grad, MORPH_GRADIENT, element, Point(-1, 1), 1);
	imshow("morph_grad_img", morph_grad);






	 
		
	waitKey(0);
	return 0;

}