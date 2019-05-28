# VoiceControlledBluetooth

A circuit that responds to voice commands which are relayed over through a Bluetooth connection was built. 
A voice input is given to the phone which converts speech to text in an app. 
This string of text is then transmitted to the Arduino UNO over a Bluetooth connection which is established using a HC-05 Bluetooth module.
The HC-05 Bluetooth module is connected to the Arduino UNO.  
The Arduino UNO is coded with responses to specific text commands which it executes using the L293D motor driver.
The motor driver is used to run the two motors attached to the two wheels at the back of the bot. 
An Ultrasonic sensor in the front mounted on a servo motor. 
It ensures the bot avoids any obstacles on its way by checking in every direction that the bot intends to move towards.

