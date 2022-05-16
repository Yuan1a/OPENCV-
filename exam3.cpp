///////////////////////////ʵ��3///////////////////////////////
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
		cout << "δ��ȡ����ͼƬ��" << endl;
		return -1;
	}
	else
	{
		cvtColor(img, gray, CV_RGB2GRAY);
		imshow("�Ҷ�ͼ", gray);
		//��֤��ͨ��
		cout << "��ͼ��ͨ����Ϊ��" << gray.channels() << endl;
		
		//����ͼ��ʹ�ò�ͬ��ֵ��ʽ ����resize() ��ʽ��resize(input,output,output image Size(X,X),x axis����,y axis����,��ֵ��ʽ��7�����в鿴�����嵥)
		//eg��
		resize(gray, smallimg, Size(256, 256), 0, 0, 3);//��СͼƬ��ѡinter_area ���3 ������0.5��
		resize(gray, bigimg, Size(768, 768), 0, 0, 0);//�Ŵ�1.5��
		imshow("��Сͼ", smallimg);
		imshow("�Ŵ�ͼ", bigimg);

		//��תͼ������Ƕȣ���getRotationMatrix2D(center,+��/-˳ʱ��+�Ƕ�,���ű���) �õ�2*3��������warpAffine()��������
		Point2f center((float)gray.rows*0.5, (float)gray.cols*0.5);
		rotate = getRotationMatrix2D(center,-45, 1);
		warpAffine(gray, res, rotate, gray.size());
		imshow("˳ʱ����ת45��", res);

		//����ͼƬ�Ĵ������� ����absdiff()���� ��ֵ���о���ֵ
		//��ʽabsdiff(input img1,input img2,output image)
		absdiff(img, src, result);
		namedWindow("��ͼ���� ����ȡ����ֵ");
		imshow("ԭͼ1", img);
		imshow("ԭͼ2", src);
		imshow("��ͼ���� ����ȡ����ֵ", result);


	}
	waitKey(0);
	return 0;



}