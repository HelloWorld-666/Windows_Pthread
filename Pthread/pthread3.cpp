//#include <stdio.h>
//#include <iostream>
//#include <windows.h>    //CreateThread()
//#include <tchar.h>
//#include <process.h>    //_beginthread()
//
//
////�ź���Semaphore��
//int counts = 0;
//const DWORD THREAD_NUM1 = 10;
//HANDLE hThreadSemaphore;
//HANDLE hMutex = NULL;
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    int num = *(int*)pM;                   //68��69��˳�����෴������ͬ��������
//    ReleaseSemaphore(hThreadSemaphore, 1, NULL);                                        //Semaphoreֵ����
//    //�����߳�����Ҫһ���Ŀ����ģ��������̲߳����ܵ�һʱ��ִ�е�����
//    WaitForSingleObject(hMutex, INFINITE);
//    Sleep(50);
//    counts++;
//    Sleep(0);                                                                           //�������߳��л�������ִ��
//    printf("�̴߳��ݲ����̱߳��Ϊ��%d  ȫ�ֱ���countsֵΪ��%d\n", num, counts);
//    //cout << "i = " << *(int*)pM << '\t' << "counts = " << counts << endl;             //��Ϊendl��ԭ����������룬��Ҫ�û�������������������
//    ReleaseMutex(hMutex);
//
//    return 0;
//}
//
//int main()
//{
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread2"));
//    int n = 20;
//    HANDLE handle[THREAD_NUM1];                                                         //ע�⣺handle[N];  i < N;  WaitForMultipleObjects(N, ...)
//    handle[0] = NULL;
//
//    hThreadSemaphore = CreateSemaphore(NULL, 0, 1, NULL);                               //���ԡ���ʼSemaphoreֵ�����pthread������������Semaphore
//
//    for (int i = 0; i < THREAD_NUM1; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, &i, 0, NULL);
//        Sleep(0);
//        WaitForSingleObject(hThreadSemaphore, INFINITE);                                //��ǰֵΪ 0 ���ȴ�ReleaseSemaphore() +1 ʹ�ź���ֵ > 0
//        ReleaseMutex(hMutex);
//    }
//    WaitForMultipleObjects(THREAD_NUM1, handle, TRUE, INFINITE);                        //�ȴ��ڶ��������е��ں˶���ģ����ں˶������ź�ʱ�������̲߳Żᱻ���ȣ�������ֵ��˳��ִ����ȥ������������������˲���ΪTRUE������lpHandles�����е����ж����״̬�����ź�ʱ���ú�������
//    CloseHandle(hThreadSemaphore);
//
//    getchar();
//    return 0;
//}

/*
    https://blog.csdn.net/morewindows/article/details/7481609
*/