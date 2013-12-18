void scanFaces();
void scanaFace(int i);
void scanFour(int i, bool outside);
TColors scanColor(int faceNumber);
void rankRed();
void setUpSensor();
bool solvabler();
bool solve();
bool findPair(TColors col1, TColors col2);
bool findTorio(TColors col1, TColors col2, TColors col3);

void scanFaces(){
	nxtDisplayCenteredTextLine(0,"Scanning...");
	di[0] = 27;
	di[1] = 18;
	di[2] = 36;
	ClearTimer(T3);
	if(simulator){
		TColors colorlist[6] = { YELLOWCOLOR, GREENCOLOR, BLACKCOLOR, WHITECOLOR, BLUECOLOR, REDCOLOR };
		for(int i=0;i<6;i++){
			for(int j=0;j<9;j++){
				face[i*9+j]=colorlist[i];
			}
		}
		solving=true;
		return;
	}

	for(int i=0;i<54;i++) face[i] = 7;
	getOut();
	setUpSensor();

	for(int i=0;i<6;i++){
		centerFace = i;
		scanaFace(i);
		moveTo(spinner, 120);
		adjust(table,90);
		flip();
		turn(2);
	}

	rankRed();
	moveTo(table, 0);
	moveTo(spinner,150);
	getIn();
}

void scanaFace(int i){
	moveTo(spinner, 0);
	face[i*9] = scanColor(i*9);

	scanFour(i, false);
	scanFour(i, true );

	if(i % 2 == 1) {
		moveTo(table, 180);
	}else{
		moveTo(table, -90);
	}
}

void scanFour(int i, bool outside){
	int lala, counter = 1, hihi = 1, inval= 19;
	if(outside){
		hihi+=4;
		inval+= 10;
	}else{
		moveFor(table,-22);
	}
	moveTo(spinner,inval);
	lala = nMotorEncoder[table];
	face[i*9+hihi] = scanColor(i*9+hihi);
	motor[table] = -20;
	while(abs(nMotorEncoder[table] - lala) < 308){
		if(abs(nMotorEncoder[table] - lala) > counter*90){
			face[i*9+counter+hihi] = scanColor(i*9+counter+hihi);
			counter++;
		}
		showData();
	}
	motor[table] = 0;
}

TColors scanColor(int faceNumber){
	TColors colorFound = SensorValue[color];
	if(colorFound == REDCOLOR) {
		short ADValues[4];
		long sum = 0;
		for(int i=0;i<100;i++){
			getColorSensorData(color, colorAtoD,    &ADValues[0]);
			sum += ADValues[0];
		}
		if(redCount>35) return colorFound;
	  reds[redCount] = faceNumber;
	  reds[redCount+1] = sum;
	  redCount+=2;
	}
	return colorFound;
}

void rankRed(){
	TColors colorList[4] = {BLUECOLOR, YELLOWCOLOR, GREENCOLOR, WHITECOLOR};
	long compe[2], place[2];
	for(int i=0;i<6;i++){
		if(face[i*9]==REDCOLOR){
			place[0] = i*9;
			place[1] = (place[0]+27)%54;
			break;
		}
	}
	for(int j=0;j<18;j++){
		if(reds[j*2]==place[0]) compe[0] = reds[j*2+1];
		if(reds[j*2]==place[1]) compe[1] = reds[j*2+1];
	}
	if(compe[0]<compe[1]) face[place[1]] = BLACKCOLOR;
	else									face[place[0]] = BLACKCOLOR;
	for(int i=0;i<4;i++){
		for(int k=0;k<2;k++){
			findPair(REDCOLOR, colorList[i]);
			place[k] = pairC[0];
			for(int j=0;j<18;j++){
				if(reds[j*2]==place[k]){
					compe[k] = reds[j*2+1];
					break;
				}
			}
			face[place[k]] = BLACKCOLOR;
		}
		if(compe[0]>compe[1]) face[place[1]] = REDCOLOR;
		else									face[place[0]] = REDCOLOR;
	}
	for(int i=0;i<4;i++){
		for(int k=0;k<2;k++){
			findTorio(REDCOLOR, colorList[i], colorList[(i+1)%4]);
			place[k] = toriC[0];
			for(int j=0;j<18;j++){
				if(reds[j*2]==place[k]){
					compe[k] = reds[j*2+1];
					break;
				}
			}
			face[place[k]] = BLACKCOLOR;
		}
		if(compe[0]>compe[1]) face[place[1]] = REDCOLOR;
		else									face[place[0]] = REDCOLOR;
	}
}

void setUpSensor(){
	int angle[2];
	motor[spinner] = -20;
	while(SensorValue[color]==BLACKCOLOR) angle[0] = nMotorEncoder[spinner];
	motor[spinner] = 0;
	moveFor(spinner, -100);
	motor[spinner] = 20;
	while(SensorValue[color]==BLACKCOLOR) angle[1] = nMotorEncoder[spinner];
	motor[spinner] = 0;
	moveTo(spinner, (angle[0]+angle[1])/2);
	nMotorEncoder[spinner] = 0;
}

bool solvabler(){
	TColors save[54];
	bool result;
	for(int i=0;i<54;i++)	save[i] = face[i];
	simulator = true;
	result = solve();
	if(!result){
		displayData();
		for(int i=0;i<54;i++) face[i] = save[i];
		di[0] = 27;
		di[1] = 18;
		di[2] = 36;
		sbyte switcher;
		findPair(REDCOLOR,GREENCOLOR);
		switcher = pairC[0];
		findPair(BLACKCOLOR,GREENCOLOR);
		face[pairC[0]] = REDCOLOR;
		face[switcher] = BLACKCOLOR;
		result = solve();
	}

	for(int i=0;i<54;i++) face[i] = save[i];
	di[0] = 27;
	di[1] = 18;
	di[2] = 36;
	simulator = false;
	if(result){
		goalCount = moveCount;
	}else{
		flip();
		adjust(table,90);
		nMotorEncoder[table]   = 0;
	}
	return result;
}
