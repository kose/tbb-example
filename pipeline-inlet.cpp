// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeline-inlet.cpp
/// @brief パイプライン：入口の処理
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#include <iostream>

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-inlet.hpp"


///
/// コンストラクタ
///
Inlet::Inlet(const int& runmode) : runmode(runmode),
  tbb::filter(tbb::filter::serial_in_order)
{
  std::cerr << "Construct: inpput" << std::endl;

  // USBカメラ
  capture.open(0);

  if (!capture.isOpened()) {
    throw std::runtime_error("Can not open USB Camera.");
  }

#if 1 // information
  cv::Mat image_in;

  capture >> image_in;

  int width = image_in.cols;
  int height = image_in.rows;

  std::cout << "inlet resolution: " << width << "x" << height << std::endl;
#endif
}



///
/// デストラクタ
///
Inlet::~Inlet()
{
  std::cerr << "Destruct: pipeline-inlet" << std::endl;
}



///
/// 処理本体：動画入力
///
void* Inlet::operator() (void*)
{
  auto* pdata = new PipelinedData;

  if (runmode == 0) {
    return nullptr;
  }

  cv::Mat image_in;

  capture >> image_in;

  // ファイルの終端処理
  if (image_in.empty()) {
    return nullptr;
  }

  pdata->image_in = image_in.clone();

  return pdata;
}

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

