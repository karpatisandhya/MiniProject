EventBoard:RTC-Driven Message Display System
Overview:
EventBoard is an embedded system project developed using the LPC2148 ARM7 microcontroller. The system automatically displays scheduled messages on a 16x2 LCD based on the current date and time obtained from the Real-Time Clock (RTC).
The project acts as a digital notice board where messages are displayed automatically at predefined times without human intervention. It is suitable for educational institutions, offices, industries, and public information systems.

Features:
RTC-based event scheduling
Automatic message display according to date and time
16x2 LCD interface for message output
Scrolling display for long messages
Multiple event management support
Keypad-based user interaction
Real-time monitoring of scheduled events
Easy event configuration and management

Hardware Components:
1.LPC2148       -ARM7 Microcontroller
2.16x2 LCD      -Message Display Unit
3.RTC           -Real-Time Clock Module
4.Matrix Keypad -User Input Device
5.Power Supply  -System Power Source
6.Connecting Wires-Hardware Interfacing

Software Requirements:
1.Embedded C\
2.Keil uVision IDE
3.Flash Magic

Working Principle:
1.The RTC continuously maintains the current date and time.
2.Event messages are stored along with their scheduled timings.
3.The microcontroller continuously compares RTC values with stored event timings.
4.When a scheduled event time matches the current RTC time, the corresponding message is displayed on the LCD.
5.Messages longer than the LCD width are displayed using scrolling.

Project Structure:
EventBoard/ │
├── main.c
├── RTC.c
├── RTC.h
├── lcd.c
├── lcd.h
├── KPM.c
├── KPM.h
├── delay.c
├── delay.h
├── adminmode_func.c
├── adminmode_func.h 
└── README.md

Applications:
1.Digital Notice Boards
2.College Announcement Systems
3.Classroom Reminder Systems
4.Office Information Displays
5.Event Management Systems
6.Industrial Shift Notifications
7.Public Information Displays

Key Concepts Used:
1.Embedded C Programming
2.RTC Programming
3.LCD Interfacing
4.Keypad Interfacing
5.Event Scheduling
6.String Manipulation
7.Scrolling Display Techniques

Results:
Successfully implemented RTC-based event scheduling.
Accurate message triggering based on real-time clock data.
Reliable LCD message display system.
Smooth scrolling functionality for lengthy messages.
User-friendly event management interface.

Future Enhancements:
EEPROM-based permanent storage
GSM-based SMS notifications
Wi-Fi/IoT integration using ThingSpeak
Mobile application control
Cloud-based event management
Multiple display unit support

Author:
Sandhya Karpati
Electronics and Communication Engineering(ECE)
Embedded Systems Enthusiast


