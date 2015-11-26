
#include"basic_feature.h"
void basic_feature(vector<vector<square>> &rangesquare,int *p)
{
for(vector<vector<square>>::iterator ite=rangesquare.begin();ite<rangesquare.end();ite++)
{
vector<square> vtemp=*ite;
int word_width;//宽度
ztkd( vtemp ,word_width);
p[0]=word_width;
int word_height;//高度
ztgd(vtemp,word_height);
p[1]=word_height;
int word_num;//数目,需要修改的
zfnum(vtemp,word_num,word_width);
p[2]=word_num;
int word_space;
zfspace(vtemp,word_space, word_width);
p[3]=word_space;
int tempint=0;
for(vector<square>::iterator it=vtemp.begin();it<vtemp.end();)
{
tempint++;
if(((it->squ2.x-it->squ1.x)<word_width/2)||((it->squ2.x-it->squ1.x)>2*word_width))
{
vtemp.erase(vtemp.begin()+tempint);//
continue;
}
else if(((it->squ2.y-it->squ1.y)<word_height/2)||((it->squ2.y-it->squ1.y)>2*word_height))
{
vtemp.erase(vtemp.begin()+tempint);//
continue;
}
else it++;
}
vtemp.swap(*ite);
}

}
void ztkd(vector<square> vtemp,int &word_width)
{
int num=0;
int numtemp=1;
int size=0;
int *p =new int[vtemp.size()+1];
int temp=0;
for(vector<square>::iterator k=vtemp.begin();k!=vtemp.end();k++)
{
p[temp]=k->squ2.x-k->squ1.x;
temp++;	
}
int flag=0;
for(int j=0;j<vtemp.size();j++)
{
for(int i=0;(i<vtemp.size());i++)
{
if(i==j)
continue;
if(*(p+j)==*(p+i))
{
numtemp++;
if(numtemp>vtemp.size()/2)
{
flag=1;
size=j;
break;
}

}
}
if(flag==1)
break;
if(numtemp>num)
{
num==numtemp;
size=j;	
}	
}
num=p[size];
delete p;
word_width=num;
}
void ztgd(vector<square> vtemp,int &word_height)
{
int num=0;
int numtemp=1;
int size=0;
int *p =new int[vtemp.size()+1];
int temp=0;
for(vector<square>::iterator k=vtemp.begin();k!=vtemp.end();k++)
{
p[temp]=k->squ2.y-k->squ1.y;
temp++;	
}
int flag=0;
for(int j=0;j<vtemp.size();j++)
{
for(int i=0;(i<vtemp.size());i++)
{
if(i==j)
continue;
if(*(p+j)==*(p+i))
{
numtemp++;
if(numtemp>vtemp.size()/2)
{
flag=1;
size=j;
break;
}

}
}
if(flag==1)
break;
if(numtemp>num)
{
num==numtemp;
size=j;	
}	
}
num=p[size];
delete p;
word_height=num;
}
void zfnum(vector<square> vtemp,int &word_num,int size)//字符数个数
{
int n=0;
int *q=new int[vtemp.size()+1];
int temp=0;
for(vector<square>::iterator k=vtemp.begin();k!=vtemp.end();k++)
{
q[temp]=k->squ1.x;
temp++;
}
for(int i=0;i<temp;i++)
if(q[i]!=0)
{
for(int j=i+1;j<temp;j++)
{
if(q[j]!=0)
if(abs(q[i]-q[j])<size)
q[j]=0;
}
}
for(int i=0;i<temp;i++)
{
if(q[i]!=0)
n++;
}
delete q;
word_num=n;
}
void zfspace(vector<square> vtemp,int &word_space,int size)
{
sort(vtemp.begin(),vtemp.end(),cmp);
vector<int> p;
int *q=new int[vtemp.size()+1];
int q_int=0,p_int=0;
for(vector<square>::iterator ite=vtemp.begin();ite<vtemp.end();ite++)
{
q[q_int++]=ite->squ1.x;
}
for(int i=0;i<vtemp.size();i++)
{
if(q[i+1]-q[i]>size)
p.push_back(q[i+1]-q[i]-size);
}
int sum=0;
for(int i=0;i<p.size();i++)//还是应该求频率最高的
sum+=p[i];
if(p.size()!=0)
word_space=sum/p.size();
else word_space=0;
delete q;
}
bool cmp(square s1,square s2)//排序条件
{
if(s1.squ1.x!=s2.squ1.x) return (s1.squ1.x-s2.squ1.x<0);
else return (s1.squ1.x-s2.squ1.x<0);
}
