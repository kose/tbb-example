// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  pipeline-data.hpp
/// @brief パイプライン： パイプラインに流すデータ構造体
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <opencv2/opencv.hpp>

///
/// パイプライン： パイプラインに流すデータ構造体
///
typedef struct {

  cv::Mat image_in;             ///< 入力画像
  cv::Mat image_edge;           ///< エッジ画像

} PipelinedData;

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///
