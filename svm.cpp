#include"svm_detect.h"
void svm_detect()
{
vector<float> x;
ifstream fileIn("G:\\pendetect.txt", ios::in); /* 读入支持向量，没必要读入样本的向量 */
float val = 0.0f;
while(!fileIn.eof())
{
fileIn>>val;
x.push_back(val);
}
fileIn.close();

vector<Rect> found, found_filtered;
cv::HOGDescriptor hog(cv::Size(64,64), cv::Size(16,16), cv::Size(8,8), cv::Size(8,8), 9);
hog.setSVMDetector(x);

Mat img;
img=imread("G:\\pic\\pospl\\2.jpg",0);
hog.detectMultiScale(img, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);
size_t i, j;
for( i = 0; i < found.size(); i++ )
{
Rect r = found[i];
for( j = 0; j < found.size(); j++ )
if( j != i && (r & found[j]) == r)
break;
if( j == found.size() )
found_filtered.push_back(r);
}
for( i = 0; i < found_filtered.size(); i++ )
{
Rect r = found_filtered[i];
// the HOG detector returns slightly larger rectangles than the real objects.
// so we slightly shrink the rectangles to get a nicer output.
r.x += cvRound(r.width*0.1);
r.width = cvRound(r.width*0.8);
r.y += cvRound(r.height*0.07);
r.height = cvRound(r.height*0.8);
rectangle(img, r.tl(), r.br(), cv::Scalar(255,0,0), 3);
}
imshow("people detector", img); 

}
