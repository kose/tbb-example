// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  pipeleine-edge.hpp
/// @brief パイプライン: エッジ抽出処理
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once

#include <oneapi/tbb.h>
#include <opencv2/opencv.hpp>

#include "pipeline-data.hpp"
#include "sobel-filter.hpp"


///
/// エッジ算出処理
///
class Edge {
public:

  Edge () {}

  Container* operator()(Container* pdata) const {

    int width = pdata->image_in.cols;
    int height = pdata->image_in.rows;

    pdata->image_edge.create(height, width, CV_8UC1);
    pdata->image_edge = cv::Scalar::all(128); // FIXME: 無駄 (端をグレイにするためなのに)

    cv::Mat image_gray(height, width, CV_8UC1);
    cvtColor(pdata->image_in, image_gray, cv::COLOR_RGB2GRAY);

    // ソーベルフィルタ処理
    // TBB 並列化版ソーベルフィルタ (class SobelFilter の operator() を分割 & 並列実行)
    tbb::parallel_for (tbb::blocked_range2d<size_t>(1, image_gray.rows - 1, 1, image_gray.cols - 1),
                       SobelFilter(image_gray, pdata->image_edge), tbb::auto_partitioner());

    return pdata;
  }
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///


