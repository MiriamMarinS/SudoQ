# SOLVING SUDOQ

```
g++ -o obj/sudo.o -c src/sudo.cpp -I include/
g++ -o obj/cell.o -c src/cell.cpp -I include/
g++ -o obj/utils.o -c src/utils.cpp -I include/
g++ obj/sudo.o obj/cell.o obj/utils.o -o sudoQ
```