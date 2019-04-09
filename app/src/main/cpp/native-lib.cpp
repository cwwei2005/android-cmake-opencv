#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C" JNIEXPORT jstring



JNICALL
Java_com_example_xy_csdn_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {

//    cv::Mat image = cv::Mat::zeros(100,100,CV_8UC1);

    Mat src = imread("Infrared_20190409_144423.jpg");
    Mat dst;
    medianBlur(src,dst,3);
    imwrite("med.jpg",dst);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



JNIEXPORT jintArray JNICALL Java_com_example_xy_csdn_MainActivity_gray(
        JNIEnv *env, jclass obj, jintArray buf, int w, int h) {

    jint *cbuf = (env)->GetIntArrayElements(buf, JNI_FALSE);
    if (cbuf == NULL) {
        return 0;
    }

    Mat imgData(h, w, CV_8UC4, (unsigned char *) cbuf);

    uchar *ptr = imgData.ptr(0);
    for (int i = 0; i < w * h; i++) {
        //计算公式：Y(亮度) = 0.299*R + 0.587*G + 0.114*B
        //对于一个int四字节，其彩色值存储方式为：BGRA
        int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
                               ptr[4 * i + 0] * 0.114);
        ptr[4 * i + 1] = grayScale;
        ptr[4 * i + 2] = grayScale;
        ptr[4 * i + 0] = grayScale;
    }

    int size = w * h;
    jintArray result = (env)->NewIntArray(size);
    (env)->SetIntArrayRegion(result, 0, size, cbuf);
    (env)->ReleaseIntArrayElements(buf, cbuf, 0);
    return result;
}

//extern "C"
//JNIEXPORT jintArray JNICALL
//Java_com_example_xy_csdn_MainActivity_getGray(JNIEnv *env, jobject instance, jintArray buf_,
//                                                jint w, jint h) {
//    jint *buf = env->GetIntArrayElements(buf_, NULL);
//
//    if (buf == NULL)return 0;
//    Mat imgData(h, w, CV_8UC4, (unsigned char *) buf);//创建Mat矩阵对象
//
//    uchar *ptr = imgData.ptr(0);
//    for (int i = 0; i < w * h; i++) {
//        //计算公式：Y(亮度) = 0.299*R + 0.587*G + 0.114*B
//        //对于一个int四字节，其彩色值存储方式为：BGRA,注意这是opencv对像素的存储
//        int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
//                               ptr[4 * i + 0] * 0.114);
//        ptr[4 * i + 1] = grayScale;
//        ptr[4 * i + 2] = grayScale;
//        ptr[4 * i + 0] = grayScale;
//    }
//    int size = w * h;
//    jintArray result = env->NewIntArray(size);
//    env->SetIntArrayRegion(result, 0, size, buf);
//    env->ReleaseIntArrayElements(buf_, buf, 0);
//    return result;
//}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_xy_csdn_MainActivity_getGray(JNIEnv *env, jobject instance, jintArray buf_, jint w, jint h) {
    jint *buf = env->GetIntArrayElements(buf_, NULL);

    if (buf == NULL)return 0;
    Mat imgData(h, w, CV_8UC4, (unsigned char *) buf);//创建Mat矩阵对象

    uchar *ptr = imgData.ptr(0);
    for (int i = 0; i < w * h; i++) {
        //计算公式：Y(亮度) = 0.299*R + 0.587*G + 0.114*B
        //对于一个int四字节，其彩色值存储方式为：BGRA,注意这是opencv对像素的存储
        int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
                               ptr[4 * i + 0] * 0.114);
        ptr[4 * i + 1] = static_cast<uchar>(grayScale);
        ptr[4 * i + 2] = static_cast<uchar>(grayScale);
        ptr[4 * i + 0] = static_cast<uchar>(grayScale);
    }
    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, buf);
    env->ReleaseIntArrayElements(buf_, buf, 0);
    return result;



//    jint *cbuf = (env)->GetIntArrayElements(buf_, JNI_FALSE);
//    if (cbuf == NULL) {
//        return 0;
//    }
//
//    Mat imgData(h, w, CV_8UC4, (unsigned char *) cbuf);
//
//    uchar *ptr = imgData.ptr(0);
//    for (int i = 0; i < w * h; i++) {
//        //计算公式：Y(亮度) = 0.299*R + 0.587*G + 0.114*B
//        //对于一个int四字节，其彩色值存储方式为：BGRA
//        int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
//                               ptr[4 * i + 0] * 0.114);
//        ptr[4 * i + 1] = grayScale;
//        ptr[4 * i + 2] = grayScale;
//        ptr[4 * i + 0] = grayScale;
//    }
//
//    int size = w * h;
//    jintArray result = (env)->NewIntArray(size);
//    (env)->SetIntArrayRegion(result, 0, size, cbuf);
//    (env)->ReleaseIntArrayElements(buf_, cbuf, 0);
//    return result;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_xy_csdn_MainActivity_blurImage(JNIEnv *env, jobject instance, jintArray pixels_,
                                                jint w, jint h) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);
    Mat img(h, w, CV_8UC4, pixels);
    medianBlur(img,img,31);
    int size = w * h;
    jintArray array = env->NewIntArray(size);
    env->SetIntArrayRegion(array, 0, size, pixels);
    env->ReleaseIntArrayElements(pixels_, pixels, 0);
    return array;
}