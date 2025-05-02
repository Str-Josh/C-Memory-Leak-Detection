# C-Memory-Leak-Detector

```gcc -c MemoryLeakDetector.c```
```gcc -c LinkedList.c```
```gcc MemoryLeakDetector.o LinkedList.o -Wl,--wrap=malloc -Wl,--wrap=free -o DetectMemoryLeaks```
