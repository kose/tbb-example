// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  pipeline-inlet.hpp
/// @brief パイプライン: 入口のクラス
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <chrono>

#include <oneapi/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// パイプライン：入力のクラス
///
class Inlet {
public:

  Inlet(const int& runmode, const bool& pause) :
    runmode(runmode), pause(pause)
  {
    frame_number = 0;

    capture.open(0);

    if (!capture.isOpened()) {
      throw std::runtime_error("Can not open VideoCapture: ");
    }

    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
  }
  
  Inlet(const Inlet& f) : capture(f.capture), runmode(f.runmode), pause(f.pause) {}

  PipelinedData* operator()( oneapi::tbb::flow_control& fc ) const {

    PipelinedData* pdata = new PipelinedData(frame_number++);


    capture >> pdata->image_in;

    // ポーズする
    while (pause) {
       std::this_thread::sleep_for(std::chrono::milliseconds(100));

       if (runmode == 0) {
        break;
      }
    }
    
    if (pdata->image_in.empty() || runmode == 0) {
      fc.stop();
      std::cerr << "total frame: " << frame_number << std::endl;
      return NULL;
    }
    
    return pdata;
  }
  

private:
  mutable int frame_number;
  mutable cv::VideoCapture capture;
  const int& runmode;
  const bool& pause;
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

