#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#define path3LenTH 8 //3������ӿ���վ����վ����Ŀ
#define path3LenPY 9
#define path1Len 15
#define path2Len 17
#define path4Len 6
#define transferCount 5
const int pathMax=17;//��ĵ�����·�ĳ���
const int timeConsume=2;//ÿһվ���ĵ�ʱ��
const double price=0.5;//ÿһվ��Ʊ��
int successful=0;//�ж��Ƿ��½�ɹ�
//int starting,ending;//��㣬�յ���±�
using namespace std;
std::string transfer[transferCount]={"��Ԫǰ","�ʹ�","������·","��ʤΧ","���ݶ�վ"};

//���崰�ڴ�С�ĺ���
void modeset(int w,int h) {
//	�˺������ô��ڴ�СΪ w*h
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
 * �˳�����
 */
void end()
{
    cout<<"               _____        _        __       __    \n"
          "              /__   \\/\\  /\\/_\\    /\\ \\ \\/\\ /\\/ _\\   \n"
          "                / /\\/ /_/ //_\\\\  /  \\/ / //_/\\ \\    \n"
          "               / / / __  /  _  \\/ /\\  / __ \\ _\\ \\   \n"
          "               \\/  \\/ /_/\\_/ \\_/\\_\\ \\/\\/  \\/ \\__/   "<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"��                       ��л����ʹ�ã�                       ��"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
}


void Metroline::map(){
    cout<<"                    ���ݵ�ͼ·��                       "<<endl;
    cout<<"                        ����Ԫ��                    "<<endl;
    cout<<"                        |                    "<<endl;
    cout<<"                        ����ݻ�վ             "<<endl;
    cout<<"                        |                                                          ����ӿ���վ "<<endl;
    cout<<"                        ��Խ�㹫԰                    ����ݶ�վ-|                /"<<endl;
    cout<<"                        |                             |          |               /"<<endl;
    cout<<"                        �������                      ���ֺ���  ����������      ����ɽ"<<endl;
    cout<<"                        |                             |        /                /"<<endl;
    cout<<"           �¼���       |��Ԫǰ  ��ʿ��԰      ���   |       /                /"<<endl;
    cout<<"  ����·��----��---��---��----��----��----��----��----��������·------��------��ڶ�"<<endl;
    cout<<"        |        ���ſ� |  ũ����       ��ɽ��        |             ʯ����"<<endl;
    cout<<"    ��ɳ��              ����㳡                    ���齭�³�"<<endl;
    cout<<"        |               |                             |"<<endl;
    cout<<"    �����              ���ж���                      ������"<<endl;
    cout<<"        |               |     ����   �д�   ����      |"<<endl;
    cout<<"    �ӿڡ�              ��------��-----��-----��------��ʹ�----��----��----��----��----����ʤΧ"<<endl;
    cout<<"        |             ������                          |    ���   ĥ��ɳ �¸۶�  ����    |"<<endl;
    cout<<"    ���ʡ�                                            �����                             ���ѧ�Ǳ�"<<endl;
    cout<<"                                                      |                                  |"<<endl;
    cout<<"                                                      ���ʯ                             ���ѧ����"<<endl;
    cout<<"                                                      |                                  |"<<endl;
    cout<<"                                                      ��Ϫ��¡----������----��خ�㳡 ��ӿ"<<endl;
    cout<<"                                                                                         |"<<endl;
    cout<<"                                                                                         ����ʢ-----����"<<endl;
    cout<<"                                    (��Ϊ����վ�㣬��Ϊ��ͨվ��)                           "<<endl;
    //cout<<"--------------------------------------------------------------------------------------"<<endl;

}

void Metroline::mapBeforeLogin(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     �������������[ ���������������[    �������[   �������[���������������[�����������������[�������������[  �������������[         |*"<<endl;
    cout<<"*|    �����X�T�T�T�T�a �^�T�T�������X�a    ���������[ ���������U�����X�T�T�T�T�a�^�T�T�����X�T�T�a�����X�T�T�����[�����X�T�T�T�����[        |*"<<endl;
    cout<<"*|    �����U  �������[  �������X�a     �����X���������X�����U�����������[     �����U   �������������X�a�����U   �����U        |*"<<endl;
    cout<<"*|    �����U   �����U �������X�a      �����U�^�����X�a�����U�����X�T�T�a     �����U   �����X�T�T�����[�����U   �����U        |*"<<endl;
    cout<<"*|    �^�������������X�a���������������[    �����U �^�T�a �����U���������������[   �����U   �����U  �����U�^�������������X�a        |*"<<endl;
    cout<<"*|     �^�T�T�T�T�T�a �^�T�T�T�T�T�T�a    �^�T�a     �^�T�a�^�T�T�T�T�T�T�a   �^�T�a   �^�T�a  �^�T�a �^�T�T�T�T�T�a         |*"<<endl;
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
    cout<<"*|                         ��ӭʹ�õ�����·��ѯϵͳ                             |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             �밴�������¼                                   |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
}


void Metroline::mapLogin(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     �������������[ ���������������[    �������[   �������[���������������[�����������������[�������������[  �������������[         |*"<<endl;
    cout<<"*|    �����X�T�T�T�T�a �^�T�T�������X�a    ���������[ ���������U�����X�T�T�T�T�a�^�T�T�����X�T�T�a�����X�T�T�����[�����X�T�T�T�����[        |*"<<endl;
    cout<<"*|    �����U  �������[  �������X�a     �����X���������X�����U�����������[     �����U   �������������X�a�����U   �����U        |*"<<endl;
    cout<<"*|    �����U   �����U �������X�a      �����U�^�����X�a�����U�����X�T�T�a     �����U   �����X�T�T�����[�����U   �����U        |*"<<endl;
    cout<<"*|    �^�������������X�a���������������[    �����U �^�T�a �����U���������������[   �����U   �����U  �����U�^�������������X�a        |*"<<endl;
    cout<<"*|     �^�T�T�T�T�T�a �^�T�T�T�T�T�T�a    �^�T�a     �^�T�a�^�T�T�T�T�T�T�a   �^�T�a   �^�T�a  �^�T�a �^�T�T�T�T�T�a         |*"<<endl;
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
    cout<<"*|                         ��ӭʹ�õ�����·��ѯϵͳ                             |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                               1.��½�˺�                                     |*"<<endl;
    cout<<"*|                               2.ע���˺�                                     |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
}

void Metroline::mapMenu(){
    cout<<"**********************************************************************************"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|     �������������[ ���������������[    �������[   �������[���������������[�����������������[�������������[  �������������[         |*"<<endl;
    cout<<"*|    �����X�T�T�T�T�a �^�T�T�������X�a    ���������[ ���������U�����X�T�T�T�T�a�^�T�T�����X�T�T�a�����X�T�T�����[�����X�T�T�T�����[        |*"<<endl;
    cout<<"*|    �����U  �������[  �������X�a     �����X���������X�����U�����������[     �����U   �������������X�a�����U   �����U        |*"<<endl;
    cout<<"*|    �����U   �����U �������X�a      �����U�^�����X�a�����U�����X�T�T�a     �����U   �����X�T�T�����[�����U   �����U        |*"<<endl;
    cout<<"*|    �^�������������X�a���������������[    �����U �^�T�a �����U���������������[   �����U   �����U  �����U�^�������������X�a        |*"<<endl;
    cout<<"*|     �^�T�T�T�T�T�a �^�T�T�T�T�T�T�a    �^�T�a     �^�T�a�^�T�T�T�T�T�T�a   �^�T�a   �^�T�a  �^�T�a �^�T�T�T�T�T�a         |*"<<endl;
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
    cout<<"*|                           ��ӭʹ�õ�����·��ѯϵͳ                           |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                              ��ѡ����Ĳ��� :                                |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             ��1�� �鿴����ͼ                                 |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             ��2�� ��ѯ����·��                               |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             ��3�� ��ѯվ����Ϣ                               |*"<<endl;
    cout<<"*|                                                                              |*"<<endl;
    cout<<"*|                             ��4�� �˳�����                                   |*"<<endl;
    cout<<"**********************************************************************************"<<endl;
    cout<<"����������Ҫ�Ĺ��ܱ�ţ�";
}



Metroline::Metroline(string p[],int n)
{
    if(n>pathMax) throw"����";
    for(int i=0;i<pathMax;i++)
    {
        metro[i]=p[i];
    }
}

/*
 * ������վ����ֱ���ʱ��
 * ���������±�i�����վ�����ƣ��յ�վ�����ƣ�������·���ڼ�����l
 */
void Metroline::direct(int i,string sp,string fp,string p[],int lineNum)
{
    //starting=i;
    int timeConsumeAll = 0;
    for(int j=0;j<pathMax;j++)
        if(fp==p[j])
        {
            cout<<"����ֱ��,����"<<lineNum<<"�ų�!"<<endl;
            if(i<j)
            {
                cout<<"��·��Ϊ:"<<endl;
                for(int k=i;k<=j;k++)
                {
                    if(k!=j)
                    {
                        cout<<p[k]<<"-->>";
                        timeConsumeAll += timeConsume;
                    }
                    else cout<<p[k];
                }
                cout << endl << "��ʱ" << timeConsume*abs(j-i) << "����" << endl;
                if(abs(j-i)*price<=2)
                cout <<"Ʊ��2Ԫ" << endl;
                else
                     cout <<"Ʊ��" <<price*abs(j-i) << "Ԫ" << endl;
            }
            else
            {
                cout<<"��·��Ϊ:"<<endl;
                for(int k=i;k>=j;k--)
                {
                    if(k!=j)
                    {
                        cout<<p[k]<<"-->>";
                        timeConsumeAll += timeConsume;
                    }
                    else cout<<p[k];
                }
                cout << endl << "��ʱ" << timeConsume*abs(j-i) << "����" << endl;
                 if(abs(j-i)*price<=2)
                cout<< "Ʊ��2Ԫ" << endl;
                else
                     cout <<"Ʊ��" <<price*abs(j-i) << "Ԫ" << endl;
            }
        }
    //cout << endl << "��ʱ" << timeConsumeAll << "����" << endl;
}

/*
 * sp��� fp�յ�
 * i�������±꣬j���յ���±꣬sp����㣬fp���յ㣬p1��p2�ǵ�����·
 * p1�������·��p2���յ���·
 */
void Metroline::hc(int i,int j,string sp,string fp,string p1[],string p2[])
{
    /**** to do list: ��BFSȥ��Ѱ ·�� ****/
    /**** �˴��߼������⣬�п���������ֱ�Ӳ�ֹ��һ����ͬվ ****/

    for(auto & x : transfer)//��������վ�������
        for(int l=0;l<pathMax;l++)
            for(int l1=0;l1<pathMax;l1++)
            {
                if(x==p2[l] && x==p1[l1])
                {
                    //l��l1�ֱ������תվ�����������е�λ��
                    //i��l���Աȣ�����p2������վ������·
                    //j��l1���Աȣ�����p1���յ�վ������·
                    if(i<l)
                    {
                        for(int y=i;y<l;y++)
                        {
                            cout<<"��"<<p2[y]<<" ";
                        }
                        if(j<l1)
                        {
                            cout<<"��"<<x<<"ת��,"<<" --*--*-- ";
                            for(int z=l1;z>j;z--)
                            {
                                cout<<"��"<<p1[z]<<" ";
                            }
                            cout<<"��"<<fp<<endl;
                        }
                        else if(j>l1)
                        {
                            cout<<"��"<<x<<"ת��,"<<"   ";
                            for(int z=l1;z<j;z++)
                            {
                                cout<<"��"<<p1[z]<<" ";
                            }
                            cout<<"��"<<fp<<endl;
                        }
                        cout << "��ʱ" << timeConsume*(abs(l-i)+abs(l1-j)) << "����" << endl;
                         if((abs(l-i)+abs(l1-j))*price<=2){
                        cout << "Ʊ��2Ԫ" << endl;}
                         else
                     cout << "Ʊ��" <<price*(abs(l-i)+abs(l1-j)) << "Ԫ" << endl;
                    }
                    else if(i>l)
                    {
                        for(int y=i;y>l;y--)
                        {
                            cout<<"��"<<p2[y]<<" ";
                        }
                        if(j<l1)
                        {
                            cout<<"��"<<x<<"ת��,"<<"   ";
                            for(int z=l1;z>j;z--)
                            {
                                cout<<"ת"<<p1[z]<<" ";
                            }
                            cout<<"��"<<fp<<endl;
                        }
                        else if(j>l1)
                        {
                            cout<<"��"<<x<<"ת��,"<<"   ";
                            for(int z=l1;z<j;z++)
                            {
                                cout<<"ת"<<p1[z]<<" ";
                            }
                            cout<<"��"<<fp<<endl;
                        }
                        cout << "��ʱ" << timeConsume*(abs(l-i)+abs(l1-j)) << "����" << endl;
                        if((abs(l-i)+abs(l1-j))*price<=2)
                cout << "Ʊ��2Ԫ" << endl;
                else
                     cout << "Ʊ��" <<price*(abs(l-i)+abs(l1-j)) << "Ԫ" << endl;
                    }
                }
            }
}

/*
 * �жϵ���վ�Ƿ������·��,�����ڵ�ͼ�е��±�
 * stationΪ��Ҫ��ѯ��վ�㣬p[]Ϊ�������·����
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
    cout<<"����������㣺";
    cin>>sp;
    beginFp:
    cout<<"�������յ㣺";
    cin>>fp;

    /*
     * �ж��������ʼվ���յ�վ�Ƿ����
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
        cout<<"����ĳ������д����������룺";
        goto beginSp;
    }
    if(!flagFp)
    {
        cout<<"������յ���д����������룺"<<endl;
        goto beginFp;
    }
}

void Metroline::SearchLine(string path3TH[],string path3PY[],string path1[],string path2[], string path4[], string pathAll[][pathMax]){
    system("cls");
    Metroline::map();//��ӡ��ͼ
    string sp,fp;//spΪ����վ��fpΪ�յ�վ
    InStation:
    Metroline::inStation(sp,fp,pathAll);//���������վ���Ƿ����

    /*
     * ��������������в��裺
     * 1.�ж��յ����ڼ����ߣ�����1������
     * 2.�ж�������ڼ�����
     * 3.�ж��յ������Ƿ���ͬһ���ߣ������ͬһ��������˵��ֱ��
     * 4.�������ͬһ������˵��Ҫת�ߣ����ú�����
     * */

    /* i��spվ��������·������±꣬k1��fpվ������·������±�
     * splineNum��spվ������·��pathAll�����е��±꣬fplineNum��fpվ������·��pathAll�����е��±�
     * pathAll�����±�
     * 0 -- 1����
     * 1 -- 2����
     * 2 -- 3����-���
     * 3 -- 3����-��خ
     * 4 -- 4����
     */


    int i = -1, k1 = -1, splineNum = -1, fplineNum = -1;
    while(i==-1){
        i = Metroline::search(sp,pathAll[++splineNum]);
    }
    while(k1==-1){
        k1 = Metroline::search(fp,pathAll[++fplineNum]);
    }

    /**** to do:���λ��ˣ�  ****/

    //���յ�վ��1����
    if(fplineNum == 0){
        if (splineNum == 0) {
            Metroline::direct(i, sp, fp, path1, 1);//�������ֱ��
        } else{//��������ֱ�����������·
            if (splineNum == 1) {
                cout << "��Ҫ���ˣ�ת�̷�ʽΪ��2·ת1·��" << endl;
                Metroline::hc(i, k1, sp, fp, path1, path2);
            }
            if (splineNum == 4) {
                cout << "��Ҫ���ˣ�ת�̷�ʽ��4·ת1·��" << endl;
                Metroline::hc(i, k1, sp, fp, path1, path4);
            }
        }
    }

        //���յ�վ��3����-���
    else if(fplineNum == 2){
        if (splineNum == 2) {
            Metroline::direct(i, sp, fp, path3TH, 3);//�������ֱ��
        } else{//��������ֱ�����������·
            if (splineNum == 0) {
                cout << "ת�̷�ʽ��1·ת3·��" << endl;
                Metroline::hc(i, k1, sp, fp, path3TH, path1);
            }
            else if (splineNum == 3) {
                cout << "ת�̷�ʽ��3·ת3·��" << endl;
                Metroline::hc(i, k1, sp, fp, path3TH, path3PY);
            }

        }
    }

        //���յ�վ��3����-��خ
    else if(fplineNum == 3){
        if (splineNum == 3) {
            Metroline::direct(i, sp, fp, path3PY, 3);//�������ֱ��
        } else{//��������ֱ�����������·
            if (splineNum == 0) {
                cout << "ת�̷�ʽ��1·ת3·��" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path1);
            } else if (splineNum == 1) {
                cout << "ת�̷�ʽ��2·ת3·��" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path2);
            }else if (splineNum == 2) {
                cout << "ת�̷�ʽ��3·ת3·��" << endl;
                Metroline::hc(i, k1, sp, fp, path3PY, path3TH);
            }
        }
    }

        //���յ�վ��2����
    else if(fplineNum == 1){
        if (splineNum == 1) {
            Metroline::direct(i, sp, fp, path2, 2);//�������ֱ��
        } else{//��������ֱ�����������·
            if (splineNum == 0) {
                cout << "��Ҫ���ˣ�ת�̷�ʽ��1·ת2·��" << endl;
                Metroline::hc(i, k1, sp, fp, path2, path1);
            } else if (splineNum == 4) {
                cout << "��Ҫ���ˣ�ת�̷�ʽ��4·ת2·��" << endl;
                Metroline::hc(i, k1, sp, fp, path2, path4);
            }
        }
    }

        //���յ�վ��4����
    else if(fplineNum == 4){
        if (splineNum == 4) {
            Metroline::direct(i, sp, fp, path4, 4);//�������ֱ��
        } else{//��������ֱ�����������·
            if (splineNum == 0) {
                cout << "ת�̷�ʽ��1·ת4·��" << endl;
                Metroline::hc(i, k1, sp, fp, path4, path1);
            } else if (splineNum == 1) {
                cout << "ת�̷�ʽ��2·ת4·��" << endl;
                Metroline::hc(i, k1, sp, fp, path4, path2);
            }
        }
    }

    cout<<"\n"<<"                             ������������Y/y �˳����������"<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;

    char t = getch();
    if(t=='y'||t=='Y')
        goto InStation;
}


/**
 * ��ӡע���˺ŵĸ�����
 */
void subtitle2()
{
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<" ��               �����·�����Ҫע����˺��Լ����루���벻�ó���10λ��           ��"<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;

}

int pick(char nameIn[20],char passwordIn[20])
{
    FILE*fp;
    char name[20],password[20];
    fp=fopen("id.txt","r");
    for(;!feof(fp);)//���ÿһ���˺����½��ʮ��һ��
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
    cout<<"������ѧ�ţ�";cin>>name;
    while(true) {
        cout << "���������룺";
        cin >> password;//��Ҫ�жϵ�һ�κ͵ڶ���ʮ����ͬ������ͬ��Ҫ����������
        cout<<"���ٴ��������루������һ�£�:";
        cin>>password2;
        if(strcmp(password,password2)==0)
        {
            fprintf(fp, "%s %s\n", name, password);
            cout<<"ע��ɹ�����ӭʹ�ã�"<<endl;
            break;
        }
        else cout<<"�����������벻һ�£�����������"<<endl;
    }
    fclose(fp);
}

void logIn()
{
    Metroline::mapLogin();
    char ifLog = getch();
    if(ifLog=='1') {
        int correct = 1, a;//�жϵ�½�Ƿ�ɹ�
        int attempt = 0;//���Դ���
        while (correct) {
            char name[20], password[20];
            cout << "�������û�����";
            scanf("%s", name);
            cout << "���������룺";
            scanf("%s", password);
            a = pick(name, password);
            if (a == 1) {
                printf("��½�ɹ��� ��ӭʹ�ã�\n");
                correct = 0;
                successful = 1;
            } else {
                cout << "�û��������������" << endl;
                attempt++;
            }//����������û������������Ҫ����������
            if (attempt == 3) {
                cout << "�����û�����������������Σ��Զ��˳�����" << endl;
                end();
            }//���������������ֱ���˳�����
        }
    } else if(ifLog=='2'){
        enroll();
    } else{
        end();
    }
}

void Metroline::StationInfo(string path3TH[],string path3PY[],string path1[],string path2[], string path4[]){
    Metroline::map();//��ӡ��ͼ
    cout<<"������վ�����ƣ�";
    string sta;
    cin>>sta;
    for(int i=0;i<pathMax;i++)
        if(sta==path3TH[i])
            cout<<"3����-��Ӿ�����վ"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path3PY[i])
            cout<<"3����-��خ������վ"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path1[i])
            cout<<"1���߾�����վ"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path2[i])
            cout<<"2���߾�����վ"<<endl;
    for(int i=0;i<pathMax;i++)
        if(sta==path4[i])
            cout<<"4���߾�����վ"<<endl;

}


/**** main���� ****/
int main() {

    //���崰�ڴ�С
    //modeset(100,100);

    //����ͼ��Ϣ¼�뵽�ַ���������
    string path3TH[pathMax] = {"���ݶ�վ","�ֺ���","������·","ʯ����","�ڶ�","��ɽ","��ӿ���վ"};
    string path3PY[pathMax] = {"������·","�齭�³�","�����","�ʹ�","����","��ʯ","��Ϫ��¡","����","��خ�㳡"};
    string path1[pathMax] = {"���ݶ�վ","��������","������·","���","��ɽ��","��ʿ��԰","ũ����","��Ԫǰ","���ſ�","�¼���","����·","��ɳ","����","�ӿ�","����"};
    string path2[pathMax] = {"��Ԫ��","���ݻ�վ","Խ�㹫԰","������","��Ԫǰ","����㳡","�ж���","������","����","�д�","����","�ʹ�","���","ĥ��ɳ","�¸۶�","����","��ʤΧ"};
    string path4[pathMax] = {"��ʤΧ","��ѧ�Ǳ�","��ѧ����","��ӿ","��ʢ","����"};
    string pathAll[5][pathMax] = {{"���ݶ�վ", "��������",  "������·", "���",  "��ɽ��", "��ʿ��԰", "ũ����",  "��Ԫǰ", "���ſ�", "�¼���", "����·", "��ɳ", "����", "�ӿ�",  "����"},
                                  {"��Ԫ��",  "���ݻ�վ", "Խ�㹫԰", "������", "��Ԫǰ", "����㳡", "�ж���",  "������", "����",  "�д�",  "����",  "�ʹ�", "���", "ĥ��ɳ", "�¸۶�", "����", "��ʤΧ"},
                                  {"���ݶ�վ", "�ֺ���",   "������·", "ʯ����", "�ڶ�",  "��ɽ",   "��ӿ���վ"},
                                  {"������·", "�齭�³�",  "�����",  "�ʹ�",  "����",  "��ʯ",   "��Ϫ��¡", "����",  "��خ�㳡"},
                                  {"��ʤΧ",  "��ѧ�Ǳ�",  "��ѧ����", "��ӿ",  "��ʢ",  "����"}
    };

    Metroline a(path1,path1Len);//1����
    Metroline b(path2,path2Len);//2����
    Metroline c(path4,path4Len);//4����
    Metroline e(path3TH,path3LenTH);//3����-���
    Metroline f(path3PY,path3LenPY);//3����-��خ

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
        cout<<"�����������,����������"<<endl;
        n=getch();
    }
    if(n=='1'){
        system("cls");
        Metroline:: map();
        cout<<"��������������˵�"<<endl;
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
        cout<<"��������������˵�"<<endl;
        getch();
        system("cls");
        goto user;
    }
    if(n=='4'){
        system("cls");
        system("cls");
        system("cls");
        end();
        cout<<"��������˳�";
        n = getch();
    }

}
