void step0();
void step1();
void step2();
bool step3();
void step4();
bool step5();
bool step6();
bool step7();
bool step8();
bool checker();

bool solve(){
	solving = true;
	power = 100;
	ClearTimer(T3);
	moveCount = 0;
	centerFace = 3;
	nxtDisplayCenteredTextLine(0,"Solving...");
	for(int i=1;i<=4;i++){
		step1();
		Run();
		changeFront();
	}
	nxtDisplayCenteredTextLine(0,"Cross Done");
	for(int i=1;i<=4;i++){
		step2();
		Run();
		changeFront();
	}
	nxtDisplayCenteredTextLine(0,"Bottom Done");
	if(step3()==false) return false;
	nxtDisplayCenteredTextLine(0,"Sides Done");
	step4();
	nxtDisplayCenteredTextLine(0,"Adjust Done");
	centerFace = 0;
	step5();
	nxtDisplayCenteredTextLine(0,"Cross Done");
	if(step6()==false) return false;
	nxtDisplayCenteredTextLine(0,"Top Done");
	if(step7()==false) return false;
	nxtDisplayCenteredTextLine(0,"Sides Done");
	if(step8()==false) return false;
	nxtDisplayCenteredTextLine(0,"CUBE DONE");

	power = 30;
	getOut();
	moveFor(table, 1440);
	getIn();

	return true;
}

void step0(){
	nxtDisplayCenteredTextLine(0,"Mixing Cube");
	int dontMove[2] = {-1,-1}, x = -1, number = 0;
	for(int i=0;i<20;i++){
		while(x==dontMove[0]||x==dontMove[1]) x = (rand()+6)%6;
		do number = ((rand()+4)%4-1); while(number==0);
		twist(number,x*9);
		if(dontMove[0]!=(x+3)%6){
			dontMove[0] = x;
			dontMove[1] = -1;
		}else{
			dontMove[1] = x;
		}
	}
	nxtDisplayCenteredTextLine(0,"Cube Ready");
	moveCount-=20;
}

void step1(){
	findPair(face[27], face[36]);
	switch(pairC[0]){
		case  1: orderList = "U2F2"; return;
		case  2: orderList = "U'F2"; return;
		case  3: orderList = "F2"; return;
		case  4: orderList = "UF2"; return;

		case 10: orderList = "DRD'"; return;
		case 11: orderList = "BDRD'"; return;
		case 12: orderList = "D'L'D"; return;
		case 13: orderList = "UR'FR"; return;

		case 19: orderList = "L'F'"; return;
		case 20: orderList = "F'"; return;
		case 21: orderList = "LF'L'"; return;
		case 22: orderList = "D2BD2"; return;

		case 28: orderList = "B2U2F2"; return;
		case 29: orderList = "R2UF2"; return;
		case 30: orderList = ""; return;
		case 31: orderList = "L2U'F2"; return;

		case 37: orderList = "DR'D'"; return;
		case 38: orderList = "FDR'D'"; return;
		case 39: orderList = "D'LD"; return;
		case 40: orderList = "DRD'F"; return;

		case 46: orderList = "RF"; return;
		case 47: orderList = "D2B'D2"; return;
		case 48: orderList = "R'FR"; return;
		case 49: orderList = "F"; return;
	}
}

void step2(){
	findTorio(face[27], face[36], face[18]);
	switch(toriC[0]){
		case  5: orderList = "L'BL'B'L2"; return;
		case  6: orderList = "F'D2BD2F"; return;
		case  7: orderList = "L'F'L2FL"; return;
		case  8: orderList = "RF2R'F2R'"; return;

		case 14: orderList = "L'U2L"; return;
		case 15: orderList = "L'BU2B'L"; return;
		case 16: orderList = "B'FU'BF'"; return;
		case 17: orderList = "FU'F'"; return;

		case 23: orderList = "LU2L2UL"; return;
		case 24: orderList = "L'UF'L2FL"; return;
		case 25: orderList = "L'U'L"; return;
		case 26: orderList = "U2L'UL"; return;

		case 32: orderList = "BL'B2U'BL"; return;
		case 33: orderList = "L'R'U2LR"; return;
		case 34: orderList = "F'U'F'R'F2R"; return;
		case 35: orderList = ""; return;

		case 41: orderList = "F'U2F2U'F'"; return;
		case 42: orderList = "UL'U'L"; return;
		case 43: orderList = "FUF'"; return;
		case 44: orderList = "L'F'L2FU'L"; return;

		case 50: orderList = "L'RULR'"; return;
		case 51: orderList = "R'FU2F'R"; return;
		case 52: orderList = "FU2F'"; return;
		case 53: orderList = "L'UL"; return;
	}
}

bool step3(){
	int side[4] = {13,21,38,48};
	string orders[2] = {"RUR'U'F'U'F","L'U'LUFUF'"};
	TColors sideFace,topFace;
	sbyte lag=3,lala = 0;
	for(int j=0;j<10;j++){
		for(int i=0;i<5;i++){
			if(i==4){
				if(face[36]==face[39]&&face[36]==face[37]&&
					 face[45]==face[49]&&face[45]==face[47]&&
					 face[ 9]==face[10]&&face[ 9]==face[12]&&
					 face[18]==face[22]&&face[18]==face[20]) return true;
				while((face[36]==face[39]&&face[18]==face[20])||(face[39]==face[0]||face[20]==face[0])){
					if(!solvable) return false;
					changeFront();
				}
				orderList = orders[1];
				Run();
				break;
			}
			if(face[i+1]!=face[0]&&face[side[i]]!=face[0]){
				sideFace = face[side[i]];
				topFace = face[i+1];
				while(face[36]!=sideFace){
					if(!solvable) return false;
					changeFront();
				}
				lag = 0;
				if(topFace==face[18]) lag+=1;
				findPair(topFace,sideFace);
				if(lag==1){
					twist(pairC[0]%4, 0);
				}else{
					twist((pairC[0]+2)%4,0);
				}
				orderList = orders[lag];
				Run();
				lala++;
				break;
			}
		}
	}
	return false;
}

void step4(){
	int theorder[4], faceNum[4] = {45, 9, 18, 36}, holder, counter;
	while(true){
		counter = 0;
		for(int i=0;i<4;i++){
			findTorio(face[0],face[faceNum[i]],face[faceNum[(i+1)%4]]);
			if(toriC[0]>toriC[1]) toriC[0] = toriC[1];
			if(toriC[0]>toriC[2]) toriC[0] = toriC[2];
			theorder[i] = toriC[0]-5;
		}
		while((theorder[0]+1)%4!=theorder[1]&&counter<4){
			counter++;
			holder = theorder[0];
			for(int i=0;i<3;i++)theorder[i] = theorder[i+1];
			theorder[3] = holder;
		}
		if(theorder[3]==(theorder[2]+1)%4)return;
		for(int i=0;i<theorder[0];i++) changeFront();
		orderList = "RUR'U'F'U2FURUR'";
		Run();
	}
}

bool step5(){
	int tops[4], count = 0;
	for(int i=1;i<=4;i++){
		if(face[0] == face[i]){
			tops[count] = i;
			count++;
		}
	}
	if(count==4) return true;
	if(count==1) return false;
	if(count==0){
		orderList = "R'LFRL'U2R'LFRL'";
		Run();
	}else if(tops[1]-tops[0]==2){
		orderList = "R'LFRL'UR'";
		Run();
		orderList = "LFRL'UR'LFRL'";
		Run();
	}
	while(face[3]!=face[0]||face[4]!=face[0]){
		if(!solvable) return false;
		changeFront();
	}
	orderList = "R'LFRL'U2R'LFRL'";
	Run();
	return true;
}

bool step6(){
	int tops[4], count = 0;
	for(int i=5;i<=8;i++){
		if(face[0] == face[i]){
			tops[count] = i;
			count++;
		}
	}
	orderList = "RUR'URU2R'";
	while(count!=1&&count!=4){
		if(count==0){
			while(face[25]!=face[0]||face[53]!=face[0]){
				if(!solvable) return false;
				changeFront();
			}
		}else{
			while(face[7]==face[0]){
				if(!solvable) return false;
				changeFront();
			}
		}
		Run();
		count=0;
		for(int i=5;i<=8;i++){
			if(face[0] == face[i]){
				tops[count] = i;
				count++;
			}
		}
	}
	if(count==4) return true;
	if(count==1){
		while(face[7]!=face[0]){
			if(!solvable) return false;
			changeFront();
		}
		if(face[42]==face[0]){
			orderList = "RUR'URU2R'";
		}else{
			changeFront();
			orderList = "L'U'LU'L'U2L";
		}
		Run();
	}
	return true;
}

bool step7(){
	int sideCount[4], count = 0, sideOrder[4] = {13,21,38,48};
	for(int i=0;i<4;i++){
		if(face[sideOrder[i]]==face[sideOrder[i]+4]){
			sideCount[count] = i;
			count++;
		}
	}
	if(count==4) return true;
	orderList = "F2UR'LF2RL'UF2";
	if(count==0) Run();
	while(true){
		if(!solvable) return false;
		if(face[38]==face[25]&&face[48]==face[42]) break;
		if(face[38]==face[53]&&face[21]==face[42]) break;
		changeFront();
	}
	if(face[38]==face[53]) orderList = "F2U'R'LF2RL'U'F2";
	Run();
	return true;
}

bool step8(){
	if(checker()) return true;
	bool hold = simulator;
	simulator = true;
	string moveList[18] = {"R","R'","R2","L","L'","L2","F","F'","F2","B","B'","B2","U","U'","U2","D","D'","D2"};
	for(int i=0;i<54;i++) dummy[i] = face[i];
	for(int i=0;i<3 ;i++) dummyD[i]=   di[i];
	for(int i=0;i<18;i++){
		for(int j=0;j<54;j++) face[j] = dummy[j];
		for(int i=0;i<3 ;i++) di[i]   =dummyD[i];
		orderList = moveList[i];
		Run();
		if(checker()){
			for(int j=0;j<54;j++) face[j] = dummy[j];
			for(int i=0;i<3 ;i++) di[i]   =dummyD[i];
			simulator = hold;
			Run();
			return true;
		}
	}
	return false;
}

bool checker(){
	for(int i=0;i<6;i++){
		for(int j=1;j<9;j++){
			if(face[i*9]!=face[i*9+j]) return false;
		}
	}
	return true;
}
