# morse-code-arduino-lcd
Morse Code Communication System using Arduino + I2C LCD

This project is an Arduino-based Morse code communication system that converts keyboard (serial) input into readable text displayed on a 16x2 I2C LCD. It demonstrates real-time decoding of Morse sequences using buffer-based processing and includes an automatic inactivity reset system for improved usability.

How it works:
The system receives Morse code input through the Serial Monitor using dots (.) and dashes (-). Each sequence is stored in a buffer until a space or newline is detected. The Arduino then decodes the Morse sequence into its corresponding character using a lookup table and displays it on the LCD in real time.
If no input is detected for 10 seconds, the system automatically clears the display to allow a fresh start.

Features
- Real-time Morse code decoding (A–Z, 0–9)
- Serial keyboard input system
- Buffer-based character processing
- I2C LCD output display
- Word separation using /
- Automatic screen reset after 10 seconds of inactivity
- Lightweight and optimized for Arduino UNO

Key Concepts Used
- Serial communication handling
- String buffering system
- Lookup-table decoding logic
- Non-blocking timing using millis()
- Embedded system state management

Hardware Requirements
- Arduino UNO
- 16x2 I2C LCD Display
- USB connection (for serial input via keyboard)
- Jumper wires

Future Improvements
- Add buzzer for Morse audio feedback
- Physical button input system
- Wireless Morse communication between two Arduinos
- OLED upgrade for better display clarity

Author
- Developed as an embedded systems learning project focusing on communication protocols, real-time input handling, and microcontroller-based text processing.
