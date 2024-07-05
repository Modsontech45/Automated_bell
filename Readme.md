# Automated Talking Bell

This project is an automated talking bell created using two ATmega328p microcontrollers. The setup involves:

- **Two ATmega328p microcontrollers:** Used to solve memory issues.
- **RTC Module:** Provides time, date, and temperature.
- **LCD Screen:** Displays the time, date, and temperature.
- **Serial Communication:** Connects the two ATmega328p microcontrollers.
- **SD Card Reader:** Stores the audio files to be played.

## How It Works

### Sender (First ATmega328p)

1. **Gets Data:** 
    - Retrieves time, date, and temperature from the RTC module.
2. **Displays Information:** 
    - Prints the time, date, and temperature on the LCD screen.
3. **Sends Data:** 
    - Transmits the information to the second ATmega328p via the serial port at a baud rate of 9600.

### Receiver (Second ATmega328p)

1. **Receives Data:**
    - Gets the data sent by the first ATmega328p.
2. **Analyzes Data:**
    - Processes the received information.
3. **Checks Time:**
    - Continuously monitors if it is time to play the ringing tone.
    - Decisions are based on the received data.
4. **Plays Audio:**
    - When it is time, plays the audio file stored on the SD card.

This project efficiently manages memory constraints by distributing tasks between two microcontrollers and ensures accurate timekeeping and audio playback using an RTC module and an SD card reader.
