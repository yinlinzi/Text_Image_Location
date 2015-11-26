#include"functionmser.h"//双阈值mser算法
void double_sort_location(Mat gray,vector<vector<square>> &rangesquare)
{
vector<square> v1,v2;
firstwo_mser_location(gray,v1,v2);
sort_v1(v1,rangesquare);
vector<vector<square>> rangesquare_v2;
sort_v1(v2,rangesquare_v2);
sort(rangesquare.begin(),rangesquare.end(), sort_range_condition);
sort(rangesquare_v2.begin(),rangesquare_v2.end(), sort_range_condition);
double_sort(rangesquare_v2,rangesquare);
}
bool sort_range_condition(vector<square>v1,vector<square> v2)
{
if(v1.at(0).squ1.x!=v2.at(0).squ1.x) return (v1.at(0).squ1.x>v2.at(0).squ1.x);
}
void double_sort(vector<vector<square>> rangesquare_v2,vector<vector<square>> &rangesquare)//双次的排序
{
for(vector<vector<square>>::iterator ite=rangesquare.begin();ite<rangesquare.end();)
{
if((*ite).size()<2)
ite=rangesquare.erase(ite);
else ite++;
}
for(vector<vector<square>>::iterator ite=rangesquare_v2.begin();ite<rangesquare_v2.end();)
{
if((*ite).size()<2)
ite=rangesquare_v2.erase(ite);
else ite++;
}
int sum_v1=0;
int av_v1=0;
vector<square> vtemp_v3;
for(vector<vector<square>>::iterator ite=rangesquare.begin();ite<rangesquare.end();ite++)
{
vector<square> vtemp_v1=*ite;
for(vector<square>::iterator ite_v1=vtemp_v1.begin();ite_v1<vtemp_v1.end();ite_v1++)
sum_v1+=ite_v1->squ1.y;
av_v1=sum_v1/vtemp_v1.size();
int sum_v2=0,av_v2=0;
for(vector<vector<square>>::iterator it=rangesquare_v2.begin();it<rangesquare_v2.end();it++)
{
vector<square> vtemp_v2=*it;
for(vector<square>::iterator ite_v2=vtemp_v2.begin();ite_v2<vtemp_v2.end();ite_v2++)
sum_v2+=ite_v2->squ1.y;
av_v2=sum_v2/vtemp_v2.size();
if(av_v2-av_v1>7)
break;
if(abs(av_v1-av_v2)<7)
{
sort(vtemp_v1.begin(),vtemp_v1.end(),sort_condition);
sort(vtemp_v2.begin(),vtemp_v2.end(),sort_condition);
int flag=0;
for(vector<square>::iterator ite_v2=vtemp_v2.begin();ite_v2<vtemp_v2.end();ite_v2++)
{
for(vector<square>::iterator ite_v1=vtemp_v1.begin();ite_v1<vtemp_v1.end();ite_v1++)
{
if(ite_v1->squ1.x==ite_v2->squ1.x)
{
flag=0;
break;
}
else if(ite_v1->squ1.x<ite_v2->squ1.x)
{
if(ite_v2->squ1.x-ite_v1->squ1.x>8)
{
flag=1;
continue;
}
else
{
flag=0;
break;
}
}
else
{
if(flag==1)
{
if(ite_v1->squ1.x-ite_v2->squ1.x<8)
{
flag=0;
break;
}
else//添加的元素
{
vtemp_v3.push_back(*ite_v2);
flag=0;
break;
}
}
else
{
if(ite_v1->squ1.x-ite_v2->squ1.x<8)
{
flag=0;
break;
}
else
{
vtemp_v3.push_back(*ite_v2);
break;
}
}
}
}
}
}
}
for(vector<square>::iterator ite_v3=vtemp_v3.begin();ite_v3<vtemp_v3.end();ite_v3++)
vtemp_v1.push_back(*ite_v3);
(*ite).swap(vtemp_v1);
}
}
bool sort_condition(square s1,square s2)
{
if(s1.squ1.x!=s2.squ1.x) return (s1.squ1.x-s2.squ1.x)<0;
else return (s1.squ1.x-s2.squ1.x)<0;
}
void sort_v1(vector<square> v1,vector<vector<square>> &rangesquare)//第一次排序已经好的
{
vector<square> tempuse,tempuse1;//用来避免内存出错
Point a1,a2;
a1.x=500;//引导第一个数据
a1.y=500;
a2.x=500;
a2.y=500;
square square2;
square2.squ1=a1;
square2.squ2=a2;
tempuse.push_back(square2); 
rangesquare.push_back(tempuse);
for(vector<square>::iterator it=v1.begin();it!=v1.end();it++)
{
int flagtemp=0;
int temp=0;
vector<vector<square>>::iterator ite = rangesquare.begin(); 
vector<square> vtemp = *ite;
while(ite!=rangesquare.end())
{
vtemp = *ite;
{
for(vector<square>::iterator k=vtemp.begin();k!=vtemp.end();k++)
if(abs(it->squ1.y-k->squ1.y)<7)//////////////????
{
square square2;
square2.squ1=it->squ1;
square2.squ2=it->squ2;
vtemp.insert(vtemp.begin(),square2);/////
vtemp.swap(rangesquare.at(temp));
flagtemp=1;
break;
}
if(flagtemp==1)
break;
ite++;
temp++;
continue;
}
}
{
if(flagtemp==1)
continue;
tempuse1.clear();
square square2;
square2.squ1=it->squ1;
square2.squ2=it->squ2;
tempuse1.push_back(square2);
rangesquare.push_back(tempuse1);
}
}

}
void firstwo_mser_location(Mat gray,vector<square> &v1,vector<square> &v2)
{
MSER ms(10,100,1000,0.25,0.2,200,1.01,0.003,5);
vector<vector<Point>> regions;
ms(gray, regions, Mat()); 
MSER ms1(3,100,1000,0.25,0.2,200,1.01,0.003,5);
vector<vector<Point>> regions1;
ms1(gray, regions1, Mat()); 
for( vector<vector<Point> >::iterator k=regions.begin();k!=regions.end();k++)
{	
int xd=0,yd=0,xx=10000,yx=10000;//最多一千万像素
vector<Point> vtemp = *k;
for(int j=0; j<vtemp.size(); j++) 
{
Point a=vtemp.at(j);
if(a.x>xd) xd=a.x;
if(a.y>yd) yd=a.y;
if(a.x<xx) xx=a.x;
if(a.y<yx) yx=a.y;
}
/* CvPoint a3,a4;//
a3.x=xx;
a3.y=yx;
a4.x=xd;
a4.y=yd;
rectangle(gray,a3,a4,CV_RGB(255,0,0)); 
myshow(gray);//*/
if((((float)(yd-yx))/gray.rows)>0.5)//字长度太大
continue;
if(((((float)(xd-xx))/gray.cols)>0.5))//字宽度太大
continue;
if((float)(yd-yx)/(float)(xd-xx)>3||(float)(xd-xx)/(float)(yd-yx)>3)
continue;
CvPoint a1,a2;
a1.x=xx;
a1.y=yx;
a2.x=xd;
a2.y=yd;
/*rectangle(gray,a1,a2,CV_RGB(255,0,0)); //
myshow(gray);//*/
square s1;
s1.squ1=a1;
s1.squ2=a2;
v1.push_back(s1);
}
for( vector<vector<Point> >::iterator k=regions1.begin();k!=regions1.end();k++)
{	
int xd=0,yd=0,xx=10000,yx=10000;//最多一千万像素
vector<Point> vtemp = *k;
for(int j=0; j<vtemp.size(); j++) 
{
Point a=vtemp.at(j);
if(a.x>xd) xd=a.x;
if(a.y>yd) yd=a.y;
if(a.x<xx) xx=a.x;
if(a.y<yx) yx=a.y;
}
/*CvPoint a3,a4; //
a3.x=xx;
a3.y=yx;
a4.x=xd;
a4.y=yd;
rectangle(gray,a3,a4,CV_RGB(255,0,0));
myshow(gray);//*/
if((((float)(yd-yx))/gray.rows)>0.5)//字长度太大
continue;
if(((((float)(xd-xx))/gray.cols)>0.5))//字宽度太大
continue;
if((float)(yd-yx)/(float)(xd-xx)>3||(float)(xd-xx)/(float)(yd-yx)>3)
continue;
CvPoint a1,a2;
a1.x=xx;
a1.y=yx;
a2.x=xd;
a2.y=yd;
/*rectangle(gray,a1,a2,CV_RGB(255,0,0)); //
myshow(gray);//*/
square s1;
s1.squ1=a1;
s1.squ2=a2;
v2.push_back(s1);
}
}
