#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
 
#define high 25 //画布高
#define width 60 //画布宽
#define border -1 //边界
#define blank 0 //空白
#define plane 1 //飞机
#define bullet 2 //子弹
#define enemy 3 //敌机
#define destroy 4 //摧毁标记
 
int canvas[high+2][width+2]; //游戏场景的高和宽
int pos_h, pos_w; //飞机位置
int enemynum; //敌机数量
int interval; //同个计次来模拟时间间隔
int itv_move; //敌机移动的时间间隔
int itv_new; //敌机刷新的时间间隔
int score; //分数
int IsOver; //判断游戏是否结束
 
void Startup(); //游戏数值初始化
void Show(); //游戏界面输出
void UpdateInput(); //与输入无关的游戏状态更新
void UpdateNormal(); //因输入导致的游戏状态更新
void gotoxy(int x,int y){ //回调光标
 COORD pos;
 pos.X=x-1;
 pos.Y=y-1;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void HideCursor(){ //隐藏光标函数
 CONSOLE_CURSOR_INFO cursor;
 cursor.bVisible = FALSE;
 cursor.dwSize = sizeof(cursor);
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorInfo(handle, &cursor);
}
 
int main(){
 Startup(); //初始化
 while(IsOver){ //游戏循环
 UpdateInput();
 UpdateNormal();
 
 Show();
 }
 printf("\t\tgame over!\n");
 Sleep(2500); //暂停游戏结束界面（毫秒）
 system("pause");
 return 0;
}
void Startup(){ //游戏数值初始化
 IsOver=1;
 score=0; //初始化分数
 for(int i=0;i<high+2;i++){ //初始化画布
 for(int j=0;j<width+2;j++){
 if(i==0 || i==high+1 ||
 j==0 || j==width+1){
 canvas[i][j]=border;
 }
 else canvas[i][j]=blank;
 }
 }
 pos_h=high/2; //初始化飞机竖直坐标
 pos_w=width/2; //初始化飞机水平坐标
 canvas[pos_h][pos_w]=plane; //初始化飞机位置
 enemynum=3; //敌机数量
 srand(time(NULL));
 interval=4; //初始化时间间隔计数
 itv_move=5; //初始化敌机移动时间间隔
 itv_new =40; //初始化敌机刷新时间间隔
}
void Show(){ //游戏界面输出
 HideCursor(); //隐藏光标
 gotoxy(1,1); //回调光标、刷新画面
 for(int i=0;i<high+2;i++){
 for(int j=0;j<width+2;j++){
 if( canvas[i][j] == plane ){ //当前位置为飞机位置
 printf("*");
 }
 else if( canvas[i][j] == bullet ){ //当前位置为子弹位置
 printf("|");
 }
 else if( canvas[i][j] == enemy ){ //当前位置为敌机位置
 printf("@");
 }
 else if( canvas[i][j] == border ){ //当前位置为边界
 printf("#");
 }
 else if( canvas[i][j] == blank ){ //当前位置无物，且在边界内
 printf(" ");
 }
 else if( canvas[i][j] == destroy ){ //当前位置无物，且在边界内
 printf("x");
 }
 }
 printf("\n");
 }
 printf("\n得分：%d",score);
}
void UpdateInput(){ //与输入无关的游戏状态更新
 char key_W=GetKeyState('W'), //监测 W 键是否按下
 key_S=GetKeyState('S'), //监测 S 键是否按下
 key_A=GetKeyState('A'), //监测 A 键是否按下
 key_D=GetKeyState('D'), //监测 D 键是否按下
 key_attack=GetKeyState(' '); //监测 空格 键是否按下
 if(kbhit()){ //当有键按下时
 if(key_W<0){ //当按下 W 键，上移
 if(pos_h>1){
 canvas[pos_h][pos_w]=blank;
 if(canvas[pos_h-1][pos_w] == enemy){ //下个位置是敌机，撞毁
 canvas[pos_h-1][pos_w]= destroy;
 IsOver=0;
 }
 else canvas[--pos_h][pos_w]=plane;
 }
 }
 if(key_S<0){ //当按下 S 键，下移
 if(pos_h<high){
 canvas[pos_h][pos_w]=blank;
 if(canvas[pos_h+1][pos_w] == enemy){ //下个位置是敌机，撞毁
 canvas[pos_h+1][pos_w]= destroy;
 IsOver=0;
 }
 else canvas[++pos_h][pos_w]=plane;
 }
 }
 if(key_A<0){ //当按下 A 键，左移
 if(pos_w>1){
 canvas[pos_h][pos_w]=blank;
 if(canvas[pos_h][pos_w-1] == enemy){ //下个位置是敌机，撞毁
 canvas[pos_h][pos_w-1]= destroy;
 IsOver=0;
 }
 else canvas[pos_h][--pos_w]=plane;
 }
 }
 if(key_D<0){ //当按下 D 键，右移
 if(pos_w<width){
 canvas[pos_h][pos_w]=blank;
 if(canvas[pos_h][pos_w+1] == enemy){ //下个位置是敌机，撞毁
 canvas[pos_h][pos_w+1]= destroy;
 IsOver=0;
 }
 else canvas[pos_h][++pos_w]=plane;
 }
 }
 if(key_attack<0){ //当按下空格键，发射子弹
 if(pos_h!=1)canvas[pos_h-1][pos_w]=bullet;
 }
 }
}
void UpdateNormal(){ //因输入导致的游戏状态更新
 int temp[high+2][width+2]; //用来判断原位置的临时数组
 for(int i=1;i<=high;i++){
 for(int j=1;j<=width;j++){
 temp[i][j]=canvas[i][j];
 }
 }
 for(int i=1;i<=high;i++){ //遍历临时数组，修改画布
 for(int j=1;j<=width;j++){
 if(temp[i][j]==enemy && interval%itv_move==0){ //当前位置为敌机
 canvas[i][j]=blank;
 if(temp[i+1][j]==bullet){ //下面为子弹，敌机被击中
 canvas[i+1][j]=blank;
 score++;
 printf("\a"); //击中音效
 }
 else if(i<high){
 canvas[i+1][j]=enemy;
 }
 if(i+1==pos_h&&j==pos_w){ //下面为飞机，玩家飞机被撞毁
 canvas[i+1][j]=destroy;
 IsOver=0;
 }
 }
 if(temp[i][j]==bullet){ //当前位置为子弹
 canvas[i][j]=blank;
 if(temp[i-1][j]==enemy){ //下个位置是敌机，敌机被击毁
 canvas[i-1][j]=blank;
 score++;
 printf("\a");
 }
 else if(i>1){
 canvas[i-1][j]=bullet;
 }
 }
 }
 }
 if(interval%itv_new==0) //刚好到时间间隔
 for(int i=0;i<enemynum;i++){ //新增敌机群
 canvas[rand()%2+1][rand()%width+1]=enemy;
 }
 if(interval<=100){ //时间间隔计次
 interval++;
 }
 else{ //时间间隔计次清零
 interval=0;
 }
}