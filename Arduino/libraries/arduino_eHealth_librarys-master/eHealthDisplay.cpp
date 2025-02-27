/*
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)."
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 0.1
 *  Author: Luis Martín & Ahmad Saad
 */


// include this library's description file
#include "eHealthDisplay.h"
#ifndef eHealth_h
	#include "eHealth.h"
#endif

#define pushButton 4

//LOGO EHEALTH
	 const uint8_t PROGMEM eHealthLogo[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x1F, 0x00, 0x3C, 0x00, 0x78, 0x0F, 0x0E, 0x18, 0x0F, 0xC0, 0x0F, 0xC0, 0x00, 0x00,
	0x00, 0x00, 0x7F, 0xC0, 0xFE, 0x01, 0xFE, 0x0F, 0x1F, 0x3C, 0x1F, 0xF0, 0x1F, 0xE0, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xC1, 0xFF, 0x83, 0xFF, 0x0F, 0x3E, 0x3C, 0x3F, 0xF0, 0x3F, 0xF0, 0x00, 0x00,
	0x00, 0x01, 0xFF, 0xE3, 0xFF, 0x87, 0xFF, 0x8F, 0xFE, 0x3C, 0x7F, 0xF8, 0x7F, 0xF8, 0x00, 0x00,
	0x00, 0x01, 0xE1, 0xC7, 0xC7, 0xC7, 0xC7, 0xCF, 0xFC, 0x3C, 0x78, 0x7C, 0x78, 0x78, 0x00, 0x00,
	0x00, 0x01, 0xE0, 0x07, 0x83, 0xC7, 0x83, 0xCF, 0xF8, 0x3C, 0xF0, 0x3C, 0xF0, 0x3C, 0x00, 0x00,
	0x00, 0x01, 0xC0, 0x07, 0x83, 0xCF, 0x03, 0xCF, 0xF0, 0x3C, 0xF0, 0x3C, 0xF0, 0x3C, 0x00, 0x00,
	0x00, 0x01, 0xE0, 0x07, 0x83, 0xC7, 0x03, 0xCF, 0xF0, 0x3C, 0xF0, 0x3C, 0xF0, 0x3C, 0x00, 0x00,
	0x00, 0x01, 0xE0, 0xC7, 0x83, 0xC7, 0x83, 0xCF, 0xFC, 0x3C, 0xF0, 0x3C, 0x78, 0x7C, 0x00, 0x00,
	0x00, 0x01, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0x8F, 0xFE, 0x3C, 0xF0, 0x3C, 0x7F, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xE3, 0xFF, 0x83, 0xFF, 0x8F, 0x3E, 0x3C, 0xF0, 0x3C, 0x7F, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0x7F, 0xC1, 0xFF, 0x03, 0xFF, 0x0F, 0x1F, 0x3C, 0xF0, 0x3C, 0x3F, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x3F, 0x00, 0xFE, 0x00, 0xFE, 0x07, 0x0E, 0x38, 0x70, 0x38, 0x0F, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x7F, 0xF0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x60, 0x3E, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0xF8, 0x03, 0xF8, 0x03, 0xF0, 0x78, 0xF0, 0xFF, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0xFC, 0x07, 0xFC, 0x0F, 0xFC, 0x79, 0xF1, 0xFF, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0xFE, 0x0F, 0xFE, 0x0F, 0xFC, 0x7B, 0xF3, 0xFF, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0xBF, 0x1F, 0x3E, 0x1F, 0x3C, 0x7F, 0xE3, 0xC0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x0F, 0x1E, 0x0F, 0x1E, 0x08, 0x7F, 0xC3, 0xFE, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x0F, 0x3C, 0x0F, 0x3C, 0x00, 0x7F, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0xBC, 0x0F, 0x3C, 0x00, 0x7F, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0x9E, 0x0F, 0x3C, 0x00, 0x7F, 0x80, 0xFF, 0xC0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0x9E, 0x1F, 0x1E, 0x1C, 0x7F, 0xC0, 0x03, 0xC0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0x9F, 0xFF, 0x1F, 0xFC, 0x7B, 0xE0, 0xFF, 0xC0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0x8F, 0xFF, 0x0F, 0xFC, 0x79, 0xF1, 0xFF, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1E, 0x07, 0x07, 0xFF, 0x07, 0xF8, 0x78, 0xF1, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0C, 0x07, 0x01, 0xE6, 0x01, 0xE0, 0x30, 0x60, 0xFE, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Cooking-Hacks logo. 
 const uint8_t PROGMEM cookingLogo[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x83, 0x00, 0x00, 0x00, 0x06, 0x0C, 0x00, 0xC0, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x00, 0x03, 0xC7, 0x80, 0x00, 0x00, 0x0F, 0x1E, 0x01, 0xE0, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x00, 0x03, 0xC7, 0x80, 0x00, 0x00, 0x0F, 0x1E, 0x01, 0xE0, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x00, 0x03, 0xC7, 0x80, 0x00, 0x00, 0x0F, 0x1F, 0xE1, 0xE0, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x1F, 0xC0, 0x03, 0xC7, 0x8F, 0xE0, 0x7F, 0x0F, 0x1F, 0xF1, 0xFF, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x3F, 0xE0, 0x03, 0xC7, 0x9F, 0xF0, 0xFF, 0x8F, 0x1F, 0xF1, 0xFF, 0x80, 0x00, 0x07, 0xF0, 0x00,
	0x30, 0x70, 0x03, 0xFF, 0x98, 0x38, 0xFF, 0x8F, 0x1F, 0xE1, 0xFF, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x70, 0x73, 0xF3, 0xFF, 0xB8, 0x39, 0xE3, 0xCF, 0x1E, 0x01, 0xFF, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x7F, 0xF7, 0xFB, 0xFF, 0xBF, 0xF9, 0xC1, 0xCF, 0x1E, 0x01, 0xE3, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x7F, 0xF3, 0xF3, 0xC7, 0xBF, 0xF9, 0xC1, 0xCF, 0x1E, 0x01, 0xE3, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x7F, 0xE0, 0x03, 0xC7, 0xBF, 0xF1, 0xE3, 0xCF, 0x1F, 0x39, 0xE3, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x30, 0x00, 0x03, 0xC7, 0x98, 0x00, 0xFF, 0xCF, 0x8F, 0xF9, 0xE3, 0xC0, 0x3F, 0xFF, 0xFF, 0xFE,
	0x3F, 0xC0, 0x03, 0xC7, 0x9F, 0xE0, 0xFF, 0xCF, 0xE7, 0xF9, 0xE3, 0xC0, 0x3F, 0xFF, 0xFF, 0xFE,
	0x1F, 0xC0, 0x03, 0xC7, 0x8F, 0xE0, 0x7E, 0xC7, 0xE3, 0xF0, 0xC1, 0x80, 0x3F, 0xFF, 0xFF, 0xFE,
	0x00, 0x00, 0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFE,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFE,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFE,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFE,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00,
	0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x20, 0x0F, 0xDF, 0x9F, 0x1F, 0x1C, 0x0F, 0xF1, 0xF1, 0xF1, 0xCF, 0xC0, 0x00, 0x07, 0xF0, 0x00,
	0x1F, 0x90, 0x50, 0xA0, 0x20, 0xA0, 0x08, 0x0A, 0x08, 0x0A, 0x10, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x5F, 0xD0, 0x9F, 0x20, 0xA0, 0x08, 0x0A, 0x09, 0xFA, 0x10, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x50, 0x10, 0x80, 0xA0, 0xA0, 0x08, 0x0A, 0x0A, 0x0A, 0x10, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x00, 0x50, 0x10, 0x80, 0xA0, 0xA0, 0x08, 0x0A, 0x0A, 0x0A, 0x10, 0x40, 0x00, 0x07, 0xF0, 0x00,
	0x3F, 0x8F, 0x90, 0x9F, 0x1F, 0x20, 0x0F, 0xF1, 0xF1, 0xF2, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
//***************************************************************
// Constructor of the class										*
//***************************************************************

	eHealthDisplayClass::eHealthDisplayClass(void){/*void constructor*/}

//***************************************************************
// Public Methods												*
//***************************************************************

	//!******************************************************************
	//!	Name: init()													*
	//!	Description: Configure and initializes the LCD.					*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.init();									*
	//!******************************************************************
	
	void eHealthDisplayClass::init(void)
	{
		//Configure the eHealth push-Button
		pinMode(pushButton, INPUT);
		clearLCD();
		delay(2000);

		//It prints the eHealth logo. 
		image(0,64,128,64,eHealthLogo);

		coordinates(1, 15);
		writeLCD("www.cooking-hacks.com"); 	delay(4000);

		clearLCD();

		//It prints cooking hacks logo. 
		image(0,64,128,64,cookingLogo);	delay(3000); 
		clearLCD();  
		delay(500);
	}

	//!******************************************************************
	//!	Name: initValuesScreen()										*
	//!	Description: Configure some parameters of the values screen.	*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.initValuesScreen();						*
	//!******************************************************************
	
	void eHealthDisplayClass::initValuesScreen()
	{
		bodyPosition = 0;
		oxygen = 0;
		
		eHealth.initPositionSensor();	delay(50);
		eHealth.initPulsioximeter();	delay(50);
		clearLCD();		delay(50);
		
		coordinates(99, 60);	writeLCD("Pose");			delay(100);
		coordinates(1,60);	writeLCD("CURRENT DATA");		delay(100);
		coordinates(1, 47);	writeLCD("Pulse (bpm)");		delay(100);
		coordinates(1, 35);	writeLCD("Conductance");		delay(100);
		coordinates(1, 22);	writeLCD("Oxygen");			delay(100);
		coordinates(90, 22);	writeLCD("%");				delay(100);
		coordinates(1, 9);	writeLCD("Temperature");		delay(100);
		coordinates(105, 9);	writeLCD("C");				delay(100);
		
		pixel (103,9,1);	pixel (104,9,1);
		pixel (103,8,1);	pixel (104,8,1);
	}

	//!******************************************************************
	//!	Name:	printValuesScreen()										*
	//!	Description: Refresh the values of the sensors in the screen.	*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.printValuesScreen();					*
	//!******************************************************************
	
	void eHealthDisplayClass::printValuesScreen(void)
	{
		
		delay(100);

		//Prints the current value of diastolic pressure.
		if (pulse != eHealth.getBPM()) {
			pulse = eHealth.getBPM();
			clearSpace(70, 40, 90, 47);
			coordinates(70,47);	Serial.print(pulse);
			delay(10);
		}

		//Stores the current value of skin conductance. 
		float conductance = eHealth.getSkinConductance();
		delay(20);

		//If conductance == -1, the sensor is no connected. 
		if ( conductance == -1 ) {
			coordinates(70,35);	Serial.print(F("NOCN")); //No connected message. 
			delay(10);
		} 
		else {		
			coordinates(70,35);	Serial.print(conductance,2);
			delay(10);
		}

		if (oxygen != eHealth.getOxygenSaturation())
		{
			oxygen = eHealth.getOxygenSaturation();
			clearSpace(70, 15, 90, 22);
			coordinates(70, 22);	Serial.print(oxygen);
			delay(10);
		}

		//Prints the current value of temperature. 
		coordinates(70,9);	Serial.print(eHealth.getTemperature(),2);
		delay(10);

		//If no changes in position, don't refresh the screen. 
		if (bodyPosition != eHealth.getBodyPosition()) {

			bodyPosition = eHealth.getBodyPosition();
			clearSpace(95, 34, 117, 50); // Clear the previous position. 

				 if (bodyPosition == 1) supinePosition();
			else if (bodyPosition == 2) leftLateralPosition();
			else if (bodyPosition == 3) rigthLateralPosition();
			else if (bodyPosition == 5) standPosition();
			else pronePosition();
		}
				
		delay(10);
	}

	//!******************************************************************
	//!	Name:	initECGScreen()											*
	//!	Description: Configure some parameters of the ECG screen.		*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.initECGScreen();						*
	//!******************************************************************
	
	void eHealthDisplayClass::initECGScreen(void)
	{
		clearLCD();    
		delay(200);

		timePrevious = 0;
		timePreviousMeassure = 0;
		time = 0;
		countPrevious = 0;

		//ECG LOGO
		line(20, 49, 21, 49, 1); 	line(22, 49, 24, 55, 1);
		line(24, 55, 28, 45, 1);	line(28, 45, 29, 49, 1);
		line(29, 49, 32, 49, 1);	delay(100);        

		//LETRAS POR PANTALLA 
		coordinates(42, 52);	writeLCD("ECG");
		coordinates(100, 52);	writeLCD( "cpm"); 

		delay(150);
		timePreviousMeassure = millis();
		count = 0;
		printHeart(1);
		x = 8;
	}

	//!******************************************************************
	//!		Name:	printECGScreen()									*
	//!		Description: Refresh the ECG wave in the LCD screen.		*
	//!		Param : void												*
	//!		Returns: void												*
	//!		Example: eHealthDisplay.printECGScreen();					*
	//!******************************************************************
	
	void eHealthDisplayClass::printECGScreen(void)
	{
		
		for (int j=0; j<45; j++){
			pixel(8,j,0);
		}
		
		delay(20);

		if (millis()-timePreviousMeassure > 10000){
			countsPerMinute = 6*count;
			timePreviousMeassure = millis();
			count = 0;
			//Clear space
			coordinates(95, 52);	backspace();
			coordinates(90, 52);	backspace();
			coordinates(85, 52);	backspace();
			coordinates(80, 52);	backspace();
			writeLcdDec(countsPerMinute);
			delay(20);
		}

		delay(10);
		printHeart(1);

		// Input 1   
		valRead = map(analogRead(0), 0, 1023, 5, 45);
		pixel (x, valRead, 1);

		if(x>12){
			line(x-1, prevRead, x, valRead, 1);
		}

		//Hearth blink
		if(valRead> 30)
		{
			count=count+1;
			printHeart(0);
			delay(200);
		}

		//Wave refresh 
		for (int j = 5; j<45; j++){
			pixel(x+1,j,0);
		}

		//Previous value
		prevRead = valRead;
		x++; 		
		if (x == 120) x = 8;
	}

	//!******************************************************************
	//!	Name: initAirFlowScreen()										*
	//!	Description: Configure some parameters of the AirFlow screen.	*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.initAirFlowScreen();					*
	//!******************************************************************
	
	void eHealthDisplayClass::initAirFlowScreen()
	{
		clearLCD();
		delay(200);

		timePrevious = 0;
		timePreviousMeassure = 0;
		time = 0;
		countPrevious = 0;
		coordinates(53, 52);
		writeLCD( "bpm");

		printLung(1);	delay(200);
		
		timePreviousMeassure = millis();
		count = 0;

		x=8;
	}

	//!******************************************************************
	//!	Name: printAirFlowScreen()										*
	//!	Description: It prints the AirFlow wave in the LCD screen.		*
	//!	Param : void													*
	//!	Returns: void													*
	//!	Example: eHealthDisplay.printAirFlowScreen();					*
	//!******************************************************************
	
	void eHealthDisplayClass::printAirFlowScreen(void)
	{
		int j = 0;
		
		for (j=0; j<45; j++)
		{
			pixel(8, j, 0);
		}
		
		delay(10);   

		//Lung picture
		if (millis()-timePreviousMeassure > 10000) {
			countsPerMinute = 6*count;
			timePreviousMeassure = millis();
			//Apnea signal OFF

			apneaAdvise(0);

			coordinates(94, 52);	backspace();
			coordinates(99, 52);	backspace();
			coordinates(104, 52);	backspace();
			coordinates(109, 52);	backspace();
			coordinates(114, 52);	backspace();
			coordinates(119, 52);	backspace();
			coordinates(124, 52);	backspace();
			delay(10);  

			if(count ==0 ){
				//Apnea sinal ON
				apneaAdvise(1);

				coordinates(94, 52);
				writeLCD("Apnea");
				delay(5);
			}

			count = 0;
			//Clear the space
			coordinates(53, 52);	backspace();
			coordinates(50, 52);	backspace();
			coordinates(45, 52);	backspace();
			coordinates(40, 52);	backspace();

			writeLcdDec(countsPerMinute);
			delay(20);
		}

			//Lung ON
			printLung(1);

			// Input 1   
			valRead = analogRead(1);

			valRead   = map(valRead, 0, 1023, 5, 45);
			delay(100);
			pixel (x, valRead, 1);
     
			if(x>8){
				line(x-1, prevRead, x, valRead, 1);
			}

			if(valRead> 7)	waveState=1;
			

			if(waveState==1)
			{
				if(valRead<6)
				{
					//Lung OFF
					printLung(0);
					count=count+1;
					waveState=0;
					delay(100);
				}
			}

			//Wave refresh
			for (j = 5; j < 40 ; j++)
			{
				pixel(x+1,j,0);
			}

			prevRead = valRead;  

		x++;

		if (x == 120) x = 8;
	}

//***************************************************************
// Private Methods												*
//***************************************************************

	//! Clear all data writed in the LCD. 
	void eHealthDisplayClass::clearLCD()
	{
		Serial.print(char(0x7C));
		Serial.print(char(0x00));
		delay(20);
	}

	//! It writes data in decimal format.
	void eHealthDisplayClass::writeLcdDec(int data)
	{
		Serial.print(data,DEC);
		delay(20);
	}

	//! It prints data in the LCD.
	void eHealthDisplayClass::writeLCD(char *data){
	  Serial.print(data);
	  delay(20);
	}
	
	//! It prints a back space in the LCD.
	void eHealthDisplayClass::backspace()
	{
		Serial.print(char(0x08));
		delay(20);
	}

	/*! It changes the baud rate uart communication with the LCD. 
		"1" =  4.800bps "2" =  96,00bps
		"3" = 19,200bps "4" =  38,400bps 
		"5" = 57,600bps "6" = 115,200bps
	*/
	void eHealthDisplayClass::changeBaudrate(char frec)
	{								//"1" =  4.800bps "2" =  96,00bps
		Serial.print(char(0x7C));	//"3" = 19,200bps "4" =  38,400bps 
		Serial.print(char(0x07));	//"5" = 57,600bps "6" = 115,200bps
		Serial.print(char(frec)); 
		delay(20);
	}

	//! It places the write pointer in the x-y position.  
	void eHealthDisplayClass::coordinates(int x, int y)
	{									//x from 0 to 127
		Serial.print(char(0x7C));		//y from 0 to  63
		Serial.print(char(0x18));
		Serial.print(char(x));
		Serial.print(char(0x7C)); 
		Serial.print(char(0x19));
		Serial.print(char(y));
		delay(20);
	}

	//! It activates or deactivates a pixel. 
	void eHealthDisplayClass::pixel (int x, int y, int onOff)
	{									//x from 0 to 127 
		Serial.print(char(0x7C));		//y from 0 to  63
		Serial.print(char(0x10));		//on_off=1 ON
		Serial.print(char(x));			//on_off=0 Off
		Serial.print(char(y));
		Serial.print(char(onOff));
	}

	//!It draws or erases a line. 
	void eHealthDisplayClass::line (int fromX,
									int fromY,
									int toX,
									int toY,
									int onOff)
	{ 
		Serial.print(char(0x7C));
		Serial.print(char(0x0C));
		Serial.print(char(fromX));
		Serial.print(char(fromY));
		Serial.print(char(toX));
		Serial.print(char(toY));
		Serial.print(char(onOff));
		delay(20);
	}

	//! It draws or erases a circule. 
	void eHealthDisplayClass::eHealthDisplayClass::circle (	int x,
															int y,
															int radio,
															int onOff)
	{ 
		Serial.print(char(0x7C));             
		Serial.print(char(0x03));               
		Serial.print(char(x));
		Serial.print(char(y));
		Serial.print(char(radio));  
		Serial.print(char(onOff));
		delay(20);
	}

	//! It draws or erases a rectangle. 
	void eHealthDisplayClass::rectangle(int fromX,
										int fromY,
										int toX,
										int toY,
										int onOff)
	{ 
		Serial.print(char(0x7C));             
		Serial.print(char(0x0F));               
		Serial.print(char(fromX));
		Serial.print(char(fromY));
		Serial.print(char(toX));
		Serial.print(char(toY));  
		Serial.print(char(onOff));
		delay(20);
	}

	//! It clears an area of the LCD. 
	void eHealthDisplayClass::clearSpace (	int fromX,
											int fromY,
											int toX,
											int toY)
	{ 
		Serial.print(char(0x7C));
		Serial.print(char(0x05));
		Serial.print(char(fromX));
		Serial.print(char(fromY));
		Serial.print(char(toX));
		Serial.print(char(toY));  
		delay(20);
	}

	//! It draws an image stored in an array.
void eHealthDisplayClass::image(int desde_x, int desde_y, int hasta_x, int hasta_y, const uint8_t *array) {
		q=0;
		int final = this->ancho + desde_x;
		int y = this->alto - 1;
		for (a = 0; a <= alto ; a++)
		{
			for (x = desde_x; x < final ; x=x+8)   
			{       
				temp = pgm_read_word_near(array + q);
				for (z=x; z < (x+8); z++)
			{
				if (temp & 0x80)pixel(z,y,1);
				temp= temp<<1;
			} 
			q++;
			}
			y--;
		}
	}


	//! It prints a lung in the AirFlow screen. 
	void eHealthDisplayClass::printLung(uint8_t onOff)
	{
		pixel (10,50 , onOff);	pixel (10,49 , onOff);	pixel (10,48 , onOff);
		pixel (10,47 , onOff);	pixel (10,46 , onOff);	pixel (11,51 , onOff);
		pixel (11,46 , onOff);	pixel (12,52 , onOff);	pixel (12,46 , onOff);
		pixel (13,53 , onOff);	pixel (13,46 , onOff);	pixel (14,53 , onOff);
		pixel (14,52 , onOff);	pixel (14,51 , onOff);	pixel (14,50 , onOff);
		pixel (14,49 , onOff);	pixel (14,48 , onOff);	pixel (14,47 , onOff);
		pixel (14,46 , onOff);	pixel (15,50 , onOff);	pixel (16,51 , onOff);
		pixel (16,52 , onOff);	pixel (16,53 , onOff);	pixel (16,54 , onOff);
		pixel (16,55 , onOff);	pixel (16,56 , onOff);	pixel (17,50 , onOff);       
		pixel (13,51 , onOff);	pixel (19,51 , onOff);	pixel (13,49 , onOff);
		pixel (19,49 , onOff);	pixel (18,53 , onOff);	pixel (18,52 , onOff);
		pixel (18,51 , onOff);	pixel (18,50 , onOff);	pixel (18,49 , onOff);
		pixel (18,48 , onOff);	pixel (18,47 , onOff);	pixel (18,46 , onOff);
		pixel (19,53 , onOff);	pixel (19,46 , onOff);	pixel (20,52 , onOff);
		pixel (20,46 , onOff);	pixel (21,51 , onOff);	pixel (21,46 , onOff);
		pixel (22,50 , onOff);	pixel (22,49 , onOff);	pixel (22,48 , onOff);
		pixel (22,47 , onOff);	pixel (22,46 , onOff);
	}


	//!It prints the apnea advise.
	void eHealthDisplayClass::apneaAdvise(uint8_t onOff)
	{
		line(90, 41, 90, 56, onOff);	line(77, 41, 77, 56, onOff);
		line(77, 56, 90, 56, onOff);	line(77, 41, 90, 41, onOff);
		
		pixel (84,54,onOff);	pixel (84,53,onOff);	pixel (84,52,onOff);
		pixel (84,51,onOff);	pixel (84,50,onOff);	pixel (84,49,onOff);
		pixel (84,48,onOff);	pixel (84,47,onOff);	pixel (84,44,onOff);
		pixel (84,43,onOff);	pixel (83,54,onOff);	pixel (83,53,onOff);
		pixel (83,52,onOff);	pixel (83,51,onOff);	pixel (83,50,onOff);
		pixel (83,49,onOff);	pixel (83,48,onOff);	pixel (83,47,onOff);
		pixel (83,44,onOff);	pixel (83,43,onOff);
	}

	//! It prints a heart in the LCD.
	void eHealthDisplayClass::printHeart(uint8_t onOff)
	{
		pixel (10,50 , onOff);	pixel (11,51 , onOff);
		pixel (12,50 , onOff);	pixel (13,49 , onOff);
		pixel (14,50 , onOff);	pixel (15,51 , onOff);
		pixel (16,50 , onOff);	pixel (10,50 , onOff);    
		pixel (10,49 , onOff);	pixel (16,49 , onOff);
		pixel (11,48 , onOff);	pixel (15,48 , onOff);
		pixel (12,47 , onOff);	pixel (14,47 , onOff);
		pixel (13,46 , onOff);
	}

	//! It prints a guy in stand/sit position.  
	void eHealthDisplayClass::standPosition()
	{
		line(108,50,113,50,1);	line(107,49,114,49,1);
		line(107,48,108,48,1);	line(110,48,111,48,1);
		line(113,48,114,48,1);	line(107,47,114,47,1);
		line(107,46,114,46,1);	line(107,45,108,45,1);
		line(113,45,114,45,1);	line(107,44,114,44,1);
		line(108,43,113,43,1);	line(110,42,110,35,1);
	}

	//! It prints a guy in rigth lateral position.
	void eHealthDisplayClass::rigthLateralPosition()
	{
		line(100, 35, 100, 40, 1);	line(101, 34, 101, 41, 1);
		line(102, 34, 102, 35, 1);	line(102, 37, 102, 38, 1);
		line(102, 40, 102, 41, 1);	line(103, 34, 103, 41, 1);
		line(104, 34, 104, 41, 1);	line(105, 34, 105, 35, 1);
		line(105, 40, 105, 41, 1);	line(106 ,34, 106, 41, 1);
		line(107 ,35, 107, 40, 1);	line(108, 37, 115, 37,1);
	}

	//! It prints a guy in letf lateral position.  
	void eHealthDisplayClass::leftLateralPosition()
	{
		line(100, 35, 100, 40, 1);	line(101, 34, 101, 41, 1);
		line(102, 34, 102, 41, 1);	line(103, 34, 103, 41, 1);
		line(104, 34, 104, 41, 1);	line(105, 34, 105, 41, 1);
		line(106 ,34, 106, 41, 1);	line(107 ,35, 107, 40, 1);
		line(108, 37, 115, 37,1);
	}

	//! It prints a guy in supine position.
	void eHealthDisplayClass::supinePosition()
	{
		line(100, 35, 100, 40, 1);	line(101, 34, 101, 41, 1);
		line(102, 34, 102, 38, 1);	line(102, 40, 102, 41, 1);
		line(103, 34, 103, 41, 1);	line(104, 34, 104, 41, 1);
		line(105, 34, 105, 38, 1);	line(106 ,34, 106, 41, 1);
		line(107 ,35, 107, 40, 1);	line(107 ,37, 114, 37, 1);
	}

	//! It prints a guy in prone position.
	void eHealthDisplayClass::pronePosition()
	{
		line(100, 35, 100, 40, 1);	line(101, 34, 101, 41, 1);
		line(102, 34, 102, 35, 1);	line(102, 37, 102, 41, 1);
		line(103, 34, 103, 41, 1);	line(104, 34, 104, 41, 1);
		line(105, 38, 105, 41, 1);	line(106 ,34, 106, 41, 1);
		line(107 ,35, 107, 40, 1);	line(107 ,37, 114, 37, 1);
	}
	

//***************************************************************
// Preinstantiate Objects										*
//***************************************************************

	eHealthDisplayClass eHealthDisplay = eHealthDisplayClass();





