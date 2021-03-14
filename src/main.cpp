#include "header.h"
char qr_info[] = "123+321";
char order_info[3] = "";
void setup() {
Serial.begin(9600,SERIAL_8N1);  //启动串行通信
    get_order_info();
    if (qr_info[0]== order_info[0]){
        Serial.print("yes");
    } else{
        Serial.print("no");
    }
//    Serial.print(order_info[0]);
//    Serial.print(qr_info[0]);
//Serial.print(qr_info[1]);
}
void loop(){



}
// 获取物料原始摆放顺序
void get_order_info(){

    claw(0,1);
    order_info[0]= read_rgb();
    claw(0,2);
    order_info[1] = read_rgb();

}

// 爪子动作设置
void claw(int stage,int action){
//    (0,1) 爪子伸到左边物料检测颜色
//    (0,2) 爪子伸到中间边物料检测颜色

}