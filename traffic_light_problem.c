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
};

struct lane_of_cars_s westboundCars;
struct lane_of_cars_s eastboundCars;
struct lane_of_cars_s northboundCars;
struct lane_of_cars_s southboundCars;

void drawWestboundLane(char * trafficColor, struct lane_of_cars_s westboundCars);
void drawEastboundLane(char * trafficColor, struct lane_of_cars_s eastboundCars);
void drawUpperVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars);
void drawLowerVerticalRoad(char * trafficColor, struct lane_of_cars_s northboundCars, struct lane_of_cars_s southboundCars);

void drawIntersection(void)
{
	printf("Hello World! \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("__________          __________ \n");
	printf("\n");
	printf("----------          ---------- \n");
	printf("\n");
	printf("__________          __________ \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
	printf("          |    !    |          \n");
}

void drawRoad(char * street, char * trafficColor, int8_t westBoundCars, int8_t eastBoundCars)
{
	drawUpperVerticalRoad(trafficColor,northboundCars,southboundCars);
	drawWestboundLane(trafficColor,westboundCars);
	printf("----------          ---------- \n");
	drawEastboundLane(trafficColor,eastboundCars);
	drawLowerVerticalRoad(trafficColor,northboundCars,southboundCars);
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

void main(void)
{
	memset(&westboundCars, 0, sizeof(struct lane_of_cars_s));
	memset(&eastboundCars, 0, sizeof(struct lane_of_cars_s));
	memset(&northboundCars, 0, sizeof(struct lane_of_cars_s));
	memset(&southboundCars, 0, sizeof(struct lane_of_cars_s));

	westboundCars.carsWaitingAtIntersection = 5;
	westboundCars.carsInIntersection = 1;
	westboundCars.carsLeavingIntersection = 3;

	eastboundCars.carsWaitingAtIntersection = 2;
	eastboundCars.carsInIntersection = 1;
	eastboundCars.carsLeavingIntersection = 7;

	northboundCars.carsWaitingAtIntersection = 9;
	northboundCars.carsInIntersection = 1;
	northboundCars.carsLeavingIntersection = 2;

	southboundCars.carsWaitingAtIntersection = 4;
	southboundCars.carsInIntersection = 1;
	southboundCars.carsLeavingIntersection = 1;

	drawRoad("horizantal","R",2,3);
}