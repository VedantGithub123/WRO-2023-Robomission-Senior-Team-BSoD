int min(int num1, int num2){ // Finds minimum value of 2 integers
	if (num1<num2){
		return num1;
	}
	return num2;
}

void pickBlock(){ // Picks up a block
	setMotorSpeed(arm, 35);
	sleep(1000);
	setMotorSpeed(arm, -100);
	sleep(700);
	setMotorSpeed(arm, 0);
	//sleep(100);
}

void dropBlock(){ // Drops a block
	setMotorSpeed(grab, 15);
	sleep(200);
	setMotorSpeed(grab, 100);
	sleep(600);
	setMotorSpeed(grab, -100);
	sleep(400);
	setMotorSpeed(grab, 0);
	resetMotorEncoder(grab);
}

task sense(){ // Sensing task
	int col = 0;
	while (true){
		col = getColorHTMarker();
		if (col>0){
			blocks[0] = col;
			break;
		}
	}

	waitUntil(htColor(1)==0);
	sleep(10);
	col = 0;

	while (true){
		col = getColorHTMarker();
		if (col>0){
			blocks[1] = col;
			break;
		}
	}
	switch(blocks[0]){
	case 1:
		playSound(soundException);
		break;
	case 2:
		playSound(soundBeepBeep);
		break;
	default:
		blocks[0] = 2;
		playSound(soundDownwardTones);
		break;
	}
	sleep(1000);
	switch(blocks[1]){
	case 1:
		playSound(soundException);
		break;
	case 2:
		playSound(soundBeepBeep);
		break;
	default:
		blocks[1] = 1;
		playSound(soundDownwardTones);
		break;
	}
	stopTask(sense);
}

task releaseBlock(){ // Task to fully release the last block
	setMotorSpeed(arm, 40);
	sleep(600);
	setMotorSpeed(arm, -100);
	sleep(600);
	setMotorSpeed(arm, 0);
}

task playMusic(){
	drawBmpfile(0, 127, "ET.rgf");
	sleep(6000);
	playSoundFile("FNA1.rsf");
	sleep(5000);
	playSoundFile("FNA2.rsf");
	sleep(5000);
	playSoundFile("FNA3.rsf");
	sleep(5000);
	playSoundFile("FNA4.rsf");
	sleep(5000);
	playSoundFile("FNA5.rsf");
	sleep(5000);
	playSoundFile("FNA6.rsf");
	sleep(5000);
	playSoundFile("FNA7.rsf");
	sleep(5000);
	playSoundFile("FNA8.rsf");
	sleep(5000);
	playSoundFile("FNA9.rsf");
	sleep(5000);
	playSoundFile("FNA10.rsf");
	sleep(5000);
	playSoundFile("FNA11.rsf");
	sleep(5000);
	playSoundFile("FNA12.rsf");
	sleep(5000);
	playSoundFile("FNA13.rsf");
	sleep(5000);
	playSoundFile("FNA14.rsf");
	sleep(5000);
	playSoundFile("FNA15.rsf");
	sleep(5000);
}
