#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_xy_csdn_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    cv::Mat image=cv::Mat::zeros(100,100,CV_8UC1);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
