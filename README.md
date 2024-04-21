# Over-The-Air Programmer (OTA)

## Overview

The Over-The-Air Programmer (OTA) project enables wireless flashing of firmware onto an Arm-based STM32F401 microcontroller. This project leverages web connectivity, cloud storage, and microcontroller technology to facilitate convenient firmware updates. The system consists of several components:

1. **Arm-based STM32F401 Microcontroller**: This serves as the target device for firmware updates. The microcontroller includes a custom bootloader flashed onto the first 16 kB of Flash Memory, allowing for firmware updates over UART.

2. **Website and Cloud Database (Firebase)**: A website interface is connected to a Firebase database, enabling users to upload and store firmware updates. The STM32F401 microcontroller fetches firmware updates from this cloud database.

3. **NodeMCU (ESP8266) Board**: This component connects to the internet and retrieves firmware updates from the website. It acts as an intermediary between the website and the STM32F401 microcontroller, transmitting firmware updates wirelessly.

4. **Raspberry Pi 4 GUI Interface**: The Raspberry Pi 4 serves as the user interface for the vehicle's infotainment system. It presents essential information such as time/date and provides functionality for checking and installing system updates.

## Components and Communication

### Communication Channels

- **STM32F401  - NodeMCU Communication**: The STM32F401 microcontroller communicates with the NodeMCU board over UART (Serial) communication. This allows the microcontroller to receive firmware updates wirelessly.

- **Raspberry Pi 4 - STM32F401 Communication**: The Raspberry Pi 4 communicates with the STM32F401  microcontroller via UART (Serial) communication. This communication channel facilitates the control of the infotainment system and the installation of firmware updates.

### Key Features

- **Wireless Firmware Updates**: Users can upload firmware updates to the cloud database via the website interface. The NodeMCU board fetches these updates and transmits them wirelessly to the STM32F401 microcontroller for installation.

- **Automatic System Updates**: The Raspberry Pi 4 GUI interface includes a "Check for Updates" feature. When activated, the system automatically fetches the latest firmware updates from the cloud database and installs them onto the STM32F401 microcontroller.

- **Enhanced Infotainment Features**: After installing system updates, the infotainment system unlocks additional features, such as a parking mode. This mode includes functionalities such as a rear camera display and ultrasonic sensor warnings to assist users in parking and avoid accidents.
- 
## Setup and Configuration

To set up and deploy the Over-The-Air Programmer (OTA) system, follow these steps:

1. **Hardware Setup**:
   - Connect the NodeMCU board to the internet.
   - Connect the Raspberry Pi 4 to the STM32F401 microcontroller via UART communication.

2. **Software Installation**:
   - Install the necessary firmware on the STM32F401 microcontroller, including the custom bootloader.
   - Set up the Firebase database and configure the website interface for firmware uploads.

3. **Run the System**:
   - Ensure all components are powered on and properly connected.
   - Access the Raspberry Pi 4 GUI interface for user interaction.
   - Use the "Check for Updates" feature to fetch and install the latest firmware updates.

Acknowledgments
Special thanks to the contributors and supporters of this project in IMT/WazeefaTech who have helped in its development and improvement.
_______________________________________________________________________________________________

Feel free to reach out with any questions, feedback, or suggestions. Happy flashing! 🚀🔧

