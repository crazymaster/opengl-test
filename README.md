opengl-test
===========

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

参考サイト
---------

- [☆PROJECT ASURA☆ [OpenGL]　『メッシュを読み込む！！(2)　～Xファイル～』](http://asura.iaigiri.com/OpenGL/gl44.html)
- [「攻殻機動隊」「電脳コイル」の世界を実現！ - ARToolKitを使った拡張現実感プログラミング - 工学ナビ](http://kougaku-navi.net/ARToolKit/index.html)
