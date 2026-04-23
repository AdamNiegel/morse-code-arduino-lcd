# morse-code-arduino-lcd
Arduino-based Morse code input system with real-time decoding on a 16x2 I2C LCD display.

Features:
Morse input via keyboard
Real-time decoding
LCD display output
Auto-clear timeout system

Circuit setup:
Arduino UNO
I2C LCD (0x27)
Serial input (keyboard)

How it works:
The system receives Morse code input through the serial keyboard using dots (.) and dashes (-). Each sequence is stored in a buffer and decoded into its corresponding letter or number using a lookup table. The decoded characters are then displayed in real time on a 16x2 I2C LCD. The system also includes a timer-based reset that automatically clears the display after 10 seconds of inactivity, ensuring a clean interface for new input.
