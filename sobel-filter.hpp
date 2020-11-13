// Copyright (C) 2018, 2020 KOSEKI Yoshinori
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

  // コンストラクター
  SobelFilter(const cv::Mat& image_in, cv::Mat& image_out);

  // デストラクタ
  virtual ~SobelFilter();

  // Sobel フィルターの並列実行
  void operator() (const tbb::blocked_range2d<size_t>& range) const;
};

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///
