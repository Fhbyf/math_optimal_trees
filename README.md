# Оптимальные алфавитные деревья
## Постороение алгоритмами Ху—Таккера и Гарсия—Уочса
Проект реализует алгоритмы постороения оптимальных алфавитных деревьев Ху—Таккера и Гарсия—Уочса.
Подробно об алгоритмах и об их реализации, читайте в [этом документе](https://github.com/DjGlobal/math_optimal_trees/blob/master/about.pdf).

Пример использования написанных библиотек — программа для кодирования текста при помощи алгоритмов Ху—Таккера и Гарсия—Уочса.

### Windows
[Исполняемый файл](https://drive.google.com/drive/folders/0B3i4nTNVsML6SWpZNG9LSmlLQjQ) (Google Drive).

### Linux
Для сборки нужен `g++` и следующий порядок команд:
```
g++ -std=c++11 -c includes/nodes.cpp -o includes/nodes.o
```
```
g++ -std=c++11 -c includes/pseudo_trees.cpp -o includes/pseudo_trees.o
```
```
g++ -std=c++11 -c includes/stack_algorithm.cpp -o includes/stack_algorithm.o
```
```
g++ -std=c++11 -finput-charset=CP1251 includes/nodes.o includes/pseudo_trees.o 
includes/stack_algorithm.o optimal_trees.cpp -o optimal_trees
```
Запуск:
```
./optimal_trees
```

### Описание работы
На вход программе подаётся некоторый текстовый файл. Считывая его посимвольно, программа считает количество вхождений каждого символа, после чего пару "символ—вес" перегоняет в формат узлов дерева, последовательность которых отдаётся одному из двух алгоритмов.

На выходе мы получаем кодирование каждого символа последовательностью нолей и единиц строго по построенному дереву. Программа выводит на экран ключи кодирования — пару "символ — код", то же самое записывает в текстовый файл. После этого исходный текст кодируется и тоже записывается в отдельный текстовый файл.

Для проверки правильности работы программы можно использовать файлы [1.txt](https://github.com/Fhbyf/math_optimal_trees/raw/master/optimal_trees/optimal_trees/1.txt) (пример из [учебника "Комбинаторные алгоритмы"](https://cloud.mail.ru/public/7NJS/6nYQoqXEB) Т. Ч. Ху, М. Т. Шинг, 2004) или [text.txt](https://github.com/Fhbyf/math_optimal_trees/raw/master/optimal_trees/optimal_trees/text.txt) (Шестой сонет Шекспира).
