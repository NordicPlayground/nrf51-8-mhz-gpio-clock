nrf51-8-mhz-gpio-clock
==================

This project sets up an 8 MHz clock on a regular GPIO (by default LED_1), using a 16 MHz timer, GPIOTE and the PPI. 

Requirements
------------
- nRF51 SDK version 5.1.0
- nRF51822 Development Kit 

The project may need modifications to work with later versions or other boards. For instance, if you have an Evaluation Kit, you can make it work by changing the BOARD define in the project settings. 

To compile it, clone the repository in the nrf51822/Board/pca10001/s110/ folder.

About this project
------------------
This application is one of several applications that has been built by the support team at Nordic Semiconductor, as a demo of some particular feature or use case. It has not necessarily been thoroughly tested, so there might be unknown issues. It is hence provided as-is, without any warranty. 

However, in the hope that it still may be useful also for others than the ones we initially wrote it for, we've chosen to distribute it here on GitHub. 

The application is built to be used with the official nRF51 SDK, that can be downloaded from www.nordicsemi.no, provided you have a product key for one of our kits.
