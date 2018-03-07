//----------------------------------------------------------
//ファイル名  	2048.cpp
//概要			数字ゲーム
//作成日		2014/09/01
//更新日		2014/09/08
//作成者		張シン
//----------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#define MAX_Y 17
#define MAX_X 29

int dim[4][4] = {0};			//配列
int score = 0;					//スコア
int hiscore = 0;				//前10位のスコア

void setCursor(int y, int x);	//カーソル位置を設定する関数
void title();					//開始画面
void map_print();				//背景の表示
void rule_print();				//ルールの表示
void output();					//数字を出す
void dim_print();				//配列の表示
void action();					//操作
void achive(int x);				//目標達成の表示
void fuction();			//ゲームの流れ
void gameover();				//ゲームオーバーの表示


int main(void)
{			
	int playerInput;	//プレイヤーの入力を受け取る
	int end = 0;		//終了フラグ
	int i;				//カウンタ

	srand((unsigned int)time(NULL));	//現在の時間を使って乱数表を変更する

	//スタート画面の表示
	title();
	for(i = 0;i > 5; i++){
		//0.2秒ごとに2回改行
		Sleep( 200 );
		printf("\n\n");
	}

	do{
		playerInput = _getch();		//プレイヤーの入力を受け取る
		switch (playerInput){
			//ゲームのスタート
			case '1':		fuction();		break;
			//ルールの表示
			case '9':		rule_print();	break;
			//終わり
			case '0':		end = 1;		break;
			//フラグを変更する	
		}
	}while(end == 0);
		
	_getch();
	return 0;
}


/*setCursor------------------------------------------------------------------------------------st
概要：		位置を設定する
使用変数：	y	縦軸
			x	横軸
引数：		y、ｘ
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void setCursor(int y, int x)
{
	HANDLE hStdOut;	//	出力コンソールのハンドル

	//ハンドルの取得
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hStdOut == INVALID_HANDLE_VALUE){
		return;
	}
	//カーソル位置の設定
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(hStdOut, coord);
}
/*setCursor---------------------------------------------------------------------------------end*/

/*title----------------------------------------------------------------------------------------st
概要：		開始画面
使用変数：	 i
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void title()
{	
	int i;	//カウンタ	
	
	for(i = 0; i < 20; i++)	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	
		if(i % 2 == 0){
			system("cls");
			printf("\n\n");
			printf("                ■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("                ■                                          ■\n");
			printf("                ■    ○○      ○○        ○      ○○    ■\n");
			printf("                ■  ○    ○  ○    ○  ○  ○    ○    ○  ■\n");
			printf("                ■        ○  ○    ○  ○  ○    ○    ○  ■\n");
			printf("                ■      ○    ○    ○  ○  ○      ○○    ■\n");
			printf("                ■    ○      ○    ○  ○○○○  ○    ○  ■\n");
			printf("                ■  ○        ○    ○      ○    ○    ○  ■\n");
			printf("                ■  ○○○○    ○○        ○      ○○    ■\n");
			printf("                ■                                          ■\n");
			printf("                ■■■■■■■■■■■■■■■■■■■■■■■\n"); 
		}else{
			system("cls");
			printf("\n\n");
			printf("                □□□□□□□□□□□□□□□□□□□□□□□\n");
			printf("                □                                          □\n");
			printf("                □    ●●      ●●        ●      ●●    □\n");
			printf("                □  ●    ●  ●    ●  ●  ●    ●    ●  □\n");
			printf("                □        ●  ●    ●  ●  ●    ●    ●  □\n");
			printf("                □      ●    ●    ●  ●  ●      ●●    □\n");
			printf("                □    ●      ●    ●  ●●●●  ●    ●  □\n");
			printf("                □  ●        ●    ●      ●    ●    ●  □\n");
			printf("                □  ●●●●    ●●        ●      ●●    □\n");
			printf("                □                                          □\n");
			printf("                □□□□□□□□□□□□□□□□□□□□□□□\n"); 
		}
		Sleep(200);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	printf("\n\n");
	printf("                        ※※※※※※※※※※※※※※※\n");
	printf("                        ※                          ※\n");
	printf("                        ※◆     1       スタート   ※\n");
	printf("                        ※                          ※\n");
	printf("                        ※◆     9       説明       ※\n");
	printf("                        ※                          ※\n");
	printf("                        ※◆     0       エンド     ※\n");
	printf("                        ※                          ※\n");
	printf("                        ※※※※※※※※※※※※※※※\n");

}
/*title-------------------------------------------------------------------------------------end*/

/*rule_print-----------------------------------------------------------------------------------st
概要：		ルール説明
使用変数：	なし
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void rule_print()
{
	system("cls");
	printf("          ◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇\n");
	printf("          ◆                                                      ◆\n");
	printf("          ◇  ●  操作方法                                        ◇\n");
	printf("          ◆                                                      ◆\n");
	printf("          ◇      8：↑    4：←    6：→    5：↓                ◇\n");
	printf("          ◆    数字キー8、5，4，6を押すと、                      ◆\n");
	printf("          ◇ ・上下左右に空白があれば移動させることができます。   ◇\n");
	printf("          ◆ ・同じ数字同士は、重ねると足し算されて１枚のタイル   ◆\n");
	printf("          ◇   になります 。                                      ◇\n");
	printf("          ◆                                                      ◆\n");
	printf("          ◇  ●  例(図１の時、8を押すと、図２になる)             ◇\n");
	printf("          ◆      -----------------         -----------------     ◆\n");
	printf("          ◇      |   | 2 |   | 4 |         |   | 4 | 2 | 8 |     ◇\n");
	printf("          ◆      |---+---+---+---|         |---+---+---+---|     ◆\n");
	printf("          ◇      |   |   |   |   |   8     |   |   | 8 |   |     ◇\n");
	printf("          ◆      |---+---+---+---|  ＝＞   |---+---+---+---|     ◆\n");
	printf("          ◇      |   | 2 | 2 |   |         |   |   |   |   |     ◇\n");
	printf("          ◆      |---+---+---+---|         |---+---+---+---|     ◆\n");
	printf("          ◇      |   |   | 8 | 4 |         |   |   |   |   |     ◇\n");
	printf("          ◆      -----------------         ----------------      ◆\n");
	printf("          ◇         　  図１                      図２           ◇\n");
	printf("          ◆ ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
	printf("それでは、2048のタイルを目指して、スタートしましょう");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf(" ◆\n");
	printf("          ◇          ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("1: ゲームスタート");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("　　0：ゲーム終了　　　　　");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("◇\n");
	printf("          ◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆\n");

}
/*rule_print--------------------------------------------------------------------------------end*/

/*map_print------------------------------------------------------------------------------------st
概要：		背景の表示
使用変数：	map[MAX_Y][MAX_X]  iCnt_Y  iCnt_X  
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void map_print()
{
	system("cls");
	int iCnt_Y;							//縦軸のカウンタ
	int iCnt_X;							//横軸のカウンタ
	int map[MAX_Y][MAX_X] = {
		//0 1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//0
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//1
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//2
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//3
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//4
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//5
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//6
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//7
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//8
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//9
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//0
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//1
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1},//2		
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//3
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//4
		{3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3},//5
		{1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1} //6
	};

	printf(" \n");
	//黄色に変更する
	setCursor(1, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	
	for(iCnt_Y = 0; iCnt_Y < MAX_Y; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X < MAX_X; iCnt_X++){				
			switch(map[iCnt_Y][iCnt_X])	{					
				case 0:		printf("  ");		break;	//	空白							
				case 1:		printf("□");		break;	//	壁
				case 2:		printf("＝");		break;	//	壁
				case 3:		printf("Ⅱ");		break;	//	壁
			}
		}
		printf(" \n");
	}
	//白に変更する
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
	//ボタンの表示	
	setCursor(18, 10);
	printf(" __ ");		
	setCursor(19, 5 * 2);
	printf("|８|			8：↑  4：←  6：→  5：↓");
	setCursor(20, 3 * 2);
	printf(" __  --  __");
	setCursor(21, 3 * 2);
	printf("|４||５||６|		押す方向に向いて、移動する");	
	setCursor(22, 3 * 2);
	printf(" --  --  -- ");
	
	//ランキングの表示
	setCursor(5, 30 * 2);
	printf("★-★  SCORE ★-★");
	setCursor(6, 30 * 2);
	printf("｜              ｜");
	setCursor(7, 30 * 2);
	printf("★ 歴史最高点:  ★");
	setCursor(8, 30 * 2);
	printf("｜              ｜");
	setCursor(9, 30 * 2);
	printf("★              ★");
	setCursor(10, 30 * 2);
	printf("｜ 今のスコア： ｜");
	setCursor(11, 30 * 2);
	printf("★              ★");
	setCursor(12, 30 * 2);
	printf("｜              ｜");
	setCursor(13, 30 * 2);
	printf("★==============★");	

}
/*map_print---------------------------------------------------------------------------------end*/

/*output----------------------------------------------------------------------------------------st
概要：		数字をランダムに出す
使用変数：	iCnt_Y  iCnt_X   num  score 
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void output()
{
	int iCnt_X;	//配列の横軸
	int iCnt_Y;	//配列の縦軸
	int num;

	//数字をランダムに出す
	num = (rand() % 2 + 1) * 2;	

	//数値の位置をランダムに決定
	do{
		iCnt_X = rand() % 4;			//横軸
		iCnt_Y = rand() % 4;			//縦軸
	}while(dim[iCnt_Y][iCnt_X] != 0);	//決定した位置に数字があれば、もう一度選択する

	//出すの数字を配列要素に代入
	dim[iCnt_Y][iCnt_X] = num;
	
	//最高点の計算
	if(score > hiscore)	{
		hiscore = score;		
	}

	//配列の表示
	dim_print();
}
/*output------------------------------------------------------------------------------------end*/

/*dim_print------------------------------------------------------------------------------------st
概要：		配列の表示
使用変数：	dim[4][4]  iCnt_Y  iCnt_X  
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void dim_print()
{	
	int iCnt_Y;							//縦軸のカウンタ
	int iCnt_X;							//横軸のカウンタ

	//数字の表示
	printf(" \n\n");
	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		setCursor((iCnt_Y+1) * 4 - 1, 0);
		for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){	
			//黄色に戻す			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);	
			printf("Ⅱ");			
			if(dim[iCnt_Y][iCnt_X] != 0){
				//2,4を灰色で表示
				if(dim[iCnt_Y][iCnt_X] <= 4){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//8,16を白色で表示
				else if(dim[iCnt_Y][iCnt_X] <= 16){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//32,64を青色で表示
				else if(dim[iCnt_Y][iCnt_X] <= 64){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
					printf("  %4d      ", dim[iCnt_Y][iCnt_X]);
				}
				//128,256を緑で表示
				else if(dim[iCnt_Y][iCnt_X] <= 256){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//512を黄色で表示
				else if(dim[iCnt_Y][iCnt_X] = 512){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//1024を黄色で表示
				else if(dim[iCnt_Y][iCnt_X] = 1024){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
					printf("   %4d     ", dim[iCnt_Y][iCnt_X]);
				}
				//2048以上の数字を赤色で表示
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
					printf("    %4d    ", dim[iCnt_Y][iCnt_X]);
				}
			}else{
				printf("            ");
			}
		}
		//黄色に戻す
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		printf("Ⅱ\n");
	}

	//スコアの表示
	setCursor(11, 62);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("%12d", score);
	
	//最高スコアの表示
	setCursor(8, 62);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("%12d", hiscore);

	
	return ;
}
/*dim_print---------------------------------------------------------------------------------end*/

/*action---------------------------------------------------------------------------------------st
概要：		操作
使用変数：	dim[4][4] temp[4] iCnt_Y  iCnt_X  i playerInput  sw
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void action()
{
	int iCnt_Y;			//縦軸のカウンタ
	int iCnt_X;			//横軸のカウンタ
	int playerInput;	//プレイヤーの入力を受け取る
	int temp[4];		//一時的な配列
	int i;				//カウンタ
	int sw = 0;			//配列の移動フラグ(0: できない  1：できる )
	
	playerInput = _getch();		// プレイヤーの入力を受け取る

	// プレイヤーの現在地の移動と入力等を行う
	switch(playerInput)
	{
		// 数字を上に移動
		case '8':	
			//1列ずつ、移動する
			for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){								
				//一時的な配列の要素番号の初期化					
				i = 0;
				//1行ずつ、判断する
				for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){						
					//0以外の数字を一時的な配列に入れる
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i++;
					}						
				}
				//使っていない要素を0とする
				for (; i < 4; temp[i++] = 0);
				i = 0;

				//移動した列をチェックする
				//一時的な配列の数字が全部、元列に入れた時、ループから抜ける
				for(iCnt_Y = 0; iCnt_Y < 4 && i < 4; iCnt_Y++){							
					//新しい配列の値と違う場合（つまり、数字が移動した）
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//入り替え
						dim[iCnt_Y][iCnt_X] = temp[i];
						//移動できるフラグ
						sw = 1;		
					}
					//隣に同じ数字同士がある場合
					if(i < 3 && dim[iCnt_Y][iCnt_X] == temp[i + 1] && temp[i + 1] != 0 ){
						//移動しながら、足す
						dim[iCnt_Y][iCnt_X] += temp[i + 1];
						temp[i + 1] = 0;
						//同じ数字が足したら、スコアが増加する
						score = dim[iCnt_Y][iCnt_X] + score;
						//次の値をチェックする
						i++;
						//移動できるフラグ
						sw = 1;		
					}
					//前の値が同じかどうか問わず、次の値をチェックする
					i++;							
				}
				if(iCnt_Y < i){
					for(; iCnt_Y < 4; iCnt_Y++){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}					
			break;

		// 右に移動
		case '6':
			//1行ずつ、移動する
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){	
				//一時的な配列の初期化										
				i = 3;
				//1列ずつ、判断する
				for(iCnt_X = 3; iCnt_X >= 0; iCnt_X--){						
					//0以外の数字を一時的な配列に入れる
					if(dim[iCnt_Y][iCnt_X] != 0){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i--;
					}						
				}
					
				//使っていない要素を0とする
				for(; i >= 0; i--){	
					temp[i] = 0;										
				}
				i = 3;
				//移動した列をチェックする
				//一時的な配列の数字が全部、元列に入れた時、ループから抜ける
				for(iCnt_X = 3; iCnt_X >= 0 && i >= 0; iCnt_X--){							
					//新しい配列の値と違う場合（つまり、数字が移動した）
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//入り替え
						dim[iCnt_Y][iCnt_X] = temp[i];
						//移動できるフラグ
						sw = 1;		
					}
					//隣に同じ数字同士がある場合
					if(i >=0 && dim[iCnt_Y][iCnt_X] == temp[i - 1] && temp[i - 1] != 0 ){
						//移動しながら、足す
						dim[iCnt_Y][iCnt_X] += temp[i - 1];
						//同じ数字が足したら、スコアが増加する
						score = dim[iCnt_Y][iCnt_X] + score;
						//次の値をチェックする
						i--;
						//移動できるフラグ
						sw = 1;		
					}
					//前の値が同じかどうか問わず、次の値をチェックする
					i--;							
				}
				if(iCnt_X > i){
					for(; iCnt_X >= 0; iCnt_X--){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}
			break;

		// 左に移動
		case '4':
			//1行ずつ、移動する
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){	
				//一時的な配列の初期化	
				i = 0;
				//1行ずつ、判断する
				for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){						
					//0以外の数字を一時的な配列に入れる
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i++;
					}						
				}
				//使っていない要素を0とする
				for (; i < 4; temp[i++] = 0);
					
				i = 0;

				//移動した列をチェックする
				//一時的な配列の数字が全部、元列に入れた時、ループから抜ける
				for(iCnt_X = 0; iCnt_X < 4 && i < 4; iCnt_X++){							
					//新しい配列の値と違う場合（つまり、数字が移動した）
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//入り替え
						dim[iCnt_Y][iCnt_X] = temp[i];
						//移動できるフラグ
						sw = 1;		
					}
					//隣に同じ数字同士がある場合
					if(i < 3 && dim[iCnt_Y][iCnt_X] == temp[i + 1] && temp[i + 1] != 0 ){
						//移動しながら、足す
						dim[iCnt_Y][iCnt_X] += temp[i + 1];
						temp[i + 1] = 0;
						//同じ数字が足したら、スコアが増加する
						score = dim[iCnt_Y][iCnt_X] + score;
						//次の値をチェックする
						i++;
						//移動できるフラグ
						sw = 1;		
					}
					//前の値が同じかどうか問わず、次の値をチェックする
					i++;							
				}
				if(iCnt_X < i){
					for(; iCnt_X < 4; iCnt_X++){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}
			}
			break;

		// 下に移動
		case '5':
			//1列ずつ、移動する
			for(iCnt_X = 0; iCnt_X < 4; iCnt_X++){								
				//一時的な配列の要素番号の初期化					
				i = 3;
				//1行ずつ、判断する
				for(iCnt_Y = 3; iCnt_Y >= 0; iCnt_Y--){						
					//0以外の数字を一時的な配列に入れる
					if(dim[iCnt_Y][iCnt_X] != 0 ){	
						temp[i] = dim[iCnt_Y][iCnt_X];
						i--;
					}						
				}

				//使っていない要素を0とする
				for (; i >= 0; temp[i--] = 0);
					
				i = 3;
				//移動した列をチェックする
				//一時的な配列の数字が全部、元列に入れた時、ループから抜ける
				for(iCnt_Y = 3; iCnt_Y >= 0 && i >= 0; iCnt_Y--){							
					//新しい配列の値と違う場合（つまり、数字が移動した）
					if(dim[iCnt_Y][iCnt_X] != temp[i]){
						//入り替え
						dim[iCnt_Y][iCnt_X] = temp[i];
						//移動できるフラグ
						sw = 1;		
					}
					//隣に同じ数字同士がある場合
					if(i >=0 && dim[iCnt_Y][iCnt_X] == temp[i - 1] && temp[i - 1] != 0 ){
						//移動しながら、足す
						dim[iCnt_Y][iCnt_X] += temp[i - 1];
						//同じ数字が足したら、スコアが増加する
						score = dim[iCnt_Y][iCnt_X] + score;
						//次の値をチェックする
						i--;
						//移動できるフラグ
						sw = 1;		
					}
					//前の値が同じかどうか問わず、次の値をチェックする
					i--;							
				}
				if(iCnt_Y > i){
					for(; iCnt_Y >= 0; iCnt_Y--){
						dim[iCnt_Y][iCnt_X] = 0;
					}
				}				
			}					
			break;
	}
	//移動した場合、もう１つ数字を出す				
	if(sw == 1){
		output();
	}
}
/*action------------------------------------------------------------------------------------end*/

/*achive---------------------------------------------------------------------------------------st
概要：		操作
使用変数：	map[11][23]  map2048[11][23] map4096[11][23]  map8192[11][23]  iCnt_Y iCnt_X  
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void achive(int x)
{
	int iCnt_Y;			//縦軸のカウンタ
	int iCnt_X;			//横軸のカウンタ
	int i;				//カウンタ

	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
			if(x == 2048 || x == 4096 || x == 8192){
				for(i = 0; i < 20; i++){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
					if(i % 2 == 0){
						setCursor(7, 12 * 2);
						printf("☆★☆★☆★☆★☆★☆★☆★☆★☆");
						setCursor(8, 12 * 2);
						printf("★                              ★");
						setCursor(9, 12 * 2);
						printf("☆                              ☆");
						setCursor(10, 12 * 2);
						printf("★                              ★");
						setCursor(11, 12 * 2);
						printf("☆★☆★☆★☆★☆★☆★☆★☆★☆");
					}else{
						setCursor(7, 12 * 2);
						printf("★☆★☆★☆★☆★☆★☆★☆★☆★");
						setCursor(8, 12 * 2);
						printf("☆                              ☆");
						setCursor(9, 12 * 2);
						printf("★                              ★");
						setCursor(10, 12 * 2);
						printf("☆                              ☆");
						setCursor(11, 12 * 2);
						printf("★☆★☆★☆★☆★☆★☆★☆★☆★");
					}
					setCursor(9, 14 * 2);
					//点数を青で表示
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	
					printf(" %d",x);
					//文字を白で表示
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	
					printf(" 点達成！すごいですね～");
					//ストップ
					Sleep(200);
				}
				system("cls");
				//背景の表示
				map_print();
				dim_print();
			}		
		}
	}		
}
/*achive------------------------------------------------------------------------------------end*/

/*fuction--------------------------------------------------------------------------------------st
概要：		操作
使用変数：	dim[4][4] iCnt_Y iCnt_X i sw  
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void fuction()
{
	int iCnt_Y;			//縦軸のカウンタ
	int iCnt_X;			//横軸のカウンタ
	int i;				//カウンタ
	int sw;				//スイッチ

	system("cls");
	//背景の表示
	map_print();

	//配列を初期化する
	for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
		for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
			dim[iCnt_Y][iCnt_X] = 0;					
		}
	}
	//スコアを初期化する
	score = 0;

	//最初に2つの数字を出す
	for (i = 0; i < 2; output(), i++);
				
	do{
		sw = 0;		//移動できないと初期化する
		action();	//`移動しながら、計算する

		//目標達成の表示
		for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
			for(iCnt_X = 0; iCnt_X <4; iCnt_X++){	
				achive(dim[iCnt_Y][iCnt_X]);	//2048、4096，8192をチェックする				
			}
		}
		
		if (sw == 0){
			//左右の同じ数字をチェックする
			for(iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++){
				for(iCnt_X = 0; iCnt_X < 3; iCnt_X++){	
					//右に同じ数字同士がある場合
					if(dim[iCnt_Y][iCnt_X] == dim[iCnt_Y][iCnt_X + 1]){
						sw = 1;				//移動できるので,ループを続ける
						break;				//無駄な処理をなしにする
					}					
				}
			}
			//上下の同じ数字をチェックする
			for (iCnt_X = 0; iCnt_X < 4; iCnt_X++) {
				for (iCnt_Y = 0; iCnt_Y < 3; iCnt_Y++) {
					//下に同じ数字同士がある場合
					if (dim[iCnt_Y][iCnt_X] == dim[iCnt_Y + 1][iCnt_X]) {
						sw = 1;				//移動できるので,ループを続ける
						break;				//無駄な処理をなしにする
					}
				}
			}
		}		

		//空白をチェックする
		for (iCnt_Y = 0; iCnt_Y < 4; iCnt_Y++) {
			for (iCnt_X = 0; iCnt_X <4; iCnt_X++) {
				//空白がある場合
				if (dim[iCnt_Y][iCnt_X] == 0) {
					sw = 1;				//移動できるので,ループを続ける
					break;				//無駄な処理をなしにする
				}
			}
		}
	}while(sw == 1);

	//
	gameover();
	
}
/*fuction------------------------------------------------------------------------------------end*/

/*gameover--------------------------------------------------------------------------------------st
概要：		操作
使用変数：	dim[4][4] iCnt_Y iCnt_X i sw  
引数：		なし
戻り値：	なし
-----------------------------------------------------------------------------------------------*/
void gameover()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("          \n\n");
	printf("          ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("          ☆       ●●●         ●       ●      ●  ●●●●   ☆\n");
	printf("          ☆    ●       ●     ●●      ●●  ●●  ●          ☆\n");
	printf("          ☆   ●             ●  ●     ● ●● ●  ●           ☆\n");
	printf("          ☆  ●  ●●●    ●●●●    ●  ●  ●  ●●●●      ☆\n");
	printf("          ☆  ●   ●●   ●      ●   ●      ●  ●             ☆\n");
	printf("          ☆   ●● ●  ●        ●  ●      ●  ●●●●●      ☆\n");
	printf("          ☆                                                      ☆\n");
	printf("          ☆         ●●●   ●        ●  ●●●●     ●●●   ☆\n");
	printf("          ☆       ●     ●  ●      ●   ●          ●      ● ☆\n");
	printf("          ☆     ●       ●  ●    ●    ●          ●      ●  ☆\n");
	printf("          ☆    ●       ●   ●  ●     ●●●●    ●●●●     ☆\n");
	printf("          ☆    ●      ●    ●●      ●          ●   ●       ☆\n");
	printf("          ☆     ●●●       ●       ●●●●●  ●      ●     ☆\n");
	printf("          ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("          今回のスコアは");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf(" %d ", score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("点で、");

	if(score >= hiscore){
		printf("歴史最高点を取った。おめでとう！\n\n");
	}else{
		printf("歴史最高点を超えていない。残念です！！\n\n");
	}
	printf("            もう一度挑戦しますか？（");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("１: YES");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("     0 : NO");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("）\n");
}
/*gameover------------------------------------------------------------------------------------end*/
