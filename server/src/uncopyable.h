#pragma once

class Uncopyable
{
   protected:
    // allow construction
    Uncopyable() {}           // and destruction of
    virtual ~Uncopyable() {}  // derived objects...
   private:
    Uncopyable(const Uncopyable&);
    // ...but prevent copying
    Uncopyable& operator=(const Uncopyable&);
};