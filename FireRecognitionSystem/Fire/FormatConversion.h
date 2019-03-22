/*************************************************************************/
/*                          Copyright Notice                             */
/* The code can not be copied or provided to other people without the    */
/* permission of Zhang Hao,otherwise intellectual property infringement  */
/* will be prosecuted.If you have any questions,please send me an email. */
/* My email is kingderzhang@foxmail.com. The final interpretation rights */
/* are interpreted by ZhangHao.                                          */
/*                  Copyright (C) ZhangHao All rights reserved           */
/*************************************************************************/

#ifndef FORMATCONVERSION_H
#define FORMATCONVERSION_H

#include <QImage>
#include <opencv.hpp>
#include <opencv2/core.hpp>

/**
 * @ClassName: FormatConversion
 * @Description: QImage和Mat之间的格式转换
 * @Autor: zhanghao kinderzhang@foxmail.com
 * @date: 2018-12-05 13:38:43
 * @Version: 1.0.0
 * @update_autor
 * @update_time
**/
class FormatConversion
{
public:

    cv::Mat QImage2Mat(QImage image);

    QImage Mat2QImage(cv::Mat mat);

};

#endif // FORMATCONVERSION_H
