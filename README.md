# win-service
a windwows program service wrapper,you can use this package register an exe to windwos service
## usage
```
win_service -help
win_service.exe [options argv]
win_service.exe -install
win_service.exe -uninstall
```
## config wins_service.ini
``` 
[common]
serveice_name = "windwons service name"
monitor_exe = name.exe
```
## [doc of windows service](https://docs.microsoft.com/en-us/windows/win32/services/about-services)
