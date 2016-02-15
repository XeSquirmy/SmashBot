#ifndef ILLUSION_H
#define ILLUSION_H

#include "Chain.h"

class Illusion : public Chain
{

public:
   
   Illusion(bool isOnRight, uint shortenLength);
   ~Illusion();
   void PressButtons();
   bool IsInterruptible();
   
private:
   
   bool m_isOnRight;
   uint m_shortenLength;
   uint m_startingFrame;
   uint FULL;
   uint FULLSHORT;
   uint HALF;
   uint SHORT;

};

#endif
