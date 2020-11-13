// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeline-outlet.hpp
/// @brief パイプライン: 出口のクラス
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// パイプライン：出口のクラス
///
class Outlet : public tbb::filter {
public:

  /// コンストラクタ
  Outlet(tbb::mutex& mutex, cv::Mat& canvas);

  /// デストラクタ
  virtual ~Outlet();

  /// 処理本体
  void* operator() (void* data);

private:
  tbb::mutex& mutex;            ///< 排他処理のための
  cv::Mat& canvas;              ///< 表示画面

};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

