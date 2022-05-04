
# Exsample of oneAPI Threading Building Blocks (oneTBB) / OpenCV.

## これは？ 
oneTBB を使った並列処理のサンプルです。

- 空間方向：フレーム内のソーベルフィルタ
- 時間方向：フレーム処理をパイプラインで並列化


## References
- [インテルopenAPIスレッディング・ビルディング・ブロック クロスアーキテクチャーの託すベースのプログラミングの最適化](https://jp.xlsoft.com/documents/intel/tbb/2021/optimize-task-based-programming-in-a-cross-architecture-world.pdf)
- [Working on the Assembly Line: parallel_pipeline](https://oneapi-src.github.io/oneTBB/main/tbb_userguide/Working_on_the_Assembly_Line_pipeline.html)
- [old TBB2020 branch](https://github.com/kose/tbb-example/tree/tbb2020)

## Environment
This implementation has been tested with oneTBB 2021.5.0 (Homebrew) / OpenCV 4.5.5-openvino-2022.1.0 on MacOS 12.3.1

