#include <stdint.h>
#define SIZE 518400

struct sensor
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	int8_t temperature;
};
void Help ();
uint8_t AddInfo (struct sensor* info, char *filename);
float AverageM (struct sensor* info, uint8_t monthN);
int8_t MinTempM (struct sensor* info, uint8_t monthN);
int8_t MaxTempM (struct sensor* info, uint8_t monthN);
float AverageY (struct sensor* info, uint16_t yearN);
int8_t MinTempY (struct sensor* info, uint16_t yearN);
int8_t MaxTempY (struct sensor* info, uint16_t yearN);
void AllTimeReport (struct sensor* info);
void MonthReport (struct sensor* info, uint8_t monthN);
