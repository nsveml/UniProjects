# Описание

В качестве аргументов quick_sort должно быть передано число потоков, либо не передано ничего (алгоритм будет выполняться ежинственным потоком).

# Принцип работы

Алгоритм быстрой сортировки подразумевает разделение массива на две части относительно опор-
ного элемента, после чего над каждым из подмассивов проделывается тоже самое. В случае па-
раллельности каждому процессу удобно отдавать получившийся в результате разделения массива
подмассив дочернему процессу, для контроля количества процессов каждый "родитель" делится со
своим "ребенком" частью своих процессов. Если процесс не может создать дочерний процесс, то
он продолжает обработку своей части массива линейно (линейный quicksort реализован и процесс
обращается к нему).

Функция quick_sort_parallel подготавливает данные для функции quick_sort_parallel_thread, по-
сле чего эта функция сначала запускается главным потоком, а затем передается в функцию pthread_create
при создании нового процесса. Эта функция вызывает функцию partition, которая нужным обра-
зом обрабатывает фрагмент массива, затем проверяет, можно ли создать поток, если можно, то
формирует данные для него, если нельзя, то продолжает обработку своего фрагмента линейно.