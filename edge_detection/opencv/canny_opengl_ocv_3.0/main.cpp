/*
 * Canny edge detection using OpenCV (CPU) with code benchmarking.
 *
 * 2016 Alexandre Lopes
 */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <time.h>
 
using namespace cv;
using namespace std;
 
int main( )
{
    struct timespec t_init_wall, t_io_wall, t_conv_wall, t_canny_wall;  
    clock_t         t_init_cpu,  t_io_cpu,  t_conv_cpu,  t_canny_cpu;
    double          t_init_ocv,  t_io_ocv,  t_conv_ocv,  t_canny_ocv;

    // calculating cpu time and wall time, using both time.h and getTickCount from opencv
    clock_gettime(CLOCK_MONOTONIC, &t_init_wall);
    t_init_cpu = clock();
    t_init_ocv = getTickCount();

    UMat src1;
    src1 = imread("../pic32mz2048ech100_07_se_1500x_5kv_15mm_no_border.png", CV_LOAD_IMAGE_COLOR).getUMat( ACCESS_READ );
    namedWindow( "Original image", CV_WINDOW_AUTOSIZE );
 
    clock_gettime(CLOCK_MONOTONIC, &t_io_wall);
    t_io_cpu = clock();
    t_io_ocv = getTickCount();

    UMat gray, edge, draw;
    cvtColor(src1, gray, CV_BGR2GRAY);
 
    clock_gettime(CLOCK_MONOTONIC, &t_conv_wall);
    t_conv_cpu = clock();
    t_conv_ocv = getTickCount();

    // edge detection
    Canny( gray, edge, 50, 150, 3);
 
    clock_gettime(CLOCK_MONOTONIC, &t_canny_wall);
    t_canny_cpu = clock();
    t_canny_ocv = getTickCount();

    // save to disk
    edge.convertTo(draw, CV_8U);
    imwrite("edges.png",  draw);

    // uncomment to display image
    //  namedWindow("image", CV_WINDOW_AUTOSIZE);
    //  imshow("image", draw);
    //  waitKey(0);                                       

    // timming
    
    cout << "Elapsed CPU time (IO)       " <<  (double)(t_io_cpu - t_init_cpu)/CLOCKS_PER_SEC << endl;
    cout << "Elapsed CPU time (Convert)  " <<  (double)(t_conv_cpu - t_io_cpu)/CLOCKS_PER_SEC << endl;
    cout << "Elapsed CPU time (Canny)    " <<  (double)(t_canny_cpu - t_conv_cpu)/CLOCKS_PER_SEC <<  endl;


    cout << "Elapsed wall time (IO)      " <<  (t_io_wall.tv_sec  - t_init_wall.tv_sec)
                                             +(t_io_wall.tv_nsec - t_init_wall.tv_nsec)/1000000000.0 << endl;

    cout << "Elapsed wall time (Convert) " <<  (t_conv_wall.tv_sec  - t_io_wall.tv_sec)
                                             +(t_conv_wall.tv_nsec  - t_io_wall.tv_nsec)/1000000000.0 << endl;

    cout << "Elapsed wall time (Canny)   "   <<  (t_canny_wall.tv_sec  - t_conv_wall.tv_sec)
                                             +(t_canny_wall.tv_nsec  - t_conv_wall.tv_nsec)/1000000000.0 << endl;

    cout << "Elapsed OCV time (IO)       " <<  (double)(t_io_ocv - t_init_ocv)/getTickFrequency() << endl;
    cout << "Elapsed OCV time (Convert)  " <<  (double)(t_conv_ocv - t_io_ocv)/getTickFrequency() << endl;
    cout << "Elapsed OCV time (Canny)    " <<  (double)(t_canny_ocv - t_conv_ocv)/getTickFrequency() <<  endl;

    return 0;
} 
