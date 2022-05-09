// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  pipeline-outlet.hpp
/// @brief パイプライン: 出口のクラス
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <iostream>
#include <mutex>
#include <oneapi/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// パイプライン：出口のクラス
///
class Outlet {
public:
  Outlet (Canvas& canvas) : canvas(canvas) {}


  void operator()(PipelinedData* pdata) const {

    int width = pdata->image_in.cols;
    int height = pdata->image_in.rows;

    cv::Mat result(height, width * 2, CV_8UC3);
    pdata->image_in.copyTo(result(cv::Rect(0, 0, width, height)));
    cvtColor(pdata->image_edge, result(cv::Rect(width, 0, width, height)), cv::COLOR_GRAY2RGB);

    {
      // std::scoped_lock lk{canvas.mutex};           // C++17
      std::lock_guard<std::mutex> lock(canvas.mutex); // C++11
    
      result.copyTo(canvas.image);
    }
  }

private:
  Canvas& canvas;
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

