/*Competition 1 Team 1
//Declartion of Variables
/*Left Side*/
int LEFT_MOTOR = 0;
int LEFT_MOTOR_SPEED = 50;
int LEFT_TOUCH = 10;
int LEFT_EYE = 2;
int leftJustActivated = 0;
/*Right Side*/
int RIGHT_MOTOR = 3;
int RIGHT_MOTOR_SPEED = 50;
int RIGHT_TOUCH = 15;
int RIGHT_EYE = 3;
int rightJustActivated = 0;
/*Sleep Times*/
float turnDelay = 0.13;
float backDelay = 0.2;
float randomTime = 0.5;
/*other variables*/
int lastSensorOnTrack=LEFT_EYE; //0: left 2: right
int lastSensorOffTrack; //0: left 2: right
int LEFT_MAX_LIGHT;
int LEFT_MIN_LIGHT;
int RIGHT_MAX_LIGHT;
int RIGHT_MIN_LIGHT;
float _timer;
int beepCode=0;
int amplifier=6;
void main(){
	
	Calibrator(); // Calibrate MAX and MIN light readings for each sensor.
    start_process(UpdateLastOnTrackSensor());//Constantly update the last sensor on track.
	start_process(UpdateLastOffTrackSensor());//Constantly update the last sensor off track
	start_process(MakeNoise());//Make sound indications
    while(1){
        // need a multitasked program to check which one is last on track which one is off.
        if(OnTrack(LEFT_EYE))
          {
            if(OnTrack(RIGHT_EYE))
            {
                //Both sensors are o track, turn away from the last off track sensor.
                if (lastSensorOffTrack==LEFT_EYE)
				{
					VeerRight();
					while(OnTrack(RIGHT_EYE)){}//Wait untill RIGHT_EYE is off track
					beepCode=2;
				}	
				else
           		{
					VeerLeft();
					while(OnTrack(LEFT_EYE)){} //Wait untill LEFT_EYE is off track
					beepCode=1;
				}	
            }
            else
            {
                //Right off, left on.
                VeerLeft();
				while(OnTrack(LEFT_EYE)){}// Wait untill LEFT_EYE is off track
				beepCode=1;
            }
        }
        else
		{
            if(OnTrack(RIGHT_EYE))
            {
                //Right on, left off.
                VeerRight();
				while(OnTrack(RIGHT_EYE)){}// Wait untill RIGHT_EYE is off track
				beepCode=2;
            }
            else
            {
                //Both are off track, not good, veer back towards the side of the last sensor on track until it's on track again
                if (lastSensorOffTrack==LEFT_EYE)
				{
					VeerLeft();
					reset_timer();
					beepCode=4;
					while(!OnTrack(LEFT_EYE)//Wait untill LEFT_EYE is on track
					{
						if(timer()>1) VeerLeft(10);//seek path
						if(timer()>2) VeerLeft(20);
						if(timer()>3) VeerLeft(30);
					}
					beepCode=0;
				}
				else
				{
					VeerRight();
					reset_timer();
					beepCode=4;
					while(!OnTrack(RIGHT_EYE) //Wait untill RIGHT_EYE is on track
					{
						if(timer()>1) VeerRight(10);//seek path
						if(timer()>2) VeerRight(20);
						if(timer()>3) VeerRight(30);
					}
					beepCode=0;
				}					
            }
        }
    }
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
        forward();
        beeper_on();
        light=analog(sensor);
        if(light<MAX_LIGHT) MAX_LIGHT=light;
		printf("MAX_LIGHT: "+MAX_LIGHT);
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
    while(timer()<3.){
        backward();
        beeper_on();
        light=analog(sensor);
        if(light>MIN_LIGHT) MIN_LIGHT=light;
		printf("MIN_LIGHT: "+MIN_LIGHT);
    }
	beeper_off();
    stop();
    return MIN_LIGHT;
}
int OnTrack(int sensor){
	string divider;
	if (sensor==LEFT_EYE) divider=(LEFT_MIN_LIGHT - LEFT_MAX_LIGHT)/2+LEFT_MAX_LIGHT;
	if (sensor==RIGHT_EYE) divider=(RIGHT_MIN_LIGHT - RIGHT_MAX_LIGHT)/2+RIGHT_MAX_LIGHT;
    if(analog(sensor)<divider)
	{
		printf(sensor+" on track");
		return 1;
	}	
	
    else
	{
		printf(sensor+" off track");
		return 0;
	}
}
//Multitasking processes
void UpdateLastOnTrackSensor(){
    while(1)
      {
        if(OnTrack(LEFT_EYE)) lastSensorOnTrack=LEFT_EYE;
        if(OnTrack(RIGHT_EYE)) lastSensorOnTrack=RIGHT_EYE;
    }
}
void UpdateLastOffTrackSensor(){
    while(1)
      {
        if(!OnTrack(LEFT_EYE)) lastSensorOffTrack=LEFT_EYE;
        if(!OnTrack(RIGHT_EYE)) lastSensorOffTrack=RIGHT_EYE;
    }
}
void MakeNoise(){
	switch(beepCode)
	{
		case 0:
			beeper_off();
			break;
		case 1://left off
			set_beeper_pitch(1000.);
			beeper_on();
			sleep(0.1);
			beeper_off();
			beepCode=0;
			break;
		case 2://right off
			set_beeper_pitch(200.);
			beeper_on();
			sleep(0.1);
			beeper_off();
			beepCode=0;
			break;
		case 3://both on
			set_beeper_pitch(1000.);
			beeper_on();
			sleep(0.1);
			beeper_off();
			sleep(0.1);
			beeper_on();
			sleep(0.1);
			beeper_off();
			beepCode=0;
			break;
		case 4://both off
			set_beeper_pitch(1000.);
			beeper_on();
			amplifier=6;
			while(beepCode>0)
			{
				if(amplifier%5>0)
				set_beeper_pitch((amplifier%5)*200.);
				amplifier++;
				sleep(0.2);
			}
			break;
		case 5://both off
			set_beeper_pitch(1000.);
			beeper_on();
			break;
		default:
			break;
	}
}
//Utility
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
void VeerRight(int curve=0){//curve range from -100 to 100, -100: narrow curve, 0: medium curve, 50: wide curve, 100: Straight line
    motor(LEFT_MOTOR,LEFT_MOTOR_SPEED);
    motor(RIGHT_MOTOR,curve);
}
void VeerLeft(int curve=0){//curve range from -100 to 100, -100: narrow curve, 0: medium curve, 50: wide curve, 100: Straight line
    motor(RIGHT_MOTOR,LEFT_MOTOR_SPEED);
    motor(LEFT_MOTOR,curve);
}
void Calibrator(){
	//Find the max and min light readings of each motor
    LEFT_MAX_LIGHT=FIND_MAX_LIGHT(LEFT_EYE);
    LEFT_MIN_LIGHT=FIND_MIN_LIGHT(LEFT_EYE);
    RIGHT_MAX_LIGHT=FIND_MAX_LIGHT(RIGHT_EYE);
    RIGHT_MIN_LIGHT=FIND_MIN_LIGHT(RIGHT_EYE);
	printf("MaxL 0=%d MaxR 1=%d\n",LEFT_MAX_LIGHT,RIGHT_MAX_LIGHT);
	printf("MinL 0=%d MinR 1=%d\n",LEFT_MIN_LIGHT,RIGHT_MIN_LIGHT);
	sleep(3);
	printf("Left Di 0=%d\n",(LEFT_MIN_LIGHT-LEFT_MAX_LIGHT)/2+LEFT_MAX_LIGHT);
	printf("Right Di 0=%d\n",(RIGHT_MIN_LIGHT,RIGHT_MAX_LIGHT)/2+RIGHT_MAX_LIGHT);
	sleep(3);
}
int GetLastOffTrackSensor(){
	return lastSensorOffTrack;
}
int GetLastOnTrackSensor(){
	return lastSensorOnTrack;
}
void reset_timer(){
    _timer=seconds();
}
float timer(){
    return seconds()- _timer;
}
