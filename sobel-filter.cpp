// Copyright (C) 2018, 2020 KOSEKI Yoshinori
///
/// @file  sobel-filter.cpp
/// @brief ソーベルフィルター
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#include <tbb/tbb.h>
#include <opencv2/opencv.hpp>

#include "sobel-filter.hpp"

// 0 〜 255 に収めるための
inline static unsigned char limit(int x, int min, int max)
{
  if (x >= max) return max;

  if (x <= min) return min;

  return x;
}


//
// コンストラクター
//
SobelFilter::SobelFilter(const cv::Mat& image_in, cv::Mat& image_out) :
  image_in(image_in), image_out(image_out)
{
}


//
// デストラクター
//
SobelFilter::~SobelFilter()
{
}

//
// Sobel フィルターの並列実行
//
void SobelFilter::operator() (const tbb::blocked_range2d<size_t>& range) const
{
  for (size_t y = range.rows().begin(); y != range.rows().end(); y++) {
    for (size_t x = range.cols().begin(); x != range.cols().end(); x++) {
      image_out.at<unsigned char>(y, x - 1) =
        limit(128 + image_in.at<unsigned char>(y, x - 1) - image_in.at<unsigned char>(y, x + 1)
              + image_in.at<unsigned char>(y - 1, x) - image_in.at<unsigned char>(y + 1, x),
              0, 255);
    }
  }
}

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

