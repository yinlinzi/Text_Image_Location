#include"enhance_image.h"
void enhance_image(Mat dst,vector<vector<square>> rangesquare,vector<Mat> &vmat)
{
int left=10000,right=0,up,down;
int sumup=0,sumdown=0;
for(vector<vector<square>>::iterator k=rangesquare.begin();k<rangesquare.end();k++)
{
vector<square> vtemp=*k;
for(vector<square>::iterator it=vtemp.begin();it<vtemp.end();it++)
{
sumup+=it->squ1.y;
sumdown+=it->squ2.y;
if(it->squ1.x<left)
left=it->squ1.x;
if(it->squ2.x>right)
right=it->squ2.x;
}
up=sumup/vtemp.size();
down=sumdown/vtemp.size();
square s1;
s1.squ1.x=left;
s1.squ1.y=up;
s1.squ2.x=right;
s1.squ2.y=down;
Mat p1=picturn3(dst,s1);
Mat pout;
imageturn(p1,pout);
IplImage imgtemp=pout;
IplImage* pImg =cvCloneImage(&imgtemp);
IplImage * pResult=cvCreateImage(cvSize(pImg ->width,pImg ->height),8,1);
IplImage *pimg=cvCreateImage(cvSize(pImg ->width,pImg ->height),8,1);
cvCvtColor(pImg,pimg,CV_BGR2GRAY);
KMeans2(pimg,pResult,0,3);//k_means聚类
IplImage *img_dilate=cvCreateImage(cvSize(pImg ->width,pImg ->height),8,1);
cvDilate( pResult,img_dilate, NULL,1);//膨胀算法，效果会更好
vmat.push_back(img_dilate);
cvNamedWindow("图像显示",1);///*
cvShowImage("图像显示",img_dilate);
cvWaitKey(0);//一直等待按键没有这句的话图像不能正常显示
cvReleaseImage(&pResult);//释放图像内存
cvDestroyWindow("图像显示");//销毁窗口资源*/
}

}
void imageturn(Mat imagein,Mat &imageout)//将rgb转化hsv，然后改变hsv图像。
{
IplImage imgtemp=imagein;
IplImage* src =cvCloneImage(&imgtemp);
IplImage* floathsv = NULL;
IplImage* floatimgH = NULL;
IplImage* floatimgS = NULL;
IplImage* floatimgV = NULL;
IplImage* floatimgZ = NULL;
CvSize size = cvGetSize( src );
IplImage* imgout=cvCreateImage( size, 8, 3 );
floathsv = cvCreateImage( size, 8, 3 );
floatimgH = cvCreateImage( size, 8, 1 );
floatimgS = cvCreateImage( size,8, 1 );
floatimgV = cvCreateImage( size, 8, 1 );
floatimgZ = cvCreateImage( size, 8, 1 );
cvCvtColor(src,floathsv,CV_BGR2HSV);
cvSplit( floathsv, floatimgH, floatimgS, floatimgV, NULL);
Mat V(floatimgV,true);
Mat Vout;
sharpen(V,Vout);
imgtemp=Vout;
floatimgV=cvCloneImage(&imgtemp);
cvSmooth(floatimgV, floatimgZ, CV_MEDIAN);//中值滤波
cvEqualizeHist( floatimgZ, floatimgV ); //直方图均衡化
cvMerge( floatimgH, floatimgS, floatimgV,0,imgout);
Mat M(imgout,true);
imageout=M;
}
void sharpen(Mat imagein,Mat &imageout)
{
//创建并初始化滤波模板
cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
kernel.at<float>(1,1) = 5.0;
kernel.at<float>(0,1) = -1.0;
kernel.at<float>(1,0) = -1.0;
kernel.at<float>(1,2) = -1.0;
kernel.at<float>(2,1) = -1.0;
imageout.create(imagein.size(),imagein.type());
//对图像进行滤波
cv::filter2D(imagein,imageout,imagein.depth(),kernel);
}
bool KMeans2( const IplImage * pImg ,IplImage * pResult ,int sortFlag ,int nClusters )
{

assert ( pImg != NULL && pImg -> nChannels == 1);

// 创建样本矩阵， CV_32FC1 代表位浮点通道（灰度图像）

CvMat * samples = cvCreateMat (( pImg -> width )* ( pImg -> height ),1, CV_32FC1 );

// 创建类别标记矩阵， CV_32SF1 代表位整型通道

CvMat * clusters = cvCreateMat (( pImg -> width )* ( pImg -> height ),1, CV_32SC1 );

// 创建类别中心矩阵

CvMat * centers = cvCreateMat ( nClusters , 1, CV_32FC1 );

// 将原始图像转换到样本矩阵

{
int k = 0;

CvScalar s ;

for ( int i = 0; i < pImg -> width ; i ++)

{

for ( int j =0; j < pImg -> height ; j ++)

{

s . val [0] = ( float ) cvGet2D ( pImg , j , i ). val [0];

cvSet2D ( samples , k ++, 0, s );

}

}

}

// 开始聚类，迭代次，终止误差 .0

cvKMeans2 ( samples , nClusters , clusters , cvTermCriteria ( CV_TERMCRIT_ITER + CV_TERMCRIT_EPS ,100, 1.0), 1, 0, 0, centers );

// 无需排序直接输出时

if ( sortFlag == 0)

{

int k = 0;

int val = 0;

float step = 255 / (( float ) nClusters - 1);

CvScalar s ;

for ( int i = 0; i < pImg -> width ; i ++)

{

for ( int j = 0; j < pImg -> height ; j ++)

{

val = ( int ) clusters -> data . i [ k ++];

s . val [0] = 255- val * step ; // 这个是将不同类别取不同的像素值，

cvSet2D ( pResult , j , i , s ); // 将每个像素点赋值

}

}

return TRUE ;
} 
}
