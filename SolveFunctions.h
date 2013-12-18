void Run();

void Run(){
	changeFrontCount = 0;
	string faceList[6] = {"U","B","L","D","F","R"};
	string frontCha, orders = orderList;
	sbyte num[2];
	while(true){
		if(orders=="") break;
		frontCha = strIndex(orders,0);
		for(int i=0;i<6;i++){
			if(faceList[i]==frontCha){
				num[1] = i;
				StringDelete(orders,0,1);
				break;
			}
		}
		num[0] = 1;
		if(orders==""){
		}else{
			frontCha = strIndex(orders,0);
			if(frontCha=="'"){
				num[0] = -1;
				StringDelete(orders,0,1);
			}else if(frontCha=="2"){
				num[0] = 2;
				StringDelete(orders,0,1);
			}
		}
		twist(num[0],num[1]*9);
	}
}

bool findPair(TColors col1, TColors col2){
	sbyte pairs[12][2] = {{1 ,13},{2 ,21},{3 ,38},{4 ,48},{37,49},{47,10},
		                    {12,22},{20,39},{30,40},{31,19},{28,11},{29,46}};
	for(int i=0;i<12;i++){
		if(face[pairs[i][0]]==col1&&face[pairs[i][1]]==col2){
			pairC[0] = pairs[i][0];
			pairC[1] = pairs[i][1];
			return true;
		}
		if(face[pairs[i][0]]==col2&&face[pairs[i][1]]==col1){
			pairC[0] = pairs[i][1];
			pairC[1] = pairs[i][0];
			return true;
		}
	}
	return false;
}


bool findTorio(TColors col1, TColors col2, TColors col3){
	sbyte torios[8][3] = {{5 ,52,14},{6 ,17,26},{7 ,25,43},{8 ,42,53},
		                    {32,23,16},{33,15,51},{34,50,41},{35,44,24}};
	for(int i=0;i<8;i++){
		if(face[torios[i][0]]==col1||face[torios[i][1]]==col1||face[torios[i][2]]==col1){
			if(face[torios[i][0]]==col2||face[torios[i][1]]==col2||face[torios[i][2]]==col2){
				if(face[torios[i][0]]==col3||face[torios[i][1]]==col3||face[torios[i][2]]==col3){
					if(face[torios[i][0]]==col1){
						toriC[0] = torios[i][0];
						if(face[torios[i][1]]==col2){
							toriC[1] = torios[i][1];
							toriC[2] = torios[i][2];
						}else{
							toriC[1] = torios[i][2];
							toriC[2] = torios[i][1];
						}
						return true;
					}else if(face[torios[i][1]]==col1){
						toriC[0] = torios[i][1];
						if(face[torios[i][0]]==col2){
							toriC[1] = torios[i][0];
							toriC[2] = torios[i][2];
						}else{
							toriC[1] = torios[i][2];
							toriC[2] = torios[i][0];
						}
						return true;
					}else{
						toriC[0] = torios[i][2];
						if(face[torios[i][0]]==col2){
							toriC[1] = torios[i][0];
							toriC[2] = torios[i][1];
						}else{
							toriC[1] = torios[i][1];
							toriC[2] = torios[i][0];
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}
