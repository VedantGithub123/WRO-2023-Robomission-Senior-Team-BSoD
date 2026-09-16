void zone1(){ // This zone completes the fueling, sensing the marking blocks, and goes to the cargo area

	startTask(sense); // Starts the task to sense the blocks in parallel while moving

	movePID(30,-0.5,0,0,0.3,-700,30,-0.5,0,0,0.3,700); // Pushes the ship into the fueling area

	movePID(40,-1,0,0,0.9,30,40,-1,0,0,0.9,-30);

	movePID(100,-0.5,0,0,2,1090,70,-0.5,0,0,0.06,0); // Turns to get into position

	stopTask(sense);

	// Wall squares
	clearTimer(T4);
	while (time1(T4)<1700){
		setMotorSpeed(left, min((time1(T4)*2), 100));
		setMotorSpeed(right, -1*min((time1(T4)*2), 100));
	}

	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);

	sleep(200);


	// Gets into position for picking blocks
	movePID(15,-100.5,0,0,0.06,-187,15,-100.5,0,0,0.06,187;

	movePID(15,-0.5,0,0,0.015,0,15,-100.5,0,0,0.06,548);

	sleep(20);
}
