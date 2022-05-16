///////////////////////////实验2///////////////////////////////
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
		cout << "未读取到该图片！" << endl;
		return -1;
	}
	else
	{
		imshow("原图", img);
		cvtColor(img, dst, CV_RGB2GRAY);
		imshow("灰度图", dst);
//对比度和亮度调整
		//函数实现：convertTo(convertTo	(OutputArray m：输出图像,int rtype：输出矩阵类型 一般为-1,double alpha ：调整对比度,double beta ：调整亮度)) 
		//a > 1,增加图像的对比度
		//a < 1，减小图像的对比度
		//a = 0, b != 0，图像变亮或变暗
		//a < 0且b = 0, 图像的亮区域变暗，暗区域变亮
		//a = -1, b = 255, 图像亮度反转
		//使用实例：
		dst.convertTo(change_image, -1, -1, 255);	
		imshow("调节过亮度和饱和度的灰度图", change_image);

		//自编程序实现：
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
		imshow("调节过亮度灰度图", src);
		imshow("调节过饱和度的灰度图", change_image);*/

		
//直方图均衡化 灰度图像
		//调用函数equalizeHist(grayImage, resultImage);
		equalizeHist(dst, equalize_img);
		imshow("经过直方图均衡化的图像",equalize_img);
	
		
		
//对比灰度直方图
		//直方图：可以用来查看图像整体的变化形式，例如图像是否过暗、图像像素灰度值主要集中在哪些范围等，在特定的条件下也可以利用图像直方图进行图像的识别，例如对数字的识别
		//灰度直方图是灰度级的函数，它表示图像中具有某种灰度级的像素的个数，反映了图像中某种灰度出现的频率
		//绘制灰度直方图:先用cvtColor进行灰度化，再使用calcHist函数 格式：calcHist(images(读入图像的指针),nimages(读入图像个数),channels(需要统计的通道索引), mask(可选操作源码不为空则必须为8位）,hist(计算输出值) ,dims(输出直方图的维度),histSize(划分维度区间), ranges(灰度值范围), uniform=true(是否归一化处理),accumulate=false(多个图像累积计算))
		//定义calcHist的内部参数并计算直方图：
		const int channels[] = { 0 }; //需要计算的图像的通道，灰度图像为0，BGR图像需要指定B,G,R
		Mat hist_org,hist_equalize; //输出Mat类型
		int dims = 1;//直方图维度
		const int histsize[] = { 256 };//直方图每个维度划分的柱条数
		float pranges[] = { 0,255 };//每个维度的取值范围
		const float* ranges[] = { pranges };//定义一个指针 使得ranges指向pranges
		//使用calcHist例子：
		calcHist(&dst, 1, channels, Mat(), hist_org, dims, histsize, ranges, true, false);//输出计算值参数为hist
		calcHist(&equalize_img, 1, channels, Mat(), hist_equalize, dims, histsize, ranges, true, false);//输出计算值参数为hist
		//画布设定：由于绘制直方图的图像高度小于某些灰度值统计的数目，因此我们在绘制直方图时将所有的数据都缩小为原来的十分之一之后再进行绘制
		int hist_w = 512;
		int hist_h = 400;
		int width = 2;
		Mat histimage = Mat::zeros(hist_h, hist_w, CV_8UC3);//画布
		for (int i = 1; i <= hist_org.rows; i++)
		{
			rectangle(histimage, Point(width*(i - 1), hist_h - 1), Point(width*i - 1, hist_h - cvRound(hist_org.at<float>(i - 1) / 10)), Scalar(255,0, 0), 2, 8);
			//rectangle(要处理图像, Point(j,i), Point(j + img4.cols, i + img4.rows), Scalar(255, 255, 0), 2, 8),参数二三代表左上右下矩形的角坐标，参数四五六为颜色线宽线型;
		}
		for (int i = 1; i <= hist_equalize.rows; i++)
		{
			rectangle(histimage, Point(width*(i - 1), hist_h - 1), Point(width*i - 1, hist_h - cvRound(hist_equalize.at<float>(i - 1) / 10)), Scalar(255, 255, 255), 2, 8);
			//rectangle(要处理图像, Point(j,i), Point(j + img4.cols, i + img4.rows), Scalar(255, 255, 0), 2, 8),参数二三代表左上右下矩形的角坐标，参数四五六为颜色线宽线型;
		}
		imshow("灰度直方图对比", histimage);//灰度图和经过均衡化后的直方图对比

		
		

	}
	waitKey(0);
	return 0;



}