// Copyright (C) 2018, 2020 KOSEKI Yoshinori
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

#include <opencv2/opencv.hpp>

#include "tbb/pipeline.h"
#include "tbb/compat/thread"
#include "tbb/task_scheduler_init.h"

#include "pipeline-inlet.hpp"
#include "pipeline-edge.hpp"
#include "pipeline-outlet.hpp"

const static int ESC = 27;                          ///< ESCキー定義
const static std::string winName("Edge detection"); ///< ウインドウ名
const static int n_task = 4;                        ///< 同時に実行するステージ数の上限

void RunPipeline(tbb::pipeline* p)
{
  p->run(n_task);
}

///
/// メイン関数
///
int main(int argc, char *argv[])
{
  try {
    tbb::mutex mutex_canvas;      // 排他
    cv::Mat canvas_proc;          // キャンパス:処理用
    cv::Mat canvas;               // キャンパス:表示用

    int runmode = 1;              // 動作モード 0:終了、1:通常動作、2~:リザーブ
    bool pause = false;           // ポーズ状態か？
    int wait = 1000 / 30;         // 表示は 30fpsで。

    //
    // 別スレッドでパイプライン処理を実行
    //

    // パイプライン実体
    tbb::pipeline pipe;

    // Inlet()を登録
    Inlet inlet(runmode);
    pipe.add_filter(inlet);

    // Edge()を登録
    Edge edge;
    pipe.add_filter(edge);

    // Outlet()を登録
    Outlet outlet(mutex_canvas, canvas_proc);
    pipe.add_filter(outlet);

    std::thread task(RunPipeline, &pipe);

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

      if (pause) {
        continue;
      }

      {
        tbb::mutex::scoped_lock lock(mutex_canvas);
        canvas_proc.copyTo(canvas);
      }

      if (!canvas.empty()) {
        imshow(winName, canvas);
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

