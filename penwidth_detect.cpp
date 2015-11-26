#include"penwidth.h"
void penwidth(Mat src,vector<vector<square>> &rangesquare)
{
for(vector<vector<square>>::iterator ite=rangesquare.begin();ite<rangesquare.end();ite++)
{
vector<square> vtemp=*ite;
float *p=new float[vtemp.size()+1];
int p_i=0;
for(vector<square>::iterator it=vtemp.begin();it<vtemp.end();it++)
{
Mat dst;
picturn(src,dst,*it);
swt(dst,p[p_i]);
//cout<<p[p_i]<<endl;
p_i++;
}
sort(p,p+vtemp.size());//求中位数
float av=0;
if(vtemp.size()%2==0)
av=(p[vtemp.size()/2]+p[vtemp.size()/2+1])/2.0;
else av=p[vtemp.size()/2+1];
for(int i=0;i<vtemp.size();i++)///vtemp.size()会变化么???
{
if(abs(p[i]-av)>2)/////////////固定值////////
{
vtemp.erase(vtemp.begin()+i);
i--;
}
}
delete p;
vtemp.swap(*ite);////不晓得可不可以这样去更改的
}
}
void picturn(Mat src,Mat &dst,square s1)
{
CvRect rect;
rect.x=s1.squ1.x;
rect.y=s1.squ1.y;
rect.width=s1.squ2.x-s1.squ1.x;
rect.height=s1.squ2.y-s1.squ1.y;
IplImage imgtemp;
imgtemp=src;
IplImage *imgin=cvCloneImage(&imgtemp);
IplImage *imgout1=cvCreateImage(cvSize(rect.width,rect.height),8,3);
cvSetImageROI(imgin,rect);
cvCopy(imgin,imgout1);
cvResetImageROI(imgin);
float scale=rect.width/50.0;
IplImage* imgout=cvCreateImage(cvSize(imgout1->width/scale,imgout1->height/scale),8,3);//32*
cvResize(imgout1,imgout,CV_INTER_AREA);
Mat d1(imgout,true);
Mat d2;
blur( d1, d2, Size(3,3) );
IplImage imgTmp = d2;
imgout = cvCloneImage(&imgTmp);
IplImage *pCannyImg=cvCreateImage(cvGetSize(imgout),IPL_DEPTH_8U,1);	
cvCanny(imgout,pCannyImg,50,150,3);//转化为边沿检测
Mat m(pCannyImg,true);
//myshow(m);
dst=m;
}
void GradientDir(IplImage* canny,IplImage* src,int width,int height,Upoint* Atan)
{
unsigned char a00, a01, a02;
unsigned char a10, a11, a12;
unsigned char a20, a21, a22;
for (int i=1; i< height-1; ++i)
{
for (int j=1; j<width-1; ++j)
{
if (cvGet2D(canny, i, j).val[0] == 255) //边缘点
{
a00 = cvGet2D(src, i-1, j-1).val[0];
a01 = cvGet2D(src, i-1, j).val[0];
a02 = cvGet2D(src, i-1, j+1).val[0];
a10 = cvGet2D(src, i, j-1).val[0];
a11 = cvGet2D(src, i, j).val[0];
a12 = cvGet2D(src, i, j+1).val[0];
a20 = cvGet2D(src, i+1, j-1).val[0];
a21 = cvGet2D(src, i+1, j).val[0];
a22 = cvGet2D(src, i+1, j+1).val[0];
// x方向上的近似导数
double ux = a02 * (1) + a12 * (2) + a22 * (1)
+ a00 * (-1) + a10 * (-2) + a20 * (-1);
// y方向上的近似导数
double uy = a20 * (1) + a21 * (2) + a22 * (1)
+ (a00 * (-1) + a01 * (-2) + a02 * (-1));
Upoint up;
up.ux = ux; up.uy = uy;
Atan[i*width+j] = up;

}
}
}
}
void swt(Mat dst1,float &pen)
{
IplImage imgtemp=dst1;
IplImage *dst=cvCloneImage(&imgtemp);
int i,j,k,y;
unsigned char a0,a1;
double th,th1;
CvScalar color ;
Upoint up;
vector<CvPoint> vec;//存标记
vector<swtpoint> vecswt;//求出swt
vector<swtfe> swtfre;//存笔画宽度
IplImage *pCannyImg=cvCreateImage(cvGetSize(dst),IPL_DEPTH_8U,1);	
cvCanny(dst,pCannyImg,50,150,3);//转化为边沿检
Upoint* Atan = new Upoint[dst->width * dst->height+1];
GradientDir(pCannyImg,dst,dst->width,dst->height,Atan);//////////////////
IplImage *src = cvCloneImage(pCannyImg);
vec.clear();
vec.swap(vector<CvPoint>());
vecswt.clear();//清空元素
for (i=1; i<dst-> height-1; ++i)
{
for (j=1; j<dst->width-1; ++j)
{
int ls=0;
a0 = cvGet2D(pCannyImg, i, j).val[0];//b是255，代表白色
if (a0 == 255) //白点
{
color.val[0] = 120;
cvSet2D(pCannyImg, i, j, color);//找过的点设置为灰度点
vec.clear();
//判断斜率是否接近垂直
up = Atan[i*dst->width+j];
double Angle = atan2(up.uy, up.ux) * 180 / pi;
//cout<<"angle is "<<Angle<<endl;
if(Angle < 95 && Angle > -5)
{
if (Angle > 87 && Angle < 93) ////?????有问题
{
for (k = i + 1; k < dst->height-1;k++)
{
CvPoint p;
p.x = k; p.y = j; //存储梯度方向的点
vec.push_back(p);////////////////////
a1 = cvGet2D(pCannyImg, k, j).val[0]; 
if (a1 == 255)
{
Upoint po = Atan[k*dst->width+j];
th = atan2(po.uy, po.ux) * 180 / pi;
if((th > -100 && th < -80)||(80<th&&th<100))
{
//找到了匹配对边点
float SWT = k-i;
if(SWT<10)
{
color.val[0] = 120;
cvSet2D(pCannyImg, k, j, color);
//cout<<th<<"is th'vaule"<<'\t';
swtpoint swtp1;
swtp1.pointswt.x=i;
swtp1.pointswt.y=j;
swtp1.flag=1;
swtp1.swt=SWT;
vecswt.push_back(swtp1);//////////////////
//cout<<th<<"is th'vaule"<<'\t';
//cout<<SWT<<endl;//
}
for ( vector<CvPoint>::iterator it = vec.begin(); it != vec.end(); ++it ) 
{
if (SWT < 10)////20这个数字还是得考虑的
{
color.val[0] = 255;//255
cvSet2D(src, it->x, it->y, color);

}

}
/*cvNamedWindow("filter",1); //
cvShowImage("filter",src);
cvWaitKey(0);//*/
break;	
}

}
}
}
else
{
for (k = j + 1; k <dst-> width - 1; k++)
{
up = Atan[i*dst-> width+j];
y = (int)(i + (k - j) * (up.uy / up.ux));
if (y < 0 || y >= dst-> height)
{
break;
}
CvPoint p;
p.x = y; p.y = k; //存储梯度方向的点
vec.push_back(p);///////////////////////

a1 = cvGet2D(pCannyImg, y, k).val[0];
if (a1 == 255)
{
Upoint po = Atan[y*dst-> width+k];
th = atan2(po.uy, po.ux)* 180 / pi;
//cout<<"th is"<<th<<endl;
if(th<0)
th=th+180;//转正角度
if(177<th)
th=0;//转0度
Upoint p1 = Atan[i*dst-> width+j];
th1 = atan2(p1.uy, p1.ux)* 180 / pi;
//cout<<"th1 is"<<th1<<endl;
if(th1<0)
th1=th1+180;
if(th1>177)
th1=0;
if (th1 - 5 <= th && th <= th1 + 5)//-7*pi/180 5
{

//找到了匹配对边点
float SWT = sqrt(double((k - j) * (k - j) + (y - i) * (y - i)));
if(SWT<10)
{
color.val[0] = 120;
cvSet2D(pCannyImg, y, k, color);
swtpoint swtp1;
swtp1.pointswt.x=i;
swtp1.pointswt.y=j;
swtp1.flag=1;
swtp1.swt=SWT;
vecswt.push_back(swtp1);
/*cout<<th<<"is th'vaule"<<'\t';//
cout<<SWT<<endl;//*/
}
for ( vector<CvPoint>::iterator it = vec.begin(); it != vec.end(); ++it ) 
{
//	uchar a00 = cvGet2D(src, it->x, it->y).val[0];
if (SWT <10)
{
color.val[0] = 255;//255
cvSet2D(src, it->x, it->y, color);
///////////////////
}
}	

/*cvNamedWindow("filter",1); //
cvShowImage("filter",src);
cvWaitKey(0);//*/
break;	
}

}
}
}

}
}
}
}
delete Atan;
float sum=0;
for(vector<swtpoint>::iterator it = vecswt.begin(); it != vecswt.end(); ++it)
sum=sum+it->swt;
pen=sum/vecswt.size();
}
