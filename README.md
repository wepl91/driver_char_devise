# CHAR DEVISE DRIVER
* Materia: Sistemas Operativos y Redes II
* Alumnos: 
  - Capecce Bruno
  - Pereyra Lopez Walter
  
## Tools
Two little programs were made to test driver functionality, writing some text and reading it by bytes quantity
* WRITE: use this program to tests the device, args: device_path, message
  ``./write /dev/UNGS "testing driver"``

  
* READ: use this program to tests read operation on the device, args: device_path, pointer, offset

  this example read the first 3 bytes
  
  ``./read /dev/UNGS 3``
  
  this example read 3 bytes with 2 bytes offset on the device
  
  ``./read /dev/UNGS 3 2``
  
  
  
