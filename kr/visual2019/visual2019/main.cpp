#include <iostream>
using namespace std;


int* func1()
{
	int a = 10;
	return &a;
}

int* func2()
{
	int* b = new int(10);
	return b;
}

void test1()
{
	int* arr = new int[10]; // 在堆区开辟数组
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

	// 删除堆区数组
	delete[] arr;

	/*for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}*/ // 删除数组对象后无法访问
}

// 值传递
void mySwap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 地址传递
void mySwap02(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 引用传递
void mySwap03(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

class Person {
public:
	// 构造和析构不写返回值也不写void, 函数名称与类名相同
	Person(string name, int age) 
	{
		cout << "构造方法" << endl;
		this->name = name;
		this->age = new int(age);
	}
	Person(const Person& p)
	{
		cout << "拷贝构造函数" << endl;
		this->name = p.name;
		this->age = new int(*(p.age));
	}
	~Person()
	{
		if (this->age != nullptr)
		{
			cout << "析构" << endl;
			delete this->age;
		}
	}

	string getName()
	{
		return this->name;
	}

	int getAge()
	{
		return *(this->age);
	}
public:
	static int m_A; //静态成员变量，类内声明，类外初始化
private:
	string name;
	int* age;
};

int Person::m_A = 10;

void test2()
{
	Person p1 = Person("哈哈", 18);
	p1.m_A = 100;
	cout << "姓名: " << p1.getName() << ", 年龄: " << p1.getAge() << ", m_A的值为: " << p1.m_A << endl;
	Person p2 = Person(p1); // 调用拷贝构造方法
	p2.m_A = 200;
	cout << "姓名: " << p2.getName() << ", 年龄: " << p2.getAge() << ", m_A的值为: " << p2.m_A << endl;
	cout << "通过类名访问m_A的值: " << Person::m_A << endl;
}

class CBuff
{
private:
	void init()
	{
		this->m_pBuff = nullptr;
		this->m_nSize = 0;
		this->m_pnRefCount = nullptr;
	}
	void uninit()
	{
		if (this->m_pnRefCount != nullptr)
		{
			--(*this->m_pnRefCount);
		}
		if (this->m_pnRefCount == nullptr)
		{
			delete[] this->m_pBuff;
			delete this->m_pnRefCount;
			this->m_pBuff = nullptr;
			this->m_pnRefCount = nullptr;
			this->m_nSize = 0;
		}
	}
public:
	CBuff()
	{
		cout << "默认构造方法" << endl;
		init();
	}
	CBuff(const CBuff& obj)
	{
		cout << "拷贝构造-浅拷贝" << endl;
		if (obj.m_pnRefCount != nullptr)
		{
			this->m_pBuff = obj.m_pBuff;
			this->m_nSize = obj.m_nSize;
			this->m_pnRefCount = obj.m_pnRefCount;
		}

		++(*this->m_pnRefCount);
		/*this->m_pBuff = new char[obj.m_nSize];
		memset(this->m_pBuff, 0, obj.m_nSize);
		memcpy(this->m_pBuff, obj.m_pBuff, obj.m_nSize);
		this->m_nSize = obj.m_nSize;*/
	}
	~CBuff()
	{
		cout << "析构方法" << endl;
		uninit();
	}
	void Set(const char* pBuff, int nSize)
	{
		uninit();
		this->m_pBuff = new char[nSize];
		this->m_pnRefCount = new int(1);
		memset(this->m_pBuff, 0, nSize);
		memcpy(this->m_pBuff, pBuff, nSize);
		this->m_nSize = nSize;
	}

	char* Get()
	{
		return this->m_pBuff;
	}

public:
	static int value; // 静态变量公用

private:
	char* m_pBuff;
	int m_nSize;
	int* m_pnRefCount; //计数器
};

int CBuff::value = 1;

void test3()
{
	CBuff *buf = new CBuff();
	buf->Set("\x55\x55\x55\x55", 4);

	CBuff* buf1 = new CBuff();
	buf1->Set("\x44\x44\x44\x44\x44\x44\x44\x44\x44\x44\x44\x44", 100);

	CBuff *buf3 = buf1;
	delete buf;
	delete buf1;
	delete buf3;

}

class CA
{
public:
	void TestA()
	{
		cout << "CA::TestA()" << endl;
	}
	void TestA(const char*)
	{
		cout << "CA::Test(const char*)" << endl;
	}
protected:
	int m_n = 0xAAAAAAAA;
};

class CB :public CA
{
public:
	void TestA()
	{
		cout << "CB：：Test()" << endl;
		m_n = 0xDDDDDDDD;//优先调用自己的。
		CA::m_n = 0xEEEEEEEE; //显示的调用父类的。
	}
private:
	int m_n = 0xBBBBBBBB;
};

class Animal
{
public:
	Animal()
	{
		this->speak();
	}
	/*virtual ~Animal()
	{
		cout << "Animal虚析构" << endl;
	}*/
	virtual ~Animal() = 0;
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
	virtual void run()
	{
		cout << "动物在跑" << endl;
	}
};

Animal::~Animal()
{
	cout << "Animal纯虚析构" << endl;
}

class Cat :public Animal
{
public:
	Cat()
	{
		this->speak();
	}
	~Cat()
	{
		cout << "Cat析构代码" << endl;
	}
	void speak()
	{
		cout << "小猫在说话" << endl;
	}
	virtual void run()
	{
		cout << "动物在跑" << endl;
	}
};

//class Dog :public Animal
//{
//public:
//	Dog()
//	{
//		this->c = 3;
//	}
//	void speak()
//	{
//		cout << "小狗在说话" << endl;
//	}
//private:
//	int c;
//};

//void DoSpeak(Animal& animal)
//{
//	animal.speak();
//}
int test4()
{
	/*Cat cat;
	DoSpeak(cat);*/
	/*Animal* cat = new Cat();
	cat->speak();
	delete cat;*/
	Animal* a = new Cat();
	a->speak();
	delete a;
	return 0;
}

class CHero
{
public:
	//CHero(int nType)
	//{
	//	this->m_nType = nType;
	//}

	virtual void Skill(int nIdx)
	{
		switch (nIdx)
		{
		case 0:
			cout << "平A" << endl;
			break;
		case 1:
			cout << "回血" << endl;
			break;
		default:
			break;
		}
	}

//private:
//	int m_nType;
};

class CSodier :public CHero
{
public:
	void Skill(int nIdx)
	{
		switch (nIdx)
		{
		case 0:
			cout << "战士平A" << endl;
			break;
		case 1:
			cout << "战士回血" << endl;
			break;
		case 2:
			cout << "小李飞刀" << endl;
			break;
		case 3:
			cout << "铁砂掌" << endl;
			break;
		case 4:
			cout << "金钟罩, 铁布衫" << endl;
			break;
		default:
			break;
		}
	}
};

class CWizard :public CHero
{
public:
	void Skill(int nIdx)
	{
		switch (nIdx)
		{
		case 0:
			cout << "法师平A" << endl;
			break;
		case 1:
			cout << "法师回血" << endl;
			break;
		case 2:
			cout << "六脉神剑" << endl;
			break;
		case 3:
			cout << "降龙十八掌" << endl;
			break;
		case 4:
			cout << "大威天龙, 大罗法咒" << endl;
			break;
		default:
			break;
		}
	}
};

int test5()
{
	CHero* aryHeros[6]; //存放指针
	for (int i = 0; i < 6; i++)
	{
		CHero* c = NULL;
		if (i % 2 == 0)
		{
			c = new CSodier();
		}
		else
		{
			c = new CWizard();
		}
		aryHeros[i] = c;
	}

	for (int i = 0; i < 6; i++)
	{
		aryHeros[i]->Skill(i);
	}

	delete[] aryHeros;

	return 0;
}

class CInteger
{
public:
	CInteger()
	{
		cout << "无参构造" << endl;
	}

	CInteger(int a, int b)
	{
		this->m1 = a;
		this->m2 = b;
	}

	void SetM1(int a)
	{
		this->m1 = a;
	}

	void SetM2(int b)
	{
		this->m2 = b;
	}

	int GetM1()
	{
		return this->m1;
	}

	int GetM2()
	{
		return this->m2;
	}

	/*CInteger operator+(CInteger& obj)
	{
		CInteger temp;
		temp.m1 = this->m1 + obj.m1;
		temp.m2 = this->m2 + obj.m2;
		return temp;
	}

	CInteger operator+(int a)
	{
		CInteger temp;
		temp.m1 = this->m1 + a;
		temp.m2 = this->m2 + a;
		return temp;
	}*/

	CInteger& operator+(CInteger& obj)
	{
		this->m1 = this->m1 + obj.m1;
		this->m2 = this->m2 + obj.m2;
		return *this;
	}

	CInteger& operator+(int a)
	{
		this->m1 = this->m1 + a;
		this->m2 = this->m2 + a;
		return *this;
	}
private:
	int m1;
	int m2;
};

int test6()
{
	CInteger d1;
	d1.SetM1(1);
	d1.SetM2(2);
	cout << "m1的值为: " << d1.GetM1() << ", m2的值为: " << d1.GetM2() << endl;
	// 两个对象相加
	CInteger d2(3, 4);
	CInteger d3 = d1 + d2;
	cout << "m1的值为: " << d3.GetM1() << ", m2的值为: " << d3.GetM2() << endl;
	CInteger d4 = d3 + 2;
	cout << "m1的值为: " << d4.GetM1() << ", m2的值为: " << d4.GetM2() << endl;
	return 0;
}

int main() {
	//int* p1 = func1();
	//cout << "不要返回局部变量的地址" << *p1 << endl; // 10
	//cout << "不要返回局部变量的地址" << *p1 << endl; // 2065865096
	//int* p2 = func2();
	//cout << "返回堆区数据" << *p2 << endl;
	//delete p2;
	// cout << "返回堆区数据" << *p2 << endl; // 删除对象后无法查看内存指向数据
	// test1();
	/*int a = 1;
	int b = 2;
	mySwap01(a, b);
	cout << "交换后的a: " << a << ", 交换后的b: " << b << endl;*/
	//test2();
	// test3();
	/*CB b;
	b.TestA();*/
	// test4();
	//test5();
	test6();
	cout << "hello world" << endl;
	return 0;
}