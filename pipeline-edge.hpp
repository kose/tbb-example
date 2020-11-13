// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeleine-edge.hpp
/// @brief パイプライン: エッジ抽出処理
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// エッジ算出処理
///
class Edge : public tbb::filter {

 public:

  // コンストラクタ
  Edge();

  // デストラクタ
  virtual ~Edge();

  // 処理本体
  void* operator() (void* data);
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///


