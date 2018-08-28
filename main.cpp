
#include <iostream>
#include <chrono>
#include <stdint.h>
#include <bits/stdc++.h>

/* Logger */
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/* GPIO */
#include "wiringPi/wiringPi.h"
/* Image processing */
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace chrono;
using namespace cv;

/* Number of cameras on the shield */
#define CAMS_NO  4

/* Cameras switch pins */
#define GPIO_CAM12_EN       	21
#define GPIO_CAM34_EN       	26
#define GPIO_GROUP_SELECT_14	24
#define GPIO_CAM_BUSY       	7

#define GPIO_CAM56_EN			12
#define GPIO_CAM78_EN			19
#define GPIO_GROUP_SELECT_58	18

/* current camera used to capture */
int current_cam = 1;

/* Logger instance - multi-threaded */
auto console = spdlog::stdout_color_mt("");


/* Used to switch between cameras 1-4 */
static inline void select_camera(int camera)
{
    if(camera > CAMS_NO)
        camera = 1;
    else if(camera < 1)
        camera = 4;
    
    switch(camera)
    {
        case 1:	/* Select camera 1 */
        {
            digitalWrite(GPIO_GROUP_SELECT_14,	0);
            digitalWrite(GPIO_CAM12_EN,    		0);
            digitalWrite(GPIO_CAM34_EN,    		1);
            current_cam = 1;
        }break;
        
        case 2: /* Select camera 2 */
        {
            digitalWrite(GPIO_GROUP_SELECT_14,	1);
            digitalWrite(GPIO_CAM12_EN,    		0);
            digitalWrite(GPIO_CAM34_EN,    		1);
            current_cam = 2;
        }break;
        
        case 3: /* Select camera 3 */
        {
            digitalWrite(GPIO_GROUP_SELECT_14,	0);
            digitalWrite(GPIO_CAM12_EN,    		1);
            digitalWrite(GPIO_CAM34_EN,    		0);
            current_cam = 3;
        }break;
        
        case 4: /* Select camera 4 */
        {
            digitalWrite(GPIO_GROUP_SELECT_14,	1);
            digitalWrite(GPIO_CAM12_EN,    		1);
            digitalWrite(GPIO_CAM34_EN,    		0);
            current_cam = 4;
            
        }break;
        
        default: /* Throw error if camera is invalid */
        {
            cout << "Invalid camera selected! (" << camera << ")" <<  endl;
            exit(-1);
        }
    }
}

static inline void reset_cams()
{
    /* Write deaults */
    digitalWrite(GPIO_GROUP_SELECT_14, 0);
    digitalWrite(GPIO_GROUP_SELECT_58, 0);
    digitalWrite(GPIO_CAM12_EN, 1);
    digitalWrite(GPIO_CAM34_EN, 1);
    digitalWrite(GPIO_CAM56_EN, 1);
    digitalWrite(GPIO_CAM78_EN, 1);
}


int init()
{
    cout << "Initializing gpio..." << endl;
    
    /* wirepi init */
    if(wiringPiSetupGpio() != 0)
        //if(wiringPiSetupSys () != 0)
    {
        cout << "Failed to initialize GPIO pins!" << endl;
        return -1;
    }
    
    /* Config gpio pins as outputs*/
    pinMode(GPIO_CAM12_EN, OUTPUT);
    pinMode(GPIO_CAM34_EN, OUTPUT);
    pinMode(GPIO_GROUP_SELECT_14, OUTPUT);
    pinMode(GPIO_CAM_BUSY, INPUT);
    pinMode(GPIO_CAM56_EN, OUTPUT);
    pinMode(GPIO_CAM78_EN, OUTPUT);
    pinMode(GPIO_GROUP_SELECT_58, OUTPUT);
    
    /* Reset cams */
    reset_cams();
    
    /* Select first camera by default */
    select_camera(2);
    
    /* Init camera driver */
    system("sudo modprobe bcm2835-v4l2");
    system("sudo v4l2-ctl -d 0 -p 90");
    
    
    //    /* Wait 200ms for camera */
    //    auto start = steady_clock::now();
    // while(duration_cast<milliseconds>(steady_clock::now() - start).count() <= 200);
    
    
    /* Wait for camera */
    auto start = steady_clock::now();
    while(duration_cast<milliseconds>(steady_clock::now() - start).count() <= 200);
    
    // while(1)
    // {
    // 	select_camera(current_cam);
    // 	cout << "current camera: " << current_cam << endl;
    
    // 	cin.get();
    // 	current_cam++;
    // }
    
    return 0;
}

int main(int argc, char** argv)
{
    if(init() != 0)
    {
        return -1;
    }
    
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        console->error("Cannot open camera");
        return -1;
    }
    
    /* Capture resolution */
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    
    /* Create different windows for every camera */
    namedWindow("Camera_1", CV_WINDOW_AUTOSIZE);
    namedWindow("Camera_2", CV_WINDOW_AUTOSIZE);
    namedWindow("Camera_3", CV_WINDOW_AUTOSIZE);
    namedWindow("Camera_4", CV_WINDOW_AUTOSIZE);
    
    unsigned long f = 0;
    auto start = steady_clock::now();
    
    while (1)
    {
        Mat frame;
        if (!cap.read(frame))
        {
            cout << "Cannot read a frame from camera" << endl;
            continue;
        }
        
        /* Enable next camera and in the meanwhile display current frame */
        //select_camera(++current_cam);
        
        auto elapse = duration_cast<seconds>(steady_clock::now() - start).count();
        ++f;
        auto fps = elapse ? f / elapse : 0;
        if (!(elapse % 5) && fps) // print the framerate every 5s, for 1s
        {
            cout << "fps: " << fps << ", total frames: " << f
                 << " elapsed time: " << elapse << "s\n";
        }
        
        imshow( ("Camera_" + std::to_string(current_cam)) , frame);
        
        if (waitKey(30) == 27)
        {
            //cout << "Exit, fps: " << fps << endl;
            break;
        }
    }
    return 0;
}

