//#include <stdio.h>
//#include <iostream>
//#include <windows.h>
//#include <tchar.h>
//#include <fstream>
//#include <string>
//#include <tchar.h>
//
//using namespace std;
//
////�����������߳�ͬ��
//HANDLE hMutex = NULL;
//
//DWORD WINAPI Fun(LPVOID lpParament)
//{
//    for (int i = 0; i < 10; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        cout << "A Thread Fun Display!" << endl;
//        ReleaseMutex(hMutex);
//        //Sleep(200);     //SleepҪ����ѭ���ڲ�
//    }
//
//    return 0L;
//}
//
//int main()
//{
//    HANDLE handle1 = CreateThread(NULL, NULL, Fun, NULL, NULL, NULL);
//    CloseHandle(handle1);                                               //Close�����������Ľ������̣߳����ǽ��ں˵����ü�����1������0ʱ�ŻᱻOS����
//
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread"));
//    for(int i = 0; i < 10; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);                          //����һ����������  INFINITE�����޵ȴ�
//        cout << "Main Thread Fun Display!" << endl;
//        ReleaseMutex(hMutex);                                           //�ͷŻ�������
//        //Sleep(200);     //SleepҪ����ѭ���ڲ�
//    }
//
//    getchar();
//    return 0;
//}
//
//
///*
//    ֻ����һ���߳�ӵ�жԹ�����Դ�Ķ�ռ�����������û�����(Mutex)�������߳�ͬ����
//    https://www.cnblogs.com/codingmengmeng/p/5913068.html
//*/