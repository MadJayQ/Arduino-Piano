#include <EEPROM.h>
#include "pitches.h"
/*
 Name:		SongLoader.ino
 Created:	10/18/2017 10:01:12 AM
 Author:	jakei_000
*/

int global_adr = 25;
int mario_melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0,NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0,NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
byte mario_tempo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

//
//Underworld melody
int underworld_melody[] = {
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0, NOTE_DS4, NOTE_CS4, NOTE_D4,
	NOTE_CS4, NOTE_DS4,
	NOTE_DS4, NOTE_GS3,
	NOTE_G3, NOTE_CS4,
	NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	NOTE_GS4, NOTE_DS4, NOTE_B3,
	NOTE_AS3, NOTE_A3, NOTE_GS3,
	0, 0, 0
};
//Underwolrd tempo
byte underworld_tempo[] = {
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	6, 18, 18, 18,
	6, 6,
	6, 6,
	6, 6,
	18, 18, 18,18, 18, 18,
	10, 10, 10,
	10, 10, 10,
	3, 3, 3
};

int starwars_melody[] = {
	NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_B4,
	NOTE_G4, NOTE_E4, NOTE_B4, NOTE_G4,
	NOTE_D5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_B4,
	NOTE_FS4, NOTE_E4, NOTE_G4, NOTE_GS4,
	NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5,
	NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_DS5,
};

byte starwars_tempo[] = {
	8, 8, 8, 16, 16,
	8, 16, 16, 4,
	8, 8, 8, 16, 16,
	8, 16, 16, 4,
	8, 16, 16, 8, 16, 16,
	32, 32, 16, 16, 16, 8, 16, 16
};

int pirates_melody[] = {
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,

	NOTE_A4, NOTE_A4,
	//Repeat of first part
	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4

};

//125 = 16
//250 = 8
//375 = 4

byte pirates_tempo[] = 
{
	16, 16, 8, 16, 16,
	16, 16, 16, 16, 16,
	16, 16, 8, 16, 16,
	16, 16, 375, 16,

	16, 16, 8, 16, 16,
	16, 16, 8, 16, 16,
	16, 16, 8, 16, 16,
	16, 16, 4, 16,

	16, 16, 8, 16, 16,
	16, 16, 8, 16, 16,
	16, 16, 8, 16, 16,
	16, 16, 16, 8, 16,

	16, 16, 8, 16, 16,
	8, 16, 8, 16,
	16, 16, 8, 16, 16,
	16, 16, 4, 4,

	8, 16,

	8, 16, 4, 8, 16, 4,
	16, 16, 16, 16, 16, 16, 16, 16, 4,
	8, 16, 4, 8, 16, 4,
	16, 16, 16, 16, 16, 1
};

int* songs[4];
byte* notes[4];
int song_sizes[4];
struct song {
	int melody_start_adr;
	int tempo_start_adr;
	byte num_notes;
	byte tempo;
};
struct songs_header {
	song songs[4];
	byte num_songs = 4;
};
songs_header toc;

bool writeInteger(int adr, int val) {
	if (adr >= 1023)
	{
		Serial.println("MEMORY BOUNDS EXCEEDED");
		return false;
	}
	byte hi = (val & 0xFF);
	byte lo = ((val >> 8) & 0xFF);

	EEPROM.write(adr, hi);
	EEPROM.write(adr + 1, lo);
	return true;
}
void dumpMemory() {
	int adr = 0;
	byte value = 0;
	while (adr < EEPROM.length()) {
		value = EEPROM.read(adr);
		Serial.print(adr, DEC);
		Serial.print("\t");
		Serial.print(value, HEX);
		Serial.println();
		++adr;
	}
}
void writeHeaderSpace() {
	int adr = 0;
	EEPROM.write(adr, toc.num_songs);
	adr++;
	for (int i = 0; i < 4; i++) {
		writeInteger(adr, toc.songs[i].melody_start_adr);
		adr += (sizeof(int));
		writeInteger(adr, toc.songs[i].tempo_start_adr);
		adr += (sizeof(int));
		EEPROM.write(adr, toc.songs[i].tempo);
		adr++;
		EEPROM.write(adr, toc.songs[i].num_notes);
		adr++;
	}
}
void loadSongInfo() {
	toc.num_songs = sizeof(songs) / sizeof(int);
	toc.songs[0].num_notes = sizeof(mario_melody) / sizeof(int);
	songs[0] = mario_melody;
	notes[0] = mario_tempo;
	toc.songs[0].tempo = 200;

	toc.songs[1].num_notes = sizeof(underworld_melody) / sizeof(int);
	songs[1] = underworld_melody;
	notes[1] = underworld_tempo;
	toc.songs[1].tempo = 100;

	toc.songs[2].num_notes = sizeof(starwars_melody) / sizeof(int);
	songs[2] = starwars_melody;
	notes[2] = starwars_tempo;
	toc.songs[2].tempo = 50;

	songs[3] = pirates_melody;
	notes[3] = pirates_tempo;
	toc.songs[3].tempo = 80;;
	toc.songs[3].num_notes = sizeof(pirates_melody) / sizeof(int);
}

void loadSongs() {
	for (int i = 0; i < toc.num_songs; i++) {
		if (songs[i] == NULL) continue;
		int song_size = toc.songs[i].num_notes;
		if (song_size == 0) continue;
		toc.songs[i].melody_start_adr = global_adr;
		for (int j = 0; j < song_size; j++) {
			writeInteger(global_adr, songs[i][j]);
			global_adr += sizeof(int);
		}
	}
}

void loadTempos() {
	for (int i = 0; i < toc.num_songs; i++) {
		if (songs[i] == NULL) continue;
		int song_size = toc.songs[i].num_notes;
		if (song_size == 0) continue;
		toc.songs[i].tempo_start_adr = global_adr;
		for (int j = 0; j < song_size; j++) {
			EEPROM.write(global_adr, notes[i][j]);
			global_adr++;
		}
	}
}
void setup() {
	memset(songs, 0, sizeof(songs));
	memset(notes, 0, sizeof(notes));
	memset(song_sizes, 0, sizeof(song_sizes));
	loadSongInfo();
	Serial.begin(9600);
	while (!Serial) {

	}
	Serial.print("Number of songs: ");
	Serial.println(toc.num_songs);
	loadSongs();
	loadTempos();
	writeHeaderSpace();
	dumpMemory();
}

void loop() {

}
