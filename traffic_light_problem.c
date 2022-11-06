#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


struct lane_of_cars_s
{
	int8_t carsWaitingAtIntersection;
	int8_t carsInIntersection;
	int8_t carsLeavingIntersection;
	int8_t carsThatHaveLeft;
	
	int8_t popularity;
	int8_t timeWaiting;
};

struct intersection_s
{
	char * horizantalTrafficColor;
	char * verticalTrafficColor;

	struct lane_of_cars_s eastboundCars;
	struct lane_of_cars_s westboundCars;
	struct lane_of_cars_s northboundCars;
	struct lane_of_cars_s southboundCars;
};



struct intersection_s myIntersection;

char * setHorizantalTrafficLight(struct intersection_s intersection);
char * setVerticalTrafficLight(struct intersection_s intersection);

void drawIntersection(struct intersection_s intersection);
void drawWestboundLane(char * trafficColor, struct lane_of_cars_s westboundCars);
void drawEastboundLane(char * trafficColor, struct lane_of_cars_s eastboundCars);
void drawUpperVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars);
void drawLowerVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars);
void delay(int16_t ms);
void advanceLane(char * trafficColor, struct lane_of_cars_s * lane);
int8_t checkForCrashes(void);
void initIntersection(void);

char * setHorizantalTrafficLight(struct intersection_s intersection)
{
	return "R";
}

char * setVerticalTrafficLight(struct intersection_s intersection)
{
	return "R";
}

void drawIntersection(struct intersection_s intersection)
{
	drawUpperVerticalRoad(intersection.verticalTrafficColor,intersection.northboundCars,intersection.southboundCars);
	drawWestboundLane(intersection.horizantalTrafficColor,intersection.westboundCars);
	printf("----------          ---------- \n");
	drawEastboundLane(intersection.horizantalTrafficColor,intersection.eastboundCars);
	drawLowerVerticalRoad(intersection.verticalTrafficColor,intersection.northboundCars,intersection.southboundCars);
}

void drawUpperVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars)
{
	char * southboundCarPlaceholder;

	//Show southbound cars waiting at the intersection and northbound cars leaving the intersection
	for(int8_t i = 0; i < 10; i++)
	{
		if(i >= 10 - southboundCars.carsWaitingAtIntersection)
		{
			southboundCarPlaceholder  = "+";
		}
		else{southboundCarPlaceholder  = " ";}

		if(i == 9)
		{
			printf("          |  %s ! %s |          \n",southboundCarPlaceholder,trafficColor);
		}
		else if (i == 5)
		{
			if(northboundCars.carsLeavingIntersection > 0)
			{
				printf("          |  %s ! + |          \n",southboundCarPlaceholder);
			}
			else{printf("          |  %s !   |          \n",southboundCarPlaceholder);}
		}
		else{printf("          |  %s !   |          \n",southboundCarPlaceholder);}
	}

	//Show cars in the middle of the intersection
	if(southboundCars.carsInIntersection > 0)
	{
		printf("__________   X      __________ \n");
	}
	else
	{
		printf("__________          __________ \n");
	}
}

void drawLowerVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars)
{
	char * northboundCarPlaceholder;

	//Show cars in the middle of the intersection
	if(northboundCars.carsInIntersection > 0)
	{
		printf("__________       X  __________ \n");
	}
	else
	{
		printf("__________          __________ \n");
	}

	//Show northbound cars waiting at the intersection and southbound cars leaving the intersection
	for(int8_t i = 0; i < 10; i++)
	{
		if(i < northboundCars.carsWaitingAtIntersection)
		{
			northboundCarPlaceholder  = "+";
		}
		else{northboundCarPlaceholder  = " ";}

		if(i == 0)
		{
			printf("          |  %s ! %s |          \n",trafficColor,northboundCarPlaceholder);
		}
		else if (i == 5)
		{
			if(southboundCars.carsLeavingIntersection > 0)
			{
				printf("          |  + ! %s |          \n",northboundCarPlaceholder);
			}
			else{printf("          |    ! %s |          \n",northboundCarPlaceholder);}
		}
		else{printf("          |    ! %s |          \n",northboundCarPlaceholder);}
	}


}

void drawWestboundLane(char * trafficColor, struct lane_of_cars_s westboundCars)
{
	//Show cars moving away from the intersection
	//Note: Because we don't really care about these cars, I will only display one of them
	//even if there is more than one car moving away from the intersection
	if(westboundCars.carsLeavingIntersection > 0)
	{
		printf("    +    %s", trafficColor);
	}
	else
	{
		printf("         %s", trafficColor);
	}

	//Show cars in the middle of the intersection
	if(westboundCars.carsInIntersection > 0)
	{
		printf("       X  ");
	}
	else
	{
		printf("          ");
	}

	//Show cars waiting at the intersection
	for(int8_t i = 0; i < 10; i++)
	{
		if(i < westboundCars.carsWaitingAtIntersection)
		{
			printf("+");
		}
		else{printf(" ");}
	}
	printf("\n");
}

void drawEastboundLane(char * trafficColor, struct lane_of_cars_s eastboundCars)
{

	//Show cars waiting at the intersection
	for(int8_t i = 0; i < 10; i++)
	{
		if(i >= 10 - eastboundCars.carsWaitingAtIntersection)
		{
			printf("+");
		}
		else{printf(" ");}
	}

	//Show cars in the middle of the intersection
	if(eastboundCars.carsInIntersection > 0)
	{
		printf("  X       ");
	}
	else
	{
		printf("          ");
	}

	//Show cars moving away from the intersection
	//Note: Because we don't really care about these cars, I will only display one of them
	//even if there is more than one car moving away from the intersection
	if(eastboundCars.carsLeavingIntersection > 0)
	{
		printf("%s   +     \n", trafficColor);
	}
	else
	{
		printf("%s         \n", trafficColor);
	}
}

void delay(int16_t ms)
{
    //Storing start time
    clock_t startTime = clock();
 
    //Looping till required time is not achieved
    while(clock() < startTime + ms);
}

void advanceLane(char * trafficColor, struct lane_of_cars_s * lane)
{
	//Move any cars on the leaving side of the intersection into oblivion
	//but mark them in the total lane count
	if(lane->carsLeavingIntersection > 0)
	{
		lane->carsLeavingIntersection--;
		lane->carsThatHaveLeft++;
	}

	//Move any cars in the intersection to the leaving side of the intersection
	if(lane->carsInIntersection > 0)
	{
		lane->carsInIntersection--;
		lane->carsLeavingIntersection++;
	}

	//Move a waiting car into the intersection if possible
	if((strcmp(trafficColor, "G") == 0) && (lane->carsWaitingAtIntersection > 0))
	{
		lane->carsWaitingAtIntersection--;
		lane->carsInIntersection++;
	}

	//Add cars to the lane randomly (but not more than 10 cars can ever be added to the lane ever)
	if(lane->carsWaitingAtIntersection + lane->carsInIntersection + lane->carsLeavingIntersection + lane->carsThatHaveLeft < 10)
	{
		int addCarToLane = rand();
		if((addCarToLane % lane->popularity) == 0)
		{
			lane->carsWaitingAtIntersection++;	
		}
	}

	//Keep track of how long cars have cumulatively waited at this part of the intersection
	lane->timeWaiting += lane->carsWaitingAtIntersection;
}

int8_t checkForCrashes(void)
{
	int8_t isHorizantalCarInIntersection = (myIntersection.westboundCars.carsInIntersection | myIntersection.eastboundCars.carsInIntersection);
	int8_t isVerticalCarInIntersection = (myIntersection.northboundCars.carsInIntersection | myIntersection.northboundCars.carsInIntersection);

	if(isHorizantalCarInIntersection && isVerticalCarInIntersection){return 1;}
	return 0;
}

void initIntersection(void)
{
	memset(&myIntersection, 0, sizeof(struct intersection_s));

	myIntersection.eastboundCars.popularity = 3;
	myIntersection.westboundCars.popularity = 5;
	myIntersection.northboundCars.popularity = 2;
	myIntersection.southboundCars.popularity = 4;
}

void main(void)
{
	//Initialize the intersection
	initIntersection();

	//Run traffic through the intersection for a set period of time
	for(int8_t i = 0; i < 120; i++)
	{
		//Update the traffic lights
		myIntersection.horizantalTrafficColor = setHorizantalTrafficLight(myIntersection);
		myIntersection.verticalTrafficColor = setVerticalTrafficLight(myIntersection);

		//Advance the lanes if possible
		advanceLane(myIntersection.horizantalTrafficColor, &myIntersection.westboundCars);
		advanceLane(myIntersection.horizantalTrafficColor, &myIntersection.eastboundCars);
		advanceLane(myIntersection.verticalTrafficColor, &myIntersection.northboundCars);
		advanceLane(myIntersection.verticalTrafficColor, &myIntersection.southboundCars);

		//Draw the intersection
		system("clear");
		drawIntersection(myIntersection);
		fflush(stdout);
		delay(1000);

		//Check to make sure no cars have crashed
		if(checkForCrashes() == 1)
		{
			printf("FAIL: Car crash!\n");
			return;
		}

		//Check if all the cars have left the lanes
		if(myIntersection.northboundCars.carsThatHaveLeft == 10 && myIntersection.southboundCars.carsThatHaveLeft == 10 && myIntersection.westboundCars.carsThatHaveLeft == 10 && myIntersection.eastboundCars.carsThatHaveLeft == 10)
		{
			int16_t totalWaitTime = myIntersection.northboundCars.timeWaiting + myIntersection.southboundCars.timeWaiting + myIntersection.westboundCars.timeWaiting + myIntersection.eastboundCars.timeWaiting;
			printf("SUCCESS: You got all the cars through! The total wait time was: %i seconds!\n", totalWaitTime);
			return;
		}
	}

	//If the animation time's out, let them know their score.
	int8_t totalCarsThatMadeIt = myIntersection.northboundCars.carsThatHaveLeft + myIntersection.southboundCars.carsThatHaveLeft + myIntersection.westboundCars.carsThatHaveLeft + myIntersection.eastboundCars.carsThatHaveLeft;
	printf("FAIL: Traffic Jam! You ran out of time. You got %i/40 cars through in 120 seconds.\n", totalCarsThatMadeIt);
}
