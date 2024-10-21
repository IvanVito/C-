# Репозиторий проектов CPP

## Обзор

Этот репозиторий содержит четыре проекта: **matrixCPP** (Матрицы), **copyContainers** (Контейнеры), **snake** (Змейка) и **3DViewer(3Д Вьювер)**. Цель этих проектов — продемонстрировать использование C++ для реализации основных структур данных, алгоритмов и игр с объектно-ориентированным подходом. Каждый проект включает исчерпывающие модульные тесты для обеспечения корректности реализации. Подробности по каждому проекту приведены ниже.

## Проекты

### 1. [matrixCPP (Матрицы)](https://github.com/IvanVito/CPP/tree/main/matrixCPP)

#### Описание

В проекте была реализована `s21_matrix+` — это библиотека для операций с матрицами, на основе объектно-ориентированного подхода на языке C++. Библиотека включает основные операции с матрицами, такие как сложение, вычитание, умножение, а также более сложные операции, такие как транспонирование, вычисление алгебраических дополнений, определителя и обратной матрицы.

#### Функциональные возможности

- **Базовый и параметризованный конструкторы**: Создание матриц с размерностями по умолчанию или заданными параметрами.
- **Конструкторы копирования и перемещения**: Эффективная обработка копирования и переноса матриц.
- **Операции с матрицами**: 
  - Проверка на равенство (`EqMatrix`)
  - Сложение (`SumMatrix`)
  - Вычитание (`SubMatrix`)
  - Умножение на число (`MulNumber`) и на другую матрицу (`MulMatrix`)
  - Транспонирование (`Transpose`)
  - Вычисление матрицы алгебраических дополнений (`CalcComplements`)
  - Вычисление определителя (`Determinant`)
  - Вычисление обратной матрицы (`InverseMatrix`)
- **Перегрузка операторов**: Реализация операторов для операций с матрицами (`+`, `-`, `*`, `==`, `=`, `+=`, `-=`, `*=`, `()`)
- **Обработка исключений**: Управление исключительными ситуациями, такими как несоответствие размерностей и сингулярные матрицы.

#### Использование

Включите заголовочный файл `s21_matrix_oop.h` в свой проект и подключите скомпилированную статическую библиотеку `s21_matrix_oop.a`.

#### Тестирование

Предоставлены модульные тесты с использованием библиотеки GTest для обеспечения корректности операций с матрицами. Используйте предоставленный Makefile для сборки и запуска тестов.

### 2. [copyContainers (Контейнеры)](https://github.com/IvanVito/CPP/tree/main/copyContainers)

#### Описание

В данном проекте была разработана `s21_containers` —  библиотека, реализующая стандартные контейнерные классы C++: `list`, `map`, `queue`, `set`, `stack` и `vector`. Кроме того, библиотека включает `array` и `multiset`, а также методы для вставки множества элементов.

#### Функциональные возможности

- **Реализация стандартных контейнеров**:
  - **List**: Двусвязный список со стандартными операциями и итераторами.
  - **Vector**: Динамический массив со стандартными операциями и итераторами.
  - **Map**: Словарь на основе дерева бинарного поиска.
  - **Set**: Коллекция уникальных элементов на основе дерева бинарного поиска.
  - **Queue**: Коллекция FIFO на основе двусвязного списка.
  - **Stack**: Коллекция LIFO на основе динамического массива.
- **Дополнительные контейнеры**:
  - **Array**: Статический массив с фиксированным размером.
  - **Multiset**: Коллекция, допускающая дублирование элементов, на основе дерева бинарного поиска.
- **Многоэлементные вставки**:
  - `insert_many` для `List` и `Vector`
  - `insert_many_back` для `List`, `Vector` и `Queue`
  - `insert_many_front` для `List` и `Stack`
  - `insert_many` для `Map`, `Set` и `Multiset`
- **Шаблонная реализация**: Обеспечивает гибкость типов для элементов контейнера.
- **Поддержка итераторов**: Позволяет обход и манипуляцию элементами контейнера.
- **Безопасность исключений**: Надежная обработка граничных условий и недопустимых операций.

#### Использование

Включите заголовочный файл `s21_containers.h` в свой проект. Реализация контейнеров расположена в хедерах

#### Тестирование

Предоставлены модульные тесты с использованием библиотеки GTest для обеспечения корректности и производительности операций контейнера. Используйте предоставленный Makefile для сборки и запуска тестов.

### 3. [snake (Змейка)](https://github.com/IvanVito/CPP/tree/main/snake)

**Описание:**
Проект включает реализацию игры **Змейка** и **Тетрис**. Змейка реализована на C++, а Тетрис — на C. Проект также включает консольный и десктопный интерфейсы с использованием паттерна MVC и библиотеки Qt. Для Тетриса предусмотрен отдельный [репозиторий](https://github.com/IvanVito/C/tree/main/tetris).

**Функциональные возможности:**
- **Игровой процесс:** Змейка движется по полю, увеличивается в длине при поедании яблок. Победа при длине 200 блоков; поражение — при столкновении с границей или самим собой. Управление стрелками, ускорение зажатой клавишей (пробел).
- **Подсчет очков:** Очки начисляются за каждое съеденное яблоко, максимальное количество очков сохраняется между запусками программы. Отображение текущих очков и максимального рекорда.

**Использование:**
- Для сборки и запуска приложений используйте Makefile:
  - **Установка:** `make install`
  - **Запуск CLI версии:** `make play_cli`
  - **Запуск Qt версии:** `make play_qt`

**Тестирование:**
Модульные тесты с использованием Google Test (GTest). Отчеты о покрытии тестами и проверка утечек памяти с помощью lcov и Valgrind. Сборка и запуск тестов осуществляется с помощью Makefile.`

### 4. [3DViewer(3Д Вьювер)](https://github.com/IvanVito/CPP/tree/main/3DViewer)

#### Описание

Данная программа визуализирует каркасные модели в трехмерном пространстве. При проектировании использовались следующие паттерны проектирования: синглтон, шаблонный метод, фасад, модель-представление-контроллер. Программа разработана на языке C++ стандарта C++17 и фреймворка QT. Данный проект является групповым проектом. За обработку модели и ее трансформацию (за "бекенд") отвечал я (s21: lesleyle), за "фронт" и работу в QT отвечала моя напарница ([s21: lemongrb](https://github.com/Shyrasya)

#### Функциональные возможности

- 1. Загрузка каркасной модели из файла формата obj (поддержка только списка вершин и поверхностей);
- 2. Перемещение модели на заданное расстояние относительно осей X, Y, Z;
- 3. Поворот модели на заданный угол относительно своих осей X, Y, Z;
- 4. Масштабирование модели на заданное значение.
- 5. Настройка типа проекции (параллельная и центральная).
- 6. Настройка типа (сплошная, пунктирная линия), цвета и толщины ребер, способ отображения (отсутствует, круг, квадрат), цвет и размер вершин.
- 7. Программа позволяет выбирать цвет фона.
- 8. Настройки сохраняются между перезапусками программы
- 9. Программа позволяет сохранять полученные («отрендеренные») изображения в файл в форматах bmp и jpeg.
- 10. Программа позволяет по специальной кнопке записывать небольшие «скринкасты» — текущие пользовательские аффинные преобразования загруженного объекта в gif-анимацию (640x480, 10fps, 5s)

#### Использование

**Установка программы**
Пропишите в папке 'src' даннаую команду 'make install' для сборки проекта

**Запуск программы**
После сборки проекта вы можете запустить его с помощью команды: 'make launch'

#### Тестирование

Предоставлены модульные тесты с использованием библиотеки GTest для проверки преобразований объекта и валидности введенных данных. Используйте предоставленный Makefile для сборки и запуска тестов. Для запуска тестов, пропишите из папки 'src' команду 'make tests'.

## Заключение

Проекты в этом репозитории демонстрируют реализацию различных аспектов программирования на C++, включая работу с матрицами, реализацию стандартных контейнеров, проектирование программ и игр с разнообразными паттернами. Каждый проект обеспечен тестами и документацией для поддержки надежности и удобства использования.
