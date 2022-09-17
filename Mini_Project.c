#include <stdio.h>
#include <stdlib.h>

#define TEMP_CONTROLLER 1


enum state{

	off=0, on=1  //for the state of AC, Engine, Controller

};

enum state AC = off;
enum state engine = off;
enum state controller = off;


struct variables
{
	int vehicle_speed;
	int room_temp;
	int engine_temp;

}v;  //struct of name "v" containing the variable of vehical



void display(void){  //to display the output of vehical states and variables

	if(v.vehicle_speed == 30){

		if(AC == off){

			AC = on;
		}

		v.room_temp = (v.room_temp * (5/4)) + 1;

#if TEMP_CONTROLLER == 1   //if temp controller is 0 this will not compile

		if(controller == off){

					controller = on;
				}

		v.engine_temp = (v.engine_temp * (5/4)) + 1;

#endif
	}


	if(engine == on){
		printf("Engine is ON\n");
	}
	else
		printf("Engine is OFF\n");

	if(AC == on){
		printf("AC is ON\n");
	}
	else
		printf("AC is OFF\n");

	printf("Vehicle speed: %d Km/Hr\n", v.vehicle_speed );
	printf("Room Temperature: %d C\n", v.room_temp);

#if TEMP_CONTROLLER == 1   //if temp controller is 0 this will not compile

	if(controller == on){
		printf("Engine Temperature Controller is ON\n");
	}
	else
		printf("Engine Temperature Controller is OFF\n");

	printf("Engine Temperature is: %d C\n", v.engine_temp);

#endif

}



void Traffic_light(void){

	char color;
	printf("Enter the required traffic light color:\n ");
	scanf(" %c", &color);

	switch(color){

		case 'G':
		case 'g':
		{
			v.vehicle_speed = 100;
			display();

		}
		break;

		case 'O':
		case 'o':
		{
			v.vehicle_speed = 30;
			display();

		}
		break;

		case 'R':
		case 'r':
		{
			v.vehicle_speed = 0;
			display();

		}
		break;

		default:
		{
			printf("Error input");
		}
	}
}


void Room_temp(void){

	int rm_temp;
	printf("Enter the required room temperature:\n ");
	scanf("%d", &rm_temp);



	if((rm_temp < 10) || (rm_temp > 30)){

		AC =on;
		v.room_temp = 20;
	}

	else{

		AC = off;
	}

	display();
}


#if TEMP_CONTROLLER == 1

void Engine_temp(void){

	int eng_temp;
	printf("Enter the required engine temperature:\n ");
	scanf("%d", &eng_temp);

	if((eng_temp < 100) || (eng_temp > 150)){
		controller = on;
		v.engine_temp=125;
	}

	else{
			controller = off;

	}

	display();
}

#endif


void Sensor_menu(char *sensor){

	printf("\nSensors set menu:\n "
			"a. Turn off the engine\n "
			"b. Set the traffic light color.\n "
			"c. Set the room temperature (Temperature Sensor)\n ");

#if TEMP_CONTROLLER == 1

	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");

#endif

	scanf(" %c", sensor);

	if (*sensor == 'a'){

		printf("Turn off the vehicle engine\n");
	}

}


void Menu(char *choice){

	printf("Please choose what you want:\n "
			"a. Turn on the vehicle engine\n "
			"b. Turn off the vehicle engine\n "
			"c. Quit the system\n\n");

	scanf(" %c", choice);

	switch( *choice){

		case 'A':
		case 'a':
		{
			printf("Turn on the vehicle engine\n");
		}
		break;

		case 'B':
		case 'b':
		{
			printf("Turn off the vehicle engine\n");
		}
		break;

		case 'C':
		case 'c':
		{
			printf("Quit the system\n");
		}
		break;

		default:
		{
			printf("Error input\n");
		}
	}

}



int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char choice;
	char sensor;


	v.room_temp = 35;
	v.engine_temp = 90;
	v.vehicle_speed = 100;

	while (1) {

		Menu(&choice);
		while (choice == 'b' || choice == 'B') {    //turn off the engine
			engine = off;
			Menu(&choice);
		}

		if (choice == 'c' || choice == 'C') {       //Quit the system
			return 0;
		}

		if (choice == 'a' || choice == 'A') {       //turn on the engine
			engine = on;

			while (engine == on) {
				Sensor_menu(&sensor);
				if (sensor == 'a' || sensor == 'A') {
					engine = off;
					break;         //exit the while loop
				}
				if (sensor == 'b' || sensor == 'B') {
					Traffic_light();
				}
				if (sensor == 'c' || sensor == 'C') {
					Room_temp();
				}
#if TEMP_CONTROLLER==1

				if (sensor == 'd' || sensor =='D') {
					Engine_temp();
				}
#endif
			}
		}
	}
	return 0;
}





