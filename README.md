test3
=====

OpenGLのテストプログラム

Windows、Ubuntuで動作確認

install方法
-----------

	$ make

### 注意

Linux上で

	OpenGL Warning: XGetVisualInfo returned 0 visuals for …

というメッセージが出た後に、セグメンテーションフォルトが発生して動かない場合は、
~/.bashrc に

	export LIBGL_ALWAYS_INDIRECT=1

を追加してください。

操作方法
--------

- ← : 左に移動
- → : 右に移動
- ↑ : 前に移動
- ↓ : 後に移動
- h,l : カメラ横回転
- j,k : カメラ縦回転
- u,i : カメラ距離調整
- z,x : モデル回転

