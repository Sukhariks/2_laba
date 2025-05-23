# 2_laba

# Лабораторная работа: Реализация разности мультимножеств с поддержкой вложенных структур

## Цель
Разработать программу для вычисления разности двух мультимножеств, учитывающую вложенные элементы и различные типы данных (целые числа, строки). Демонстрация применения полиморфизма, рекурсии и STL-контейнеров.

## Задача
Реализовать алгоритм, который:
1. Обрабатывает мультимножества с элементами разных типов.
2. Поддерживает вложенные структуры любой глубины.
3. Учитывает кратность вхождений элементов.
4. Обеспечивает корректное сравнение и клонирование элементов.

## Используемые понятия и источники
1. **Полиморфизм** (виртуальные функции, `dynamic_cast`) — [Документация C++](https://en.cppreference.com/).
2. **Умные указатели** (`unique_ptr`) — Страуструп Б. "Язык программирования C++".
3. **STL-контейнеры** (`multiset`, `vector`) — Джосаттис Н. "Стандартная библиотека C++".
4. **Рекурсия** — Кормен Т. и др. "Алгоритмы: построение и анализ".

## Описание алгоритмов
### Структура данных
- Базовый класс `Element` с методами `equals`, `print`, `clone`, `toString`.
- Производные классы:
  - `IntElement` — для целых чисел.
  - `StringElement` — для строк.
  - `SetElement` — для вложенных множеств (хранит элементы в `multiset<string>`).

### Алгоритм разности (`multiset_difference`)
1. Копирование элементов второго множества.
2. Для каждого элемента первого множества:
   - Поиск совпадения в копии второго множества.
   - Удаление найденного элемента из копии.
   - Добавление в результат, если элемент не найден.

### Ввод/вывод
- Рекурсивный парсинг ввода с использованием `<` и `>` для обозначения множеств.
- Поддержка строк в кавычках (`"text"`) и чисел.

## Результаты тестирования
**Пример 1:**
