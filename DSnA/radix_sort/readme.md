# Описание

Реализация алгоритма поразрядной сортировки для сортировки ключей, являющихся автомобильными номерами типа «A 999 AA».

Поразрядная сортировка по сути своей представляет из себя поэтапную сортировку подсчетом, которая по очереди применяется к каждому из разрядов, начиная с самого младшего и заканчивая самым старшим.

Для сортировки ключей, являющихся автомобильными номерами типа «A 999 AA», мне показалось
наиболее естественным разбиение на следующие разряды:
* Первая буква номера;
* Значение числа в номере автомобиля;
* Две последние буквы номера.