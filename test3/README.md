make方法
========

	Windows : $ make
	Linux : $ make linux

注意
====

Linux上で

	OpenGL Warning: XGetVisualInfo returned 0 visuals for …

というメッセージが出た後に、セグメンテーションフォルトが発生して動かない場合は、
.bashrc に

	export LIBGL_ALWAYS_INDIRECT=1

を追加してください。

