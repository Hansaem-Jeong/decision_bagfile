#include "ros/ros.h"

#include <stdio.h>

#include "data_bagfile/aes_data.h"
#include "data_bagfile/Chassis.h"
#include "data_bagfile/Sensor.h"
#include "data_bagfile/Traffic.h"
#include "data_bagfile/Line.h"
#include "data_bagfile/AEB.h"

#define NUMROWS      1000
#define NUM_CHASSIS  12
#define NUM_SENSOR   11
#define NUM_TRAFFIC  10
#define NUM_LINE     11
#define NUM_AEB       2

#define CHASSIS_PATH "/home/avees/hansaem_/test_ws/src/data_bagfile/src/Chassis.txt"
#define SENSOR_PATH "/home/avees/hansaem_/test_ws/src/data_bagfile/src/Sensor.txt"
#define TRAFFIC_PATH "/home/avees/hansaem_/test_ws/src/data_bagfile/src/Traffic.txt"
#define LINE_PATH "/home/avees/hansaem_/test_ws/src/data_bagfile/src/Line.txt"
#define AEB_PATH "/home/avees/hansaem_/test_ws/src/data_bagfile/src/AEB.txt"

double chassis[NUMROWS][NUM_CHASSIS];
double sensor[NUMROWS][NUM_SENSOR];
double traffic[NUMROWS][NUM_TRAFFIC];
double line[NUMROWS][NUM_LINE];
double aeb[NUMROWS][NUM_AEB];

void load_data(void);


int main(int argc, char** argv)
{
    int cnt = 0;

    ros::init(argc, argv, "AES_data");
    ros::NodeHandle nh;

    ros::Publisher pub_AES_data    = nh.advertise<data_bagfile::aes_data>("AES_data_pub",1);
    ros::Publisher pub_chassis = nh.advertise<data_bagfile::Chassis>("Chassis_data_pub",1);
    ros::Publisher pub_sensor  = nh.advertise<data_bagfile::Sensor>("Sensor_data_pub",1);
    ros::Publisher pub_traffic = nh.advertise<data_bagfile::Traffic>("Traffic_data_pub",1);
    ros::Publisher pub_line    = nh.advertise<data_bagfile::Line>("Line_data_pub",1);
    ros::Publisher pub_aeb     = nh.advertise<data_bagfile::AEB>("AEB_data_pub",1);

    ros::Rate loop_rate(100/7);  // 70ms

    data_bagfile::aes_data aesMsg;
    data_bagfile::Chassis  chassisMsg;
    data_bagfile::Sensor   sensorMsg;
    data_bagfile::Traffic  trafficMsg;
    data_bagfile::Line     lineMsg;
    data_bagfile::AEB      aebMsg;

    load_data();

    while ( ros::ok() && cnt++ < 1000 ) { 
        chassisMsg.timestamp           = chassis[cnt][0];
        chassisMsg.invehicle_yaw       = chassis[cnt][1];
        chassisMsg.invehicle_gloposy   = chassis[cnt][2];
        chassisMsg.invehicle_gloposx   = chassis[cnt][3];
        chassisMsg.invehicle_velocity  = chassis[cnt][4];
        chassisMsg.invehicle_gloaccx   = chassis[cnt][5];
        chassisMsg.invehicle_glovelx   = chassis[cnt][6];
        chassisMsg.invehicle_glovely   = chassis[cnt][7];
        chassisMsg.invehicle_cg2rearbumper  = chassis[cnt][8];
        chassisMsg.invehicle_cg2frontbumper = chassis[cnt][9];
        chassisMsg.invehicle_length         = chassis[cnt][10];
        chassisMsg.invehicle_width          = chassis[cnt][11];
     
        sensorMsg.timestamp       = sensor[cnt][0];
        sensorMsg.camera_dtct     = sensor[cnt][1];
        sensorMsg.camera_relposy  = sensor[cnt][2];
        sensorMsg.camera_relposx  = sensor[cnt][3];
        sensorMsg.camera_relvely  = sensor[cnt][4];
        sensorMsg.camera_relvelx  = sensor[cnt][5];
        sensorMsg.frontradar_dtct = sensor[cnt][6];
        sensorMsg.frontradar_relposy = sensor[cnt][7];
        sensorMsg.frontradar_relposx = sensor[cnt][8];
        sensorMsg.frontradar_relvely = sensor[cnt][9];
        sensorMsg.frontradar_relvelx = sensor[cnt][10];
    
        trafficMsg.timestamp               = traffic[cnt][0];
        trafficMsg.traffic_rv_gloposy      = traffic[cnt][1];
        trafficMsg.traffic_rv_gloposx      = traffic[cnt][2];
        trafficMsg.traffic_rv_headingangle = traffic[cnt][3];
        trafficMsg.traffic_rv_glovelx      = traffic[cnt][4];
        trafficMsg.traffic_rv_glovely      = traffic[cnt][5];
        trafficMsg.traffic_rv_cg2rearbumper  = traffic[cnt][6];
        trafficMsg.traffic_rv_cg2frontbumper = traffic[cnt][7];
        trafficMsg.traffic_rv_length         = traffic[cnt][8];
        trafficMsg.traffic_rv_width          = traffic[cnt][9];
    
        lineMsg.timestamp    = line[cnt][0];
        lineMsg.linepoly_a_l = line[cnt][1]; 
        lineMsg.linepoly_a_r = line[cnt][2]; 
        lineMsg.linepoly_b_l = line[cnt][3]; 
        lineMsg.linepoly_b_r = line[cnt][4]; 
        lineMsg.linepoly_c_l = line[cnt][5]; 
        lineMsg.linepoly_c_r = line[cnt][6]; 
        lineMsg.linepoly_d_l = line[cnt][7]; 
        lineMsg.linepoly_d_r = line[cnt][8]; 
        lineMsg.sensor_line_front_nline_left  = line[cnt][9]; 
        lineMsg.sensor_line_front_nline_right = line[cnt][10]; 

        aebMsg.timestamp    = aeb[cnt][0];
        aebMsg.linepoly_a_l = aeb[cnt][1];

        aesMsg.chassis = chassisMsg;
        aesMsg.sensor  = sensorMsg;
        aesMsg.traffic = trafficMsg;
        aesMsg.line = lineMsg;
        aesMsg.aeb = aebMsg;

 
        pub_chassis.publish(chassisMsg);
        pub_sensor.publish(sensorMsg);
        pub_traffic.publish(trafficMsg);
        pub_line.publish(lineMsg);
        pub_aeb.publish(aebMsg);
        pub_AES_data.publish(aesMsg);

        loop_rate.sleep();

    }


    return 0;
}

void load_data()
{
	int index = 0;
	int j = 0;
	int err = 0;
	// Chassis
	FILE* pFile = fopen(CHASSIS_PATH, "r");
	if (pFile == NULL) {
		printf("unable to find the file.\n");
	}

	while (index < NUMROWS)  // EOF != ??? &&
	{
		for (j = 0;j < NUM_CHASSIS - 1;j++)
		{
			err = fscanf(pFile, "%lf,", &chassis[index][j]);
		}
		err = fscanf(pFile, "%lf\n", &chassis[index][j]);
                printf("111111111111\n");
		index += 1;
	}
	fclose(pFile);

	// Sensor
        pFile = fopen(SENSOR_PATH, "r");
	if (pFile == NULL) {
		printf("unable to find the file.\n");
	}

        index=0;
	while (index < NUMROWS)  // EOF != ??? &&
	{
		for (j = 0;j < NUM_SENSOR - 1;j++)
		{
			err = fscanf(pFile, "%lf,", &sensor[index][j]);
		}
		err = fscanf(pFile, "%lf\n", &sensor[index][j]);
                printf("Sensor : %lf\n", sensor[index][4]);
		index += 1;
	}
	fclose(pFile);

        index=0;
	// Traffic
	pFile = fopen(TRAFFIC_PATH, "r");
	if (pFile == NULL) {
		printf("unable to find the file.\n");
	}

	while (index < NUMROWS)  // EOF != ??? &&
	{
		for (j = 0;j < NUM_TRAFFIC - 1;j++)
		{
			err = fscanf(pFile, "%lf,", &traffic[index][j]);
		}
		err = fscanf(pFile, "%lf\n", &traffic[index][j]);
		index += 1;
	}
	fclose(pFile);

        index=0;
	// Line
	pFile = fopen(LINE_PATH, "r");
	if (pFile == NULL) {
		printf("unable to find the file.\n");
	}

	while (index < NUMROWS)  // EOF != ??? &&
	{
		for (j = 0;j < NUM_LINE - 1;j++)
		{
			err = fscanf(pFile, "%lf,", &line[index][j]);
		}
		err = fscanf(pFile, "%lf\n", &line[index][j]);
		index += 1;
	}
	fclose(pFile);
        index=0;

	// Sensor
	pFile = fopen(AEB_PATH, "r");
	if (pFile == NULL) {
		printf("unable to find the file.\n");
	}

	while (index < NUMROWS)  // EOF != ??? &&
	{
		for (j = 0;j < NUM_AEB - 1;j++)
		{
			err = fscanf(pFile, "%lf,", &aeb[index][j]);
		}
		err = fscanf(pFile, "%lf\n", &aeb[index][j]);
		index += 1;
	}
	fclose(pFile);
}
