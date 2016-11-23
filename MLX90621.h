/*
 * MLX90621.h
 *
 *  Created on: 08.07.2014
 *      Author: Max Ritter
 *
 *  Adapted by https://github.com/longjos
 *  	Adapted for use with Arduino UNO
 */

#ifndef MLX90621_H_
#define MLX90621_H_

#ifdef __cplusplus

//Libraries to be included
#include <Arduino.h>
#include <Wire.h>

const byte PACKET_SIZE 		= 32;

const int EEPROM_SIZE 		= 256;
const uint8_t NUM_PIXELS 	= 64;

const byte RAM_ADDRESS 		= 0x60;
const byte EEPROM_ADDRESS 	= 0x50;
const byte CONFIG_ADDRESS 	= 0x92;

const byte READ_EEPROM 		= 0x00;
const byte READ_RAM 		= 0x02;
const byte WRITE_REGISTER	= 0x03;
const byte WRITE_OSC_TRIM 	= 0x04;

const byte PTAT_ADDRESS 	= 0x40;
const byte CPIX_ADDRESS 	= 0x41;
const byte OSC_CHECK 		= 0xAA;
const byte CONF_CHECK 		= 0x55;

//Begin registers
const byte CAL_ACOMMON_L 	= 0xD0;
const byte CAL_ACOMMON_H 	= 0xD1;
const byte CAL_ACP_L 		= 0xD3;
const byte CAL_ACP_H 		= 0xD4;
const byte CAL_BCP 			= 0xD5;
const byte CAL_alphaCP_L 	= 0xD6;
const byte CAL_alphaCP_H 	= 0xD7;
const byte CAL_TGC 			= 0xD8;
const byte CAL_AI_SCALE 	= 0xD9;
const byte CAL_BI_SCALE 	= 0xD9;

// EEPROM addresses for ambient temperature constants
const byte VTH_L 			= 0xDA;
const byte VTH_H 			= 0xDB;
const byte KT1_L 			= 0xDC;
const byte KT1_H 			= 0xDD;
const byte KT2_L 			= 0xDE;
const byte KT2_H 			= 0xDF;
const byte KT_SCALE 		= 0xD2;

//Common sensitivity coefficients
const byte CAL_A0_L 		= 0xE0;
const byte CAL_A0_H 		= 0xE1;
const byte CAL_A0_SCALE 	= 0xE2;
const byte CAL_DELTA_A_SCALE= 0xE3;
const byte CAL_EMIS_L 		= 0xE4;
const byte CAL_EMIS_H 		= 0xE5;
const byte CAL_KSTA_L 		= 0xE6;
const byte CAL_KSTA_H 		= 0xE7;

const byte OSC_TRIM_VALUE 	= 0xF7;
const byte POR_BIT 			= 10;


class MLX90621 {
private:
	/* Variables */
	uint8_t eeprom_buffer[EEPROM_SIZE]; /**<RAM buffer to store the sensor's EEPROM data. Contains compensation values*/
	int refresh_rate; /**<Refresh rate of the sensor in Hz. {0 (0.5 Hz), 1, 2, 4, 8, 16, 32}*/

	// Config methods
	void load_sensor();
	void read_EEPROM();
	void write_trimming_value();
	void set_configuration(int _refresh_rate);
	void precalculate_constants();
	uint8_t get_resolution();
	uint16_t get_config();
	void check_configuration();
	bool needs_reload();

	// Utilities
	int16_t twos_16(uint8_t highByte, uint8_t lowByte);
	int8_t twos_8(uint8_t byte);
	uint16_t unsigned_16(uint8_t highByte, uint8_t lowByte);

	// Ambient temperature
	int get_PTAT();

	// Object temperature
	void precalculate_frame_values();
	int get_compensation_pixel();
	void get_IR(int ir_buffer[]);
	float calculate_pixel(uint8_t pixel_num, int ir_buffer[]);

	// Ambient temperature compensation constants
	uint16_t k_t1_scale;
	uint16_t k_t2_scale;
	float v_th;
	float k_t1;
	float k_t2;

	// Object temperature compensation constants
	float resolution_comp;
	float tgc;
	float emissivity;
	int16_t a_common;
	uint16_t a_i_scale;
	uint16_t b_i_scale;
	float alpha_cp;
	float a_cp;
	float b_cp;

	// Object temperature frame constants
	float ambient;
	float tak4;
	float v_cp_off_comp;

public:
	void initialise(int);
	void get_temperatures(float output_buffer[]);
	void print_temperatures(Serial_ &ser);
	float get_ambient_temperature();
};

#endif
#endif
