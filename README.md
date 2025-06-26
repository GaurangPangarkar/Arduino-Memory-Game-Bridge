# Arduino-Memory-Game-Bridge# Arduino Memory Game with Bluetooth Bridge

![Full Project Setup Overview](images/project_full_setup.png)

## 🚀 Project Overview

I built this as a fun take on the classic Simon-style memory game, while exploring how two Arduinos can communicate using Bluetooth — with a Python bridge acting as the middleman and PC as bridge.

The game logic resides on one Arduino (the "Game Master" or "Arduino 1"), handling pattern generation and button input. It sends game prompts and feedback (like "Watch Pattern!", "Correct!", "YOU WON!") as text messages. These messages are then relayed wirelessly to a second Arduino (the "Display Unit" or "Arduino 2") via a Python script on the PC acting as a serial-to-Bluetooth bridge. The Display Unit's sole purpose is to receive these messages and present them clearly on a 16x2 LCD screen.

## ✨ Features
* **Interactive Memory Game:** Players follow a light and sound pattern, repeating it using four colored buttons.
* **Two-Arduino Architecture:** Separates game logic from display logic for modularity.
* **PC as Communication Bridge:** A Python script facilitates wireless serial communication between the two Arduinos using a standard USB connection for Arduino 1 and a Bluetooth module (HC-05) for Arduino 2.
* **LCD Display Feedback:** Clear, real-time game status updates displayed on a 16x2 character LCD.
* **Visual and Audio Cues:** LEDs light up and a buzzer (if connected, otherwise just LED flashes) indicates pattern steps and button presses.
* **Debounced Button Inputs:** Software debouncing ensures reliable button presses.

## 🔌 Components Used

* **Arduino Uno (x2):** One for game logic (Arduino 1), one for LCD display (Arduino 2).
* **HC-05 Bluetooth Module:** For wireless serial communication between PC and Arduino 2.
* **16x2 LCD Display (with I2C module):** For displaying game prompts and results. (An I2C module simplifies wiring greatly).
* **Push Buttons (x4):** Player input for repeating the pattern.
* **LEDs (x4):** Visual indicators for pattern display and feedback.
* **Resistors (x4):** Appropriate resistors for LEDs (e.g., 220 Ohm).
* **Potentiometer (10k Ohm):** For LCD contrast adjustment (if not using I2C module or if I2C module has its own).
* **Breadboards (x2 or more):** For prototyping the circuits.
* **Jumper Wires:** For making connections.
* **PC/Laptop:** Running the Python bridge script.

## 🏗️ Hardware Setup & Wiring

The project consists of two main interconnected circuits.

### Detailed Circuit Diagram (Tinkercad)

This diagram illustrates the primary component connections to each Arduino.

**Important Note:** The HC-05 Bluetooth module, crucial for the wireless link, is not available in Tinkercad's component library for simulation. Its connections are therefore depicted in the real-life photos below.

![Tinkercad Wiring Diagram](images/tinkercad_wiring_diagram.png)

* **Arduino 1 (Game Master):**
    * Buttons are connected to digital pins D2, D4, D6, D8 with internal pull-up resistors (or external pull-down).
    * LEDs are connected to digital pins D3, D5, D7, D9.
    * A0 (Analog pin 0) is left open for `randomSeed()` initialization.
    * Connected to PC via USB for serial communication.
* **Arduino 2 (Display Unit):**
    * LCD display is connected (e.g., via I2C module, or directly to digital pins if not using I2C).
    * HC-05 Bluetooth module's `TX` pin connects to Arduino's `RX` pin, and `RX` to Arduino's `TX` (often through a voltage divider for 5V to 3.3V conversion for HC-05 RX).
    * Powered via USB or external supply.

### Real-Life Project Photos

These photographs provide a comprehensive view of the assembled hardware, including the HC-05 Bluetooth module.

#### Full Project Layout

An overview of the entire physical setup, showing both Arduino boards, breadboards, and peripherals.

![Complete Project Overview](images/project_full_setup.png)

#### Display Unit & Game Controls Close-up

A closer look at the LCD display, player buttons, and associated LEDs, demonstrating the user interface.

![Physical LCD and Buttons](images/physical_lcd_buttons.png)

## 💻 Software Setup

1.  **Arduino IDE:**
    * **Arduino 1 (Game Master):** Upload the code located in `arduino_sketches/arduino1_game/arduino1_game.ino`. This code handles the core game logic, pattern generation, button input, and sends game status messages via `Serial.println()`.
    * **Arduino 2 (Display Unit):** This Arduino runs a sketch (not included in this repository as its source was unavailable) that listens for incoming serial data from the HC-05 module and displays it on the 16x2 LCD. It's configured to receive messages via software serial (connected to the HC-05).

2.  **Python Environment:**
    * Ensure Python is installed on your PC.
    * Install the `pyserial` library:
        ```bash
        pip install pyserial
        ```
    * The Python bridge script is located at `python_bridge/arduino_bluetooth_bridge.py`.
    * **Before Running:** You must first pair your HC-05 Bluetooth module with your PC. After pairing, check your PC's Device Manager to identify the virtual COM port assigned to the HC-05 (e.g., `COM16`). You also need to identify the COM port for Arduino 1 (e.g., `COM11`).
    * **Edit the Python script:** Open `arduino_bluetooth_bridge.py` and update the `ARDUINO1_PORT` and `HC05_PORT` variables to match the COM ports on your system.
    * **Run the script:**
        ```bash
        python python_bridge/arduino_bluetooth_bridge.py
        ```

## ▶️ How to Play

1.  Ensure both Arduinos are powered on and connected as per the wiring diagram and photos.
2.  Run the Python bridge script on your PC.
3.  The LCD on Arduino 2 will display "Game Ready! Watch Pattern."
4.  Observe the sequence of LED flashes (the pattern).
5.  When prompted "Now your turn!", press the corresponding buttons in the correct sequence.
6.  Receive feedback ("Correct!", "WRONG!", "YOU WON!") on the LCD.

## 📄 License

This project is licensed under the [MIT License](LICENSE).

Feel free to open an issue on this repository if you have questions or suggestions!