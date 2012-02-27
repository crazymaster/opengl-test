//-------------------------------------------------------------
// File : XLoader.h
//
// DirectX X File Loader Library
//
// Date : May. 10, 2008
// Version: 1.0
// Author : Pocol
//--------------------------------------------------------------

#ifndef _X_LOADER_H_INCLUDED_
#define _X_LOADER_H_INCLUDED_

// Disable Warning C4996
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//linux
#ifndef WIN32
#define MAX_PATH FILENAME_MAX
#endif //win32

//
// include
//
#include <iostream>
#include <cmath>
#include <vector>

//windows or other
#ifdef WIN32
	#include <windows.h>
	#include <stdio.h>
#else
	#include <cstring>
	#include <cstdio>
	#include <fstream>
	#define ZeroMemory(x,y) memset(x,0x00,y)
#endif

#include <GL/glut.h>
using namespace std;

//
// define
//
#ifndef _SAFE_DELETE
#define SafeDelete(x) { if (x) { delete x; x = NULL; } }
#endif
#ifndef _SAFE_DELETEARRAY
#define SafeDeleteArray(x) { if (x) { delete [] x; x = NULL; } }
#endif

//
// forward declarations
//
class XFace;
class XMesh;
class XMaterial;
class XModel;

//
// XVector2 struct
//
struct XVector2
{
	float x, y; 
	operator float* () { return (float*)&x; }
	operator const float*() const { return (const float*)&x; }
};

//
// XVector3 struct
//
struct XVector3
{ 
	float x, y, z; 
	operator float*() { return (float*)&x; }
	operator const float*() const { return (const float*)&x; }
};

//
// XColor struct
//
struct XColor 
{
	float r, g, b, a; 
	operator float*() { return (float*)&r; }
	operator const float*() const { return (const float*)&r; }
};

//
// XBoundingSphere struct
// 判定球
//
struct XBoundingSphere
{
	XVector3 center;
	float radius;
};

//
// XBoundingBox struct
// 判定box
//
struct XBoundingBox
{
	XVector3 min;
	XVector3 max;
};

//
// XFace class
// 面データを保持する
// このクラスは１つの面のデータを管理する
// つまり面ごとにインスタンスを作成する必要がある
//
class XFace
{
public :
	int element;
	int indexMaterial;
	int indexVertices[4];
	int indexNormals[4];
	int indexTexCoords[4];
	XFace &operator = (XFace &ob);
	XFace();	//コンストラクタ　データの初期化のみ
	void SetVertexIndex(int index[]);		//頂点インデックスをセットする（indexVertices[]）３〜４つ。三角形と四角形
	void SetNormalIndex(int index[]);		//法線インデックスをセットする（indexNormals[]）頂点と同じだけ
	void SetTexCoordIndex(int index[]);	//テクスチャ座標インデックスをセットする（indexTexCoords[]）頂点と同じだけ
};

//
// XMaterial class
// マテリアル
//
class XMaterial
{
public :
	char name[MAX_PATH];
	XColor ambient;
	XColor diffuse;
	XColor specular;
	XColor emissive;
	float power;
	char textureFileName[MAX_PATH];
	XMaterial &operator = (XMaterial &ob);
	XMaterial();
	void SetName(char *str);	//名前をセットする（name[]）
	void SetTextureFileName(char *str);	//テクスチャファイル名をセットする（textureFileName[]）
};

//
// XMesh class
// メッシュ
// メッシュデータ本体。頂点・法線・UV座標・面　を持つ
//
class XMesh
{
public :
	char name[MAX_PATH];
	int numVertices;
	int numNormals;
	int numTexCoords;
	int numFaces;
	XVector3* vertex;	//頂点
	XVector3* normal;	//法線
	XVector2* texcoord;	//UV座標
	XFace* face;		//面(上３つのインデックスの指定で表現。テクスチャは含む）
	XMesh &operator = (XMesh &ob);
	XMesh();
	int AddVertex(XVector3 &ob);	//頂点を追加する
	int AddNormal(XVector3 &ob);	//法線を追加する
	int AddTexCoord(XVector2 &ob);	//テクスチャ座標を追加する
	int AddFace(XFace &ob);		//面を追加する
	void Release();	//メモリ開放
	void SetName(char *str);	//名前をセットする（name）
};

//
// ここ自作
// Frameクラス
// フレームごとにインスタンスが必要。
//
class XFrame
{
public:
	float TransformMatrix[4][4];	//変換行列
	float OffsetMatrix[4][4];	//オフセット行列
	float CombineMatrix[4][4];	//合成行列
	float SkinningMatrix[4][4];	//スキニング行列
	char *name;	//フレーム名
	vector<XFrame*> child;	//子フレームのvector配列
	size_t index;	//フレーム番号
	XFrame(vector<XFrame*>* frame);
	void Animate(float *parent);	//合成行列の計算
};

//
// XModel class
// Xモデル
// このクラスのインスタンス１つで１つのXモデルを管理する　外からはこいつだけ使う
// メッシュ・マテリアル・判定球orBOX　を持つ。一応2つ以上のメッシュにも対応。判定球orBOXはこのモデルがギリギリ入る大きさの球とBOXのこと
// Load()で読み込み、Render()で3D空間に実体を作る(配置する、レンダリングする)
//
class XModel
{
private:
	void ComputeBoundingSphere();
	void ComputeBoundingBox();
	GLuint DisplayList;	//ディスプレイリスト

public:
	int numMeshes;
	int numMaterials;
	XMesh *mesh;			//メッシュ（頂点・法線・UV座標・面）
	XMaterial *material;		//マテリアル（反射率・テクスチャ等）
	//vector<XFrame*> Frame;	//フレームの配列(モデルの全フレームへのポインタを格納)
	XBoundingSphere sphere;	//判定球
	XBoundingBox box;		//判定box

	bool Load(char *filename);	//Xファイルをロードする ←こいつが一番がんばってる
	void Release();	//確保したメモリを解放する
	//頂点配列・VBO・ディスプレイリストなしの描画
	void Render(int index, float scale=1.0f);	//指定したメッシュをレンダリング
	void Render(float scale=1.0f);	//すべてのメッシュをレンダリングする(内部でRender()(上のやつ)を呼ぶ)
	//ディスプレイリストを使用した描画
	void SetDListRender(float scale=1.0f);	//ディスプレイリストを作る。Load()内で呼ばれる
	void DListRender();	//ディスプレイリストですべてのMeshをレンダリングする。
	//
	int AddMesh(XMesh ob);
	int AddMaterial(XMaterial ob);
	XModel();
};


/*-----------------------------------------------------------------------------------*
	Xオブジェクト
	Xファイルから読み込み、管理
 *-----------------------------------------------------------------------------------*/
class XObj{
public:
	XModel *model;
	float x, y, z;	//位置
	float ang, ax, ay, az;	//回転
	
	XObj();
	void setXModel(XModel *m);	//Xモデルの登録
	void Render();	//描画
	XVector3 center();	//判定球の中央
	float radius();	//判定球の半径
};



#endif	//　_X_LOADER_H_INCLUDED_
