/*************************************************************************/
/*                          Copyright Notice                             */
/* The code can not be copied or provided to other people without the    */
/* permission of Zhang Hao,otherwise intellectual property infringement  */
/* will be prosecuted.If you have any questions,please send me an email. */
/* My email is kingderzhang@foxmail.com. The final interpretation rights */
/* are interpreted by ZhangHao.                                          */
/*                  Copyright (C) ZhangHao All rights reserved           */
/*************************************************************************/

#ifndef FACE_H
#define FACE_H

// Qt header
#include "face_global.h"
#include <QObject>
#include <QMap>

// Usr header
#include "AirFaceOperater.h"
#include "FormatConversion.h"
/**********************Sample Code********************
 *  Face face;
 *  //设置SDK和秘钥
 *  face.setFaceAppID("t9rE5GHpKAcidmoMHXaeT3EMjQmLmSY1CZH7BDtAwDk");
 *  face.setFaceKey("DanYmSdF91GVPX37dKeSccYwonMcR98EqJcmppW9QmH5");
 *
 *  //验证秘钥,第一次需要联网验证,联网验证后就不需要再次验证
 *  face.VerifyAirFaceOperaterKey();
 *
 *  //初始化识别引擎
 *  face.InitFaceEngine();
 *
 *  //识别操作
 *  qDebug()<<face.GetAges("C:\\Users\\zhangh\\Desktop\\img\\1.jpg");
 *  qDebug()<<face.GetGender("C:\\Users\\zhangh\\Desktop\\img\\1.jpg");
 *  qDebug()<<face.FaceComparison("C:\\Users\\zhangh\\Desktop\\img\\1.jpg","C:\\Users\\zhangh\\Desktop\\img\\2.jpg");
 */

/**
 * @ClassName: Face
 * @Description: 本人脸API基于airsoft face2.0编写;
 * 需要配合opencv一起使用,此代码搭建的平台为Qt
 * @Autor: zhanghao kinderzhang@foxmail.com
 * @date: 2018-12-04 11:27:25
 * @Version: 1.0.0
 * @update_autor
 * @update_time
**/
class FACESHARED_EXPORT Face : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString faceAppID READ faceAppID WRITE setFaceAppID NOTIFY faceAppIDChanged)
    Q_PROPERTY(QString faceKey READ faceKey WRITE setFaceKey NOTIFY faceKeyChanged)
public:

    void DrawFire(Mat &inputImg,Mat foreImg);
    QImage CheckColor(Mat &inImg);

    Face();
    ~Face();
    /**
     * @MethodName: setFaceAppID
     * @Description: 设置认证APPID
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 13:35:38
     * @Version: 1.0.0
     * @Parma: [appID] 认证ID
    **/
    Q_INVOKABLE void setFaceAppID(QString appID);

    /**
     * @MethodName: setFaceKey
     * @Description: 设置人脸秘钥
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 13:36:38
     * @Version: 1.0.0
     * @Parma: [faceKey] 人脸对比秘钥
    **/
    Q_INVOKABLE void setFaceKey(QString key);

    Q_INVOKABLE QString faceAppID();
    Q_INVOKABLE QString faceKey();

    /**
     * @MethodName: VerifyAirFaceOperaterKey
     * @Description: 验证人脸比对秘钥
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 13:59:18
     * @Version: 1.0.0
     * @update_autor
     * @update_time
     * @Return: [bool]
    **/
    Q_INVOKABLE bool VerifyAirFaceOperaterKey();

    /**
     * @MethodName: InitFaceEngine
     * @Description: 初始化人脸操作引擎
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 14:57:55
     * @Version: 1.0.0
     * @Parma: [DetectedMode] 设置检测模式,图片或者视频流
     * @Parma: [OrientPriority] 设置检测角度优先级
    **/
    Q_INVOKABLE bool InitFaceEngine(AirFaceOperater::DetectedMode mode = AirFaceOperater::DetectedMode::Image,AirFaceOperater::OrientPriority priority = AirFaceOperater::OrientPriority::OP_0_ONLY);

    /**
     * @MethodName: FaceDetection
     * @Description: 人脸检测,返回检测到的人脸信息
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-05 10:39:56
     * @Version: 1.0.0
     * @Parma: [img] OpenCv Mat
     * @Return [vector<FaceRect>] 返回人脸矩形框数组
    **/
    Q_INVOKABLE vector<AirFaceOperater::FaceRect> FaceDetection(QString path);
    /**
     * @MethodName: FaceDetection
     * @Description: 人脸检测,返回检测到的人脸信息
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-05 10:39:56
     * @Version: 1.0.0
     * @Parma: [img] OpenCv Mat
     * @Return [vector<FaceRect>] 返回人脸矩形框数组
    **/
    Q_INVOKABLE vector<AirFaceOperater::FaceRect> FaceDetection(Mat &img);
    Q_INVOKABLE vector<AirFaceOperater::FaceRect> FaceDetection(QImage &img);

    /**
     * @MethodName: FaceComparison
     * @Description: 进行人脸对比
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 15:41:40
     * @Version: 1.0.0
     * @Parma: [srcPath] 待对比图片路径
     * @Parma: [dstPath] 待检测图片路径
     * @Parma: [mutilpCompare] 是否开启识别图片中多个人脸
     * @Return: [float] 相似度
    **/
    Q_INVOKABLE float FaceComparison(QString srcPath,QString dstPath,bool mutilpCompare = false);
    /**
     * @MethodName: FaceComparison
     * @Description: 进行人脸对比
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 15:44:59
     * @Version: 1.0.0
     * @Parma: [srcImg] 待对比图片Mat
     * @Parma: [dstImg] 待检测图片Mat
     * @Parma: [mutilpCompare] 是否开启识别图片中多个人脸
     * @Return: [float] 相似度
    **/
    Q_INVOKABLE float FaceComparison(Mat &srcImg, Mat &dstImg,bool mutilpCompare = false);
    Q_INVOKABLE float FaceComparison(QImage &srcImg,QImage &dstImg,bool mutilpCompare = false);

    /**
     * @MethodName: GetAges
     * @Description: 获取图像中的人年龄
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [imgPath] 图片路径
    **/
    Q_INVOKABLE vector<int> GetAges(QString imgPath);
    /**
     * @MethodName: GetAges
     * @Description: 获取图像中的人年龄
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [img] 图片
    **/
    Q_INVOKABLE vector<int> GetAges(Mat &img);
    Q_INVOKABLE vector<int> GetAges(QImage &img);

    /**
     * @MethodName: GetGender
     * @Description: 获取图像中的人性别(0->男,1->女)
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [imgPath] 图片路径
    **/
    Q_INVOKABLE vector<int> GetGender(QString imgPath);
    /**
     * @MethodName: GetGender
     * @Description: 获取图像中的人性别(0->男,1->女)
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [img] 图片
    **/
    Q_INVOKABLE vector<int> GetGender(Mat &img);
    Q_INVOKABLE vector<int> GetGender(QImage &img);

    /**
     * @MethodName: Get3DAngle
     * @Description: 获取图像中的人脸的3D角度
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [imgPath] 图片路径
    **/
    Q_INVOKABLE vector<AirFaceOperater::FaceAngle> Get3DAngle(QString imgPath);
    /**
     * @MethodName: Get3DAngle
     * @Description: 获取图像中的人脸的3D角度
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 16:58:27
     * @Version: 1.0.0
     * @Parma: [img] 图片
    **/
    Q_INVOKABLE vector<AirFaceOperater::FaceAngle> Get3DAngle(Mat &img);
    Q_INVOKABLE vector<AirFaceOperater::FaceAngle> Get3DAngle(QImage &img);

    /**
     * @MethodName: GetFaceVersionInfo
     * @Description: 获取人脸识别库的信息
     * @Autor: ZhangHao kinderzhang@foxmail.com
     * @date: 2018-12-04 15:21:15
     * @Version: 1.0.0
     * @Return: [QMap<QString, QString>] 信息名，信息值
    **/
    Q_INVOKABLE QMap<QString, QString> GetFaceVersionInfo();

signals:
    void faceAppIDChanged(QString appID);
    void faceKeyChanged(QString key);

private:
    QString m_APPID;  //APP ID
    QString m_Key;    //秘钥
    AirFaceOperater m_airsoftFace;
    FormatConversion m_f;
};

#endif // FACE_H
