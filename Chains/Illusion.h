#ifndef ILLUSION_H
#define ILLUSION_H

#include "Chain.h"

class Illusion : public Chain
{

public:
   
   Illusion(bool isFacingRight, uint shortenLength);
   ~Illusion();
   void PressButtons();
   bool IsInterruptible();
   
private:
   
   bool m_isFacingRight;
   uint m_shortenLength;
   uint m_startingFrame;

};

#endif
