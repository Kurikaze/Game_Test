#ifndef COMMANDQUEUE_HPP_INCLUDED
#define COMMANDQUEUE_HPP_INCLUDED
#include <queue>
#include "include/Command.hpp"

class CommandQueue
{
public:
    void        push(const Command& command);
    Command     pop();  //Pop the first (front) command
    bool        isEmpty() const;
private:
    std::queue<Command> mQueue;
};

#endif // COMMANDQUEUE_HPP_INCLUDED
