// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeline-inlet.hpp
/// @brief パイプライン: 入口のクラス
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"


///
/// パイプライン：入力のクラス
///
class Inlet : public tbb::filter {
public:

  /// コンストラクタ
  Inlet(const int& runmode);

  /// デストラクタ
  virtual ~Inlet();

  /// 処理本体：動画ファイル力、検出
  void* operator() (void* data);

private:
  const int& runmode;           ///< 動作モード 0:終了、1:通常動作、2~:リザーブ
  cv::VideoCapture capture;     ///< ビデオ入力
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

