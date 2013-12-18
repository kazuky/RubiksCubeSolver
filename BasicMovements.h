void moveAnd(short motorname, int targetValue);
void moveFor(short motorname, int targetValue);
void moveTo (short motorname, int targetAngle);
void adjust (short motorname, int targetAngle);
int  toAngle(int angle);
void showData();
void getOut();
void getIn();
void wait();

void moveAnd(short motorname, int targetValue){
	nMotorEncoderTarget[motorname] = abs(targetValue);
	motor[motorname] = power*sgn(targetValue);
}

void moveFor(short motorname, int targetValue){
	if(simulator) return;
	moveAnd(motorname, targetValue);
	while(motor[motorname]!=0){
		showData();
		if(nNxtButtonPressed==2||nNxtButtonPressed==1||nNxtButtonPressed==3){
			if(nNxtButtonPressed==3) phaser = (phaser+1)%2;
			else if(nNxtButtonPressed==1) gap[phaser]++;
			else 										 gap[phaser]--;
			wait();
		}
	}
}

void moveTo(short motorname, int targetAngle){
	int dist = toAngle(targetAngle-nMotorEncoder[motorname]);
	if(dist>180) dist-=360;
	moveFor(motorname, dist);
}

void adjust(short motorname, int targetAngle){
	int currentAngle = toAngle(nMotorEncoder[motorname]);

	int angle = currentAngle % targetAngle;
	if(angle > targetAngle/2) {
		angle = currentAngle + targetAngle - angle;
 	} else {
 		angle = currentAngle -angle;
 	}
 	for(int i=0;i<1;i++){
		moveTo(motorname,angle);
		if(nMotorEncoder[motorname]==angle) break;
	}
}

int toAngle(int angle){
	angle = angle%360;
	if(angle<0) angle+=360;
	return angle;
}

void getOut(){
	if(solving)
		moveTo(flipper, -45);
	else
		moveTo(flipper, -70);
}

void getIn(){
	moveTo(flipper, 0);
}

void wait() {
	while(nNxtButtonPressed == -1) {}
	while(nNxtButtonPressed != -1) {}
}
