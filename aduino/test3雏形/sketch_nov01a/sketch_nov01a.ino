//使用arduino IDE自带的Stepper.h库文件
#include <Stepper.h>
//使用本地的DHT11库文件
#include <dht11.h>
//==================================================电机驱动-宏定义======================================================
// 这里设置步进电机旋转一圈是多少步
#define STEPS 100
//设置正反转时，旋转几周,4步模式下旋转一周用2048 步。
#define CIRCLE 500
//确认光线时间，防止因为光线的变化的太快而进行的误操作
#define PMT 2000//Prevent misoperation time

//==================================================光线传感器-宏定义======================================================
//定义光敏电阻的输入信号引脚
#define PIN_INPUT 0
//定义光敏电阻的输出信号引脚
#define PIN_OUTPUT 2
//定义光线闸值
#define RESISTANCE_BRAKE 200

//==================================================温度传感器-宏定义======================================================
//定义温度传感器引脚
#define DHT11PIN 3
//定义温度闸值
#define TEMPERATURE_BRAKE 20

//==================================================ESP8266-宏定义======================================================

//===================================================电机驱动-函数申明=====================================================
//设置电机正转
void setMotorForward();
//智能模式
void noopsyche();
//设置电机反转
void setMotorReversal();

//电机运行
void startMotor(bool status);
//设置步进电机的步数和引脚（就是注意点2里面说的驱动板上IN1～IN4连接的四个数字口）。
Stepper stepper(STEPS, 8, 10, 9, 11);
//初始化窗帘为关
bool motorStatus = false;
bool noopsyche_flag = true;

//===================================================光线传感器-函数申明=====================================================
//读取光敏电阻的阻值
int readAnalog();
//检测当前光敏电阻是否达到预设的闸值
bool checkStatus();

//===================================================温度传感器-全局变量=====================================================
dht11 DHT11;



//初始化，就是析构函数
void setup()
{
  // 设置电机的转速：每分钟为90步
  stepper.setSpeed(320);

  // 初始化串口，用于调试输出信息
  Serial.begin(9600);

  Serial.println("窗帘状态：开");
  //初始化为打开状态
  
  startMotor(motorStatus);
}


//主函数，相当于C语言的main函数
void loop()
{
//  Serial.println(Serial.read());
  Serial.println(Serial.available());
  if ( Serial.available())
  {
        char zhi_ling = Serial.read();
        Serial.print(zhi_ling);
        if (97 == zhi_ling)
        {
          noopsyche_flag = true;
          Serial.println("ok");
        }
        else if (78 == zhi_ling)
        {
          noopsyche_flag = false;
          Serial.println("ok");
        }
    
        else if (79 == zhi_ling)
        {
          startMotor(true);
          Serial.println("ok");
          return ;
        }
        else if (67 == zhi_ling)
        {
          startMotor(false);
          Serial.print("ok");
          return ;
        }
  }
  if (noopsyche_flag == true)
  {
      noopsyche();
  }

}


void noopsyche()
{
  //获取光敏电阻当前的阻值
  int analog = readAnalog();
  //如果当前的阻值达到了预设的闸值
  if (checkStatus()) {
    //延时2秒后，再次检测阻值是否达到了预设的闸值
    //如果达到了预设的阻值，就开始让电机正转
    delay(PMT);
    if (checkStatus()) {
      startMotor(true);
      //延时半秒
      delay(500);
    } else {
      return;
    }
  } else {
    delay(PMT);
    if (!checkStatus()) {
      startMotor(false);
      //延时半秒
      delay(500);
    } else {
      return;
    }
  }

}

//电机运行
void startMotor(bool status) {
  //获取光敏电阻当前的阻值
  int analog = readAnalog();
  //用串口打印光敏电阻检测到的阻值和？？？（我也不知道这是什么，待研究）
  Serial.print("光敏传感器阻值:");
  Serial.println(analog);
  if (status == true && motorStatus == false ) {
    //开始正转
    setMotorForward();
  }
  //如果参数为假，并且当前窗帘为关闭状态，那
  else if (status == false && motorStatus == true) {
    //开始反转
    setMotorReversal();
  }
  else {
    return;
  }
  //切换当前电机状态
  motorStatus = (motorStatus == true) ? false : true;
  Serial.print("电机状态为：");
  Serial.println(motorStatus);
}

//检测当前光敏电阻是否达到预设的闸值
//检测当前的温度是否达到了预设的闸值
bool checkStatus() {
  bool status;
  //获取当前的温度
  float temperature = readDht11();
  int val = analogRead(PIN_INPUT);
  //当他检测到当前的光线或者温度达到了预设的值时，就返回ture，否则返回假
  status = (val <= RESISTANCE_BRAKE && temperature >(float)TEMPERATURE_BRAKE) ? true : false;
  //返回false时，窗帘为打开状态。
//  status = (val <= RESISTANCE_BRAKE) ? true : false;
  return status;
}

//读取光敏电阻的阻值
int readAnalog() {
  int val = analogRead(PIN_INPUT);
  return val;
}


//设置电机正转
void setMotorForward() {
  //顺时针旋转一周
  Serial.println("正传一周");
  //按设定的值开始顺时针旋转
  stepper.step(CIRCLE);
}
//设置电机反转
void setMotorReversal() {
  //逆时针旋转一周
  Serial.println("反传一周");
  //按设定的值开始逆时针旋转
  stepper.step(-CIRCLE);
}

//读取当前的温度
int readDht11() {
  //Serial.println("/n");
  int chk = DHT11.read(DHT11PIN);

  //湿度
  float humidity = (float)DHT11.humidity;
  //温度
  float temperature = (float)DHT11.temperature;
  Serial.print("温度 (oC): ");
  Serial.println((float)DHT11.temperature, 2);
  return temperature;
}
