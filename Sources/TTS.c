//
//  TTS.c
//  R_TTS
//
//  Created by RocKK on 12/19/13.
//  Copyright (c) 2013 RocKK.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms are permitted
//  provided that the above copyright notice and this paragraph are
//  duplicated in all such forms and that any documentation,
//  advertising materials, and other materials related to such
//  distribution and use acknowledge that the software was developed
//  by the RocKK.  The name of the
//  RocKK may not be used to endorse or promote products derived
//  from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED ''AS IS'' AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#include <string>
#include <iostream>
#include "Download.c"

void speakFromString(const char* string)
{
	const char* address = "http://www.translate.google.com/translate_tts?tl=en&q=";
	char result[100];   // array to hold the result.
	strcpy(result,address); // copy string address into the result.
	strcat(result,string); // append string string to the result.
	downloadFileWithNameFromUrl("speak.mp3",result);//save audio to mp3 file
	system("afplay speak.mp3 &");//play mp3 file [you should change this bash command depending on your os].
}