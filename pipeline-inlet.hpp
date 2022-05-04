// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  pipeline-inlet.hpp
/// @brief パイプライン: 入口のクラス
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <oneapi/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// パイプライン：入力のクラス
///
class Inlet {
public:

  Inlet(const int frame_number, cv::VideoCapture& capture, const int& runmode) :
    frame_number(frame_number), capture(capture), runmode(runmode) {}
  
  Inlet(const Inlet& f) : frame_number(f.frame_number), capture(f.capture), runmode(f.runmode) {}


  Container* operator()( oneapi::tbb::flow_control& fc ) const {

    Container* pdata = new Container(frame_number++);


    capture >> pdata->image_in;

    if (pdata->image_in.empty() || runmode == 0) {
      fc.stop();
      std::cerr << "::end::" << std::endl;
      return NULL;
    }
    
    return pdata;
  }
  

private:
  mutable int frame_number;
  cv::VideoCapture& capture;
  const int& runmode;
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

