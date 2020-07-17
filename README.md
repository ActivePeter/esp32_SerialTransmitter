[https://github.com/ActivePeter/esp32_SerialTransmitter](https://github.com/ActivePeter/esp32_SerialTransmitter)

## 这是一个用esp32做串口透传助手的项目

一般我们单片机无线传输数据会选则使用hc05这种蓝牙透传模块。

这里提供一个使用esp32的方案

原理是使一个esp32 开启一个ap热点，然后开启一个tcp服务端。

另一个esp32连入热点并且进行tcp通信

