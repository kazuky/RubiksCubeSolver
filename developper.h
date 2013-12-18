void findMoves();
void findOrgP(TColors col1, TColors col2);
void findOrgT(TColors col1, TColors col2, TColors col3);
void simulate();
bool checked();

string thedata[54];
int check();
int result, faceN[3], countT = 1, countP = 1;
int haha[12][2] = {{0 ,9 },{0 ,18},{0 ,36},{0 ,45},{9 ,18},{9 ,27},
	                 {9 ,45},{36,18},{36,27},{36,45},{27,18},{27,45}};
int doreListP[3][2] = {{11,28},{46,29},{19,31}};
int doreListT[3][3] = {{32,16,23},{33,15,51},{34,41,50}};
sbyte pairs[12][2] = {{1 ,13},{2 ,21},{3 ,38},{4 ,48},{10,47},{11,28},
	                 	  {12,22},{19,31},{20,39},{40,30},{37,49},{46,29}};
sbyte torios[8][3] = {{5,14,52},{6,17,26},{7,25,43},{8,53,42},{32,16,23},{33,51,15},{34,50,41},{35,24,44}};

void findMoves(){
	string moveList[18] = {"R","R'","R2","L","L'","L2","F","F'","F2","B","B'","B2","U","U'","U2","D","D'","D2"};
	for(int i=0;i<54;i++) dummy[i] = face[i];
	long totalCount, counter;
	int moves[6];
	thedata[35] = "0";
	thedata[30] = "0";

	for(int i=1;i<=6;i++){
		for(totalCount=0;totalCount<pow(18,i);totalCount++){
		for(int m=0;m<54;m++) face[m] = dummy[m];
			counter = totalCount;
			for(int j=i-1;j>=0;j--){
				moves[j] = counter/(pow(18,j));
				counter-=moves[j]*pow(18,j);
			}
			for(int j=0;j<i;j++){
				orderList = moveList[moves[j]];
				Run();
			}
			result = check();
			if(result!=0){
				if(sgn(result) == -1){
					result = abs(result)-1;
					findOrgP(face[faceN[0]],face[faceN[1]]);
					if(thedata[pairC[result]]==""){
						countP++;
						for(int j=0;j<i;j++){
							thedata[pairC[result]] = thedata[pairC[result]]+moveList[moves[j]];
						}
					}
				}else{
					result--;
					findOrgT(face[faceN[0]],face[faceN[1]],face[faceN[2]]);
					if(thedata[toriC[result]]==""){
						countT++;
						for(int j=0;j<i;j++){
							thedata[toriC[result]] = thedata[toriC[result]]+moveList[moves[j]];
						}
					}
				}
			}
			nxtDisplayCenteredTextLine(2,"L %d, T %d, P %d",i, countT, countP);
			nxtDisplayCenteredTextLine(3,"%d%%Complete",100*totalCount/pow(18,i));
			nxtDisplayCenteredTextLine(5,"Pattern %d",totalCount);
		}
	}
	nxtDisplayCenteredTextLine(3,"Failed");
	wait();
}

int check(){
	int lala = 0, dore;
	if(face[27]==face[28]&&face[ 9]==face[11]) lala++;
	else dore = 0;
	if(face[27]==face[29]&&face[45]==face[46]) lala++;
	else dore = 1;
	if(face[27]==face[31]&&face[18]==face[19]) lala++;
	else dore = 2;
	if(lala<2) return 0;
	if(lala == 3         &&
		 face[27]==face[30]&&
		 face[36]==face[40]){
		if(face[27]==face[32]&&face[9]==face[16]&&face[18]==face[23]) lala++;
		else dore = 0;
		if(face[27]==face[33]&&face[45]==face[51]&&face[9]==face[15]) lala++;
		else dore = 1;
		if(face[27]==face[34]&&face[36]==face[41]&&face[45]==face[50]) lala++;
		else dore = 2;
		if(lala<5) return 0;
		if(lala==5){
			findOrgT(face[35],face[24],face[44]);
			if(toriC[0]!=doreListT[dore][0]&&toriC[0]!=doreListT[dore][1]&&toriC[0]!=doreListT[dore][2]) return 0;
		}
		for(int i=0;i<8;i++){
			if(i<4) faceN[0] = 0;
			else    faceN[0] = 27;
			faceN[1]=9*(i%4+1);
			if(faceN[1]>18) faceN[1]+=9;
			faceN[2]=9*((1+i)%4+1);
			if(faceN[2]>18) faceN[2]+=9;
			findTorio(face[faceN[0]],face[faceN[1]],face[faceN[2]]);
			for(int j=0;j<3;j++){
				if(35 == toriC[j]) return j+1;
			}
		}
	}else{
		if(lala==2){
			findOrgP(face[30],face[40]);
			if(pairC[0]!=doreListP[dore][0]&&pairC[0]!=doreListP[dore][1]) return 0;
		}
		for(int i=0;i<12;i++){
			faceN[0] = haha[i][0];
			faceN[1] = haha[i][1];
			findPair(face[faceN[0]],face[faceN[1]]);
			for(int j=0;j<2;j++){
				if(30 == pairC[j]) return -j-1;
			}
		}
	}
	return 0;
}

void findOrgP(TColors col1, TColors col2){
	int pair[2];
	for(int i=0;i<12;i++){
		if(dummy[pairs[i][0]]==col1&&dummy[pairs[i][1]]==col2){
			pair[0] = pairs[i][0];
			pair[1] = pairs[i][1];
			break;
		}
		if(dummy[pairs[i][0]]==col2&&dummy[pairs[i][1]]==col1){
			pair[0] = pairs[i][1];
			pair[1] = pairs[i][0];
			break;
		}
	}
	pairC[0] = pair[0];
	pairC[1] = pair[1];
}

void findOrgT(TColors col1, TColors col2, TColors col3){
	int torio[3];
	for(int i=0;i<8;i++){
		if(dummy[torios[i][0]]==col1||dummy[torios[i][1]]==col1||dummy[torios[i][2]]==col1){
			if(dummy[torios[i][0]]==col2||dummy[torios[i][1]]==col2||dummy[torios[i][2]]==col2){
				if(dummy[torios[i][0]]==col3||dummy[torios[i][1]]==col3||dummy[torios[i][2]]==col3){
					if(dummy[torios[i][0]]==col1){
						torio[0] = torios[i][0];
						if(dummy[torios[i][1]]==col2){
							torio[1] = torios[i][1];
							torio[2] = torios[i][2];
						}else{
							torio[1] = torios[i][2];
							torio[2] = torios[i][1];
						}
						break;
					}else if(dummy[torios[i][1]]==col1){
						torio[0] = torios[i][1];
						if(dummy[torios[i][0]]==col2){
							torio[1] = torios[i][0];
							torio[2] = torios[i][2];
						}else{
							torio[1] = torios[i][2];
							torio[2] = torios[i][0];
						}
						break;
					}else{
						torio[0] = torios[i][2];
						if(dummy[torios[i][0]]==col2){
							torio[1] = torios[i][0];
							torio[2] = torios[i][1];
						}else{
							torio[1] = torios[i][1];
							torio[2] = torios[i][0];
						}
						break;
					}
				}
			}
		}
	}

	toriC[0] = torio[0];
	toriC[1] = torio[1];
	toriC[2] = torio[2];
}
void simulate(){
	int count = 0;
	int turnsList[4] = {9,18,36,45};
	while(true){
		if(checked()) displayData();
		nxtDisplayCenteredTextLine(4,"%d",count);
		twist(1,turnsList[count%4]);
		count++;
	}
}

bool checked(){
	for(int i=0;i<6;i++){
		if(face[9*i+0]==face[9*i+1]&&
			 face[9*i+0]==face[9*i+2]&&
		   face[9*i+0]==face[9*i+3]&&
		   face[9*i+0]==face[9*i+4]&&
		   face[9*i+0]==face[9*i+5]&&
		   face[9*i+0]==face[9*i+6]&&
		   face[9*i+0]==face[9*i+7]&&
		   face[9*i+0]==face[9*i+8]){
		  if(i==5){
		  	return true;
			}else{
				continue;
			}
		}
		break;
	}
	return false;
}
