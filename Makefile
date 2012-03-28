########################################################
# Makefile for OpenGL
# Uses GNU Make-specific extensions
# MinGW 
# GCC 4.6.2

########################################################
# Build target
#

# ターゲットファイル (生成する実行ファイル)
TARGET = a.exe
TARGET_LINUX = a.out

########################################################
# Command settings
#

# C++ Compiler
CXX = g++

# Remove command
RM = rm

########################################################
#  コンパイルオプションの設定
#

# 追加のインクルードパス
CXXFLAGS =

# リリース時のコンパイルオプション
#CXXFLAGS += -O3 -Wall

# デバッグ時のコンパイルオプション
CXXFLAGS += -g -pg -O0 -Wall

########################################################
# リンカオプションの設定
#

# 追加のライブラリ
#
LDFLAGS = -lglew32 -lfreeglut -lglu32 -lopengl32 -lwinmm -lgdi32
LDFLAGS_LINUX = -lglut -lGLU -lGL

# GUI アプリケーションをコンパイルする際のリンカオプション
#
#   真っ黒なコマンドプロンプトが出てきてイヤーンな人は、
#   以下のコメントを外してください。
#
#LDFLAGS += -mwindows

########################################################
########################################################
# コンパイルするソースファイルのあるディレクトリ
#
#   ワイルドカード (*) も使えます。
#   この例では、カレントディレクトリにある、すべてのC言語
#   ソースファイルをコンパイルします。
#
INCLUDES = . ./* # 以下、必要なだけ ./*/* ./*/*/*... を繰り返す

########################################################
# 除外するファイル
#
#   ワイルドカード (*) も使えます。
#   ここで指定されたファイルはコンパイルされません。
#   テスト用のソースファイルなどはここで指定してください。
#
EXCLUDES = ./XMesh/XLoader_sub.cpp

########################################################
# ソースファイルの検索 / 除外
#
SRC := $(wildcard $(addsuffix /*.cpp, $(INCLUDES)))
SRC := $(filter-out $(wildcard $(EXCLUDES)), $(SRC))

OBJS := $(SRC:.cpp=.o)
DEPENDS :=$(SRC:.cpp=.d)

########################################################
# サフィックスルール
#

# *.cpp ファイルから *.oファイルを生成 (コンパイル)
.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -c -o $@ $(CXXFLAGS) $<

########################################################
# make ビルドルール
#

# all: (default target)
.PHONY: all
all: $(TARGET)

# linux: linux用 *.out ファイルのビルド
.PHONY: linux
linux: $(TARGET_LINUX)
$(TARGET_LINUX): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS_LINUX) -o $@

# clean: 生成したターゲット (*.o) を削除
.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPENDS)

# ターゲットファイル: *.exe ファイルのビルド
$(TARGET): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

# ヘッダーファイルの依存関係
%.d: %.cpp
	@set -e; $(CXX) -MM $(CXXFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@
-include $(DEPENDS)
