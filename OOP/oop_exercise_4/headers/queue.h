#ifndef QUEUE_H
#define QUEUE_H

class TQueue {
  public:
  // Конструктор по умолчанию
  TQueue();
  // Конструктор копирования очереди.
  TQueue(const TQueue& other);
  // Метод, добавляющий фигуру в конец очереди.
  void Push(const Triangle& polygon);
  // Метод, убирающий первую фигуру из очереди.
  const Triangle Pop();
  // Метод, возвращающий ссылку на первую в очереди фигуру
  const Triangle& Top();
  // Метод, проверяющий пустоту очереди
  bool Empty();
  // Метод, возвращающий длину очереди
  size_t Length();
  // Оператор вывода очереди в формате:
  // "=> Sn Sn-1 ... S1 =>", где Si - площадь фигуры,
  //  а n – номер последней фигуры в очереди
  friend std::ostream& operator<<(std::ostream& os, const TQueue& queue);
  // Метод, удаляющий все элементы контейнера,
  // но позволяющий пользоваться им.
  void Clear();
  // Деструктор
  virtual ~TQueue();

  protected:
  int size, capacity;
  Triangle* storage;
  void extend();

};

#include"queue.cpp"

#endif