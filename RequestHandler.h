#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "ThreadPool.h"

class RequestHandler 
{
private:
    ThreadPool m_tpool; // пул потоков
public:
    RequestHandler();
    ~RequestHandler();
    template<typename F, typename... Args> 
    void pushRequest(F&& func, Args&&... args)  // отправка запроса на выполнение
    {
        m_tpool.push_task(std::forward<F>(func), std::forward<Args>(args)...);
    }
};

#endif // REQUESTHANDLER_H