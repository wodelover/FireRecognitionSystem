#ifndef FIRE_H
#define FIRE_H

#include <QObject>
#include <QImage>
#include <FormatConversion.h>
#include "opencv.hpp"
using namespace std;
using namespace cv;

/*
   此类的主要作用是用于检测图片中的火焰位置并进行标记
*/

class Fire : public QObject
{

public:
    Fire();
    QImage CheckColor(Mat &inImg);

private:
    void DrawFire(Mat &inputImg,Mat foreImg);
    FormatConversion m_f;

};

#endif // FIRE_H
