## project #2 : thread-safe-counter in RTOS class
### OS Environment : Ubuntu Linux 18.04

### Compare performance (mutex vs semaphore)

### 🚀 Mutex 
<img width="100%" src="https://user-images.githubusercontent.com/54614865/121772182-d26c6800-cbae-11eb-8a63-947299a360c1.png"/>

### 🚀 Semaphore
<img width="100%" src="https://user-images.githubusercontent.com/54614865/121772180-d0a2a480-cbae-11eb-8800-30536ab4bb4e.png"/>
 
### 🚀 Performance measurement result(time command)
<img width="90%" src="https://user-images.githubusercontent.com/54614865/121800804-da8bdc80-cc6e-11eb-9b83-fcd65987bce0.png"/>

### 🚀 My Analysis
- Mutex is faster than Semaphore
- The difference between mutex and semaphore is,
 * Semaphores can be Mutex, but Mutex cannot be Semaphores.
 * The biggest difference is the number of synchronization targets managed.
   Mutex is used when there is only one synchronization destination, and semaphores when there is more than one synchronization destination.

### 🚀 [Refer to(click here!)][참조 링크 URL]
[참조 링크 URL]: https://github.com/jongchank/car-tos-2021/blob/main/16-inter-process-communication/sem1.c

20183392 안현빈
