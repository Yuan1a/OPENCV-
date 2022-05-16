///////////////////////////实验1///////////////////////////////
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;  //使得下列参数不必加CV_ eg：cv_imread可写为imread
using namespace std; //使用cout<<xx<<endl必须加上
int main()
{
	Mat img, dst; 
	// imread读入函数 格式：imread("文件路径",IMREAD_YY) YY指COLOR GRAYSCALE UNCHANGED 等等
	img = imread("E:\\lena.jpg");
	if (!img.data)   //判定读入图片是否存在
	{
		cout << "该图片并不存在" << endl;
		return 0;
	}
	else
	{
		//imshow显示函数 格式：imshow（"字符",定义参数）
		imshow("原图", img);

		//imwrite写出函数 格式：imwrite（"图片保存.格式"，写入图片） 
		imwrite("lena.png", img); //eg：将原来的JPG文件转为PNG文件 存在项目根目录下

		//cvtColor图像颜色空间转换函数 格式：cvtColor（读入图像参数，转换图像参数，什么转什么（eg：CV_RGB2GRAY））
		//eg：先利用cvtColor函数转换RGB为GRAY图，再使用imwrite函数保存为PNG格式的灰度图
		cvtColor(img, dst, CV_RGB2GRAY);
		imshow("灰度处理图", dst);
		imwrite("gray_lena.png" ,dst);

		//读取图片基本属性如行数cols，列数rows，（色彩）通道数channels：返回mat的通道数，图像大小size；PS:rgb图像为3，8位灰度图为1
		//但是用imread()函数读取灰度图和rgb图时，得到的mat的channels均为3
		cout << "图像行数：" << img.cols << "\t图像列数为：" << img.rows << "\t通道数为：" << img.channels() <<"\t图像大小"<< img.size <<endl;
		cout << "图像行数：" << dst.cols << "\t图像列数为：" << dst.rows << "\t通道数为：" << dst.channels() <<"\t图像大小"<< dst.size <<endl;
		 
		//分离图片颜色通道采用split函数 格式：split(image,mv)
		vector<Mat> mv;
		split(img, mv);
		imshow("Blue", mv[0]);
		imshow("Green", mv[1]);
		imshow("Red", mv[2]);


		//直方图：可以用来查看图像整体的变化形式，例如图像是否过暗、图像像素灰度值主要集中在哪些范围等，在特定的条件下也可以利用图像直方图进行图像的识别，例如对数字的识别
		//灰度直方图是灰度级的函数，它表示图像中具有某种灰度级的像素的个数，反映了图像中某种灰度出现的频率
		//绘制灰度直方图:先用cvtColor进行灰度化，再使用calcHist函数 格式：calcHist(images(读入图像的指针),nimages(读入图像个数),channels(需要统计的通道索引), mask(可选操作源码不为空则必须为8位）,hist(计算输出值) ,dims(输出直方图的维度),histSize(划分维度区间), ranges(灰度值范围), uniform=true(是否归一化处理),accumulate=false(多个图像累积计算))
	    //定义calcHist的内部参数并计算直方图：
		Mat hist;//calHist计算输出参数
		const int channels[] = { 0 }; //需要计算的图像的通道，灰度图像为0，BGR图像需要指定B,G,R
		int dims = 1;//直方图维度
		const int histsize[] = { 256 };//直方图每个维度划分的柱条数
		float pranges[] = { 0,255 };//每个维度的取值范围
		const float* ranges[] = { pranges };//定义一个指针 使得ranges指向pranges
		//使用calcHist例子：
		calcHist(&dst, 1, channels, Mat(), hist, dims, histsize, ranges, true, false);//输出计算值参数为hist
		//画直方图：
		
		int hist_w = 512;
	    int hist_h = 400;
		int width = 2;
		Mat histimage = Mat::zeros(hist_h, hist_w, CV_8UC3);//画布
		 for (int i = 1; i <= hist.rows; i++) //行扫描
			   {
			    rectangle(histimage,Point(width*(i - 1), hist_h - 1),Point(width*i - 1, hist_h - cvRound(hist.at<float>(i - 1) / 20)),Scalar(255, 255, 255),2,8);
				//rectangle(要处理图像, Point(j,i), Point(j + img4.cols, i + img4.rows), Scalar(255, 255, 0), 2, 8),参数二三代表左上右下矩形的角坐标，参数四五六为颜色线宽线型;
			   }
		 imshow("灰度直方图", histimage);

			
		
	}
	waitKey(0); //延迟函数
	return 0;
}