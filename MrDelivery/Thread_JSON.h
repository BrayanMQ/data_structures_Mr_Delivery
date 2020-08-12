#ifndef THREAD_JSON_H
#define THREAD_JSON_H

#include <QThread>


class Thread_JSON : public QThread
{
    Q_OBJECT

public:
    Thread_JSON();
    void run ();
};

#endif // THREAD_JSON_H
