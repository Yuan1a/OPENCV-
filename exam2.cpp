///////////////////////////ʵ��2///////////////////////////////
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img, dst,src,change_image,equalize_img;
	img = imread("E://lena.jpg");
	if (!img.data)
	{
		cout << "δ��ȡ����ͼƬ��" << endl;
		return -1;
	}
	else
	{
		imshow("ԭͼ", img);
		cvtColor(img, dst, CV_RGB2GRAY);
		imshow("�Ҷ�ͼ", dst);
//�ԱȶȺ����ȵ���
		//����ʵ�֣�convertTo(convertTo	(OutputArray m�����ͼ��,int rtype������������� һ��Ϊ-1,double alpha �������Աȶ�,double beta ����������)) 
		//a > 1,����ͼ��ĶԱȶ�
		//a < 1����Сͼ��ĶԱȶ�
		//a = 0, b != 0��ͼ�������䰵
		//a < 0��b = 0, ͼ���������䰵�����������
		//a = -1, b = 255, ͼ�����ȷ�ת
		//ʹ��ʵ����
		dst.convertTo(change_image, -1, -1, 255);	
		imshow("���ڹ����Ⱥͱ��ͶȵĻҶ�ͼ", change_image);

		//�Ա����ʵ�֣�
		/*int height = dst.rows;
		int width1 = dst.cols;
		float alpha = 1.3;
		float beta = 30;
		dst = Mat::zeros(dst.size(), dst.type());
		for (int row = 0; row < height; row++) 
		{
			for (int col = 0; col < width1; col++) 
			{
				if (dst.channels() == 3) 
				{
					float b = dst.at<Vec3b>(row, col)[0];
					float g = dst.at<Vec3b>(row, col)[1];
					float r = dst.at<Vec3b>(row, col)[2];
						
					src.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
					src.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
					src.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
				}
				else if (dst.channels() == 1) 
				{
					float v_gray = dst.at<uchar>(row, col);
					src.at<uchar>(row, col) = saturate_cast<uchar>(v_gray * alpha + beta);
				}
			 }
		}
		imshow("���ڹ����ȻҶ�ͼ", src);
		imshow("���ڹ����ͶȵĻҶ�ͼ", change_image);*/

		
//ֱ��ͼ���⻯ �Ҷ�ͼ��
		//���ú���equalizeHist(grayImage, resultImage);
		equalizeHist(dst, equalize_img);
		imshow("����ֱ��ͼ���⻯��ͼ��",equalize_img);
	
		
		
//�ԱȻҶ�ֱ��ͼ
		//ֱ��ͼ�����������鿴ͼ������ı仯��ʽ������ͼ���Ƿ������ͼ�����ػҶ�ֵ��Ҫ��������Щ��Χ�ȣ����ض���������Ҳ��������ͼ��ֱ��ͼ����ͼ���ʶ����������ֵ�ʶ��
		//�Ҷ�ֱ��ͼ�ǻҶȼ��ĺ���������ʾͼ���о���ĳ�ֻҶȼ������صĸ�������ӳ��ͼ����ĳ�ֻҶȳ��ֵ�Ƶ��
		//���ƻҶ�ֱ��ͼ:����cvtColor���лҶȻ�����ʹ��calcHist���� ��ʽ��calcHist(images(����ͼ���ָ��),nimages(����ͼ�����),channels(��Ҫͳ�Ƶ�ͨ������), mask(��ѡ����Դ�벻Ϊ�������Ϊ8λ��,hist(�������ֵ) ,dims(���ֱ��ͼ��ά��),histSize(����ά������), ranges(�Ҷ�ֵ��Χ), uniform=true(�Ƿ��һ������),accumulate=false(���ͼ���ۻ�����))
		//����calcHist���ڲ�����������ֱ��ͼ��
		const int channels[] = { 0 }; //��Ҫ�����ͼ���ͨ�����Ҷ�ͼ��Ϊ0��BGRͼ����Ҫָ��B,G,R
		Mat hist_org,hist_equalize; //���Mat����
		int dims = 1;//ֱ��ͼά��
		const int histsize[] = { 256 };//ֱ��ͼÿ��ά�Ȼ��ֵ�������
		float pranges[] = { 0,255 };//ÿ��ά�ȵ�ȡֵ��Χ
		const float* ranges[] = { pranges };//����һ��ָ�� ʹ��rangesָ��pranges
		//ʹ��calcHist���ӣ�
		calcHist(&dst, 1, channels, Mat(), hist_org, dims, histsize, ranges, true, false);//�������ֵ����Ϊhist
		calcHist(&equalize_img, 1, channels, Mat(), hist_equalize, dims, histsize, ranges, true, false);//�������ֵ����Ϊhist
		//�����趨�����ڻ���ֱ��ͼ��ͼ��߶�С��ĳЩ�Ҷ�ֵͳ�Ƶ���Ŀ����������ڻ���ֱ��ͼʱ�����е����ݶ���СΪԭ����ʮ��֮һ֮���ٽ��л���
		int hist_w = 512;
		int hist_h = 400;
		int width = 2;
		Mat histimage = Mat::zeros(hist_h, hist_w, CV_8UC3);//����
		for (int i = 1; i <= hist_org.rows; i++)
		{
			rectangle(histimage, Point(width*(i - 1), hist_h - 1), Point(width*i - 1, hist_h - cvRound(hist_org.at<float>(i - 1) / 10)), Scalar(255,0, 0), 2, 8);
			//rectangle(Ҫ����ͼ��, Point(j,i), Point(j + img4.cols, i + img4.rows), Scalar(255, 255, 0), 2, 8),�������������������¾��εĽ����꣬����������Ϊ��ɫ�߿�����;
		}
		for (int i = 1; i <= hist_equalize.rows; i++)
		{
			rectangle(histimage, Point(width*(i - 1), hist_h - 1), Point(width*i - 1, hist_h - cvRound(hist_equalize.at<float>(i - 1) / 10)), Scalar(255, 255, 255), 2, 8);
			//rectangle(Ҫ����ͼ��, Point(j,i), Point(j + img4.cols, i + img4.rows), Scalar(255, 255, 0), 2, 8),�������������������¾��εĽ����꣬����������Ϊ��ɫ�߿�����;
		}
		imshow("�Ҷ�ֱ��ͼ�Ա�", histimage);//�Ҷ�ͼ�;������⻯���ֱ��ͼ�Ա�

		
		

	}
	waitKey(0);
	return 0;



}