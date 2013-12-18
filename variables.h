TColors face[54], dummy[54], dummyD[3];
sbyte di[3] = {27, 18, 36};//{Bottom, Left, Front};
sbyte redCount = 0, gap[2] = {13, 0}, phaser=0, power = 30;
long moveCount = 0, goalCount = -1, reds[36];
sbyte pairC[2];
sbyte toriC[3];
string orderList = "", time = "0:00";
bool simulator = false, solving = false, solvable = true;
sbyte changeFrontCount = 0;
sbyte centerFace = 0;
sbyte ref[7][12] =   {{17,25,42,52,  13,21,38,48,  14,26,43,53},
	                    {26,5 ,51,32,  22,1 ,47,28,  23,6 ,52,33},
	                    {6 ,16,35,43,  2 ,12,31,39,  7 ,17,32,44},
	                    {44,23,15,50,  40,19,11,46,  41,24,16,51},
	                    {24,34,53,7 ,  20,30,49,3 ,  25,35,50,8 },
	                    {8 ,41,33,14,  4 ,37,29,10,  5 ,42,34,15},
	                    {12,47,37,20,  9 ,45,36,18,  10,49,39,22}};
