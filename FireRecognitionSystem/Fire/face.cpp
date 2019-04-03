#include "face.h"
#include "FormatConversion.h"

Face::Face()
{

}

Face::~Face()
{

}

void Face::setFaceAppID(QString appID)
{
    if(appID!=m_APPID){
        m_APPID = appID;
        emit faceAppIDChanged(m_APPID);
    }
}

void Face::setFaceKey(QString key)
{
    if(key!=m_Key){
        m_Key = key;
        emit faceKeyChanged(m_Key);
    }
}

QString Face::faceAppID()
{
    return m_APPID;
}

QString Face::faceKey()
{
    return m_Key;
}

bool Face::VerifyAirFaceOperaterKey()
{
    return m_airsoftFace.VerifyAirFaceOperaterKey(m_APPID.toLatin1().data(),m_Key.toLatin1().data());
}

bool Face::InitFaceEngine(AirFaceOperater::DetectedMode mode, AirFaceOperater::OrientPriority priority)
{
    return m_airsoftFace.InitFaceEngine(mode,priority);
}

vector<AirFaceOperater::FaceRect> Face::FaceDetection(QString path)
{
    return m_airsoftFace.FaceDetection(path.toLatin1().data());
}

vector<AirFaceOperater::FaceRect> Face::FaceDetection(Mat &img)
{
    return m_airsoftFace.FaceDetection(img);
}

vector<AirFaceOperater::FaceRect> Face::FaceDetection(QImage &img)
{
    Mat mat;
    FormatConversion format;
    mat = format.QImage2Mat(img);
    return m_airsoftFace.FaceDetection(mat);
}

float Face::FaceComparison(QString srcPath, QString dstPath, bool mutilpCompare)
{
    return m_airsoftFace.FaceComparison(srcPath.toLatin1().data(),dstPath.toLatin1().data(),mutilpCompare);
}

float Face::FaceComparison(Mat &srcImg, Mat &dstImg, bool mutilpCompare)
{
    return m_airsoftFace.FaceComparison(&srcImg,&dstImg,mutilpCompare);
}

float Face::FaceComparison(QImage &srcImg, QImage &dstImg, bool mutilpCompare)
{
    Mat srcMat,dstMat;
    FormatConversion format;
    srcMat = format.QImage2Mat(srcImg);
    dstMat = format.QImage2Mat(dstImg);
    return m_airsoftFace.FaceComparison(&srcMat,&dstMat,mutilpCompare);
}

vector<int> Face::GetAges(QString imgPath)
{
    return m_airsoftFace.GetAges(imgPath.toLatin1().data());
}

vector<int> Face::GetAges(Mat &img)
{
    return m_airsoftFace.GetAges(&img);
}

vector<int> Face::GetAges(QImage &img)
{
    Mat mat;
    FormatConversion format;
    mat = format.QImage2Mat(img);
    return m_airsoftFace.GetAges(&mat);
}

vector<int> Face::GetGender(QString imgPath)
{
    return m_airsoftFace.GetGender(imgPath.toLatin1().data());
}

vector<int> Face::GetGender(Mat &img)
{
    return m_airsoftFace.GetGender(&img);
}

vector<int> Face::GetGender(QImage &img)
{
    Mat mat;
    FormatConversion format;
    mat = format.QImage2Mat(img);
    return m_airsoftFace.GetGender(&mat);
}

vector<AirFaceOperater::FaceAngle> Face::Get3DAngle(QString imgPath)
{
    return m_airsoftFace.Get3DAngle(imgPath.toLatin1().data());
}

vector<AirFaceOperater::FaceAngle> Face::Get3DAngle(Mat &img)
{
    return m_airsoftFace.Get3DAngle(img);
}

vector<AirFaceOperater::FaceAngle> Face::Get3DAngle(QImage &img)
{
    Mat mat;
    FormatConversion format;
    mat = format.QImage2Mat(img);
    return m_airsoftFace.Get3DAngle(mat);
}

QMap<QString, QString> Face::GetFaceVersionInfo()
{
    QMap<char *,char *> map(m_airsoftFace.GetFaceVersionInfo());
    QMap<QString, QString> info;
    QMap<char *,char *>::iterator itr = map.begin();

    for(;itr!=map.end();itr++){
        QString key = itr.key();
        QString value = itr.value();
        info.insert(key,value);
    }
    return info;
}

QImage Face::CheckColor(Mat &inImg)
{
    Mat fireImg;
    fireImg.create(inImg.size(),CV_8UC1);

    int redThre = 115; // 115~135
    int saturationTh = 45; //55~65
    Mat multiRGB[3];
    int a = inImg.channels();
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

            int maxValue = max(max(B,G),R);
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

void Face::DrawFire(Mat &inputImg,Mat foreImg)
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
