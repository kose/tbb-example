// Copyright (C) 2018-2022 KOSEKI Yoshinori
///
/// @file  edge-detect.cpp
/// @brief 並列エッジ検出
/// @author KOSEKI Yoshinori <koseki.y@gmail.com>
///

/** @mainpage

# TBB を使った並列化のサンプル

- 空間方向：フレーム内のソーベルフィルタ
- 時間方向：フレーム処理をパイプラインで並列化

*/

#include <iostream>
#include <stdexcept>
#include <mutex>

#include <opencv2/opencv.hpp>
#include <oneapi/tbb.h>

#include "pipeline-data.hpp"
#include "pipeline-inlet.hpp"
#include "pipeline-edge.hpp"
#include "pipeline-outlet.hpp"

const static int ESC = 27;                          ///< ESCキー定義
const static std::string winName("Edge detection"); ///< ウインドウ名
const static int ntoken = 4;                        ///< 同時に実行するステージ数の上限

///
/// パイプライン定義
///
void RunPipeline(const int& runmode, const bool& pause, Canvas& canvas)
{
  oneapi::tbb::filter<void, PipelinedData*> inlet(oneapi::tbb::filter_mode::serial_in_order, Inlet(runmode, pause));
  oneapi::tbb::filter<PipelinedData*, PipelinedData*> edge(oneapi::tbb::filter_mode::parallel, Edge());
  oneapi::tbb::filter<PipelinedData*, void> outlet(oneapi::tbb::filter_mode::serial_in_order, Outlet(canvas));

  oneapi::tbb::filter<void, void> f = inlet & edge & outlet;

  oneapi::tbb::parallel_pipeline(ntoken, f);
}


///
/// メイン関数
///
int main(int argc, char *argv[])
{
  try {

    Canvas canvas;
    int runmode = 1;
    bool pause = false;
    cv::Mat image_canvas;
    int wait = 1000 / 30;         // 表示は 30fpsで。
    
    // 別スレッドでパイプライン処理を実行
    std::thread task (RunPipeline, std::ref(runmode), std::ref(pause), std::ref(canvas));

    //
    // メインループ：主スレッド
    //
    while (runmode) {
      switch (cv::waitKey(wait)) {
      case ESC:
        runmode = 0;
        break;

      case ' ':
        pause = !pause;           // トグル
        break;

      default:
        ;
      }

      {
        // std::scoped_lock lk{canvas.mutex};           // C++17
        std::lock_guard<std::mutex> lock(canvas.mutex); // C++11

        image_canvas = canvas.image.clone();
      }

      if (!image_canvas.empty()) {
        imshow(winName, image_canvas);
      }
    }

    task.join();
    
    return EXIT_SUCCESS;
  }

  // -*- error -*- //

  catch (std::bad_alloc &e) {
    std::cerr << "BAD ALLOC Exception : " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  catch (const std::exception& e) {
    std::cerr << "Error: "  << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return EXIT_FAILURE;
  }
}

/// Local Variables: ///
/// truncate-lines:t ///
/// End: ///

