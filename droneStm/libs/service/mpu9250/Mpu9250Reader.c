#include "Mpu9250Reader.h"
#include "i2c.h"
#include "Delay.h"
#include "tm_stm32f4_mpu9250.h"
#include "ArrayUtil.h"

#define REG_DEFAULT 				0x68<<1
#define MAG_DEFAULT 				0x0C<<1

#define GYROSENSI500_VALUE_REG 		0x08
#define GYROSENSI_REGISTER 		 	0x1B

#define ACCELSENSI_REGISTER    		0x1C
#define ACCELSENSI_VALUE_REG   		0x00

#define SAMPLE_RATE_VALUE_REG  		0x00
#define SAMPLE_RATE_REGISTER   		0x19


#define FILTER_VALUE_REG      		0x03
#define FILTER_REGISTER				0x1A

#define DATA_REGISTER_ACCEL_GYRO    0x3B
#define DATA_GYRO_ACCEL_LENGTH      14

#define DATA_REGISTER_MAG			0x03
#define DATA_MAG_LENGTH				7
#define DATA_MAG_STATUS_RE          0x02

#define PWM_MGMT_1           		0x6B
#define PWM_MGMT_2           		0x6C
#define GYRO_GAIN 					1.0f/65.5f
#define ACCEL_GAIN 					2.0f*9.8f/32768.0f

#define SMPLRT_DIV          		0x19
#define FILTER_REG             		0x1A
#define GYRO_CONFIG_REGISTER 		0x1B
#define ACCEL_CONFIG_REGISTER_1     0x1C
#define ACCEL_CONFIG_REGISTER_2     0x1D
#define INT_PIN_CFG         		0x37
#define INT_ENABLE          		0x38


TM_MPU9250_t tlReader;


void catchErrorMpu9250(){
	static int flagDebug;
	if(flagDebug)
		return;
	flagDebug=1;
	TM_MPU9250_Init(&tlReader,TM_MPU9250_Device_0);
}

void configGeneral(Mpu9250Reader reader){
	catchErrorMpu9250();
//	writeByteViaI2C(reader.addr,SMPLRT_DIV,0x00);// config rate
//	writeByteViaI2C(reader.addr,FILTER_REG,0x03); // config filter
//	writeByteViaI2C(reader.addr,PWM_MGMT_1,0x01); // config clock
	delayMilis(10);
}

void configGyro(Mpu9250Reader reader){
	writeByteViaI2C(reader.addr,GYROSENSI_REGISTER,GYROSENSI500_VALUE_REG);
	delayMilis(10);
}


void configAccel(Mpu9250Reader reader){
	writeByteViaI2C(reader.addr,ACCELSENSI_REGISTER,ACCELSENSI_VALUE_REG);
	delayMilis(10);
}



void configMangetor(Mpu9250Reader reader){
//	writeByteViaI2C(reader.magnetAddr, 0x37, 0x22);
//	writeByteViaI2C(reader.magnetAddr, 0x38, 0x01);
//	writeByteViaI2C(reader.magnetAddr,0x0A,0x00);
//	writeByteViaI2C(reader.magnetAddr,0x0A,0x0F);
//	writeByteViaI2C(reader.magnetAddr,0x0A,0x00);
}

void parseData(Mpu9250Reader *reader,u8 *buffer,int length){
	reader->data.accelData.roll		= ((int16_t)buffer[0]  << 8) | buffer[1];
	reader->data.accelData.pitch 	= ((int16_t)buffer[2]  << 8) | buffer[3];
	reader->data.accelData.yaw  	= ((int16_t)buffer[4]  << 8) | buffer[5];
	reader->data.gyroData.roll   	= ((int16_t)buffer[8]  << 8) | buffer[9];
	reader->data.gyroData.pitch		= ((int16_t)buffer[10] << 8) | buffer[11];
	reader->data.gyroData.yaw			= ((int16_t)buffer[12] << 8) | buffer[13];
	if(length>DATA_GYRO_ACCEL_LENGTH){
		TM_MPU9250_ReadMag(&tlReader);
		reader->data.magnetData.roll  = ((int16_t)buffer[14] << 8) | buffer[15];
		reader->data.magnetData.pitch	= ((int16_t)buffer[16] << 8) | buffer[17];
		reader->data.magnetData.yaw		= ((int16_t)buffer[18] << 8) | buffer[19];
	}
}


void requestAccelAndGyro(Mpu9250Reader reader,u8 *buffer){
	//requestAndReadBytesViaI2C(reader.addr,DATA_REGISTER_ACCEL_GYRO,buffer,DATA_GYRO_ACCEL_LENGTH);
	TM_MPU9250_ReadAcce(&tlReader);
	TM_MPU9250_ReadGyro(&tlReader);
	copyData(buffer,&tlReader.Ax_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+2,&tlReader.Ay_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+4,&tlReader.Az_Raw,2,COPY_BIG_ENDIAN);
	
	copyData(buffer+8,&tlReader.Gx_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+10,&tlReader.Gy_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+12,&tlReader.Gz_Raw,2,COPY_BIG_ENDIAN);

}


void requestMagnet(Mpu9250Reader reader,u8 *buffer){
//	requestAndReadBytesViaI2C(24,3,buffer,DATA_MAG_LENGTH);
	TM_MPU9250_ReadMag(&tlReader);
	copyData(buffer,&tlReader.Mx_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+2,&tlReader.My_Raw,2,COPY_BIG_ENDIAN);
	copyData(buffer+4,&tlReader.Mz_Raw,2,COPY_BIG_ENDIAN);

}

void initMpu9250Reader(Mpu9250Reader *reader){
	reader->addr=REG_DEFAULT;
	reader->magnetAddr=MAG_DEFAULT;
	configGeneral(*reader);
//	configGyro(*reader);
//	configAccel(*reader);
//	configMangetor(*reader);
}
	




void readFullDataMpu9250(Mpu9250Reader *reader){
	u8 buffer[DATA_MAG_LENGTH+DATA_GYRO_ACCEL_LENGTH];
	requestAccelAndGyro(*reader,buffer);
	requestMagnet(*reader,buffer+DATA_GYRO_ACCEL_LENGTH);
	parseData(reader,buffer,DATA_MAG_LENGTH+DATA_GYRO_ACCEL_LENGTH);
}


void readAccelAndGyroDataMpu9250(Mpu9250Reader *reader){
	u8 buffer[DATA_GYRO_ACCEL_LENGTH];
	requestAccelAndGyro(*reader,buffer);
	parseData(reader,buffer,DATA_GYRO_ACCEL_LENGTH);
}
	


Vector3DInt16_t getRawAccel(Mpu9250Reader reader){
	return reader.data.accelData;
}
Vector3DInt16_t getRawGyro(Mpu9250Reader 	reader){
	return reader.data.gyroData;
}
Vector3DInt16_t getRawMagnet(Mpu9250Reader reader){
	return reader.data.magnetData;
}

Vector3D convertRawAccelToRealAccel(Vector3DInt16_t rawAccel){
	return scaleVector3DIntToVector3D(rawAccel,ACCEL_GAIN);
}

Vector3D convertRawGyroToRealGyro(Vector3DInt16_t rawGyro){
	return scaleVector3DIntToVector3D(rawGyro,GYRO_GAIN);
}

Vector3D convertRawMagnetToRealMagnet(Vector3DInt16_t rawMagnet){
	return scaleVector3DIntToVector3D(rawMagnet,1);
}

