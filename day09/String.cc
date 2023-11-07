#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String
{
public:
    String()
        : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }

    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]) // 默认pstr不为空，如果要判空的话，可以把_pstr初始化放在函数体中实现
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    String(const String &rhs) // 拷贝构造函数
        : _pstr(new char[strlen(rhs._pstr) + 1])
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    String & operator=(const String &rhs)
    {
        cout << "String & operator=(const String &)" << endl;
        //1、自复制
        if(this!=&rhs)
        {
            //2、释放左操作数
            if(_pstr)
            {
                delete [] _pstr;
                _pstr = nullptr;
            }
            
            //3、深拷贝
            //if(rhs._pstr),在使用任何指针前，最好判空
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        //4、返回*this
        return *this;//返回对象本身，而不是指针
    }
    
    size_t length() const
    {
        size_t len = 0;
        if(_pstr)
        {
            len = strlen(_pstr);
        }
        return len;
    }

    const char * c_str() const//从C++风格字符串转换为c风格字符串
    {
        if(_pstr)
        {
            return _pstr;
        }else
        {
            return nullptr;
        }
    }
    ~String()
    {
        cout << "~String()" << endl;
        if(_pstr)
        {
            delete[] _pstr;
            _pstr = nullptr;//避免“悬垂指针”
        }
    }

    void print() const // 不进行修改
    {
        /*
         cout << "_pstr=" << _pstr << endl;
         没有进行判空，在<<_pstr时会出现程序中断，即~String不会打印出来
        */
        if (_pstr)
        {
            cout << "_pstr=" << _pstr << endl; // 这样子写后会打印~String
        }
    }
private:
    char *_pstr;
};

int main()
{
    String str1;
    str1.print();

    cout << endl;
    String str2 = "Hello,World";//编译器优化选项，先是c风格字符串创建一个匿名的String，然后将String拷贝构造给str2（之所以是拷贝构造是因为str2是初始化）
    String str3("nihao");
    str2.print();
    str3.print();

    cout << endl;
    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();
    return 0;
}
