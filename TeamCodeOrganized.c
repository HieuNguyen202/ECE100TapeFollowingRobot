/*Competition 1 Team 1
require turtle.c, timer.c, avoid.c.*/


//Declartion of Variables
/*Left Side*/
int LEFT_MOTOR = 0;
int LEFT_MOTOR_SPEED = 95;
int LEFT_TOUCH = 10;
int LEFT_EYE = 2;
int leftJustActivated = 0;
/*Right Side*/
int RIGHT_MOTOR = 2;
int RIGHT_MOTOR_SPEED = 100;
int RIGHT_TOUCH = 15;
int RIGHT_EYE = 3;
int rightJustActivated = 0;
/*Sleep Times*/
float turnDelay = 0.13;
float backDelay = 0.2;
float randomTime = 0.5;
/*other variables*/
int lastSensorOnTrack; //0: left	2: right
int lastSensorOffTrack; //0: left	2: right



//Movement Abstractions (Defined out functions here)
/*timer.c*/
float _timer;
void reset_timer(){
    _timer=seconds();
}
float timer(){
    return seconds()- _timer;
}
/*avoid.c*/
void random_avoid(){
    backward(); sleep(backDelay);
    set_beeper_pitch(1000.); beeper_on();
    if(leftJustActivated==1) left();
    else right();
    sleep(turnDelay);
    //sleep((float)random(100)/100.+0.5);
    beeper_off();
}
void left_avoid(){
    backward(); sleep(backDelay);
    right(); sleep(turnDelay);
}
void right_avoid(){
    backward(); sleep(backDelay);
    left(); sleep(turnDelay);
}
/*turtle.ic*/
void forward(){
    motor(LEFT_MOTOR,LEFT_MOTOR_SPEED);
    motor(RIGHT_MOTOR,RIGHT_MOTOR_SPEED);
}
void backward(){
    motor(LEFT_MOTOR,-LEFT_MOTOR_SPEED);
    motor(RIGHT_MOTOR,-RIGHT_MOTOR_SPEED);
}
void right(){
    motor(LEFT_MOTOR,LEFT_MOTOR_SPEED);
    motor(RIGHT_MOTOR,-RIGHT_MOTOR_SPEED);
}
void left(){
    motor(LEFT_MOTOR,-LEFT_MOTOR_SPEED);
    motor(RIGHT_MOTOR,RIGHT_MOTOR_SPEED);
}
void stop(){
    off(LEFT_MOTOR);
    off(RIGHT_MOTOR);
}
/*Normal.c converts light sensor readings to 0 to 100 motor power levels*/
int normalize(int light, int MIN_LIGHT, int MAX_LIGHT){
    int output=100-((light-MAX_LIGHT)*100/(MIN_LIGHT-MAX_LIGHT));
    if  (output<0) output=0;
    if  (output>100) output=100;
    return output;
}
int FIND_MAX_LIGHT(int sensor){
    int light=analog(sensor);
    int MAX_LIGHT=light;
    reset_timer();
    set_beeper_pitch(1000.);
    while(timer()<3.)
      {
        right();
        beeper_on();
        light=analog(sensor);
        if(light<MAX_LIGHT) MAX_LIGHT=light;
    }
    stop();
    beeper_off();
    return MAX_LIGHT;
}
int FIND_MIN_LIGHT(int sensor){
    int light=analog(sensor);
    int MIN_LIGHT=light;
    reset_timer();
    set_beeper_pitch(500.);
    while(timer()<3.)
      {
        left();
        beeper_on();
        light=analog(sensor);
        if(light>MIN_LIGHT) MIN_LIGHT=light;
    }
    stop();
    beeper_off();
    return MIN_LIGHT;
}
int OnTrack(int sensor, int tolerance){
    if(analog(sensor)<MAX_LIGHT+tolerance) return 1;
    else return 0;
}



//Run the Methods here
void main()	{
	//NoahSolution();
	HieuSolution();
	//NickSolution();
}



//A list of Everyone's Solution Methods:
/*Noah's Solution Method*/
void NoahSolution() {
	int recent_bumps = 0;
	reset_timer();
	
	while(1) 
	{
		forward();
		if(!(digital(LEFT_EYE) > 150)) 
		{
			if (timer() < 2.) 
			{
				if (recent_bumps == 5) 
				{
					random_avoid();
					reset_timer();
					recent_bumps = 0;
				} 
				else 
				{
					left_avoid();
					reset_timer();
					recent_bumps++;
				} 
			}
				else 
				{
					left_avoid();
					reset_timer();
					recent_bumps = 1;
				}
		}	
		if (!(digital(RIGHT_EYE) > 150)) 
		{
			if (timer() < 2.) 
			{
				if(recent_bumps == 5) 
				{
					random_avoid();
					reset_timer();
					recent_bumps = 0;
				} else 
				{
					right_avoid();
					reset_timer();
					recent_bumps++;
				}
			} 
			else 
			{
				right_avoid();
				reset_timer();
				recent_bumps = 1;
			}
		}
	}
} 
/*Hieu's Solution Method*/
void HieuSolution()	{	
	int recent_bumps=0;
    int max_Bumps = 4;
    int LEFT_MAX_LIGHT=FIND_MAX_LIGHT(LEFT_EYE);
    int LEFT_MIN_LIGHT=FIND_MIN_LIGHT(LEFT_EYE);
    int RIGHT_MAX_LIGHT=FIND_MAX_LIGHT(RIGHT_EYE);
    int RIGHT_MIN_LIGHT=FIND_MIN_LIGHT(RIGHT_EYE);
    while(1){
        //motor(RIGHT_MOTOR,normalize(analog(LEFT_EYE),LEFT_MIN_LIGHT,LEFT_MAX_LIGHT));
        //motor(LEFT_MOTOR,normalize(analog(RIGHT_EYE),RIGHT_MIN_LIGHT,RIGHT_MAX_LIGHT));
	    // need a multitasked program to check which one is last on track which one is off.
        if(OnTrack(LEFT_EYE,5))
          {
            if(OnTrack(RIGHT_EYE,5))
              {
                //It encounter a turn, turn toward the last off track motor.
		if (lastSensorOffTrack==LEFT_EYE) left(); else right();
		while(OnTrack(lastSensorOnTrack)==false)
		{
		}
              }
            else
              {
                //Right off, left on -> Good keep moving forward
		forward();
              }
          }
        else
          {
            if(OnTrack(RIGHT_EYE,5))
              {
                //Right on, left off, Good keep moving forward
		forward();
              }
            else
              {
                //Both are off track, not good, veer back towards the side of the last sensor on track until it's on track again
                if (lastSensorOnTrack==LEFT_EYE) left(); else right();
		while(OnTrack(lastSensorOnTrack)==false)
		{
		}
              }
          }
    }
}
/*Nick's Solution Method*/
void NickSolution()	{
//sensors outside code


//guessing around where the sensors will be reading off and on the tape to use in the "while" and "if" conditions.
int onTape=65;
int offTape=120;

//counter var.  

int counter;

//new functions to get the robot to veer to the right or left instead of actually turning.
void veerRight(){
    
    motor(LEFT_MOTOR, 100);
    
       
}

void veerLeft(){
    motor(RIGHT_MOTOR, 100);
}



//just to get the robot moving
forward();
sleep(.02);


//assuming both sensors start on the tape this will have the robot veer to the right until the right sensor is off
do{                                 
    veerRight();
    sleep(.02);
        
        
}while(digital(RIGHT_EYE) < onTape && digital(LEFT_EYE) < onTape);
    
while(1){    
    //this just has the robot going back and fourth waiting for one sensor or the other to go off the tape.  
    if(digital(RIGHT_EYE) > offTape){
        
        veerLeft();
        sleep(.02);
        counter = 1;
    }
    
    if(digital(LEFT_EYE) > offTape){
        
        veerRight();
        sleep(.02);
        counter = 0;
        
    }
    //incase both sensors are both on the tape at the same time. 
    else{
        
        if(counter = 1){
            
            veerLeft();
            sleep(.02);
            counter = 1;        
        }
        if(counter = 0){
            veerRight();
            sleep(.02);
            counter = 0;
        }
        
    }
}
	
}



/*Competition 0 Code
Add the ability for the robot to sense obstacle, so it can make left, right, metasensed turns to avoid the obstacles.

void bumper(){
    reset_timer();
    while(1){
        forward();
        if(digital(LEFT_TOUCH)){
            if(timer()<randomTime){
                leftJustActivated=1;
                rightJustActivated=0;
                if(recent_bumps==max_Bumps){
                    random_avoid();
                    reset_timer();
                    recent_bumps=0;
                }else{
                    left_avoid();
                    reset_timer();
                    recent_bumps++;
                }
            }else{
                left_avoid();
                reset_timer();
                recent_bumps=1;
            }
        }
        if(digital(RIGHT_TOUCH)){
            if(timer()<randomTime){
                leftJustActivated=0;
                rightJustActivated=1;
                if(recent_bumps==max_Bumps){
                    random_avoid();
                    reset_timer();
                    recent_bumps=0;
                }else{
                    right_avoid();
                    reset_timer();
                    recent_bumps++;
                }
            }else{
                right_avoid();
                reset_timer();
                recent_bumps=1;
            }
        }
    }
}

