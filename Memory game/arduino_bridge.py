import serial
import time

ARDUINO1_PORT = 'COM11'
ARDUINO1_BAUD = 9600

# Replace 'COM_HC05_HERE' with the actual COM port assigned to your HC-05 after pairing with PC
HC05_PORT = 'COM16'
HC05_BAUD = 38400 # Must match bluetoothSerial.begin() in Arduino 2's code

print(f"Attempting to connect Arduino 1 on {ARDUINO1_PORT} and HC-05 on {HC05_PORT}...")

ser_ard1 = None
ser_hc05 = None

try:
    # Open serial connection to Arduino 1
    ser_ard1 = serial.Serial(ARDUINO1_PORT, ARDUINO1_BAUD, timeout=1)
    # Open serial connection to HC-05 Bluetooth module
    ser_hc05 = serial.Serial(HC05_PORT, HC05_BAUD, timeout=1)

    time.sleep(2) # Give time for connections to establish

    if ser_ard1.is_open and ser_hc05.is_open:
        print("Connections established. Bridging data from Arduino 1 to HC-05 (Arduino 2)...")
    else:
        print("Failed to open one or both serial ports. Check port names and if they are in use.")
        exit()

    while True:
        # Read from Arduino 1 (Sender)
        if ser_ard1.in_waiting > 0:
            data = ser_ard1.readline().decode('utf-8').strip() # Read a line, decode, remove whitespace
            if data:
                print(f"Received from Arduino 1: {data}")
                # Send data to HC-05 (which sends it wirelessly to Arduino 2)
                # We add '\n' because Arduino 2's code expects it as a message terminator
                ser_hc05.write((data + '\n').encode('utf-8'))
                print(f"Forwarded to HC-05: {data}")
        time.sleep(0.1) # Small delay to prevent high CPU usage

except serial.SerialException as e:
    print(f"Serial port error: {e}")
    print("Please check:")
    print(f"  1. If '{ARDUINO1_PORT}' is the correct port for Arduino 1.")
    print(f"  2. If '{HC05_PORT}' is the correct port for the HC-05.")
    print("  3. If these ports are already in use by another program (e.g., Arduino Serial Monitor).")
    print("  4. If the Arduino boards are properly connected and powered.")
except Exception as e:
    print(f"An unexpected error occurred: {e}")
finally:
    if ser_ard1 and ser_ard1.is_open:
        ser_ard1.close()
        print(f"Closed {ARDUINO1_PORT}")
    if ser_hc05 and ser_hc05.is_open:
        ser_hc05.close()
        print(f"Closed {HC05_PORT}")