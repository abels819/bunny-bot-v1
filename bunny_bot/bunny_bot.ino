
#define human_IR A2
#define sonic_in A0
#define noise_in A1

int legs_controll = 2;
int arms_controll = 4;
int spine_controll = 6;
int legs_return_signal=3;
int arms_return_signal=5;
int spine_return_signal=7;
int foot_bottom_sensor_LR = 8;
int foot_bottom_sensor_RR = 9;
int foot_bottom_sensor_LF = 10;
int foot_bottom_sensor_RF = 11;
int nose_tip_sensor = 12;
int sonic_trigger=13;
int IR_timer_detected;
int IR_timer_undetected;
int scared_timer;
int lifted_timer;
int confirm_lifted_timer_top=1; // value for brain to count if the time is long enough to judge that being lifted
int happy_limit_top=10;  //value for brain to count if the time is long enough to expire happy mode
int undetection_limit=10;  //value for brain to count if the time is long enough since first lose sign of human
int scared_timer_top=10; //value for brain to count if the time is enough to expire scared mode
int human_IR_judge_true=700; //value for human detector to decide if there is a human
int scaring_noise=100;//value for noise detector to decide if being scared    /tested & modified
void setup() {
  Serial.begin(9600);
  scared_timer=scared_timer_top+1;
  IR_timer_detected=0;
  IR_timer_undetected=undetection_limit+1;
  lifted_timer=0;
  pinMode(legs_controll, OUTPUT);
  pinMode(arms_controll, OUTPUT);
  pinMode(spine_controll, OUTPUT);
  pinMode(legs_return_signal,INPUT);
  pinMode(arms_return_signal,INPUT);
  pinMode(spine_return_signal,INPUT);
  pinMode(foot_bottom_sensor_LR, INPUT);
  pinMode(foot_bottom_sensor_RR, INPUT);
  pinMode(foot_bottom_sensor_LF, INPUT);
  pinMode(foot_bottom_sensor_RF, INPUT);
  pinMode(nose_tip_sensor, INPUT);
  pinMode(sonic_trigger,OUTPUT);
  pinMode(sonic_in,INPUT);
  randomSeed(analogRead(A0));
}


//neuron simulation send&receive protocal_________________________________________________________________________________________________________________

float check_distance(){
  digitalWrite(sonic_trigger,LOW);
  delay(2);
  digitalWrite(sonic_trigger,HIGH);
  delay(10);
  digitalWrite(sonic_trigger,LOW);
  return pulseIn(sonic_in,HIGH)/58;
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
    int gather=digitalRead(legs_return_signal)+digitalRead(arms_return_signal)+digitalRead(spine_return_signal);
    while(gather<3){
      //gather=3;
      //remove this line when deploying
      gather=digitalRead(legs_return_signal)+digitalRead(arms_return_signal)+digitalRead(spine_return_signal);
      //restore this line when deploying
    }
    //gather=0;
    //remove this line when deploying
}






//foundation motion base_________________________________________________________________________________________________________________________________
void head_check_left(){
  signal_operation(0.2);  
}
void head_check_right(){
  signal_operation(0.22);  
}
void head_check_half_left(){
  signal_operation(0.28);  
}
void head_check_half_right(){
  signal_operation(0.30);  
}
void head_check_low(){
  signal_operation(0.24);  
}
void head_check_high(){
  signal_operation(0.26);  
}
void head_return(){
  signal_operation(0.27);  
}








// motion base______________________________________________________________________________________________________________________________________________


//movements.................................................................................................................................................

void run_forward(){
  if(check_distance()>20){
    signal_operation(0.01);
  }
  Serial.println("running forward");
}
void run_left(){
  head_check_left();
  if(check_distance()>20){
    signal_operation(0.02);
  }
  head_return();
  Serial.println("running left");
}
void run_right(){
  head_check_right();
  if(check_distance()>20){
    signal_operation(0.03);
  }
  head_return();
  Serial.println("running right");
}
void walk_forward(){
  if(check_distance()>10){
    signal_operation(0.04);
  }
  Serial.println("walking forward");
}
void walk_left(){
  head_check_left();
  if(check_distance()>20){
    signal_operation(0.05);
  }
  head_return();
  Serial.println("walking left");
}
void walk_right(){
  head_check_right();
  if(check_distance()>20){
    signal_operation(0.06);
  }
  head_return();
  Serial.println("walking right");
  
}
void half_left(){
  head_check_half_left();
  if(check_distance()>50){
    signal_operation(0.18);  
  }
  head_return();
}
void half_right(){
  head_check_half_right();
  if(check_distance()>50){
    signal_operation(0.19);  
  }
  head_return();
}
void run_scared_for(){
  if(check_distance>50){
    signal_operation(0.11);
  }
  Serial.println("scared forward");
  
}
void run_scared_left(){
  head_check_left();
  if(check_distance>50){
    signal_operation(0.12);
  }
  head_return();
  Serial.println("scared left");
  
}
void run_scared_right(){
  head_check_right();
  if(check_distance>50){
    signal_operation(0.13);
  }
  head_return();
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
}
void lifted_2(){
  signal_operation(0.15);
}
void lifted_3(){
  signal_operation(0.16);
}





//mood base_________________________________________________________________________________________________________________________________________________

void do_happy(){
  int todo=random(200);
  
  if(0<=todo&&todo<10){
    walk_forward();
  }
  else if(10<=todo&&todo<18){
    walk_left();
  }
  else if(18<=todo&&todo<26){
    walk_right();
  }
  else if(26<=todo&&todo<34){
    stand_up();  
  }
  else if(34<=todo&&todo<40){
    prone();  
  }
  else if(40<=todo&&todo<45){
    face_rob_short();  
  }
  else if(45<=todo&&todo<60){
    push_human();  
  }
  else if(60<=todo&&todo<80){
    run_forward();
  }
  else if(80<=todo&&todo<100){
    run_left();
  }
  else if(100<=todo&&todo<120){
    run_right();
  }
}


//___________________________________________________________________________________________________________________________________________________________________________

void do_scared(){
  int todo=random(100);
  if(0<=todo&&todo<30){
    run_scared_for();
  }
  else if(30<=todo&&todo<60){
    run_scared_left();
  }
  else if(60<=todo&&todo<90){
    run_scared_right();
  }
}
//_____________________________________________________________________________________________________________________________________________________________________________
void do_normal(){
  int todo=random(300);
  Serial.println(todo);
  if(0<=todo&&todo<10){
    walk_forward();
  }
  else if(10<=todo&&todo<18){
    walk_left();
  }
  else if(18<=todo&&todo<26){
    walk_right();
  }
  else if(26<=todo&&todo<40){
    run_forward();  
  }
  else if(40<=todo&&todo<60){
    run_left();  
  }
  else if(60<=todo&&todo<80){
    run_right();  
  }
  else if(80<todo&&todo<120){
    face_rob_short();
  }
  else if(120<=todo&&todo<150){
    stand_up();  
  }
  else if(150<=todo&&todo<180){
    prone();
  }
  else if(180<=todo&&todo<210){
    stretch();
  }
}
//____________________________________________________________________________________________________________________________________________________________________________
void do_relaxed(){
  int todo=random(300);
  if(0<=todo&&todo<10){
    walk_forward();
  }
  else if(10<=todo&&todo<18){
    walk_left();
  }
  else if(18<=todo&&todo<26){
    walk_right();
  }
  else if(26<=todo&&todo<34){
    stand_up();  
  }
  else if(34<=todo&&todo<40){
    prone();  
  }
  else if(40<=todo&&todo<45){
    face_rob_short();  
  }
}
//_____________________________________________________________________________________________________________________________________________________________________________
int judge_mood(){
    if(analogRead(noise_in)>=scaring_noise&&analogRead(human_IR<=human_IR_judge_true)){
        scared_timer=0;
        return 2;  
    }
    else if(scared_timer<scared_timer_top){
        scared_timer++;
        return 2  ;
    }
    else if(analogRead(human_IR)>human_IR_judge_true&&scared_timer>=scared_timer_top)  {  //human detected
      IR_timer_undetected=0;
      IR_timer_detected++;
    //human detected as a resume mode or been long
      if(IR_timer_detected!=0){
        if(IR_timer_detected<happy_limit_top){    //human just showed
          return 1;  
        } 
        else{
          return 4;  
        }
        
      }
    //human detected as a new showing
      else {
        return 1; 
      }
    }
    else if(analogRead(human_IR)<human_IR_judge_true&&scared_timer>=scared_timer_top){ //human not detected
    //human undetected as long gone
      IR_timer_undetected++;
      if(IR_timer_undetected>undetection_limit){
        IR_timer_detected=0;
        return 3;  
      }
    //human undetected as just gone
      else{
        if(IR_timer_detected<happy_limit_top&&IR_timer_detected!=0){
          return 1;  
        }
        else if(IR_timer_detected>=happy_limit_top&&IR_timer_detected!=0){
          return 4;
        }  
      }
    }
}


void do_mood(){
    int mood=judge_mood();\
    Serial.println(mood);
    if(mood==1){
        do_happy();  
    }
    else if(mood==2){
        do_scared();  
    }
    else if(mood==3){
        do_normal();  
    }
    else if(mood==4){
        do_relaxed();
    }
    
}

int check_lifted() {
  int LR = digitalRead(foot_bottom_sensor_LR);
  int RR = digitalRead(foot_bottom_sensor_RR);
  int LF = digitalRead(foot_bottom_sensor_LF);
  int RF = digitalRead(foot_bottom_sensor_RF);
  if ((LR + RR + LF + RF) == 0) {
    //return 1;
  }
  else {
    //return 0;
  }
  return 0;
}

void lifted_react(){
  int todo=random(300);
  //Serial.println("lifted");
  if(todo<=20){
    lifted_1();
  }
  else if(20<todo<=50){
    lifted_2();
  }
  else if(50<todo<100){
    lifted_3();
  }
}

void loop() {
  randomSeed(analogRead(0));
  if (check_lifted() == 1) {
    if (lifted_timer > confirm_lifted_timer_top) {
      IR_timer_detected = 0;
      IR_timer_undetected = 0;
      scared_timer = 501;
      lifted_react();
    }
    else {
      delay(1);
      lifted_timer++;
    }
  }
  else {
    lifted_timer = 0;
    do_mood();
  }
}
