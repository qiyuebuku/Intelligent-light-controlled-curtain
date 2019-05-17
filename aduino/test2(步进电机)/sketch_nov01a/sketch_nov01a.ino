//使用arduino IDE自带的Stepper.h库文件
#include <Stepper.h>
// 这里设置步进电机旋转一圈是多少步
#define STEPS 100

//设置步进电机的步数和引脚（就是注意点2里面说的驱动板上IN1～IN4连接的四个数字口）。
Stepper stepper(STEPS,8,10,9,11);
void setup()
{
    // 设置电机的转速：每分钟为90步
    stepper.setSpeed(90);
    // 初始化串口，用于调试输出信息
    Serial.begin(9600);
}
void loop()
{
    //定义一个名叫fp文件指针
    FILE *fp;
    //判断按读方式打开一个名叫test的文件是否失败
    if((fp=fopen("test","r"))==NULL)//打开操作不成功
    { 
        Serial.print("a:");
        exit(1);//结束程序的执行
    }
}
