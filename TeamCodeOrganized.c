/*Competition 1 Team 1
require turtle.c, timer.c, avoid.c*/


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
        if(OnTrack(LEFT_EYE,5))
          {
            if(OnTrack(RIGHT_EYE,5))
              {
                //Both are on track, execute path seeking codes.
            }
            else
              {
                //Right off, left on -> stop or slow down right motor until... start timer
            }
        }
        else
          {
            if(OnTrack(RIGHT_EYE,5))
              {
                //Right on, left off, stop or slow down left motor until...
            }
            else
              {
                //Both are off track, keep moving forward.
                
            }
        }
    }
}
/*Nick's Solution Method*/
void NickSolution()	{
	
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

