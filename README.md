audio2mp3 CLI
========
Скачивая аудио поток с [youtube](https://youtube.com "youtube")
c помощь [youtube-dl](https://github.com/ytdl-org/youtube-dl "youtube-dl")

Нужны были mp3 а не m4a. 
Была написана программа для кодирования на всех потоках CPU.

### Ключи запуска
``` 
    -j Количество потокв.                # Равно количеству потоков в системе.
    -f Формат кодирования.               # ".mp3"
    -p Приложение для распаралелливания. # ffmpeg
    -v Включить отладочную печать.       # Поток вывода stdout.
```

Для работы необходима установка: [ffmpeg](https://ffmpeg.org/download.html 
"Dowonload ffmpeg")
### Debian:
```
# apt install ffmpeg
```

### **Установка**
```
git clone https://github.com/serg2a/audio2mp3.git
cd audio2mp3
make
make install // Копирует au2mp3 в ~/bin 
```

### **Использование**
```
$ au2mp3 file1.mp3 file2.mp3
```
или
```
$ au2mp3 *
```
> Получаем файлы mp3 там где вызвали au2mp3.


English
-------
Need to install [ffmpeg](https://ffmpeg.org/download.html 
"Dowonload ffmpeg")

	Using ffmpg in multiprocess, input list files:
## **make**
```
# git clone https://github.com/serg2a/audio2mp3.git
# cd audio2mp3
# make
```

### **example:**
convert and crate file1.mp3 file2.mp3 file3.mp3
```
# au2mp3 file1 file2 file  
```
or convret and crate *.mp3
```
# au2mp3 *
```
