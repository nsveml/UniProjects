#ifndef QUEUE_H
#define QUEUE_H

#include<memory>

template<class T>
class TQueue;

template<class T>
std::ostream& operator<< (std::ostream&, const TQueue<T>&);

template <class T>
class TQueue {
  public:
  // Конструктор по умолчанию
  TQueue();
  // Конструктор копирования очереди.
  TQueue(const TQueue& other);
  // Метод, добавляющий фигуру в конец очереди.
  void Push(const T& polygon);
  // Метод, убирающий первую фигуру из очереди.
  const T Pop();
  // Метод, возвращающий ссылку на первую в очереди фигуру
  const T& Top();
  // Метод, проверяющий пустоту очереди
  bool Empty();
  // Метод, возвращающий длину очереди
  size_t Length();
  // Оператор вывода очереди в формате:
  // "=> Sn Sn-1 ... S1 =>", где Si - площадь фигуры,
  //  а n – номер последней фигуры в очереди
  friend std::ostream& operator<< <> (std::ostream&, const TQueue&);
  // Метод, удаляющий все элементы контейнера,
  // но позволяющий пользоваться им.
  void Clear();
  // Деструктор
  virtual ~TQueue();

  protected:
  int size, capacity;
  std::shared_ptr<T[]> storage;
  void extend();

};

#include"queue.cpp"

#endif