// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeline-outlet.cpp
/// @brief パイプライン: 出口の処理
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#include <iostream>

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"
#include "pipeline-outlet.hpp"

extern int fps;


///
/// コンストラクタ
///
Outlet::Outlet(tbb::mutex& mutex, cv::Mat& canvas) :  mutex(mutex), canvas(canvas), 
  tbb::filter(tbb::filter::serial_in_order)
{
  std::cerr << "Construct: outlet" << std::endl;
}



///
/// デストラクタ
///
Outlet::~Outlet()
{
  std::cerr << "Destruct: pipeline-outlet" << std::endl;
}



///
/// 処理本体
///
void* Outlet::operator() (void* data)
{
  auto* pdata = static_cast<PipelinedData*>(data);

  if (pdata == nullptr) {
    return nullptr;
  }

  int width = pdata->image_in.cols;
  int height = pdata->image_in.rows;

  cv::Mat result(height, width * 2, CV_8UC3);
  pdata->image_in.copyTo(result(cv::Rect(0, 0, width, height)));
  cvtColor(pdata->image_edge, result(cv::Rect(width, 0, width, height)), cv::COLOR_GRAY2RGB);
  
  { // 結果画像書き込み
    tbb::mutex::scoped_lock lock(mutex);
    result.copyTo(canvas);
  }
  
  // パイプライン終端
  delete pdata;
  return nullptr;
}

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///
