using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Robo
{
   class Test
   {
      public static bool runTests()
      {
         Box b1 = new Box(0, 0, 2, 2);
         Rectangle r1 = new Rectangle(1, -1, 1, 4);
         Box expected1 = new Box(1, 0, 1, 2);
         Box result1 = b1.shrinkWrap(r1);
         if (!expected1.Equals(result1)) return false;

         Rectangle r2 = new Rectangle(1, 0, 3, 3);
         Box expected2 = new Box(1, 0, 1, 2);
         Box result2 = b1.shrinkWrap(r2);
         if (!expected2.Equals(result2)) return false;

         Rectangle r3 = new Rectangle(-1, -1, 4, 4);
         Box result3 = b1.shrinkWrap(r3);
         if (!b1.Equals(result3)) return false;

         Rectangle r4 = new Rectangle(1, 1, 1, 1);
         Box result4 = b1.shrinkWrap(r4);
         if (!result4.Equals(new Box(r4))) return false;

         Box b2 = new Box(0.5f,0.5f, 2f,2f);
         Rectangle r5 = new Rectangle(0, 0, 3, 3);
         Box result5 = b2.shrinkWrap(r5);
         if (!result5.Equals(b2)) return false;

         return true;
      }
   }
}
