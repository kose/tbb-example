// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  pipeline-data.hpp
/// @brief パイプライン： パイプラインに流すデータ構造体
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <opencv2/opencv.hpp>


//
// パイプラインを流れるデータ
//
class Container {
public:

  Container(int frame_number) : frame_number(frame_number) {}
  
  int frame_number;
  cv::Mat image_in;             // BGR
  cv::Mat image_edge;           // monochrome
};


//
// パイプラインの出力キャンバス
//
class Canvas {
public:

  Canvas() {}
  virtual ~Canvas() {}
  
  std::mutex mutex;
  cv::Mat image_canvas;
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///
