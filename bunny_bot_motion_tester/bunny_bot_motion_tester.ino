int legs_controll=2;
int spine_controll=3;
int arms_controll=4;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(legs_controll,OUTPUT);
    pinMode(arms_controll,OUTPUT);
    pinMode(spine_controll,OUTPUT);
}


void signal_operation(float pwm){
    for(int i=0;i<3;i++){
      digitalWrite(spine_controll,HIGH);
      digitalWrite(legs_controll,HIGH);
      digitalWrite(arms_controll,HIGH);
      delayMicroseconds(pwm*1000);
      digitalWrite(spine_controll,LOW);
      digitalWrite(legs_controll,LOW);
      digitalWrite(arms_controll,LOW);
      delayMicroseconds((0.1-pwm)*1000);
    }
}






//foundation motion base_________________________________________________________________________________________________________________________________
void head_check_left(){
  signal_operation(0.2);  
  Serial.println("check left");
}
void head_check_right(){
  signal_operation(0.22); 
  Serial.println("check right"); 
}
void head_check_half_left(){
  signal_operation(0.28);  
  Serial.println("check half left");
}
void head_check_half_right(){
  signal_operation(0.30);  
  Serial.println("check half right");
}
void head_check_low(){
  signal_operation(0.24);  
  Serial.println("check low");
}
void head_check_high(){
  signal_operation(0.26);  
  Serial.println("check high");
}
void head_return(){
  signal_operation(0.27);  
  Serial.println("return");
}








// motion base______________________________________________________________________________________________________________________________________________


//movements.................................................................................................................................................

void run_forward(){
  signal_operation(0.01);
  Serial.println("running forward");
}
void run_left(){
  signal_operation(0.02);
  Serial.println("running left");
}
void run_right(){
    signal_operation(0.03);
  Serial.println("running right");
}
void walk_forward(){
    signal_operation(0.04);
  Serial.println("walking forward");
}
void walk_left(){
    signal_operation(0.05);
  Serial.println("walking left");
}
void walk_right(){
    signal_operation(0.06);
  Serial.println("walking right");
  
}
void half_left(){
    signal_operation(0.18);  
  Serial.println("half left");
}
void half_right(){
    signal_operation(0.19);
    Serial.println("half right");  
}
void run_scared_for(){
    signal_operation(0.11);
  Serial.println("scared forward");
  
}
void run_scared_left(){
    signal_operation(0.12);
  Serial.println("scared left");
  
}
void run_scared_right(){
    signal_operation(0.13);
  Serial.println("scared right");
  
}

//mothions without opsition changing................................................................................................................................


void stand_up(){
  Serial.println("standing up");
  signal_operation(0.07);
}
void prone(){
  Serial.println("going prone");
  signal_operation(0.08);
}
void face_rob_short(){
  Serial.println("face robbing");
  signal_operation(0.09);
}
void push_human(){
  Serial.println("pushy pushy");
  signal_operation(0.1);
}
void stretch(){
  signal_operation(0.17);
  Serial.println("stretching");
}

void lifted_1(){
  signal_operation(0.14);
  Serial.println("lifted1");
}
void lifted_2(){
  signal_operation(0.15);
  Serial.println("lifted2");
}
void lifted_3(){
  signal_operation(0.16);
  Serial.println("lifted3");
}



void execute(int todo){
  if(todo==1){
    head_check_left();
  }
  if(todo==2){
    head_check_right();
  }
  if(todo==3){
    head_check_half_left();
  }
  if(todo==4){
    head_check_half_right();
  }
  if(todo==5){
    head_check_low();
  }
  if(todo==6){
    head_check_high();
  }
  if(todo==7){
    head_return();
  }
  if(todo==8){
    run_forward();
  }
  if(todo==9){
    run_left();
  }
  if(todo==10){
    run_right();
  }
  if(todo==11){
    walk_forward();
  }
  if(todo==12){
    walk_left();
  }
  if(todo==13){
    walk_right();
  }
  if(todo==14){
    half_left();
  }
  if(todo==15){
    half_right();
  }
  if(todo==16){
    run_scared_for();
  }
  if(todo==17){
    run_scared_left();
  }
  if(todo==18){
    run_scared_right();
  }
  if(todo==19){
    stand_up();
  }
  if(todo==20){
    prone();
  }
  if(todo==21){
    face_rob_short();
  }
  if(todo==22){
    push_human();
  }
  if(todo==23){
    stretch();
  }
  if(todo==24){
    lifted_1();
  }
  if(todo==25){
    lifted_2();
  }
  if(todo==26){
    lifted_3();
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  int todo=Serial.read();
  if(todo){
    execute(todo);
  }
}
