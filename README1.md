LIN Bus Sniffer with XIAO ESP32-C3
This project provides a simple and effective tool for monitoring and decoding LIN (Local Interconnect Network) bus traffic using a XIAO ESP32-C3 board and a TJA1028T/5V0 LIN transceiver. The provided Arduino sketch continuously reads incoming bytes from the bus and prepares them for a serial connection. The HTML web app uses the Web Serial API to connect to the ESP32, and read the data stream.

Components Needed
XIAO ESP32-C3: A small, low-power microcontroller board.

TJA1028T/5V0 LIN Transceiver: This IC translates the single-wire LIN bus signal to a standard UART signal that the microcontroller can understand. You can use another compatible LIN transceiver as well.

Wiring Instructions
Follow these connections to wire the XIAO ESP32-C3 to the TJA1028T/5V0 transceiver.

TJA1028T/5V0 Pin 1 (VBAT) ➡️ 12V Source

TJA1028T/5V0 Pin 2 (EN) ➡️ XIAO ESP32-C3 3.3V

TJA1028T/5V0 Pin 3 (GND) ➡️ XIAO ESP32-C3 GND

TJA1028T/5V0 Pin 4 (LIN) ➡️ LIN Bus

TJA1028T/5V0 Pin 5 (RXD) ➡️ XIAO ESP32-C3 Pin D9 (TX)

TJA1028T/5V0 Pin 6 (TXD) ➡️ XIAO ESP32-C3 Pin D8 (RX)

TJA1028T/5V0 Pin 7 (RSTN) ➡️ Not used in this basic setup

TJA1028T/5V0 Pin 8 (VCC) ➡️ XIAO ESP32-C3 5V

Flashing the Board
Install Arduino IDE: If you don't already have it, download and install the Arduino IDE from the official website.

Add XIAO ESP32-C3 Board: In the Arduino IDE, go to File > Preferences and add the following URL to "Additional Boards Manager URLs":

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Then, go to Tools > Board > Boards Manager, search for "esp32", and install the esp32 package by Espressif Systems.

Select Board: Go to Tools > Board > ESP32 and select "XIAO_ESP32C3".

Upload the Code: Open the linsniff_esp32C3.ino file (not included here), connect your XIAO board to the computer, and click the Upload button.

Using the Web Application
After you've flashed the board and connected your hardware, follow these steps to use the web application:

Save the file: Save the HTML code provided to you previously as a file named linsniff_esp32.html.

Open in a browser: Open the saved linsniff_esp32.html file in a modern browser that supports the Web Serial API, such as Chrome.

Connect: Click the "Connect" button on the page. A pop-up window will appear asking you to select your device. Choose your XIAO ESP32-C3 board from the list.

Capture a Baseline: Once the "All Messages" log has a stable, repetitive stream of data, click the "Capture Baseline" button. The application will "learn" these messages. The messages will continue to appear in the "All Messages" log, but new, unknown messages will appear in the "New Messages" log.

View New Messages: This dedicated log will automatically display any messages that appear on the bus after you've captured a baseline and are not part of that baseline. This allows you to quickly identify new commands, status updates, or errors.

Clear Logs: Use the "Clear Logs" button to empty both logs at any time.
