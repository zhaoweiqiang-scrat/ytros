#include <stdio.h>
#include "hardwareserial.h"
#include <ros.h>
#include <riki_msgs/Battery.h>
#include <riki_msgs/Angle.h>
#include <geometry_msgs/Vector3.h>
#include <ros/time.h>
#include "delay.h"
#include "usart.h"
#include "config.h"
#include "timer.h"
#include "led.h"
#include <riki_msgs/Battery.h>

ros::NodeHandle  nh;
riki_msgs::Battery raw_battery_msg;
//
//
//
ros::Publisher raw_battery_pub("battery", &raw_battery_msg);
typedef union {
        float real;
        uint8_t base[4];
      } u_yt;

	  
void publishBAT()
{
	raw_battery_msg.surplus_capacity_percent = Surplus_capacity_percent;
	raw_battery_pub.publish(&raw_battery_msg);
}
void print_debug()
{
    nh.loginfo("publish the battery capacity!");

}
int main(void) 
{
	uint32_t previous_debug_time = 0;
	
	SystemInit();
	LED1_Config();
	initialise();
    //delay_init(72);//72M 
	Usart3_Int(9600);
	TIM4_Int_Init(1999,35999);
    #if 0	
	nh.initNode();	
	nh.advertise(raw_battery_pub);
	while (!nh.connected()){
		nh.spinOnce();
	}  
 #endif
	nh.loginfo("Rikibase Connected!");
    //delay_ms(1000);
	while(1){
		
		publishBAT();
		if ((millis() - previous_debug_time) >= (1000 / DEBUG_RATE)) {						
			print_debug();						
		    previous_debug_time = millis();			
		} 
		nh.spinOnce();
    }
	
}


