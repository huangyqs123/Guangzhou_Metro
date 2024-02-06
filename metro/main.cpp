#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#define path3LenTH 8 //3号线天河客运站方向站的数目
#define path3LenPY 9
#define path1Len 15
#define path2Len 17
#define path4Len 6
#define transferCount 5
const int pathMax=17;//最长的地铁线路的长度
const int timeConsume=2;//每一站消耗的时间
const double price=0.5;//每一站的票价
int successful=0;//判断是否登陆成功
//int starting,ending;//起点，终点的下标
using namespace std;
std::string transfer[transferCount]={"公元前","客村","体育西路","万胜围","广州东站"};

//定义窗口大小的函数
void modeset(int w,int h) {
//	此函数设置窗口大小为 w*h
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = {w, h};
    SetConsoleScreenBufferSize(hOut,size);
    SMALL_RECT rc = {1,1,(short)w, (short)h};
    SetConsoleWindowInfo(hOut ,true ,&rc);
    return;
}

class Metroline
{
public:
    static void map();
    static void mapBeforeLogin();
    static void mapLogin();
    static void mapMenu();
    Metroline(string p[],int n);
    static void direct(int i,string startingStation,string endingStation,string p[],int l);
    static void hc(int i,int j,string startingStation,string endingStation,string p1[],string p2[]);
    static int search(string station, string p[]);
    static void inStation(string& sp, string& fp,string pathAll[][pathMax]);
    static void SearchLine(string path3TH[],string path3PY[],string path1[],string path2[], string path4[], string pathAll[][pathMax]);
    static void StationInfo(string path3TH[],string path3PY[],string path1[],string path2[], string path4[]);
private:
    string metro[pathMax];
};


/**
 * 退出程序
 */
void end()
{
    cout<<"               _____        _        __       __    \n"
          "              /__   \\/\\  /\\/_\\    /\\ \\ \\/\\ /\\/ _\\   \n"
          "                / /\\/ /_/ //_\\\\  /  \\/ / //_/\\ \\    \n"
          "               / / / __  /  _  \\/ /\\  / __ \\ _\\ \\   \n"
          "               \\/  \\/ /_/\\_/ \\_/\\_\\ \\/\\/  \\/ \\__/   "<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"★                       感谢您的使用！                       ★"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
}


void Metroline::map(){
    cout<<"                    广州地图路线                       "<<endl;
    cout<<"                        ○三元里                    "<<endl;
    cout<<"                        |                    "<<endl;
    cout<<"                        ○广州火车站             "<<endl;
    cout<<"                        |                                                          ○天河客运站 "<<endl;
    cout<<"                        ○越秀公园                    ●广州东站-|                /"<<endl;
    cout<<"                        |                             |          |               /"<<endl;
    cout<<"                        ○纪念堂                      ○林和西  ○体育中心      ○五山"<<endl;
    cout<<"                        |                             |        /                /"<<endl;
    cout<<"           陈家祠       |公元前  烈士陵园      杨箕   |       /                /"<<endl;
    cout<<"  长寿路○----○---○---●----○----○----○----○----●体育西路------○------○岗顶"<<endl;
    cout<<"        |        西门口 |  农讲所       东山口        |             石牌桥"<<endl;
    cout<<"    黄沙○              ○海珠广场                    ○珠江新城"<<endl;
    cout<<"        |               |                             |"<<endl;
    cout<<"    芳村○              ○市二宫                      ○赤岗塔"<<endl;
    cout<<"        |               |     晓港   中大   丽江      |"<<endl;
    cout<<"    坑口○              ○------○-----○-----○------●客村----○----○----○----○----●万胜围"<<endl;
    cout<<"        |             江南西                          |    赤岗   磨碟沙 新港东  琶州    |"<<endl;
    cout<<"    西朗○                                            ○大塘                             ○大学城北"<<endl;
    cout<<"                                                      |                                  |"<<endl;
    cout<<"                                                      ○大石                             ○大学城南"<<endl;
    cout<<"                                                      |                                  |"<<endl;
    cout<<"                                                      ○汉溪长隆----○市桥----○番禺广场 ○东涌"<<endl;
    cout<<"                                                                                         |"<<endl;
    cout<<"                                                                                         ○庆盛-----○蕉门"<<endl;
    cout<<"                                    (●为换乘站点，○为普通站点)                           "<<endl;
    //cout<<"--------------------------------------------------------------------------------------"<<endl;

}

void Metroline::mapBeforeLogin(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     ██████╗ ███████╗    ███╗   ███╗███████╗████████╗██████╗  ██████╗         |*"<<endl;
    cout<<"*|    ██╔════╝ ╚══███╔╝    ████╗ ████║██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗        |*"<<endl;
    cout<<"*|    ██║  ███╗  ███╔╝     ██╔████╔██║█████╗     ██║   ██████╔╝██║   ██║        |*"<<endl;
    cout<<"*|    ██║   ██║ ███╔╝      ██║╚██╔╝██║██╔══╝     ██║   ██╔══██╗██║   ██║        |*"<<endl;
    cout<<"*|    ╚██████╔╝███████╗    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝        |*"<<endl;
    cout<<"*|     ╚═════╝ ╚══════╝    ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝         |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                              LLL,     ,LLL                                   |*"<<endl;
    cout<<"*|                                LLL   LLL                                     |*"<<endl;
    cout<<"*|                                :LL   LL,                                     |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                         欢迎使用地铁线路查询系统                             |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             请按任意键登录                                   |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
}


void Metroline::mapLogin(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     ██████╗ ███████╗    ███╗   ███╗███████╗████████╗██████╗  ██████╗         |*"<<endl;
    cout<<"*|    ██╔════╝ ╚══███╔╝    ████╗ ████║██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗        |*"<<endl;
    cout<<"*|    ██║  ███╗  ███╔╝     ██╔████╔██║█████╗     ██║   ██████╔╝██║   ██║        |*"<<endl;
    cout<<"*|    ██║   ██║ ███╔╝      ██║╚██╔╝██║██╔══╝     ██║   ██╔══██╗██║   ██║        |*"<<endl;
    cout<<"*|    ╚██████╔╝███████╗    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝        |*"<<endl;
    cout<<"*|     ╚═════╝ ╚══════╝    ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝         |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                              LLL,     ,LLL                                   |*"<<endl;
    cout<<"*|                                LLL   LLL                                     |*"<<endl;
    cout<<"*|                                :LL   LL,                                     |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                         欢迎使用地铁线路查询系统                             |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                               1.登陆账号                                     |*"<<endl;
    cout<<"*|                               2.注册账号                                     |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
}

void Metroline::mapMenu(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     ██████╗ ███████╗    ███╗   ███╗███████╗████████╗██████╗  ██████╗         |*"<<endl;
    cout<<"*|    ██╔════╝ ╚══███╔╝    ████╗ ████║██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗        |*"<<endl;
    cout<<"*|    ██║  ███╗  ███╔╝     ██╔████╔██║█████╗     ██║   ██████╔╝██║   ██║        |*"<<endl;
    cout<<"*|    ██║   ██║ ███╔╝      ██║╚██╔╝██║██╔══╝     ██║   ██╔══██╗██║   ██║        |*"<<endl;
    cout<<"*|    ╚██████╔╝███████╗    ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝        |*"<<endl;
    cout<<"*|     ╚═════╝ ╚══════╝    ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝         |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                              LLL,     ,LLL                                   |*"<<endl;
    cout<<"*|                                LLL   LLL                                     |*"<<endl;
    cout<<"*|                                :LL   LL,                                     |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                 LLL LLL                                      |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                           欢迎使用地铁线路查询系统                           |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                              请选择你的操作 :                                |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             【1】 查看地铁图                                 |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             【2】 查询乘坐路线                               |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             【3】 查询站点信息                               |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             【4】 退出程序                                   |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<"请输入你需要的功能编号：";
}



Metroline::Metroline(string p[],int n)
{
    if(n>pathMax) throw"上溢";
    for(int i=0;i<pathMax;i++)
    {
        metro[i]=p[i];
    }
}

/*
 * 当两个站可以直达的时候
 * 输入起点的下标i，起点站的名称，终点站的名称，地铁线路，第几号线l
 */
void Metroline::direct(int i,string sp,string fp,string p[],int lineNum)
{
    //starting=i;
    int timeConsumeAll = 0;
    for(int j=0;j<pathMax;j++)
        if(fp==p[j])
        {
            cout<<"可以直达,乘坐"<<lineNum<<"号车!"<<endl;
            if(i<j)
            {
                cout<<"该路线为:"<<endl;
                for(int k=i;k<=j;k++)
                {
                    if(k!=j)
                    {
                        cout<<p[k]<<"-->>";
                        timeConsumeAll += timeConsume;
                    }
                    else cout<<p[k];
                }
                cout << endl << "耗时" << timeConsume*abs(j-i) << "分钟" << endl;
                if(abs(j-i)*price<=2)
                cout <<"票价2元" << endl;
                else
                     cout <<"票价" <<price*abs(j-i) << "元" << endl;
            }
            else
            {
                cout<<"该路线为:"<<endl;
                for(int k=i;k>=j;k--)
                {
                    if(k!=j)
                    {
                        cout<<p[k]<<"-->>";
                        timeConsumeAll += timeConsume;
                    }
                    else cout<<p[k];
                }
                cout << endl << "耗时" << timeConsume*abs(j-i) << "分钟" << endl;
                 if(abs(j-i)*price<=2)
                cout<< "票价2元" << endl;
                else
                     cout <<"票价" <<price*abs(j-i) << "元" << endl;
            }
        }
    //cout << endl << "耗时" << timeConsumeAll << "分钟" << endl;
}

/*
 * sp起点 fp终点
 * i是起点的下标，j是终点的下标，sp是起点，fp是终点，p1和p2是地铁线路
 * p1是起点线路，p2是终点线路
 */
void Metroline::hc(int i,int j,string sp,string fp,string p1[],string p2[])
{
    /**** to do list: 用BFS去搜寻 路线 ****/
    /**** 此处逻辑有问题，有可能两条线直接不止有一个共同站 ****/

    for(auto & x : transfer)//遍历换乘站点的数组
        for(int l=0;l<pathMax;l++)
            for(int l1=0;l1<pathMax;l1++)
            {
                if(x==p2[l] && x==p1[l1])
                {
                    //l和l1分别代表中转站在这两条线中的位置
                    //i和l做对比，代表p2，出发站所在线路
                    //j和l1做对比，代表p1，终点站所在线路
                    if(i<l)
                    {
                        for(int y=i;y<l;y++)
                        {
                            cout<<"经"<<p2[y]<<" ";
                        }
                        if(j<l1)
                        {
                            cout<<"在"<<x<<"转程,"<<" --*--*-- ";
                            for(int z=l1;z>j;z--)
                            {
                                cout<<"经"<<p1[z]<<" ";
                            }
                            cout<<"到"<<fp<<endl;
                        }
                        else if(j>l1)
                        {
                            cout<<"在"<<x<<"转程,"<<"   ";
                            for(int z=l1;z<j;z++)
                            {
                                cout<<"经"<<p1[z]<<" ";
                            }
                            cout<<"到"<<fp<<endl;
                        }
                        cout << "耗时" << timeConsume*(abs(l-i)+abs(l1-j)) << "分钟" << endl;
                         if((abs(l-i)+abs(l1-j))*price<=2){
                        cout << "票价2元" << endl;}
                         else
                     cout << "票价" <<price*(abs(l-i)+abs(l1-j)) << "元" << endl;
                    }
                    else if(i>l)
                    {
                        for(int y=i;y>l;y--)
                        {
                            cout<<"经"<<p2[y]<<" ";
                        }
                        if(j<l1)
                        {
                            cout<<"在"<<x<<"转程,"<<"   ";
                            for(int z=l1;z>j;z--)
                            {
                                cout<<"转"<<p1[z]<<" ";
                            }
                            cout<<"到"<<fp<<endl;
                        }
                        else if(j>l1)
                        {
                            cout<<"在"<<x<<"转程,"<<"   ";
                            for(int z=l1;z<j;z++)
                            {
                                cout<<"转"<<p1[z]<<" ";
                            }
                            cout<<"到"<<fp<<endl;
                        }
                        cout << "耗时" << timeConsume*(abs(l-i)+abs(l1-j)) << "分钟" << endl;
                        if((abs(l-i)+abs(l1-j))*price<=2)
                cout << "票价2元" << endl;
                else
                     cout << "票价" <<price*(abs(l-i)+abs(l1-j)) << "元" << endl;
                    }
                }
            }
}

/*
 * 判断地铁站是否存在线路中,返回在地图中的下标
 * station为需要查询的站点，p[]为给予的线路数组
 */
int Metroline::search(string station, string p[]){
    for(int i = 0; i < pathMax; i++){
        if(station == p[i]) return i;
    }
    return -1;
}


void Metroline::inStation(string& sp, string& fp,string pathAll[][pathMax]){
    beginSp:
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cout<<"请输入出发点：";
    cin>>sp;
    beginFp:
    cout<<"请输入终点：";
    cin>>fp;

    /*
     * 判断输入的起始站和终点站是否存在
     */
    bool flagSp = false, flagFp = false;
    for(int i = 0; i < pathMax; i++){
        if  ( flagSp ==0 && (pathAll[0][i] == sp || pathAll[1][i] == sp || pathAll[2][i] == sp || pathAll[3][i] == sp || pathAll[4][i] == sp) )
            flagSp = true;
        if ( flagFp == 0 && (pathAll[0][i] == fp || pathAll[1][i] == fp || pathAll[2][i] == fp || pathAll[3][i] == fp || pathAll[4][i] == fp) )
            flagFp = true;
    }
    if(!flagSp)
    {
        cout<<"输入的出发点有错，请重新输入：";
        goto beginSp;
    }
    if(!flagFp)
    {
        cout<<"输入的终点点有错，请重新输入："<<endl;
        goto beginFp;
    }
}

void Metroline::SearchLine(string path3TH[],string path3PY[],string path1[],string path2[], string path4[], string pathAll[][pathMax]){
    system("cls");
    Metroline::map();//打印地图
    string sp,fp;//sp为出发站，fp为终点站
    InStation:
    Metroline::inStation(sp,fp,pathAll);//鉴定输入的站点是否存在

    /*
     * 若存在则进行下列步骤：
     * 1.判断终点是在几号线，若在1号线则
     * 2.判断起点是在几号线
     * 3.判断终点和起点是否在同一号线，如果在同一号线则是说明直达
     * 4.如果不在同一号线则说明要转线，调用函数。
     * */

    /* i是sp站在所在线路数组的下标，k1是fp站所在线路数组的下标
     * splineNum是sp站所在线路在pathAll数组中的下标，fplineNum是fp站所在线路在pathAll数组中的下标
     * pathAll数组下标
     * 0 -- 1号线
     * 1 -- 2号线
     * 2 -- 3号线-天河
     * 3 -- 3号线-番禺
     * 4 -- 4号线
     */


    int i = -1, k1 = -1, splineNum = -1, fplineNum = -1;
    while(i==-1){
        i = Metroline::search(sp,pathAll[++splineNum]);
    }
    while(k1==-1){
        k1 = Metroline::search(fp,pathAll[++fplineNum]);
    }

    /**** to do:二次换乘！  ****/

    //当终点站在1号线
    if(fplineNum == 0){
        if (splineNum == 0) {
            Metroline::direct(i, sp, fp, path1, 1);//代表可以直达
        } else{//当不可以直达，遍历其他线路
            if (splineNum == 1) {
                cout << "需要换乘，转程方式为：2路转1路线" << endl;
                Metroline::hc(i, k1, sp, fp, path1, path2);
            }
            if (splineNum == 4) {
                cout << "需要换乘，转程方式：4路转1路线" << endl;
                Metroline::hc(i, k1, sp, fp, path1, path4);
            }
        }
    }

        //当终点站在3号线-天河
    else if(fplineNum == 2){
        if (splineNum == 2) {
            Metroline::direct(i, sp, fp, path3TH, 3);//代表可以直达
        } else{//当不可以直达，遍历其他线路
            if (splineNum == 0) {
                cout << "转程方式：1路转3路线" << endl;
                Metroline::hc(i, k1, sp, fp, path3TH, path1);
            }
            else if (splineNum == 3) {
                cout << "转程方式：3路转3路线" << endl;
                Metroline::hc(i, k1, sp, fp, path3TH, path3PY);
            }

        }
    }

        //当终点站在3号线-番禺
    else if(fplineNum == 3){
        if (splineNum == 3) {
            Metroline::direct(i, sp, fp, path3PY, 3);//代表可以直达
        } else{//当不可以直达，遍历其他线路
            if (splineNum == 0) {
                cout << "转程方式：1路转3路线" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path1);
            } else if (splineNum == 1) {
                cout << "转程方式：2路转3路线" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path2);
            }else if (splineNum == 2) {
                cout << "转程方式：3路转3路线" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path3TH);
            }
        }
    }

        //当终点站在2号线
    else if(fplineNum == 1){
        if (splineNum == 1) {
            Metroline::direct(i, sp, fp, path2, 2);//代表可以直达
        } else{//当不可以直达，遍历其他线路
            if (splineNum == 0) {
                cout << "需要换乘，转程方式：1路转2路线" << endl;
                Metroline::hc(i, k1, sp, fp, path2, path1);
            } else if (splineNum == 4) {
                cout << "需要换乘，转程方式：4路转2路线" << endl;
                Metroline::hc(i, k1, sp, fp, path2, path4);
            }
        }
    }

        //当终点站在4号线
    else if(fplineNum == 4){
        if (splineNum == 4) {
            Metroline::direct(i, sp, fp, path4, 4);//代表可以直达
        } else{//当不可以直达，遍历其他线路
            if (splineNum == 0) {
                cout << "转程方式：1路转4路线" << endl;
                Metroline::hc(i, k1, sp, fp, path4, path1);
            } else if (splineNum == 1) {
                cout << "转程方式：2路转4路线" << endl;
                Metroline::hc(i, k1, sp, fp, path4, path2);
            }
        }
    }

    cout<<"\n"<<"                             若继续则输入Y/y 退出输入任意键"<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;

    char t = getch();
    if(t=='y'||t=='Y')
        goto InStation;
}


/**
 * 打印注册账号的副标题
 */
void subtitle2()
{
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<" ★               输在下方输入要注册的账号以及密码（密码不得超过10位）           ★"<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;

}

int pick(char nameIn[20],char passwordIn[20])
{
    FILE*fp;
    char name[20],password[20];
    fp=fopen("id.txt","r");
    for(;!feof(fp);)//检查每一个账号与登陆的十分一致
    {
        fscanf(fp,"%s%s",name,password);
        if(strcmp(nameIn,name)==0&&strcmp(password,passwordIn)==0)
        {fclose(fp);return 1;}
    }
    fclose(fp);
    return 0;
}

void enroll(){
    subtitle2();
    FILE*fp;
    char name[20],password[20],password2[20];
    fp=fopen("id.txt","a");
    cout<<"请输入学号：";cin>>name;
    while(true) {
        cout << "请输入密码：";
        cin >> password;//需要判断第一次和第二次十分相同，不相同则要求重新输入
        cout<<"请再次输入密码（密码需一致）:";
        cin>>password2;
        if(strcmp(password,password2)==0)
        {
            fprintf(fp, "%s %s\n", name, password);
            cout<<"注册成功！欢迎使用！"<<endl;
            break;
        }
        else cout<<"两次输入密码不一致，请重新输入"<<endl;
    }
    fclose(fp);
}

void logIn()
{
    Metroline::mapLogin();
    char ifLog = getch();
    if(ifLog=='1') {
        int correct = 1, a;//判断登陆是否成功
        int attempt = 0;//尝试次数
        while (correct) {
            char name[20], password[20];
            cout << "请输入用户名：";
            scanf("%s", name);
            cout << "请输入密码：";
            scanf("%s", password);
            a = pick(name, password);
            if (a == 1) {
                printf("登陆成功！ 欢迎使用！\n");
                correct = 0;
                successful = 1;
            } else {
                cout << "用户名或者密码错误" << endl;
                attempt++;
            }//若密码或者用户名输入错误则要求重新输入
            if (attempt == 3) {
                cout << "输入用户名或者密码错误三次，自动退出程序" << endl;
                end();
            }//输入错误三次以上直接退出程序
        }
    } else if(ifLog=='2'){
        enroll();
    } else{
        end();
    }
}

void Metroline::StationInfo(string path3TH[],string path3PY[],string path1[],string path2[], string path4[]){
    Metroline::map();//打印地图
    cout<<"请输入站点名称：";
    string sta;
    cin>>sta;
    for(int i=0;i<pathMax;i++)
        if(sta==path3TH[i])
            cout<<"3号线-天河经过此站"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path3PY[i])
            cout<<"3号线-番禺经过此站"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path1[i])
            cout<<"1号线经过此站"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path2[i])
            cout<<"2号线经过此站"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path4[i])
            cout<<"4号线经过此站"<<endl;

}


/**** main函数 ****/
int main() {

    //定义窗口大小
    //modeset(100,100);

    //将地图信息录入到字符串数组中
    string path3TH[pathMax] = {"广州东站","林和西","体育西路","石牌桥","岗顶","五山","天河客运站"};
    string path3PY[pathMax] = {"体育西路","珠江新城","赤岗塔","客村","大塘","大石","汉溪长隆","市桥","番禺广场"};
    string path1[pathMax] = {"广州东站","体育中心","体育西路","杨箕","东山口","烈士陵园","农讲所","公元前","西门口","陈家祠","长寿路","黄沙","芳村","坑口","西朗"};
    string path2[pathMax] = {"三元里","广州火车站","越秀公园","纪念堂","公元前","海珠广场","市二宫","江南西","晓港","中大","丽江","客村","赤岗","磨碟沙","新港东","琶州","万胜围"};
    string path4[pathMax] = {"万胜围","大学城北","大学城南","东涌","庆盛","蕉门"};
    string pathAll[5][pathMax] = {{"广州东站", "体育中心",  "体育西路", "杨箕",  "东山口", "烈士陵园", "农讲所",  "公元前", "西门口", "陈家祠", "长寿路", "黄沙", "芳村", "坑口",  "西朗"},
                                  {"三元里",  "广州火车站", "越秀公园", "纪念堂", "公元前", "海珠广场", "市二宫",  "江南西", "晓港",  "中大",  "丽江",  "客村", "赤岗", "磨碟沙", "新港东", "琶州", "万胜围"},
                                  {"广州东站", "林和西",   "体育西路", "石牌桥", "岗顶",  "五山",   "天河客运站"},
                                  {"体育西路", "珠江新城",  "赤岗塔",  "客村",  "大塘",  "大石",   "汉溪长隆", "市桥",  "番禺广场"},
                                  {"万胜围",  "大学城北",  "大学城南", "东涌",  "庆盛",  "蕉门"}
    };

    Metroline a(path1,path1Len);//1号线
    Metroline b(path2,path2Len);//2号线
    Metroline c(path4,path4Len);//4号线
    Metroline e(path3TH,path3LenTH);//3号线-天河
    Metroline f(path3PY,path3LenPY);//3号线-番禺

    Metroline::mapBeforeLogin();
    char n = getch();
    system("cls");

    //Metroline::map();
    logIn();

    user:
    system("cls");
    Metroline::mapMenu();
    n=getch();
    while(n<'0'|| n>'4')
    {
        cout<<"你的输入有误,请重新输入"<<endl;
        n=getch();
    }
    if(n=='1'){
        system("cls");
        Metroline:: map();
        cout<<"按任意键返回主菜单"<<endl;
        getch();
        system("cls");
        goto user;
    }
    if(n=='2'){
        system("cls");
        Metroline::SearchLine(path3TH,path3PY,path1,path2,path4,pathAll);
        system("cls");
        goto user;
    }
    if(n=='3'){
        system("cls");
        Metroline::StationInfo(path3TH,path3PY,path1,path2,path4);
        cout<<"按任意键返回主菜单"<<endl;
        getch();
        system("cls");
        goto user;
    }
    if(n=='4'){
        system("cls");
        system("cls");
        system("cls");
        end();
        cout<<"按任意键退出";
        n = getch();
    }

}
