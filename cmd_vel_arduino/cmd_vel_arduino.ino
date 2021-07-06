#include <ros.h>
// #include <std_msgs/String.h>
// #include <std_msgs/UInt16.h>
#include <geometry_msgs/Twist.h>
//#include 
// #define BUTTON 8
// #define LED 13
#define motor_a_one 2
#define motor_a_two 3
#define motor_b_one 4
#define motor_b_two 5
#define enA 9
#define enB 10



int linear_velocity_scaling;
int angular_velocity_scaling;


ros::NodeHandle node_handle;

// std_msgs::String button_msg;
geometry_msgs::Twist twist_msg;
// std_msgs::UInt16 led_msg;

//void subscriberCallback(const std_msgs::UInt16& led_msg) {
//  if (led_msg.data  == 1) {
//    digitalWrite(LED, HIGH); 
//  } else {
//    digitalWrite(LED, LOW);
//  }
//}

void subscriberTwistBack(const geometry_msgs::Twist& twist_msg) {
  if (twist_msg.linear.x > 0 && twist_msg.angular.z == 0) {              //for forward linear 
    linear_velocity_scaling = map(twist_msg.linear.x, 0.00, 3.00, 0, 255);
    analogWrite(enA, linear_velocity_scaling);
    analogWrite(enB, linear_velocity_scaling);
    digitalWrite(motor_a_one, HIGH);
    digitalWrite(motor_a_two, LOW);
    digitalWrite(motor_b_one, HIGH);
    digitalWrite(motor_b_two, LOW);
  } 
  
  else if (twist_msg.linear.x < 0 && twist_msg.angular.z == 0) {        //for backward linear
    linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255);
    analogWrite(enA, linear_velocity_scaling);
    analogWrite(enB, linear_velocity_scaling);
    digitalWrite(motor_a_one, LOW);
    digitalWrite(motor_a_two, HIGH);
    digitalWrite(motor_b_one, LOW);
    digitalWrite(motor_b_two, HIGH);
  }
  
  else if (twist_msg.linear.x > 0 && twist_msg.angular.z > 0) {        //for right long turn 
    linear_velocity_scaling = map(twist_msg.linear.x, 0.00, 3.00, 0, 255);
    angular_velocity_scaling = map(twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, linear_velocity_scaling);
    analogWrite(enB, angular_velocity_scaling);
    digitalWrite(motor_a_one, LOW);
    digitalWrite(motor_a_two, HIGH);
    digitalWrite(motor_b_one, LOW);
    digitalWrite(motor_b_two, HIGH);
  }

  else if (twist_msg.linear.x > 0 && twist_msg.angular.z < 0) {        //for left long turn 
    linear_velocity_scaling = map(twist_msg.linear.x, 0.00, 3.00, 0, 255);
    angular_velocity_scaling = map(-twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, angular_velocity_scaling);
    analogWrite(enB, linear_velocity_scaling);
    digitalWrite(motor_a_one, HIGH);
    digitalWrite(motor_a_two, LOW);
    digitalWrite(motor_b_one, HIGH);
    digitalWrite(motor_b_two, LOW);
  }


  else if (twist_msg.linear.x < 0 && twist_msg.angular.z > 0) {        //for right long turn back
    linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255);
    angular_velocity_scaling = map(twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, linear_velocity_scaling);
    analogWrite(enB, angular_velocity_scaling);
    digitalWrite(motor_a_one, HIGH);
    digitalWrite(motor_a_two, LOW);
    digitalWrite(motor_b_one, HIGH);
    digitalWrite(motor_b_two, LOW);
  }

  else if (twist_msg.linear.x < 0 && twist_msg.angular.z < 0) {        //for left long turn back 
    linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255);
    angular_velocity_scaling = map(-twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, angular_velocity_scaling);
    analogWrite(enB, linear_velocity_scaling);
    digitalWrite(motor_a_one, LOW);
    digitalWrite(motor_a_two, HIGH);
    digitalWrite(motor_b_one, LOW);
    digitalWrite(motor_b_two, HIGH);
  }


  else if (twist_msg.linear.x == 0 && twist_msg.angular.z > 0) {        //for right onspot turn
    // linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255)
    angular_velocity_scaling = map(twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, angular_velocity_scaling);
    analogWrite(enB, angular_velocity_scaling);
    digitalWrite(motor_a_one, HIGH);
    digitalWrite(motor_a_two, LOW);
    digitalWrite(motor_b_one, LOW);
    digitalWrite(motor_b_two, HIGH);
  }

  else if (twist_msg.linear.x == 0 && twist_msg.angular.z < 0) {        //for left onspot turn 
    // linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255)
    angular_velocity_scaling = map(-twist_msg.angular.z, 0.00, 3.00, 0, 255);
    analogWrite(enA, angular_velocity_scaling);
    analogWrite(enB, linear_velocity_scaling);
    digitalWrite(motor_a_one, LOW);
    digitalWrite(motor_a_two, HIGH);
    digitalWrite(motor_b_one, HIGH);
    digitalWrite(motor_b_two, LOW);
  }



  else {
//    linear_velocity_scaling = map(-twist_msg.linear.x, 0.00, 3.00, 0, 255)
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    digitalWrite(motor_a_one, LOW);
    digitalWrite(motor_a_two, LOW);
    digitalWrite(motor_b_one, LOW);
    digitalWrite(motor_b_two, LOW);
  }
}



// ros::Publisher button_publisher("button_press", &button_msg);
// ros::Subscriber<std_msgs::UInt16> led_subscriber("toggle_led", &subscriberCallback);
ros::Subscriber<geometry_msgs::Twist> vel_subscriber("cmd_vel", &subscriberTwistBack);


void setup()
{
  pinMode(motor_a_one, OUTPUT);
  pinMode(motor_a_two, OUTPUT);
  pinMode(motor_b_one, OUTPUT);
  pinMode(motor_a_two, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // pinMode(BUTTON, INPUT);
  // pinMode(BUTTON, INPUT);
  
  node_handle.initNode();
  // node_handle.advertise(button_publisher);
  node_handle.subscribe(vel_subscriber);
//  Serial.begin(57600);
}

void loop()
{ 
  // if (digitalRead(BUTTON) == HIGH) {
  //   button_msg.data = "Pressed";
  // } else {
  //   button_mtsg.data = "NOT pressed";
  // }
//   Serial.print("Gels");
  // button_publisher.publish( &button_msg );
  node_handle.spinOnce();
  
  delay(100);
}
