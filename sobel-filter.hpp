// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  sobel-filter.hpp
/// @brief ソーベルフィルター
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

#pragma once


///
/// TBB 並列実行用クラス: Sobel フィルター
///
class SobelFilter {

  // extern
  const cv::Mat image_in;
  mutable cv::Mat image_out; // FIXME: mutableでないといけない?

 public:

  SobelFilter(const cv::Mat& image_in, cv::Mat& image_out) :
    image_in(image_in), image_out(image_out) {}

  // Sobel フィルターの並列実行
  void operator() (const tbb::blocked_range2d<size_t>& range) const
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

private:
  // 0 〜 255 に収めるための
  inline static unsigned char limit(int x, int min, int max)
  {
    if (x >= max) return max;

    if (x <= min) return min;

    return x;
  }
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///
