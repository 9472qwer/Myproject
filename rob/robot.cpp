#include "robot.h"
#include <Python.h>
#include <iostream>

// 获取单例实例的静态方法
Robot &Robot::getInstance()
{
    static Robot instance; // 在第一次调用时初始化
    return instance;
}

//机械臂初始化
int Robot::init()
{
    // 1、初始化python接口
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        std::cout << "python init failed" << std::endl;
        return 1;
    }

    // 2、初始化python系统文件路径，保证可以访问到 .py文件
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/book/Myproject/script')");

    // 3、调用python文件名，不用写后缀
    PyObject *module = PyImport_ImportModule("Robot");
    if (module == nullptr)
    {
        std::cout << "module not found: test3" << std::endl;
        return 1;
    }
    // 4、获取类
    PyObject *cls = PyObject_GetAttrString(module, "Robot");
    if (!cls)
    {
        std::cout << "class not found: Person" << std::endl;
        return 1;
    }

    // 5、给类构造函数传递参数
    // 函数调用的参数传递均是以元组的形式打包的, 2表示参数个数
    // 如果函数中只有一个参数时，写1就可以了
    PyObject *args = PyTuple_New(0);

    // // 0：第一个参数，传入 int 类型的值 1
    // PyTuple_SetItem(args, 0, Py_BuildValue("s", "jack"));
    // // 1：第二个参数，传入 int 类型的值 2
    // PyTuple_SetItem(args, 1, Py_BuildValue("i", 18));

    // 6、根据类名实例化对象
    PyObject *obj = PyEval_CallObject(cls, args);

    // 7、根据对象得到成员函数
    PyObject *func = PyObject_GetAttrString(obj, "init");
    if (!func || !PyCallable_Check(func))
    {
        std::cout << "function not found: foo" << std::endl;
        return 1;
    }

    // 8、使用C++的python接口调用该函数
    PyObject_CallObject(func, nullptr);

    // 9、结束python接口初始化
    Py_Finalize();
    return 0;
}
//抓取扫描仪的零件
void Robot::catch_scanner()
{
}
//抓取货架的零件
void Robot::catch_shelf()
{
}
//放置一个零件到3D扫描台
void Robot::put_scanner()
{
}
//放置一个零件到货架
void Robot::put_shelf()
{
}
//返回机械臂的数据
void Robot::return_data()
{
}