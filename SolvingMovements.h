void flip();
void turn(int number);
void faceDown(int cen);
void changeFront();
void twist(int number, int cen);
void displayData();

void flip(){
	//In the real world
	getIn();
	if(!solving) wait10Msec(30);
	moveFor(flipper, 80);
	moveFor(flipper, -90);
	getIn();

	if(!solving) return;
	//In the NXT's mind
	sbyte hold = di[0];
	di[0] = di[1];
	di[1] = (hold+27)%54;
}

void turn(int number){
	//In the real world (Counterclockwise)
	getOut();
	moveFor(table, 90*number);
	adjust(table,90);

	if(!solving) return;
	//In the NXT's mind
	sbyte hold;
	number = (number+4)%4;
	for(int i=0;i<number;i++){
		hold  = di[2];
		di[2] = di[1];
		di[1] = (hold+27)%54;
	}
}

void faceDown(int cen){
	if(di[0]!=cen){
		if((di[0]+27)%54==cen){
			flip();
		}else if(di[2]==cen){
			turn(-1);
		}else if((di[2]+27)%54==cen){
			turn(1);
		}else if((di[1]+27)%54==cen){
			turn(2);
		}
		flip();
	}
}

void changeFront(){
	if(changeFrontCount>8) solvable = false;
	//In the real World
	faceDown(27);
	getOut();
	moveFor(table, 90);

	//In the NXT's mind
	TColors hold;
	changeFrontCount++;
	for(int j=0; j<2; j++){
		hold = face[27+1+j*4];
		for(int k=1;k<4;k++){
			face[27+k+j*4] = face[27+k+1+j*4];
		}
		face[27+4+j*4] = hold;
	}
	for(int j=0; j<2; j++){
		hold = face[4+j*4];
		for(int k=4;k>1;k--){
			face[k+j*4] = face[k-1+j*4];
		}
		face[1+j*4] = hold;
	}
	sbyte cenList[5] = {3,6,0,0,0}, cen;
	for(int i=0;i<5;i++){
		cen = cenList[i];
		for(int j=0; j<3; j++){
			hold = face[ref[cen][j*4]];
			for(int k=0;k<3;k++){
				face[ref[cen][j*4+k]] = face[ref[cen][j*4+k+1]];
			}
			face[ref[cen][j*4+3]] = hold;
		}
	}
}

void twist(int number, int cen){
	if(number==0) return;
	//In the real world(TWIST)

	faceDown(cen);
	getIn();
	moveFor(table, 90*number+sgn(number)*gap[0]+gap[1]);
	moveFor(table, -gap[0]*sgn(number)+gap[1]);
	adjust(table, 90);

	//In the NXT's mind
	number = (number+4)%4;
	moveCount++;
	cen = di[0];
	TColors hold;
	for(int i=0;i<number;i++){
		for(int j=0; j<2; j++){
			hold = face[cen+1+j*4];
			for(int k=1;k<4;k++){
				face[cen+k+j*4] = face[cen+k+1+j*4];
			}
			face[cen+4+j*4] = hold;
		}
		for(int j=0; j<3; j++){
			hold = face[ref[cen/9][j*4]];
			for(int k=0;k<3;k++){
				face[ref[cen/9][j*4+k]] = face[ref[cen/9][j*4+k+1]];
			}
			face[ref[cen/9][j*4+3]] = hold;
		}
	}
	showData();
}

void showData(){
	int i=centerFace;
	string cols[9], colorList[7] = {"O","B","G","Y","R","W","X"}, count;
	sbyte colors[7] = {0,0,0,0,0,0,0};
	if(goalCount == -1)StringFormat(count, "%d", moveCount);
	else StringFormat(count, "%d/%d", moveCount, goalCount);
	if(solving){
		string rei = "";
		if(time100[T3]/10%60<10) rei = "0";
		StringFormat(time ,"%d:%s%d", time100[T3]/600, rei, time100[T3]/10%60);
	}
	for(int k=0;k<54;k++){
		colors[face[k]-1]++;
	}
	for(int j=0;j<9;j++){
		cols[j] = colorList[face[i*9+j]-1];
	}
	nxtDisplayTextLine(1,"  %s, %s, %s  O%d B%d ", cols[6], cols[1], cols[5], colors[0], colors[1]);
	nxtDisplayTextLine(2,"  %s, %s, %s  G%d Y%d ", cols[2], cols[0], cols[4], colors[2], colors[3]);
	nxtDisplayTextLine(3,"  %s, %s, %s  R%d W%d ", cols[7], cols[3], cols[8], colors[4], colors[5]);
	nxtDisplayTextLine(4,"           %s-%s-%d", colorList[face[(di[0]+27)%54]-1], colorList[face[di[2]]-1], centerFace);
	nxtDisplayTextLine(5," GAP%d:%d", phaser+1, gap[phaser]);
	nxtDisplayTextLine(6," Move:%s", count);
	nxtDisplayTextLine(7," Time:%s", time);
}

void displayData(){
	while(true){
		showData();
		if(nNxtButtonPressed==1){
			centerFace++;
			while(nNxtButtonPressed==1){}
		}
		if(nNxtButtonPressed==2){
			centerFace--;
			while(nNxtButtonPressed==2){}
		}
		if(nNxtButtonPressed==3){
			wait();
			return;
			twist(1, centerFace*9);
		}
		if(nNxtButtonPressed==0) {
			wait();
			return;
			changeFront();
		}
		if(centerFace<0||centerFace>5) centerFace = (centerFace+6)%6;
		wait10Msec(2);
	}
}
