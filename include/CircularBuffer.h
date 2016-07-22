template<typename T>
class CircularBuffer
{
public:
  CircularBuffer(int length);
  virtual ~CircularBuffer<T>();

  void push(T new_val);
  T pop();
protected:
  void increment(int &value);
  int length;
  int back;
  int front;
  T * values;
  bool is_start;
};

template<typename T>
CircularBuffer<T>::CircularBuffer(int length)
{
  values = new T[length];
  this->length = length;
  front = 0;
  back = 0;
  is_start = true;
}

template<typename T>
CircularBuffer<T>::~CircularBuffer()
{
  delete[] values;
}

template<typename T>
T CircularBuffer<T>::pop()
{
  int i = back;
  increment(back);
  return values[i];
}

template<typename T>
void CircularBuffer<T>::push(T new_val)
{
  if(front != back || is_start)
  {
    values[front] = new_val;
    increment(front);
  }
}

template<typename T>
void CircularBuffer<T>::increment(int &value)
{
  value++;
  if(value >= length)
  {
    value = 0;
  }
}
