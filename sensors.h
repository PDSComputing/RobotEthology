// Created on Wed March 21 2018

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_

float left_photo_value;
float right_photo_value;
int photo_offset      = 0;
float photo_coeff     = 5.0;
float photo_difference;
float photo_ratio;
float photo_threshold = 15.0;	
float photo_max       = 1023.0;

int front_bump_value;
int bump_threshold = 0;
int bump_max = 226;

int avoid_threshold = 400;
int left_ir_value;
int right_ir_value;

#endif
