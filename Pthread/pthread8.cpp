//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
///*
//        ˫�̶߳�д�������ݣ�
//        https://blog.csdn.net/MoreWindows/article/details/8646902
//*/
//CRITICAL_SECTION cs;
//
//const int N = 5;
//int Dqueue[N] = { 0 };          //����˫�����
//int i = 0; 
//int j = 0;
//HANDLE hEmptyNum;               //��������λ�� -> ��д��data��
//HANDLE hReadDataNum;            //��������λ�� -> �ɶ�ȡdata��
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    int OutputData = 0;
//    while (OutputData < 20)
//    {
//         WaitForSingleObject(hReadDataNum, INFINITE);
//
//         OutputData = Dqueue[i];
//         i = (i + 1) % N;
//         //EnterCriticalSection(&cs);
//         printf("�Ӷ����ж�ȡ����%d\n", OutputData);
//         //LeaveCriticalSection(&cs);
//
//         ReleaseSemaphore(hEmptyNum, 1, NULL);
//    }
//    
//    return 0;
//}
//
//unsigned int __stdcall WriterThreadFun(PVOID pM)
//{
//    int InputData = 0;
//    while (InputData < 20)
//    {
//        WaitForSingleObject(hEmptyNum, INFINITE);
//
//        Dqueue[j] = ++InputData;
//        j = (j + 1) % N;
//        //EnterCriticalSection(&cs);
//        printf("    ��������д������%d\n", InputData);
//        //LeaveCriticalSection(&cs);
//
//        ReleaseSemaphore(hReadDataNum, 1, NULL);
//    }
//
//    return 0;
//}
//
//int main()
//{
//    InitializeCriticalSection(&cs);
//    hEmptyNum    = CreateSemaphore(NULL, N, N, NULL);               //����2����Դ����ʼ��ΪN
//    hReadDataNum = CreateSemaphore(NULL, 0, N, NULL);
//
//    HANDLE handle[2];
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);
//    handle[1] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(2, handle, TRUE, INFINITE);
//
//    for (int k = 0; k < 2; k++)
//    {
//        CloseHandle(handle[k]);
//    }
//    CloseHandle(hReadDataNum);
//    CloseHandle(hEmptyNum);
//    DeleteCriticalSection(&cs);
//
//    getchar();
//    return 0;
//}
//
///*
//    1.�����п�ʱ����ȡ�����߳�Ҫ�ȴ�������������.
//
//    2.��������ʱ��д�������߳�Ҫ�ȴ��������п�λ.
//
//    ���ʶ���ʱ����Ҫ�������⽫�����ڶ��е����ݽṹʵ�֣����ʹ��STL�е�vector������vector�ᶯ̬���������Ҫ�����Ᵽ����            -> ��һ��������Դ���в���
//    ���ʹ��ѭ�����У���ô��ȡ�����߳�ӵ�ж�ȡָ�룬д�������߳�ӵ��д��ָ�룬���Խ����ʶ����в�ͬλ���ϵ����ݣ���˲��ý��л��Ᵽ��    -> �Զ��������Դ���в���
//*/