#include "fire.h"


Fire::Fire()
{
}

QImage Fire::CheckColor(Mat &inImg)
{
    Mat fireImg;
    fireImg.create(inImg.size(),CV_8UC1);

    int redThre = 115; // 115~135
    int saturationTh = 45; //55~65
    Mat multiRGB[3];
    split(inImg,multiRGB); //将图片拆分成R,G,B,三通道的颜色

    for (int i = 0; i < inImg.rows; i ++)
    {
        for (int j = 0; j < inImg.cols; j ++)
        {
            float B,G,R;
            B = multiRGB[0].at<uchar>(i,j); //每个像素的R,G,B值
            G = multiRGB[1].at<uchar>(i,j);
            R = multiRGB[2].at<uchar>(i,j);

            /*B = inImg.at<uchar>(i,inImg.channels()*j + 0); //另一种调用图片中像素RGB值的方法
            G = inImg.at<uchar>(i,inImg.channels()*j + 1);
            R = inImg.at<uchar>(i,inImg.channels()*j + 2);*/

//            int maxValue = max(max(B,G),R);
            int minValue = min(min(B,G),R);

            double S = (1-3.0*minValue/(R+G+B));

            //R > RT  R>=G>=B  S>=((255-R)*ST/RT)
            if(R > redThre && R >= G && G >= B && S >0.20 && S >((255 - R) * saturationTh/redThre))
            {
                fireImg.at<uchar>(i,j) = 255;
            }
            else
            {
                fireImg.at<uchar>(i,j) = 0;
            }
        }
    }

    dilate(fireImg,fireImg,Mat(5,5,CV_8UC1));

    DrawFire(inImg,fireImg);
    QImage img = m_f.Mat2QImage(inImg);
    return img;
}

void Fire::DrawFire(Mat &inputImg,Mat foreImg)
{
    vector<vector<Point>> contours_set;//保存轮廓提取后的点集及拓扑关系

    findContours(foreImg,contours_set,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

    vector<vector<Point> >::iterator iter = contours_set.begin() ;
    for(; iter!= contours_set.end(); )
    {
        Rect rect = boundingRect(*iter );
        float radius;
        Point2f center;
        minEnclosingCircle(*iter,center,radius);

        if (rect.area()> 0)
        {

            rectangle(inputImg,rect,Scalar(0,255,0));
            ++ iter;
        }
        else
        {
            iter = contours_set.erase(iter);
        }
    }
}
