##  АиСД 2023 КДЗ №2

### 1. Ганина Ксения Андреевна 212 (тг для вопросов: @kgnn47)
### 2. CLion & IDLE python & Google Tables
### 3. Сделано: генерация текста, 3 алгоритма на поиск, учёт подстановок '?' в искомый паттерн, замеры времени, графики, выводы
### 4. Не сделано: усреднение результатов, ???, перевод из .txt в .csv выполнялся через Google Tables
### 5. Задание: https://edu.hse.ru/pluginfile.php/2389113/mod_resource/content/2/Алгоритмы_поиска_строки_шаблона_ДЗ.pdf
________________________

## 3. Немного ReadMe-Moment

Данные для графиков можно посмотреть здесь: [data](https://github.com/kseniag03/algosi-karasi/tree/master/data) <br>

Кол-во символов искомой подстроки задавалось параметром цикла (от 100 до 3 000, шаг == 100, по условию) <br>
Стартовая позиция выбиралась с помощью

```cpp 
int start_position = rand() % (text.size() - count);
```

Символы подстановки '?' расставлялись на места, которые генерировались через

```cpp 
int p = rand() % pattern.size();
```

Поиск идёт по всем возможным подстановкам, вывод алгоритмов из класса ```FindStringPattern``` 
был закомментирован (как и ещё несколько строк вывода с получением подстроки или всех подходящих под маску подстрок) <br>
Вывод замеров времени также был закомментирован, в программе отрабатывает только вывод соответствующих имён выходных .txt-файлов <br>
Формат вывода следующий: 1-й столбец -- наивный алгоритм, 2-й -- КМП на обычных гранях, 3-й -- на уточненных <br>
________________________

## 4. Графики <br>

### 4.1. Бинарный алфавит, текст размера 10 000 символов, 0-4 символа подстановки

![image](data/2-alp_1e5_without.png)
![image](data/2-alp_1e5_with-1-replace.png)
![image](data/2-alp_1e5_with-2-replace.png)
![image](data/2-alp_1e5_with-3-replace.png)
![image](data/2-alp_1e5_with-4-replace.png)

### 4.2. Бинарный алфавит, текст размера 100 000 символов, 0-4 символа подстановки

![image](data/2-alp_1e6_without.png)
![image](data/2-alp_1e6_with-1-replace.png)
![image](data/2-alp_1e6_with-2-replace.png)
![image](data/2-alp_1e6_with-3-replace.png)
![image](data/2-alp_1e6_with-4-replace.png)

### 4.3. 4-символьный алфавит, текст размера 10 000 символов, 0-4 символа подстановки

![image](data/4-alp_1e5_without.png)
![image](data/4-alp_1e5_with-1-replace.png)
![image](data/4-alp_1e5_with-2-replace.png)
![image](data/4-alp_1e5_with-3-replace.png)
![image](data/4-alp_1e5_with-4-replace.png)

### 4.4. 4-символьный алфавит, текст размера 100 000 символов, 0-4 символа подстановки

![image](data/4-alp_1e6_without.png)
![image](data/4-alp_1e6_with-1-replace.png)
![image](data/4-alp_1e6_with-2-replace.png)
![image](data/4-alp_1e6_with-3-replace.png)
![image](data/4-alp_1e6_with-4-replace.png)

________________________

## 5. Дополнение

Итак, . <br>

. <br>
