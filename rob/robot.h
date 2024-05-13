#include <vector>

class Robot
{
public:
    static Robot &getInstance();

    // 将拷贝构造函数和拷贝赋值运算符声明为私有，以防止复制对象
    Robot(Robot const &) = delete;
    void operator=(Robot const &) = delete;

    //机械臂初始化
    void init();
    //抓取扫描仪的零件
    void catch_scanner();
    //抓取货架的零件
    void catch_shelf();
    //放置一个零件到3D扫描台
    void put_scanner();
    //放置一个零件到货架
    void put_shelf();
    //返回机械臂的数据
    void return_data();

private:
    //将构造函数声明为私有，以防止外部代码创建新实例
    Robot(){};
};