# Описание

Родительский процесс создает два дочерних процесса. Процессы связаны отображаемыми файлами и семафорами.

# Принцип работы

Parent принимает от пользователя строки произвольной длины и пересылает их child1. Child1 переводит строки в верхний регистр. Child2 убирает все задвоенные пробелы и пересылает результат работы родительскому процессу. Child2 выводит
полученный результат в стандартный поток вывода