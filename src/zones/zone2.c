void zone2(){ // This zone picks up the cargo, puts it in the ship, and goes back to the cargo area

	setMotorSpeed(arm, -5);

	// Grabs blocks while moving forward
	clearTimer(T4);
	while (getMotorEncoder(right)<600){ // Stops at 600 degrees

		setMotorSpeed(left, -1*min((time1(T4)*0.1), 15));
		setMotorSpeed(right, min((time1(T4)*0.1), 15));

		if (getColorHT()==blocks[0]){ // Checks if the block is the same as the first position

			if (blocks[0]==1){
				sleep(30);
			}else{
				sleep(20);
			}

			blocks[0] = -1;

			setMotorSpeed(left, 0);
			setMotorSpeed(right, 0);

			pickBlock();

			sleep(2);

		}else if (getColorHT()==blocks[1]){ // Checks if the block is the same as the second position

			if (blocks[1]==1){
				sleep(30);
			}else{
				sleep(20);
			}

			blocks[1] = -1;

			setMotorSpeed(left, 0);
			setMotorSpeed(right, 0);

			pickBlock();

			sleep(2);

		}
	}


	// Moves fast to get the the white cargo

	clearTimer(T4);
	while (getMotorEncoder(right)<850){ // Acceleration
		setMotorSpeed(left, -1*min((time1(T4)*0.1)+5, 60));
		setMotorSpeed(right, min((time1(T4)*0.1)+5, 60));
	}

	clearTimer(T4);
	while (!(getColorReflected(CS3)>midpoint2+15)){ // Decceleration
		setMotorSpeed(left, -60+min(time1(T4)*0.1, 45));
		setMotorSpeed(right, 60-min(time1(T4)*0.1, 45));
	}


	// Get into position for picking the block

	waitUntil(getColorReflected(CS3)>midpoint2+15);

	waitUntil(getColorReflected(CS2)<midpoint2-15);

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);

	//lsPID(2, midpoint2-3, -0.3, 0, 0, 3, midpoint3, 0.3, 0, 0, 1000);

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);


	// Pick up the block

	pickBlock();

	movePID(40,-0.3,0,0,0.06,600,40,-0.3,0,0,0.06,-600);

	clearTimer(T4);
	while (getMotorEncoder(left)<650){ // Stops at 650 degrees

		setMotorSpeed(left, 1*min((time1(T4)*0.1), 15));
		setMotorSpeed(right, -1*min((time1(T4)*0.1), 15));

		if (getColorHT()>0){ // Checks if there is a block

			if (blocks[0]==1){
				sleep(30);
			}else{
				sleep(20);
			}

			setMotorSpeed(left, 0);
			setMotorSpeed(right, 0);

			pickBlock();

			clearTimer(T4);

			sleep(2);
		}
	}

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);

	// Get to position for dropping blocks


	//movePID(100,-0.3,0,0,0.06,1250,100,-0.3,0,0,0.06,-1250);

	movePID(70,-0.3,0,0,0.06,0,60,-0.5,0,0,0.09,-524);

	setMotorSpeed(grab, -10);

	clearTimer(T4);
	while (time1(T4)<700){
		setMotorSpeed(left, min((time1(T4)*0.3), 60));
		setMotorSpeed(right, -1*min((time1(T4)*0.3), 60));
	}

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);

	resetMotorEncoder(left);
	resetMotorEncoder(right);


	// Drop blocks onto the big ship

	movePID(20,-0.5,0,0,0.06,-147,20,-0.5,0,0,0.06,147);

	dropBlock();

	setMotorSpeed(grab, -10);

	movePID(20,-0.5,0,0,0.06,-207,20,-0.5,0,0,0.06,207);

	dropBlock();

	setMotorSpeed(grab, -10);

	movePID(20,-0.5,0,0,0.06,-89,20,-0.5,0,0,0.06,89);

	setMotorSpeed(grab, 20);
	sleep(350);
	setMotorSpeed(grab, 70);
	sleep(800);
	setMotorSpeed(grab, -10);
	sleep(20);
	setMotorSpeed(grab, 0);

	movePID(20,-1,0,0,1,40,20,-1,0,0,1,-40);
	sleep(200);
	setMotorSpeed(grab, -100);
	sleep(600);
	setMotorSpeed(grab, 0);
	resetMotorEncoder(grab);


	// Get into position for picking blocks

	startTask(releaseBlock); // Do task in parallel to make sure the block falls properly


	clearTimer(T4);
	while (time1(T4)<2000){
		setMotorSpeed(left, -1*min((time1(T4)*0.3), 100));
		setMotorSpeed(right, 1*min((time1(T4)*0.2), 100));
	}

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);




	movePID(50,-0.5,0,0,0.09,210,50,-0.5,0,0,0.09,-210);

	movePID(30,-0.5,0,0,0.06,574,15,-0.5,0,0,0.5,0);

	movePID(50,-0.5,0,0,0.09,-350,50,-0.5,0,0,0.09,350);

	setMotorSpeed(left, -20);
	setMotorSpeed(right, 20);

	waitUntil(getColorReflected(CS2)>midpoint2+15);

	setMotorSpeed(left, -10);
	setMotorSpeed(right, 10);

	waitUntil(getColorReflected(CS2)<midpoint2-25);


	// Drops blocks onto the small ship

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);

	setMotorSpeed(left, -10);
	setMotorSpeed(right, 10);

	waitUntil(getMotorEncoder(right)>14);

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);

	dropBlock();

	setMotorSpeed(grab, -10);

	movePID(20,-0.5,0,0,0.06,-90,20,-0.5,0,0,0.06,90);

	dropBlock();

}
