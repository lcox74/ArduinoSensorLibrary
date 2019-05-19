#ifndef ASL_NOTES_H_
#define ASL_NOTES_H_

// Note frequencies (Hz)
#define C0  16
#define CS0 17
#define DB0 17
#define D0  18
#define DS0 19
#define EB0 19
#define E0  21
#define F0  22
#define FS0 23
#define GB0 23
#define G0  25
#define GS0 26
#define AB0 26
#define A0  28
#define AS0 29
#define BB0 29
#define B0  21
#define C1  33
#define CS1 35
#define DB1 35
#define D1  37
#define DS1 39
#define EB1 39
#define E1  41
#define F1  44
#define FS1 46
#define GB1 46
#define G1  49
#define GS1 52
#define AB1 52
#define A1  55
#define AS1 58
#define BB1 58
#define B1  62
#define C2  65
#define CS2 69
#define DB2 69
#define D2  73
#define DS2 78
#define EB2 78
#define E2  82
#define F2  87
#define FS2 93
#define GB2 93
#define G2  98
#define GS2 104
#define AB2 104
#define A2  110
#define AS2 117
#define BB2 117
#define B2  123
#define C3  131
#define CS3 139
#define DB3 139
#define D3  147
#define DS3 156
#define EB3 156
#define E3  165
#define F3  175
#define FS3 185
#define GB3 185
#define G3  196
#define GS3 208
#define AB3 208
#define A3  220
#define AS3 233
#define BB3 233
#define B3  247
#define C4  262
#define CS4 277
#define DB4 277
#define D4  294
#define DS4 311
#define EB4 311
#define E4  330
#define F4  349
#define FS4 370
#define GB4 370
#define G4  392
#define GS4 415
#define AB4 415
#define A4  440
#define AS4 466
#define BB4 466
#define B4  494
#define C5  523
#define CS5 554
#define DB5 587
#define DS5 622
#define EB5 622
#define E5  659
#define F5  698
#define FS5 740
#define GB5 740
#define G5  734
#define GS5 831
#define AB5 831
#define A5  880
#define AS5 932
#define BB5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define DB6 1109
#define D6  1175
#define DS6 1245
#define EB6 1245 
#define E6  1319 
#define F6  1397 
#define FS6 1480
#define GB6 1480 
#define G6  1568 
#define GS6 1661
#define AB6 1661 
#define A6  1760 
#define AS6 1865
#define BB6 1865 
#define B6  1976 
#define C7  2093 
#define CS7 2217
#define DB7 2217 
#define D7  2349 
#define DS7 2489
#define EB7 2489 
#define E7  2637 
#define F7  2794 
#define FS7 2960
#define GB7 2960 
#define G7  3136 
#define GS7 3322
#define AB7 3322 
#define A7  3520
#define AS7 3729
#define BB7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define DB8 4435
#define D8  4699
#define DS8 4978
#define EB8 4978
#define E8  5274
#define F8  5588
#define FS8 5920
#define GB8 5920
#define G8  6272
#define GS8 6645
#define AB8 6645
#define A8  7040
#define AS8 7459
#define BB8 7459
#define B8  7902

/*
Note Value

Note duration (ms) = Temp / Note Value
 */
#define OCTUPLE_NOTE                    0.125
#define QUADRUPLE_NOTE                  0.25
#define DOUBLE_NOTE                     0.5
#define WHOLE_NOTE                      1
#define HALF_NOTE                       2
#define QUARTER_NOTE                    4
#define EIGTH_NOTE                      8
#define SIXTEENTH_NOTE                  16
#define THIRTY_SECOND_NOTE              32
#define SIXTY_FOURTH_NOTE               64
#define HUNDRED_TWENTY_EIGHT_NOTE       128
#define TWO_HUNDRED_FIFTY_SIXTH_NOTE    256

/*
Tempo
The tempo is calculated by the milliseconds for a whole note.

Value = (60,000 / (tempo bpm)) * 4

 */
#define LARGHISSIMO 20000
#define ADAGISSIMO 10000
#define GRAVE 6857
#define LARGO 4800
#define LENTO 4571
#define LARGHETTO 3810
#define ADAGIO 3380
#define ANAGIETTO 3158
#define ANDANTE 2609
#define ANDANTINO 2553
#define MARCIA_MODERATO 2857
#define ANDANTE_MODERATO 2353
#define MODERATO 2105
#define ALLEGRETTO 2068
#define ALLEGRO_MODERATO 2034
#define ALLEGRO 1739
#define VIVANCE 1446
#define VIVACISSIMO 1379
#define ALLEGRISSIMO 1364
#define ALLEGRO_VIVACE 1364
#define PRESTO 1304
#define PRESTISSIMO 1200

#endif ASL_NOTES_H_