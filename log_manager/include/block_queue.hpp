// 阻塞队列
#ifndef __BLOCK_QUEUE__
#define __BLOCK_QUEUE__

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <deque>


template <class T>
class BlockDeque
{    
public:
    BlockDeque();
    ~BlockDeque();

private:

    size_t capacity_;   // 队列大小
    std::

    
};

template <class T>
BlockDeque<T>::BlockDeque()
{
}

template <class T>
BlockDeque<T>::~BlockDeque()
{
}


#endif