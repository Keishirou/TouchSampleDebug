// UnlimitedHand for Arduino ver.0044
// 2017.03.16

#ifndef UH_h
#define UH_h

typedef unsigned char     uint8_t;
//typedef unsigned int     uint32_t;
///////////////////////////////////////////////////////////////////////////////
// I2C for the Acceleration and the  Gyro                                    //
///////////////////////////////////////////////////////////////////////////////
//softi2c addition
#define NO_INTERRUPT 1
#define I2C_TIMEOUT 1000

#define SDA_PORT PORTB
#define SDA_PIN 2
#define SCL_PORT PORTD
#define SCL_PIN 3
#define FAC 1
#define I2C_CPUFREQ (F_CPU/FAC)

#include "SoftI2CMaster.h"
#include <avr/io.h>
#include <Kalman.h>

///////////////////////////////////////////////////////////////////////////////
// MPU6050 SETTING for the Acceleration and the Gyro                         //
///////////////////////////////////////////////////////////////////////////////
//-----test variables
#define MPU6050_AUX_VDDIO          0x01   // R/W
#define MPU6050_SMPLRT_DIV         0x19   // R/W
#define MPU6050_CONFIG             0x1A   // R/W
#define MPU6050_GYRO_CONFIG        0x1B   // R/W
#define MPU6050_ACCEL_CONFIG       0x1C   // R/W
#define MPU6050_FF_THR             0x1D   // R/W
#define MPU6050_FF_DUR             0x1E   // R/W
#define MPU6050_MOT_THR            0x1F   // R/W
#define MPU6050_MOT_DUR            0x20   // R/W
#define MPU6050_ZRMOT_THR          0x21   // R/W
#define MPU6050_ZRMOT_DUR          0x22   // R/W
#define MPU6050_FIFO_EN            0x23   // R/W
#define MPU6050_I2C_MST_CTRL       0x24   // R/W
#define MPU6050_I2C_SLV0_ADDR      0x25   // R/W
#define MPU6050_I2C_SLV0_REG       0x26   // R/W
#define MPU6050_I2C_SLV0_CTRL      0x27   // R/W
#define MPU6050_I2C_SLV1_ADDR      0x28   // R/W
#define MPU6050_I2C_SLV1_REG       0x29   // R/W
#define MPU6050_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU6050_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU6050_I2C_SLV2_REG       0x2C   // R/W
#define MPU6050_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU6050_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU6050_I2C_SLV3_REG       0x2F   // R/W
#define MPU6050_I2C_SLV3_CTRL      0x30   // R/W
#define MPU6050_I2C_SLV4_ADDR      0x31   // R/W
#define MPU6050_I2C_SLV4_REG       0x32   // R/W
#define MPU6050_I2C_SLV4_DO        0x33   // R/W
#define MPU6050_I2C_SLV4_CTRL      0x34   // R/W
#define MPU6050_I2C_SLV4_DI        0x35   // R  
#define MPU6050_I2C_MST_STATUS     0x36   // R
#define MPU6050_INT_PIN_CFG        0x37   // R/W
#define MPU6050_INT_ENABLE         0x38   // R/W
#define MPU6050_INT_STATUS         0x3A   // R  
#define MPU6050_ACCEL_XOUT_H       0x3B   // R  
#define MPU6050_ACCEL_XOUT_L       0x3C   // R  
#define MPU6050_ACCEL_YOUT_H       0x3D   // R  
#define MPU6050_ACCEL_YOUT_L       0x3E   // R  
#define MPU6050_ACCEL_ZOUT_H       0x3F   // R  
#define MPU6050_ACCEL_ZOUT_L       0x40   // R  
#define MPU6050_TEMP_OUT_H         0x41   // R  
#define MPU6050_TEMP_OUT_L         0x42   // R  
#define MPU6050_GYRO_XOUT_H        0x43   // R  
#define MPU6050_GYRO_XOUT_L        0x44   // R  
#define MPU6050_GYRO_YOUT_H        0x45   // R  
#define MPU6050_GYRO_YOUT_L        0x46   // R  
#define MPU6050_GYRO_ZOUT_H        0x47   // R  
#define MPU6050_GYRO_ZOUT_L        0x48   // R  
#define MPU6050_EXT_SENS_DATA_00   0x49   // R  
#define MPU6050_EXT_SENS_DATA_01   0x4A   // R  
#define MPU6050_EXT_SENS_DATA_02   0x4B   // R  
#define MPU6050_EXT_SENS_DATA_03   0x4C   // R  
#define MPU6050_EXT_SENS_DATA_04   0x4D   // R  
#define MPU6050_EXT_SENS_DATA_05   0x4E   // R  
#define MPU6050_EXT_SENS_DATA_06   0x4F   // R  
#define MPU6050_EXT_SENS_DATA_07   0x50   // R  
#define MPU6050_EXT_SENS_DATA_08   0x51   // R  
#define MPU6050_EXT_SENS_DATA_09   0x52   // R  
#define MPU6050_EXT_SENS_DATA_10   0x53   // R  
#define MPU6050_EXT_SENS_DATA_11   0x54   // R  
#define MPU6050_EXT_SENS_DATA_12   0x55   // R  
#define MPU6050_EXT_SENS_DATA_13   0x56   // R  
#define MPU6050_EXT_SENS_DATA_14   0x57   // R  
#define MPU6050_EXT_SENS_DATA_15   0x58   // R  
#define MPU6050_EXT_SENS_DATA_16   0x59   // R  
#define MPU6050_EXT_SENS_DATA_17   0x5A   // R  
#define MPU6050_EXT_SENS_DATA_18   0x5B   // R  
#define MPU6050_EXT_SENS_DATA_19   0x5C   // R  
#define MPU6050_EXT_SENS_DATA_20   0x5D   // R  
#define MPU6050_EXT_SENS_DATA_21   0x5E   // R  
#define MPU6050_EXT_SENS_DATA_22   0x5F   // R  
#define MPU6050_EXT_SENS_DATA_23   0x60   // R  
#define MPU6050_MOT_DETECT_STATUS  0x61   // R  
#define MPU6050_I2C_SLV0_DO        0x63   // R/W
#define MPU6050_I2C_SLV1_DO        0x64   // R/W
#define MPU6050_I2C_SLV2_DO        0x65   // R/W
#define MPU6050_I2C_SLV3_DO        0x66   // R/W
#define MPU6050_I2C_MST_DELAY_CTRL 0x67   // R/W
#define MPU6050_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU6050_MOT_DETECT_CTRL    0x69   // R/W
#define MPU6050_USER_CTRL          0x6A   // R/W
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W
#define MPU6050_FIFO_COUNTH        0x72   // R/W
#define MPU6050_FIFO_COUNTL        0x73   // R/W
#define MPU6050_FIFO_R_W           0x74   // R/W
#define MPU6050_WHO_AM_I           0x75   // R

#define MPU6050_D0 0
#define MPU6050_D1 1
#define MPU6050_D2 2
#define MPU6050_D3 3
#define MPU6050_D4 4
#define MPU6050_D5 5
#define MPU6050_D6 6
#define MPU6050_D7 7
#define MPU6050_D8 8

// Default I2C address for the MPU-6050 is 0x68, this is the Arno Motion Address.
#define MPU6050_I2C_ADDRESS 0xD0 //68


///////////////////////////////////////////////////////////////////////////////
// Kalman for the Acceleration and the  Gyro                                 //
///////////////////////////////////////////////////////////////////////////////
// Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf 
#define RESTRICT_PITCH 

///////////////////////////////////////////////////////////////////////////////
// MadgwickAHRS library for Quaternion                				         //
///////////////////////////////////////////////////////////////////////////////
#include <MadgwickAHRS.h>

///////////////////////////////////////////////////////////////////////////////
// VIBRATION MOTOR SETTINGS							                         //
///////////////////////////////////////////////////////////////////////////////
#define vibrationMotor_PIN 13	//(MoterV)

///////////////////////////////////////////////////////////////////////////////
// Photo-reflector PINs Setup                                                //
///////////////////////////////////////////////////////////////////////////////
#define PR_CH_NUM 8      // Number of Channels
#define PR_LED_PIN 8

///////////////////////////////////////////////////////////////////////////////
// EMS Multiplexer PINs Setup                                                //
///////////////////////////////////////////////////////////////////////////////
#define EMS_EN_PIN 7
#define EMS_S0_PIN 4
#define EMS_S1_PIN 5
#define EMS_S2_PIN 6

///////////////////////////////////////////////////////////////////////////////
// EMS BOOSTER SETUP                                                          //
///////////////////////////////////////////////////////////////////////////////
#define MAX_VOL 12//relation_V_Delay.length
#define MIN_VOL 0
#define BOOSTER_SWITCH_PIN 9 //switch pin : 
const int relation_V_Delay[13] = {60, 40, 30, 22, 17, 13, 10, 7, 5, 4, 3, 2, 1};

///////////////////////////////////////////////////////////////////////////////
// EMS PATTERN SETUP                                                         //
///////////////////////////////////////////////////////////////////////////////
#define DEF_STIMU_TIME_COUNT 200
//200
#define DEF_STIMU_HIGH_WID 200
//3000(3ms)<DEF_STIMU_LOW_WID
#define DEF_STIMU_LOW_WID 22500
//#define DEF_STIMU_LOW_WID 12500



/******************************************************************************
*	CLASS of UnlimitedHand(UH)           
******************************************************************************/
class UH{
  public:
  	Kalman kalmanX; // Create the Kalman instances
	Kalman kalmanY;
	Kalman kalmanZ;
	Kalman kalmanQx;
	Kalman kalmanQy;
	Kalman kalmanQz;
	Kalman kalmanQw;
	
	/* MadgwickAHRS Objects for Quaternion */
	Madgwick filter; 
	float gyroSenceFactor = 600;//800

	/* IMU Data */
	double accX, accY, accZ;
	double gyroX, gyroY, gyroZ;
	//int16_t tempRaw;

 
	double gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro only
	double compAngleX, compAngleY, compAngleZ; // Calculated angle using a complementary filter
	double kalAngleX, kalAngleY, kalAngleZ; // Calculated angle using a Kalman filter
 
	uint32_t timer;
	uint32_t timer2;
	float roll, pitch, yaw;
	
	int currentEMSChannel;
	int EMSTimeCount;
	int stimuHighWid;
	int stimuLowWid;
	int stimuTimeCount;
	int currentVol;

	//Contructor 
	UH(){
		
	};
	
	
	///////////////////////////////////////////////////////////////////////////////
	// MPU6050 FUNCTIONS for the Acceleration and the Gyro                        //
	///////////////////////////////////////////////////////////////////////////////
	/**  Function: MPU6050_read        ***************************/
	int MPU6050_read(uint8_t regAddr, uint8_t *buffer, int size){
		int i,n, n1, n2, error;
		n1 = i2c_start(MPU6050_I2C_ADDRESS | I2C_WRITE );
		n2 = i2c_write(regAddr);
		i2c_stop();
		/*
		Serial.println (regAddr, HEX);
		Serial.print (n1);
		Serial.print ("___rd___");
		Serial.println (n2);
		*/
		delay (50);
		int r = 0;
		while(r < (size - 1)){
			i2c_start(MPU6050_I2C_ADDRESS | I2C_READ);
			buffer[r] = i2c_read (false);
			i2c_stop();
			r++;
		} 
		i2c_start(MPU6050_I2C_ADDRESS | I2C_READ);
		buffer[r] = i2c_read (true);
		i2c_stop();
		return (0);  // return : no error
	};
	/**  Function: MPU6050_read_one    ***************************/
	int MPU6050_read_one(uint8_t regAddr){
		int i,n, n1, n2, error, oneByte, buffer;
		//read high byte at first address
		n1 = i2c_start(MPU6050_I2C_ADDRESS | I2C_WRITE );
		n2 = i2c_write(regAddr);
		i2c_stop();
		i2c_start(MPU6050_I2C_ADDRESS | I2C_READ);
		oneByte = i2c_read (false); //read one byte
		i2c_stop();
		return oneByte;  // return byte value
	};
			
	/**  Function: MPU6050_read_two    ***************************/
	int MPU6050_read_two(uint8_t regAddr){
		int i,n, n1, n2, error, hByte, lByte, buffer;
		//read high byte at first address
		n1 = i2c_start(MPU6050_I2C_ADDRESS | I2C_WRITE );
		n2 = i2c_write(regAddr);
		i2c_stop();
		
		i2c_start(MPU6050_I2C_ADDRESS | I2C_READ);
		hByte = i2c_read (false); //read high byte
		i2c_stop();
		regAddr++;
		
		//read low byte at next address
		n1 = i2c_start(MPU6050_I2C_ADDRESS | I2C_WRITE );
		n2 = i2c_write(regAddr);
		i2c_stop();
		
		i2c_start(MPU6050_I2C_ADDRESS | I2C_READ);
		lByte = i2c_read (true); //read low byte
		i2c_stop();
		
		hByte = hByte << 8;
		buffer = hByte | lByte;
		
		return buffer;  // return 
	};
	/**  Function: MPU6050_write_one    ***************************/
	int MPU6050_write_one(int regAddr, int pData){
		int i, n, n1, n2, error;
		//Serial.println ("start write");
		//Wire.beginTransmission(MPU6050_I2C_ADDRESS);
		if(!i2c_start(MPU6050_I2C_ADDRESS | I2C_WRITE)){
			return false;
		}
		// write the start address
		if(!i2c_write(regAddr)){
			return false;
		}
		if (!i2c_write(pData)){
			return false;
		}
		i2c_stop();
		return (3);
	};
			
	/**  Function: MPU6050_write_one    ***************************/
	void setupAcceleGyro(){
		TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
		if (!i2c_init()) {
			//Serial.println(F("Initialization error. SDA or SCL are low"));
		}else{
			//Serial.println(F("...done"));
		}
		
		while (!Serial);  //according to docs this holds until serial is open, this does not appear to work
		
		uint8_t c;
		int error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
		//Serial.print(F("WHO_AM_I : "));
		//Serial.print(c,HEX);
		
		//Serial.print(F(", error = "));
		//Serial.println(error,DEC);
		
		// According to the datasheet, the 'sleep' bit
		// should read a '1'.
		// That bit has to be cleared, since the sensor
		// is in sleep mode at power-up. 
		error = MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);
		/*
		Serial.print(F("PWR_MGMT_1 : "));
		Serial.print(c,HEX);
		Serial.print(F(", error = "));
		Serial.println(error,DEC);
		*/
		
		//from multiwii  set up 6050
		delay(100);
		MPU6050_write_one(0x6B, B10000000);             //PWR_MGMT_1    -- DEVICE_RESET 1
		delay(100);
		MPU6050_write_one(0x6B, 0);             //PWR_MGMT_1    -
		delay(100);
		
		error = MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);
		/*
		Serial.print(F("PWR_MGMT_1 : "));
		Serial.print(c,HEX);
		Serial.print(F(", error = "));
		Serial.println(error,DEC);
		5*/  
	};
	
	/**  Function: initAccelGyroKalman    ***************************/
	void initAccelGyroKalman(uint32_t initTime, int accelRawValues[]){
	  accX = accelRawValues[0];
	  accY = accelRawValues[1];
	  accZ = accelRawValues[2];
	  #ifdef RESTRICT_PITCH // Eq. 25 and 26
	    roll  = atan2(accY, accZ) * RAD_TO_DEG;
		pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
		yaw = atan2(accZ, accY) * RAD_TO_DEG;
	  #else // Eq. 28 and 29
	    roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
		pitch = atan2(-accX, accZ) * RAD_TO_DEG;
		yaw = atan(sqrt(accX * accX + accY * accY)/accZ) * RAD_TO_DEG;
	  #endif
 
		kalmanX.setAngle(roll); // Set starting angle
		kalmanY.setAngle(pitch);
		kalmanZ.setAngle(yaw);
		gyroXangle = roll;
		gyroYangle = pitch;
		gyroZangle = yaw;
		compAngleX = roll;
		compAngleY = pitch;
		compAngleZ = yaw;
		timer = initTime;
		timer2 = initTime;
		
		float q[4]; // Set starting quaternion data
		updateQuaternion(q);
		kalmanQx.setAngle(q[0]);
		kalmanQy.setAngle(q[1]);
		kalmanQz.setAngle(q[2]);
		kalmanQw.setAngle(q[3]);
	}
	
	
	
	/**  Function: readAccelGyro_XY_Kalman    ***************************/
	void readAccelGyro_XYZ_Kalman(int accelRawValues[], int gyroRawValues[], int angleXYZ[]){ 
	  /* Update all the values */
	  accX = accelRawValues[0];
	  accY = accelRawValues[1];
	  accZ = accelRawValues[2];
	  gyroX = gyroRawValues[0];
	  gyroY = gyroRawValues[1];
	  gyroZ = gyroRawValues[2];
 
	  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
	  timer = micros();
 
	  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
	  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
	  // It is then converted from radians to degrees
	  #ifdef RESTRICT_PITCH // Eq. 25 and 26
	    roll  = atan2(accY, accZ) * RAD_TO_DEG;//+++++++++++++++++++++++
		pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
		yaw = atan2(accZ, accY) * RAD_TO_DEG;
	  #else // Eq. 28 and 29
	    roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
		pitch = atan2(-accX, accZ) * RAD_TO_DEG;
		yaw = atan(sqrt(accX * accX + accY * accY)/accZ) * RAD_TO_DEG;
	  #endif
 
	  double gyroXrate = gyroX / 131.0; // Convert to deg/s
	  double gyroYrate = gyroY / 131.0; // Convert to deg/s
	  double gyroZrate = gyroZ / 131.0; // Convert to deg/s
 
	  #ifdef RESTRICT_PITCH
   		 // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
   		 if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
      		kalmanX.setAngle(roll);
      		compAngleX = roll;
      		kalAngleX = roll;
      		gyroXangle = roll;
    	}else{
    		kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
    	}
 
    	if (abs(kalAngleX) > 90)
      		gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
			  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
			  
		//Z
		// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
   		 if ((yaw < -90 && kalAngleZ > 90) || (yaw > 90 && kalAngleZ < -90)) {
      		kalmanZ.setAngle(yaw);
      		compAngleZ = yaw;
      		kalAngleZ = yaw;
      		gyroZangle = yaw;
    	}else{
    		kalAngleZ = kalmanZ.getAngle(yaw, gyroZrate, dt); // Calculate the angle using a Kalman filter
    	}
 
    	if (abs(kalAngleZ) > 90)
      		gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
      		kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
  	#else
    	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    		if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
      			kalmanY.setAngle(pitch);
      			compAngleY = pitch;
      			kalAngleY = pitch;
      			gyroYangle = pitch;
    		}else{
    			kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter
    		}
 
   		if (abs(kalAngleY) > 90)
    			gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
    			kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
  	#endif
 
  		gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  		gyroYangle += gyroYrate * dt;
  		gyroZangle += gyroZrate * dt;
  		//gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  		//gyroYangle += kalmanY.getRate() * dt;
 
  		compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  		compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
		compAngleZ = 0.93 * (compAngleZ + gyroZrate * dt) + 0.07 * yaw;
		
 		 // Reset the gyro angle when it has drifted too much
 		if (gyroXangle < -180 || gyroXangle > 180)
    		gyroXangle = kalAngleX;
  		if (gyroYangle < -180 || gyroYangle > 180)
			gyroYangle = kalAngleY;
		if (gyroZangle < -180 || gyroZangle > 180)
    		gyroZangle = kalAngleZ;
  
  		angleXYZ[0] =(int)kalAngleX;
  		angleXYZ[1] =(int)kalAngleY;
  		angleXYZ[2] =(int)kalAngleZ;
  		delay(1);
	}
	
	/**  Function: checkAccelGyro_XY_Kalman    ***************************/
void checkAccelGyro_XYZ_Kalman(){ 
	int accelRaw[3];
	readRawAccelValues(accelRaw);
	int gyroRaw[3];
	readRawGyroValues(gyroRaw);
	double temp = readTemperature();
	int angXYZ[3];
	readAccelGyro_XYZ_Kalman(accelRaw, gyroRaw, angXYZ);
  
  
  Serial.print(angXYZ[0], DEC);//AcX = 
  Serial.print("+"); Serial.print(angXYZ[1], DEC);// | AcY =
  Serial.print("+"); Serial.print(angXYZ[2], DEC);// | AcZ = 
  Serial.print("+"); Serial.print(temp, 3);  //temperature
  Serial.print("+"); Serial.print(gyroRaw[0], DEC);
  Serial.print("+"); Serial.print(gyroRaw[1], DEC);
  Serial.print("+"); Serial.println(gyroRaw[2], DEC);
  delay(1);
  /*
  accelRaw[0] = (int)kalAngleX;
  accelRaw[1] =(int)kalAngleY;
  accelRaw[2] =(int)gyroZangle;
  
  Serial.print(accelRaw[0], DEC);//AcX = 
    Serial.print(", "); Serial.print(accelRaw[1], DEC);// | AcY =
    Serial.print(", "); Serial.print(accelRaw[2], DEC);// | AcZ = 
    Serial.print(", "); Serial.print(tempt, 3);  //temperature
    Serial.print(", "); Serial.print(gyroRaw[0], DEC);
    Serial.print(", "); Serial.print(gyroRaw[1], DEC);
    Serial.print(", "); Serial.println(gyroRaw[2], DEC);
    delay(1);
    */
 
}
	/**  Function: checkAccelGyro_XY_Kalman_test    ***************************/
void checkAccelGyro_XYZ_Kalman_test(){ 
	int accelRaw[3];
	readRawAccelValues(accelRaw);
	int gyroRaw[3];
	readRawGyroValues(gyroRaw);
	double temp = readTemperature();
	int angXYZ[3];
	readAccelGyro_XYZ_Kalman(accelRaw, gyroRaw, angXYZ);
  
  
  Serial.print(angXYZ[0], DEC);//AcX = 
  Serial.print('\t'); Serial.print(angXYZ[1], DEC);// | AcY =
  Serial.print('\t'); Serial.print(angXYZ[2], DEC);// | AcZ = 
  Serial.print('\t'); Serial.print(temp, 3);  //temperature
  Serial.print('\t'); Serial.print(gyroRaw[0], DEC);
  Serial.print('\t'); Serial.print(gyroRaw[1], DEC);
  Serial.print('\t'); Serial.println(gyroRaw[2], DEC);
  delay(1);
  /*
  accelRaw[0] = (int)kalAngleX;
  accelRaw[1] =(int)kalAngleY;
  accelRaw[2] =(int)gyroZangle;
  
  Serial.print(accelRaw[0], DEC);//AcX = 
    Serial.print(", "); Serial.print(accelRaw[1], DEC);// | AcY =
    Serial.print(", "); Serial.print(accelRaw[2], DEC);// | AcZ = 
    Serial.print(", "); Serial.print(tempt, 3);  //temperature
    Serial.print(", "); Serial.print(gyroRaw[0], DEC);
    Serial.print(", "); Serial.print(gyroRaw[1], DEC);
    Serial.print(", "); Serial.println(gyroRaw[2], DEC);
    delay(1);
    */
 
}

	/**  Function: readRawAccelValues    ***************************/
	void readRawAccelValues(int AccelRawValue[]){
		AccelRawValue[0]= MPU6050_read_two (MPU6050_ACCEL_XOUT_H);
		AccelRawValue[1]= MPU6050_read_two (MPU6050_ACCEL_YOUT_H);
		AccelRawValue[2]= MPU6050_read_two (MPU6050_ACCEL_ZOUT_H);
	};
	/**  Function: checkRawAccelValues    ***************************/
	void checkRawAccelValues(){
		int AccelRawVal[3];
		AccelRawVal[0]= MPU6050_read_two (MPU6050_ACCEL_XOUT_H);
		AccelRawVal[1]= MPU6050_read_two (MPU6050_ACCEL_YOUT_H);
		AccelRawVal[2]= MPU6050_read_two (MPU6050_ACCEL_ZOUT_H);
		Serial.print(AccelRawVal[0], DEC);//AcX = 
		Serial.print(", "); Serial.print(AccelRawVal[1], DEC);// | AcY =
		Serial.print(", "); Serial.print(AccelRawVal[2], DEC);// | AcZ = 
	}
	/**  Function: readRawGyroValues    ***************************/
	void readRawGyroValues(int GyroRawValue[]){
		GyroRawValue[0]= MPU6050_read_two (MPU6050_GYRO_XOUT_H);
		GyroRawValue[1]= MPU6050_read_two (MPU6050_GYRO_YOUT_H);
		GyroRawValue[2]= MPU6050_read_two (MPU6050_GYRO_ZOUT_H);
	};
	/**  Function: checkRawGyroValues    ***************************/
	void checkRawGyroValues(){
		int GyroRawVal[3];
		GyroRawVal[0]= MPU6050_read_two (MPU6050_GYRO_XOUT_H);
		GyroRawVal[1]= MPU6050_read_two (MPU6050_GYRO_YOUT_H);
		GyroRawVal[2]= MPU6050_read_two (MPU6050_GYRO_ZOUT_H);
		Serial.print(", "); Serial.print(GyroRawVal[0], DEC);
		Serial.print(", "); Serial.print(GyroRawVal[1], DEC);
		Serial.print(", "); Serial.print(GyroRawVal[2], DEC);
	};
	/**  Function: readTemperature    ***************************/
	double readTemperature(){
		int tempRaw = MPU6050_read_two (MPU6050_TEMP_OUT_H);
		double calcTemp = ((double) tempRaw + 12412.0) / 340.0;
		return calcTemp;
	};
	/**  Function: checkTemperature    ***************************/
	void checkTemperature(){
		int tempRaw = MPU6050_read_two (MPU6050_TEMP_OUT_H);
		double calcTemp = ((double) tempRaw + 12412.0) / 340.0;
		Serial.print(", "); Serial.print(calcTemp, 3);  //temperature
	};
			
	///////////////////////////////////////////////////////////////////////////////
	// FUNCTIONS: QUATERNION                                                     //
	///////////////////////////////////////////////////////////////////////////////
	/**  Function: updateQuaternion( with gyro sencetive factor) */
	void updateQuaternion(float QuaternionData[], float gyroFactor){
		gyroSenceFactor = gyroFactor;
		int accelRaw[3];
		readRawAccelValues(accelRaw);
		int gyroRaw[3];
		readRawGyroValues(gyroRaw);
		filter.updateIMU_Qua((float)gyroRaw[0]/gyroSenceFactor, (float)gyroRaw[1]/gyroSenceFactor, (float)gyroRaw[2]/gyroSenceFactor, accelRaw[0], accelRaw[1], accelRaw[2], QuaternionData);
	}
	/**  Function: updateQuaternion   ****************************/	
	void updateQuaternion(float QuaternionData[]){
		int accelRaw[3];
		readRawAccelValues(accelRaw);
		int gyroRaw[3];
		readRawGyroValues(gyroRaw);
		filter.updateIMU_Qua((float)gyroRaw[0]/gyroSenceFactor, (float)gyroRaw[1]/gyroSenceFactor, (float)gyroRaw[2]/gyroSenceFactor, accelRaw[0], accelRaw[1], accelRaw[2], QuaternionData);
	}
	/**  Function: updateQuaternionKalman( with gyro sencetive factor) */
	void updateQuaternionKalman(float QuaternionData[], float gyroFactor){
		gyroSenceFactor = gyroFactor;
		int accelRaw[3];
		readRawAccelValues(accelRaw);
		int gyroRaw[3];
		readRawGyroValues(gyroRaw);
		
		double dt = (double)(micros() - timer2) / 1000000; // Calculate delta time
		timer2 = micros();

		filter.updateIMU_Qua((float)gyroRaw[0]/gyroSenceFactor, (float)gyroRaw[1]/gyroSenceFactor, (float)gyroRaw[2]/gyroSenceFactor, accelRaw[0], accelRaw[1], accelRaw[2], QuaternionData);
		//kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
		QuaternionData[0] = kalmanQx.getAngle(QuaternionData[0], 1.0f ,dt);
		QuaternionData[1] = kalmanQy.getAngle(QuaternionData[1], 1.0f ,dt);
		QuaternionData[2] = kalmanQz.getAngle(QuaternionData[2], 1.0f ,dt); 
		QuaternionData[3] = kalmanQw.getAngle(QuaternionData[3], 1.0f ,dt);
		
	}
	
	/**  Function: updateQuaternionKalman   ****************************/	
	void updateQuaternionKalman(float QuaternionData[]){
		updateQuaternionKalman(QuaternionData, gyroSenceFactor);
	}	
	/**  Function: resetQuaternion   ****************************/
	void resetQuaternion(float QuaternionData[]){
		//filter.reset();
		QuaternionData[0] = 1.0f;
		QuaternionData[1] = 0.0f;
		QuaternionData[2] = 0.0f;
		QuaternionData[3] = 0.0f;
		//updateQuaternionKalman(QuaternionData);
		
	}
	/**  Function: resetQuaternion   ****************************/
	/*void resetQuaternion(float QuaternionData[]){
		
		int accelRaw[3];
		readRawAccelValues(accelRaw);
		int gyroRaw[3];
		readRawGyroValues(gyroRaw);
		QuaternionData[0] = 0.0f;
		QuaternionData[1] = 0.0f;
		QuaternionData[2] = 0.0f;
		QuaternionData[3] = -1.0f;
		double dt = (double)(micros() - timer2) / 1000000; // Calculate delta time
		timer2 = micros();
		QuaternionData[0] = kalmanQx.getAngle(QuaternionData[0], 1.0f ,dt);
		QuaternionData[1] = kalmanQy.getAngle(QuaternionData[1], 1.0f ,dt);
		QuaternionData[2] = kalmanQz.getAngle(QuaternionData[2], 1.0f ,dt);
		QuaternionData[3] = kalmanQw.getAngle(QuaternionData[3], 1.0f ,dt);
		
		filter.updateIMU_Qua((float)gyroRaw[0]/gyroSenceFactor, (float)gyroRaw[1]/gyroSenceFactor, (float)gyroRaw[2]/gyroSenceFactor, accelRaw[0], accelRaw[1], accelRaw[2], QuaternionData);

	}*/
	///////////////////////////////////////////////////////////////////////////////
	// FUNCTIONS: VIBRATION MOTOR						                         //
	///////////////////////////////////////////////////////////////////////////////
	/**  Function: setupVibrationMotor    ***************************/
	void setupVibrationMotor(){
		pinMode(vibrationMotor_PIN, OUTPUT);
		digitalWrite(vibrationMotor_PIN, HIGH);
	}
	/**  Function: moveVibrationMotor    ***************************/
	void moveVibrationMotor(int mTime){
		digitalWrite(vibrationMotor_PIN, LOW);
		delay(mTime);
		digitalWrite(vibrationMotor_PIN, HIGH);
	}
	/**  Function: onVibrationMotor    ***************************/
	void onVibrationMotor(){
		digitalWrite(vibrationMotor_PIN, LOW);
	}
	/**  Function: offVibrationMotor    ***************************/
	void offVibrationMotor(){
		digitalWrite(vibrationMotor_PIN, HIGH);
	}
	///////////////////////////////////////////////////////////////////////////////
	// FUNCTIONS: Photo-reflectors for Muscle Motion Sensors					 //
	///////////////////////////////////////////////////////////////////////////////
	/**  Function: readPR    ***************************/
	int readPR(int channel){
		return analogRead(channel);
	}
	/**  Function: readPR    ***************************/
	void readPR(int PRValues[]){
		for(int i = 0; i < PR_CH_NUM; i ++){   
			PRValues[i] = readPR(i);
			delay(1);
		}
	}
	/**  Function: checkPR    ***************************/
	void checkPR(){
	//Loop through and read all 8 values
	//Reports back Value at channel 6 is: 346
		for(int i = 0; i < PR_CH_NUM-1; i ++){
    		Serial.print(String(readPR(i)));
    		Serial.print("_");
    		delay(1);  
  		}
		Serial.print(String(readPR(PR_CH_NUM)));
		Serial.println("");
	}

	/**  Function: checkPR    ***************************/
	void checkPR_test(){
	//Loop through and read all 8 values
	//Reports back Value at channel 6 is: 346
		for(int i = 0; i < PR_CH_NUM; i ++){
    		Serial.print(String(readPR(i)));
    		Serial.print('\t');
    		delay(1);  
  		}
		Serial.println("");
	}
	
	void initPR(){
		 pinMode(PR_LED_PIN, OUTPUT);
  		digitalWrite(PR_LED_PIN, LOW);
	}

	/** Function: checkXYZPR    ***************************/ 
	void checkXYZPR(){
	  int accelRaw[3];
	  readRawAccelValues(accelRaw);
	  int gyroRaw[3];
	  readRawGyroValues(gyroRaw);
	  int angXYZ[3];
	  readAccelGyro_XYZ_Kalman(accelRaw, gyroRaw, angXYZ);
    
	  Serial.print(angXYZ[0], DEC);//AcX = 
	  Serial.print(", "); Serial.print(angXYZ[1], DEC);// | AcY =
	  Serial.print(", "); Serial.print(angXYZ[2], DEC);// | AcZ = 
	  Serial.print(", ");

	  checkPR();
  
	  delay(1);

	}
	
	void checkKalmanXYZPR(){
		int accelRaw[3];
		readRawAccelValues(accelRaw);
		int gyroRaw[3];
		readRawGyroValues(gyroRaw);
		int angXYZ[3];
		readAccelGyro_XYZ_Kalman(accelRaw, gyroRaw, angXYZ);
		
		Serial.print(angXYZ[0], DEC);//AcX = 
		Serial.print("+"); Serial.print(angXYZ[1], DEC);// | AcY =
		Serial.print("+"); Serial.print(angXYZ[2], DEC);// | AcZ = 
		for(int i = 0; i < PR_CH_NUM; i ++){
			Serial.print("+");Serial.print(String(readPR(i)));
		}
		Serial.println("");
	}

	void checkXYZPR_test(){
	  int accelRaw[3];
	  readRawAccelValues(accelRaw);
	  int gyroRaw[3];
	  readRawGyroValues(gyroRaw);
	  double temp = readTemperature();
	  int angXYZ[3];
	  readAccelGyro_XYZ_Kalman(accelRaw, gyroRaw, angXYZ);
    
	  Serial.print(angXYZ[0], DEC);//AcX = 
	  Serial.print('\t'); Serial.print(angXYZ[1], DEC);// | AcY =
	  Serial.print('\t'); Serial.print(angXYZ[2], DEC);// | AcZ = 
	  Serial.print('\t');
	  //	  Serial.print('\t'); Serial.print(temp, 3);  //temperature
	  //	  Serial.print('\t'); Serial.print(gyroRaw[0], DEC);
	  //	  Serial.print('\t'); Serial.print(gyroRaw[1], DEC);
	  //	  Serial.print('\t'); Serial.print(gyroRaw[2], DEC);
	  
	  for(int i = 0; i < PR_CH_NUM; i ++){
	    Serial.print(String(readPR(i)));
	    Serial.print('\t');
	    delay(1);  
	  }
	  Serial.println("");

	}
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// FUNCTIONS: Controller for the Multiplexer of the EMS(Electric Muscle Stimuli			 //
	///////////////////////////////////////////////////////////////////////////////////////////
	
	
	/**  Function: connectMUX    ***************************/
	void connectMUX(int num){
		int dec2bin[] = {0, 0, 0, 0};//objects for the function:connectMUX
		for(int i=0;num>0;i++){
			dec2bin[i] = num%2;
			num = num/2;
		}
		if(dec2bin[0]==1){
			digitalWrite(EMS_S0_PIN, HIGH);
		}else{
			digitalWrite(EMS_S0_PIN, LOW);
		}
		if(dec2bin[1]==1){
			digitalWrite(EMS_S1_PIN, HIGH);
		}else{
			digitalWrite(EMS_S1_PIN, LOW);
		}
		if(dec2bin[2]==1){
			digitalWrite(EMS_S2_PIN, HIGH);
		}else{
			digitalWrite(EMS_S2_PIN, LOW);
		}
		
	}

	/**  Function: keepVoltage    ***************************/
	/*void keepVoltage(int volNum) {
		if (MIN_VOL <= volNum && volNum <= MAX_VOL) {
			int stockVolTime = f[volNum];
			int loopNum = 1500 / stockVolTime;
			for (int i = 0; i < loopNum; i++) {
				digitalWrite(BOOSTER_SWITCH_PIN, HIGH);
				delayMicroseconds(stockVolTime);
				digitalWrite(BOOSTER_SWITCH_PIN, LOW);
				delayMicroseconds(stockVolTime);
			}
		}
	}*/
	/**  Function: keepVoltage    ***************************/
	void keepVoltage(int volNum) {
		if (MIN_VOL <= volNum && volNum <= MAX_VOL) {
			int stockVolTime = relation_V_Delay[volNum];
			//int loopNum = (relation_V_Delay[0] * 2) / stockVolTime;
			int loopNum = 100 / stockVolTime;
			for (int i = 0; i < loopNum; i++) {
				digitalWrite(BOOSTER_SWITCH_PIN, HIGH);
				delayMicroseconds(stockVolTime * 20);
				//delay(stockVolTime);
				digitalWrite(BOOSTER_SWITCH_PIN, LOW);
				delayMicroseconds(stockVolTime * 20);
				//delay(stockVolTime);
			}
		}
	}
	
	/**  Function: initEMS    ***************************/
	void initEMS(){ 
		//set up the EMS MUX pins
		pinMode(EMS_EN_PIN, OUTPUT);
		pinMode(EMS_S0_PIN, OUTPUT);
		pinMode(EMS_S1_PIN, OUTPUT);
		pinMode(EMS_S2_PIN, OUTPUT);
		
		//set up the EMS booster pin and objects
		pinMode(BOOSTER_SWITCH_PIN, OUTPUT);

		//set up the EMS Pattern
		stimuTimeCount = DEF_STIMU_TIME_COUNT;
		stimuHighWid = DEF_STIMU_HIGH_WID;
		stimuLowWid = DEF_STIMU_LOW_WID;
		
		//set up 
		currentEMSChannel = -1;
		EMSTimeCount = -1;
		currentVol = 11;
	}
	
	/**  Function: setStimulationTime    ***************************/
	void setStimulationTime(){
		EMSTimeCount = stimuTimeCount;
	}
	/**  Function: setStimulationTime    ***************************/
	void setStimulationTime(int t){
		EMSTimeCount = t;
	}
	/**  Function: setStimulationChannel    ***************************/
	void setStimulationChannel(int channel){
		if(-1 <= channel && channel < 8){
			currentEMSChannel = channel;
		}
	}
	
	void setStimulationVoltage(int vol){
		currentVol = vol;
	}
	void updateEMS() { 
		if (0<=EMSTimeCount) {//if there are any EMS
			connectMUX(currentEMSChannel);//prepare the MUX connection
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse  
			delayMicroseconds(200);//time of the HIGH pulse
			digitalWrite(EMS_EN_PIN, LOW);// LOW pulse
			keepVoltage(currentVol);//charge the voltage during the LOW pulse
			//delayMicroseconds(stimuLowWid);
			EMSTimeCount--;
		} else {              //if there is no EMS
			currentEMSChannel = -1; 
			setEMS_LOW();
		}
	}
	
	void updateEMS_POWERFUL() { 
		if (0<=EMSTimeCount) {//if there are any EMS
			connectMUX(currentEMSChannel);//prepare the MUX connection
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse  
			delayMicroseconds(200);//time of the HIGH pulse
			digitalWrite(EMS_EN_PIN, LOW);// LOW pulse
			keepVoltage(currentVol);//charge the voltage during the LOW pulse
			keepVoltage(currentVol);
			//delayMicroseconds(stimuLowWid);
			EMSTimeCount--;
		} else {              //if there is no EMS
			currentEMSChannel = -1; 
			setEMS_LOW();
		}
	}

	void updateEMS_HiVoltage() { 
		if (0<=EMSTimeCount) {//if there are any EMS
			connectMUX(currentEMSChannel);//prepare the MUX connection
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse  
			delayMicroseconds(40);//time of the HIGH pulse
			digitalWrite(EMS_EN_PIN, LOW);// LOW pulse
			delayMicroseconds(120);//time of LOW pulse
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse
			delayMicroseconds(40);// time of HIGH pulse
			keepVoltage(currentVol);//charge the voltage during the HIGH pulse
			keepVoltage(currentVol);
			//delayMicroseconds(stimuLowWid);
			EMSTimeCount--;
		} else {              //if there is no EMS
			currentEMSChannel = -1; 
			setEMS_LOW();
		}
	}
	
	void updateEMS_HiVoltage_POWERFUL() { 
		if (0<=EMSTimeCount) {//if there are any EMS
			connectMUX(currentEMSChannel);//prepare the MUX connection
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse  
			delayMicroseconds(20);//time of the HIGH pulse
			digitalWrite(EMS_EN_PIN, LOW);// LOW pulse
			delayMicroseconds(160);//time of LOW pulse
			digitalWrite(EMS_EN_PIN, HIGH);//HIGH pulse
			delayMicroseconds(20);// time of HIGH pulse
			keepVoltage(currentVol);//charge the voltage during the HIGH pulse
			//delayMicroseconds(stimuLowWid);
			EMSTimeCount--;
		} else {              //if there is no EMS
			currentEMSChannel = -1; 
			setEMS_LOW();
		}
	}
	
	void setEMS_LOW(){
		digitalWrite(BOOSTER_SWITCH_PIN, LOW);
		digitalWrite(EMS_EN_PIN, LOW);
		digitalWrite(EMS_S0_PIN, LOW);
		digitalWrite(EMS_S1_PIN, LOW);
		digitalWrite(EMS_S2_PIN, LOW);
	}
};



#endif
