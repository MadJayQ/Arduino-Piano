#include <eeprom.h>
#include "pitches.h"

#define BUZZER_PIN 12
#define NOTE_REST 0
#define NOTE(Name, Octave) NOTE_##NOTE##OCTAVE


byte mode_idx = 0;
/*
 Name:		Piano.ino
 Created:	10/18/2017 10:44:19 AM
 Author:	jakei_000
*/

struct song {
	int melody_start_adr;
	int tempo_start_adr;
	byte num_notes;
	byte tempo;
};
struct songs_header {
	byte num_songs = 4;	
	song songs[4];
};
songs_header toc;

int keys[] = { 2,3,4,5,6,7,8, 9 };
int reset_idx = 10;
int TEMPO = 200;

int piano_tones[] = { NOTE_A3, NOTE_AS3, NOTE_B4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4 };
int high_piano_tones[] = { NOTE_A5, NOTE_AS5, NOTE_A6, NOTE_B6, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6 };

void playNote(int targetPin, long frequency, long length) {
	digitalWrite(13, HIGH);
	long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
											   //// 1 se/cond's worth of microseconds, divided by the frequency, then split in half since
											   //// there are two phases to each cycle
	long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
												//// multiply frequency, which is really cycles per second, by the number of seconds to
												//// get the total number of cycles to produce
	for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
		digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
		delayMicroseconds(delayValue); // wait for the calculated delay value
		digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
		delayMicroseconds(delayValue); // wait again or the calculated delay value
	}
	digitalWrite(13, LOW);

}
int calcualteDelay(byte note)
{
	int quarter_time = 60000 / TEMPO;
	double ratio = note / 4;
	double new_time = quarter_time / ratio;

	return (int)new_time;

}
int readInt(int& adr)
{
	byte lo = EEPROM.read(adr);
	byte hi = EEPROM.read(adr + 1);
	adr += sizeof(int);

	/*
	Serial.print("Hi: ");
	Serial.print(hi, HEX);
	Serial.print(" Lo: ");
	Serial.println(lo, HEX);
	*/

	return ((hi << 8)| lo);
}

void loadHeader() {
	toc.num_songs = EEPROM.read(0);
	int adr = 1;
	for (int i = 0; i < toc.num_songs; i++)
	{
		toc.songs[i].melody_start_adr = readInt(adr);
		toc.songs[i].tempo_start_adr = readInt(adr);
		toc.songs[i].tempo = EEPROM.read(adr);
		adr++;
		toc.songs[i].num_notes = EEPROM.read(adr);
		adr++;
	}

}

void playSong(int songNum)
{
	song s = toc.songs[songNum];
	int melody_adr = s.melody_start_adr;
	int tempo_adr = s.tempo_start_adr;
	TEMPO = toc.songs[songNum].tempo;
	Serial.print("Tempo: ");
	Serial.println(TEMPO, HEX);
	Serial.print("Num notes: ");
	Serial.println(s.num_notes);
	int* melody_buffer = (int*)(malloc(sizeof(int) * s.num_notes));
	byte* tempo_buffer = (byte*)(malloc(s.num_notes));
	for (int note = 0; note < s.num_notes; note++)
	{
		int melody = readInt(melody_adr);
		byte tempo = EEPROM.read(tempo_adr);
		Serial.println("AHH");
		tempo_adr++;
		melody_buffer[note] = melody;
		tempo_buffer[note] = tempo;
	}
	Serial.println("SONG LOADED");
	for (int note = 0; note < s.num_notes - 1; note++) {
		Serial.print("Note: ");
		Serial.println(note);
		Serial.println(melody_buffer[note]);
		int duration = calcualteDelay(tempo_buffer[note]);
		if (melody_buffer[note] != 0) {
			tone(BUZZER_PIN, melody_buffer[note]);
			delay(duration);
			noTone(BUZZER_PIN);
		}
		else
		{
			digitalWrite(BUZZER_PIN, LOW);
			delay(duration);
		}
	}
	free(melody_buffer);
	free(tempo_buffer);
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
//	resetFlagsInit();
//	Serial.print(F("I received from optiboot => "));
//	Serial.println(resetFlags, HEX);
	loadHeader();
}

// the loop function runs over and over again until power down or reset
void loop() {
	int buttonState = digitalRead(reset_idx);
	static bool once = true;
	if (buttonState == HIGH)
	{
		if (once)
		{
			once = false;
			mode_idx = (mode_idx + 1) % 3;
			Serial.print("Mode: ");
			Serial.println(mode_idx);
		}
	}
	else
	{
		once = true;
	}
	if (mode_idx == 0)
	{
		int tripped_button = -1;
		//Piano mode
		if (digitalRead(keys[0]) == HIGH)
		{
			tripped_button = 0;
			tone(BUZZER_PIN, piano_tones[0]);
		}
		else if (digitalRead(keys[1]) == HIGH)
		{
			tripped_button = 1;
			tone(BUZZER_PIN, piano_tones[1]);
		}
		else if (digitalRead(keys[2]) == HIGH)
		{
			tripped_button = 2;
			tone(BUZZER_PIN, piano_tones[2]);
		}
		else if (digitalRead(keys[3]) == HIGH)
		{
			tripped_button = 3;
			tone(BUZZER_PIN, piano_tones[3]);
		}
		else if (digitalRead(keys[4]) == HIGH)
		{
			tripped_button = 4;
			tone(BUZZER_PIN, piano_tones[4]);
		}
		else if (digitalRead(keys[5]) == HIGH)
		{
			tripped_button = 5;
			tone(BUZZER_PIN, piano_tones[5]);
		}
		else if (digitalRead(keys[6]) == HIGH)
		{
			tripped_button = 6;
			tone(BUZZER_PIN, piano_tones[6]);
		}
		else if (digitalRead(keys[7]) == HIGH)
		{
			tripped_button = 7;
			tone(BUZZER_PIN, piano_tones[7]);
		}
		else
		{
			tripped_button = -1;
			noTone(BUZZER_PIN);
		}
		Serial.print("Tripped button: ");
		Serial.println(tripped_button);
	}
	else if (mode_idx == 1)
	{
		//High octave piano mode
		if (digitalRead(keys[0]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[0]);
		}
		else if (digitalRead(keys[1]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[1]);
		}
		else if (digitalRead(keys[2]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[2]);
		}
		else if (digitalRead(keys[3]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[3]);
		}
		else if (digitalRead(keys[4]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[4]);
		}
		else if (digitalRead(keys[5]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[5]);
		}
		else if (digitalRead(keys[6]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[6]);
		}
		else if (digitalRead(keys[7]) == HIGH)
		{
			tone(BUZZER_PIN, high_piano_tones[7]);
		}
		else
		{
			noTone(BUZZER_PIN);
		}
	}
	else
	{
		for (int i = 0; i < toc.num_songs; i++)
		{
			int buttonState = digitalRead(keys[i]);
			if (buttonState == HIGH)
			{
				Serial.print("Playing song: ");
				Serial.println(i);
				playSong(i);
			}
		}
	}
}
