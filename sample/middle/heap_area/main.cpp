#include <iostream>
using namespace std;

int *func()
{
    // 栈区的形参和局部变量不要返回
    // int a = 10;
    // return &a;

    // new一个在堆区的数据, 可以返回地址供外部程序使用
    int *p = new int(10);
    return p;
}

void test1()
{
    int *p = func();
    cout << *p << endl;
    cout << *p << endl;
    // delete p;
    // cout << *p << endl;
}

void test3()
{
    int *p1 = new int[5];
    // cout << p1 << endl;
    for (int i = 0; i<5; i++)
    {
        cout << p1 << endl;
        p1++;
    }

    // // 给数组赋值
    // for (int i = 0; i < 5; i++)
    // {
    //     p1[i] = i + 100;
    // }

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "数组中的数据为: " << p1[i] << endl;
    // }

    // delete []p1;
    
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "数组中的数据为: " << p1[i] << endl;
    // }

    // int arr[5] = {1,2,3,4,5};
    // int arr[5];
    // for (int i = 0; i < 5; i++)
    // {
    //     arr[i] = i + 100;
    // }
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "数组中的数据为: " << arr[i] << endl;
    // }
}

// 堆区和栈区

int main()
{
    // test1();
    // test2();
    test3();
    // int a = 1;
    // int *p = &a;
    // cout << "p的值为: " << p << endl;
    // cout << "*p的值为:" << *p << endl;
    return 0;
}