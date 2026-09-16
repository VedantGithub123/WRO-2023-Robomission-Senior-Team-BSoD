// Function to move for degrees
void movePID(float leftSpeed, float leftKP, float leftKI, float leftKD, float leftAcc, float leftDegrees, float rightSpeed, float rightKP, float rightKI, float rightKD, float rightAcc, float rightDegrees){
	clearTimer(T2);
	int lSpeed;
	int rSpeed;
	int oldTime = -1;
	int lOldDeg = 0;
	int lIntegral;
	int rOldDeg = 0;
	int rIntegral;
	while (time1(T2)<5000 && !(fabs(getMotorEncoder(left))<fabs(leftDegrees)+5&&fabs(getMotorEncoder(left))>fabs(leftDegrees)-5&&fabs(getMotorEncoder(right))<fabs(rightDegrees)+5&&fabs(getMotorEncoder(right))>fabs(rightDegrees)-5)){

		lSpeed = (getMotorEncoder(left)-leftDegrees)*leftKP+(getMotorEncoder(left)-lOldDeg)/(time1(T2)-oldTime)*leftKD;

		if (fabs(lSpeed)>leftSpeed){
			lSpeed = lSpeed/fabs(lSpeed)*leftSpeed;
		}
		if (fabs(lSpeed)>leftAcc*time1(T2)){
			lSpeed = lSpeed/fabs(lSpeed)*leftAcc*time1(T2);
		}

		rSpeed = (getMotorEncoder(right)-rightDegrees)*rightKP+(getMotorEncoder(right)-rOldDeg)/(time1(T2)-oldTime)*rightKD;

		if (fabs(rSpeed)>rightSpeed){
			rSpeed = rSpeed/fabs(rSpeed)*rightSpeed;
		}
		if (fabs(rSpeed)>rightAcc*time1(T2)){
			rSpeed = rSpeed/fabs(rSpeed)*rightAcc*time1(T2);
		}

		if (rightDegrees!=0&&rightSpeed!=0&&rSpeed!=0&&fabs(rSpeed)<5){
			rSpeed = rSpeed/fabs(rSpeed)*5;
		}
		if (leftDegrees!=0&&leftSpeed!=0&&lSpeed!=0&&fabs(lSpeed)<5){
			lSpeed = lSpeed/fabs(lSpeed)*5;
		}

		setMotorSpeed(left, lSpeed);
		setMotorSpeed(right, rSpeed);

		oldTime = time1(T2);
		lOldDeg = getMotorEncoder(left);
		rOldDeg = getMotorEncoder(right);
		sleep(10);
	}
	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);
}

// Function to line follow
void lfPID(int state, float speed, float midPoint, float kP, float kI, float kD, float target, int portNum){

	clearTimer(T1);
	int oldTime = -1;
	int integral = 0;
	int oldRef = 0;
	int diff = 0;
	int tempPort = 5-portNum;
	sleep(1);

	while (true){
		// Creates the conditions based on the state
		switch (state){
			case 1:
				clearDebugStream();
  			writeDebugStream("%d", !(time1(T1)<target));
				if (!(time1(T1)<target)){
			  	resetMotorEncoder(left);
			  	resetMotorEncoder(right);
					return;
				}
				break;
			case 2:
				if (!(getColourReflection(tempPort)>target)){
			  	resetMotorEncoder(left);
			  	resetMotorEncoder(right);
					return;
				}
				break;
			case 3:
				if (!(getColourReflection(tempPort)<target)){
			  	resetMotorEncoder(left);
			  	resetMotorEncoder(right);
					return;
				}
				break;
			default:
				if (!(fabs(getMotorEncoder(right))<target)){
			  	resetMotorEncoder(left);
			  	resetMotorEncoder(right);
					return;
				}
				break;
		}

		// The proportion and derivative are added
		diff = (getColourReflection(portNum)-midPoint)*kP+(getColourReflection(portNum)-oldRef)/(time1(T1)-oldTime)*kD;

		// The integral is added
		//if (fabs(getColourReflection(portNum)-midPoint)<5){
			integral+=(getColourReflection(portNum)-midPoint)*kI*(time1(T1)-oldTime);
			//if (fabs(integral)>kI){
			//	integral = integral/fabs(integral)*kI;
			//}
		//}
		diff+=integral;

		setMotorSpeed(left, speed+diff);
		setMotorSpeed(right, -speed+diff);
		oldTime = time1(T1);
		oldRef = getColourReflection(portNum);
		sleep(2);

	}
}

// Function to line square
void lsPID(int sensor1, float mid1, float kP1, float kI1, float kD1, int sensor2, float mid2, float kP2, float kI2, float kD2, float time){
	clearTimer(T1);

	int lSpeed;
	int rSpeed;
	int oldTime = -1;
	int lOldRef = 0;
	int lIntegral;
	int rOldRef = 0;
	int rIntegral;

	while (time1(T1)<time){
		lSpeed = (getColourReflection(sensor1)-mid1)*kP1+(getColourReflection(sensor1)-lOldRef)/(time1(T1)-oldTime)*kD1;
		rSpeed = (getColourReflection(sensor2)-mid2)*kP2+(getColourReflection(sensor2)-rOldRef)/(time1(T1)-oldTime)*kD2;

		setMotorSpeed(left, lSpeed);
		setMotorSpeed(right, rSpeed);
		oldTime = time1(T1);
		lOldRef = getColourReflection(sensor1);
		rOldRef = getColourReflection(sensor2);
		sleep(10);
	}
	setMotorSpeed(left, 0);
	setMotorSpeed(right, 0);
	resetMotorEncoder(left);
	resetMotorEncoder(right);
}
