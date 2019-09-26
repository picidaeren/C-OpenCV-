# C++11 OpenCV3.0
C++ 基于 OpenCV 实现实时监控和运动检测记录

需要opencv3.0的支持，在opencv4.1.0中很多宏函数已经改变

vs2019配置完成可实现实时监控和运动检测记录

使用 C++ 和 OpenCV 提供的库函数，实现摄像头的实时监控功能，并通过监控画面的运动检测选择是否记录视频。监控人员可选择输出图像的模式以更容易的分辨监控中的异常情况。


processCamera 负责完成主要功能，包括监控数据的获取和处理。


程序中 OpenCV 中提供的几个 API：
CvCapture* cvCaptureFromCAM(int device): 此函数捕获指定设备的数据并返回一个 cvCapture 类型指针，捕获失败时返回 NULL。

cvCreateFileCapture(char * filepath): 从本地视频读入。

CvVideoWriter * cvCreateVideoWriter(char * filepath, , fps, size, is_color): 新建一个视频写入对象，返回其指针，filepath指定写入视频的路径，fps指定写入视频的帧速，size指定写入视频的像素大小，is_color仅在windows下有效，指定写入是否为彩色。

double cvGetCaptureProperty(CvCapture* capture, int property_id): 获取一个视频流的某个特性，property_id指定要获取的特性名称。

IplImage* cvQueryFrame(CvCapture* capture): 从视频流获取帧。

void cvCvtColor(const CvArr* src, CvArr* dst, int code): 按code指定的模式将src指向的帧转换后写入dst指向的地址。

void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, SparseMat& hist, int dims, const int* histSize, const float** ranges, bool uniform, bool accumulate): 为image指向的帧计算直方图，保存在 hist 中。

void normalize(const SparseMat& src, SparseMat& dst, double alpha, int normType): 按指定模式将src正常化并写入dst中。

double compareHist(const SparseMat& H1, const SparseMat& H2, int method):按method指定的方式比较两个直方图的相似程度。

int cvWriteFrame(CvVideoWriter* writer, const IplImage* image): 向视频写入流写入一帧。成功返回 1，否则返回 0。
了解这些API的基本功能后，梳理程序执行的步骤：

程序流程：
程序开始执行，
启动摄像头并获得数据流
进入循环：
捕获一帧
是否为第一帧？
是则记录该帧作为监控区域的背景
接着捕获下列的帧
分析帧的直方图
将该帧做适当的变换，输出到监视器中
分析该帧和背景帧的相似程度
相似程度是否低于阈值且当前没有在记录视频？低于阈值开始记录。(将视频生成到本地文件)
相似程度是否低于阈值且当前已经开始记录视频？低于阈值继续记录，否则停止记录。
循环中程序的停止，通过接受外部中断响应。


