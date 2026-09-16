int getColourReflection(int portNumber){ // Function to get color reflection by sensor
	switch(portNumber){
		case 1:
			return getColorReflected(CS1);
		case 2:
			return getColorReflected(CS2);
		case 3:
			return getColorReflected(CS3);
		default:
			return 0;
	}
}

int htColor(int portNumber){ // Function to get hitechnic color sensor color
	readSensor(&HCS1);
	switch(portNumber){
	case 1:
		return HCS1.color;
	default:
		return 0;
	}
}

int htHue(int portNumber){ // Function to get hitechnic color sensor color
	readSensor(&HCS1);
	switch(portNumber){
	case 1:
		return HCS1.hue;
	default:
		return 0;
	}
}

int htBlue(int portNumber){ // Function to get hitechnic color sensor blue reflection
	readSensor(&HCS1);
	switch(portNumber){
	case 1:
		return HCS1.blue;
	default:
		return 0;
	}
}

int htGreen(int portNumber){ // Function to get hitechnic color sensor green reflection
	readSensor(&HCS1);
	switch(portNumber){
	case 1:
		return HCS1.green;
	default:
		return 0;
	}
}

// Function to get the color of a block
int getColorHTMarker(){ // 0 is no color, 1 is blue, 2 is green
	if (htColor(1)==2||htColor(1)==3){
		return 1;
		}else if (htColor(1)==4){
		return 2;
		}else{
		return 0;
	}
}

// Function to get the color of a block
int getColorHT(){ // 0 is no color, 1 is blue, 2 is green
		if (htBlue(1)>19 && htHue(1)>100){
		return 1;
		}else if (htGreen(1)>7 && htBlue(1)<11 && htHue(1)>90){
		return 2;
		}else{
		return 0;
	}

	//if (htColor(1)==2||htColor(1)==3){
	//	return 1;
	//	}else if (htGreen(1)>9){
	//	return 2;
	//	}else{
	//	return 0;
	//}
}
