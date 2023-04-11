Wifi Speed Tester
This is a simple C++ program that tests your internet speed and displays your wifi information, including your location and IP address.

Requirements
C++ compiler
libcurl
RapidJSON
Installation
Clone this repository to your local machine.
Install the required libraries: libcurl and RapidJSON.
Compile the program with the command 

g++ wifi_speed_tester.cpp -o wifi_speed_tester -lcurl -lrapidjson.

Run the program with the command 

./wifi_speed_tester.

Usage
Upon running the program, you will see a banner and your wifi information, including your location, IP address, and ISP. The program retrieves this information using the ipinfo.io API.

Contributing
Feel free to fork this repository and make your own changes. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.
