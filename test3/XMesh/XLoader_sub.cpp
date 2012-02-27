//XLoader_sub.cpp
/*-----------------------------------------------------------------------------------*
 * XLoader.cppが大きくなりすぎるため、自作部だけファイルを分けた。
 * ヘッダに記されてない関数の定義もここに移した。(GetToken()とか...)
 * このファイルはXLoader.cppの中でincludeされる。
 *-----------------------------------------------------------------------------------*/

//こっから#endifまでを省略可能（開発エディタによるが）
#if 1	//囲むため
//
// global Variables
// 静的グローバル関数(このソース内でしか使用できない)
//
static char* Pointer;
static char Token[1024];


//-------------------------------------------------------------------------------------------------
// Name : CheckToken()
// Desc : 指定された文字列とトークンをチェックする
//-------------------------------------------------------------------------------------------------
static bool CheckToken(const char* str)
{
	if ( strcmp(Token, str) == 0 )
		return true;
	else
		return false;
}

//-------------------------------------------------------------------------------------------------
// Name : GetToken()
// Desc : トークンを取得する
//-------------------------------------------------------------------------------------------------
static void GetToken()
{
	char *p = Pointer;
	char *q = Token;
	bool slash=false;

	//" ¥t¥r¥n,;¥"" じゃないとこまで移動 "//"がでてくると次の行まで飛ばす
	while ( *p != '\0' && strchr(" \t\r\n,;\"/", *p) ){
		p++;
		if( *p == '/' ){
			if( slash ){
				while( !strchr("\r\n", *p) )
					p++;
			}
			slash = !slash;
		}else{
			slash = false;
		}
	}
	
	//slashはんていがあったときは戻す
	if( slash ){ p--; slash=false; }
	
	//"{}"じゃないときは、" ¥t¥r¥n,;¥"{}"が出てくるまでqに記録
	if ( *p == '{' || *p == '}' )
		(*q++) = (*p++);
	else
		while ( *p != '\0' && !strchr(" \t\r\n,;\"{}", *p ) )
			(*q++) = (*p++);

	Pointer = p;
	*q = '\0';
}

//--------------------------------------------------------------------------------------------------
// Name : GetToken()
// Desc : トークンを取得し指定された文字列を比較を行う
//--------------------------------------------------------------------------------------------------
static bool GetToken(const char* token)
{
	GetToken();
	if ( strcmp(Token, token) != 0 )
	{
		cout << "Error : 想定トークンと読込トークンが一致しません\n";
		cout << "想定トークン：" << token << endl;
		cout << "読込トークン：" << Token << endl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------
// Name : GetFloatToken()
// Desc : トークンをfloat型に変換し取得する
//--------------------------------------------------------------------------------------------------
static float GetFloatToken()
{
	GetToken();
	return (float)atof(Token);
}

//--------------------------------------------------------------------------------------------------
// Name : GetIntToken()
// Desc : トークンをint型に変換し取得する
//--------------------------------------------------------------------------------------------------
static int GetIntToken()
{
	GetToken();
	return (int)atoi(Token);
}

//-------------------------------------------------------------------------------------------------
// Name : SkipNode()
// Desc : ノードを飛ばす
//-------------------------------------------------------------------------------------------------
static void SkipNode()
{
	while ( *Pointer != '\0' )
	{
		GetToken();
		if ( strchr(Token, '{' ) ) break;
	}
	int count = 1;
	while ( *Pointer != '\0' && count > 0 )
	{
		GetToken();
		if ( strchr(Token, '{' ) ) count++;
		else if ( strchr(Token, '}') ) count--;
	}
	if ( count > 0 )
	{
		cout << "Error : カッコが一致していません\n";
		return;
	}
}

#endif	//#if 1  囲むため

///////////////////////////////////////////////////////////////////////////////////////////////////
//こっから

//行列の初期化。引数fは4x4の行列。ただの配列
void MatrixIdentity(float f[4][4])
{
	for(int g=0; g<4; g++){
		for(int r=0; r<4; r++){
			if(g==r){
				f[g][r] = 1.0;
			}else{
				f[g][r] = 0.0;
			}
		}
	}
}

//行列の乗算。o = a * b
void kakeru(float o[4][4], float a[4][4], float b[4][4])
{
	for(int g=0; g<4; g++){
		for(int r=0; r<4; r++){
			o[g][r] = a[g][0]*b[0][r] + a[g][1]*b[1][r] +
						a[g][2]*b[2][r] + a[g][3]*b[3][r];
		}
	}
}

/*-----------------------------------------------------------------------------------*
 * XFrameクラス
 *-----------------------------------------------------------------------------------*/
//コンストラクタ
XFrame::XFrame(vector<XFrame*>* frame)
{
	index = frame->size();	//フレーム番号
	frame->push_back(this);	//フレームをベクターに追加
	
	//行列の初期化
	MatrixIdentity(TransformMatrix);
	MatrixIdentity(OffsetMatrix);
	
	//フレーム名の取得
	GetToken();
	name = new char[strlen(Token)+1];
	strcpy(name, Token);
	
	//次のトークンが"{"であると確認する
	GetToken("{");
	
	//変換行列と子フレーム読み込み
	while (*Pointer!='\0') {
		GetToken();
		if (CheckToken("}")) break;
		
		//フレームの場合、子フレームを作成 
		if ( CheckToken("Frame") ) {
			child.push_back(new XFrame(frame));
		}
		
		// 変換行列を読み込む
		else if ( CheckToken("FrameTransformMatrix") ) {
			GetToken("{");
			for(int g=0; g<4; g++)
				for(int r=0; r<4; r++)
					TransformMatrix[g][r]=GetFloatToken();
			GetToken("}");
		}
		
		// 子フレームと変換行列以外は読み飛ばす
		else {
			SkipNode();
		}
	}
}
