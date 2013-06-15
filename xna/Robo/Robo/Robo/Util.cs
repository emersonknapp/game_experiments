using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Robo
{
   class Util
   {
      public static Texture2D pixel;

      public static int round(float x)
      {
         return (int)Math.Round(x);
      }
      public static int floor(float x)
      {
         return (int)Math.Floor(x);
      }
      public static int ceiling(float x)
      {
         return (int)Math.Ceiling(x);
      }

      public static void DrawHollowRect(Rectangle rectangleToDraw, int thicknessOfBorder, Color borderColor, SpriteBatch spriteBatch)
      {
         // Draw top line
         spriteBatch.Draw(pixel, new Rectangle(rectangleToDraw.X, rectangleToDraw.Y, rectangleToDraw.Width, thicknessOfBorder), borderColor);

         // Draw left line
         spriteBatch.Draw(pixel, new Rectangle(rectangleToDraw.X, rectangleToDraw.Y, thicknessOfBorder, rectangleToDraw.Height), borderColor);

         // Draw right line
         spriteBatch.Draw(pixel, new Rectangle((rectangleToDraw.X + rectangleToDraw.Width - thicknessOfBorder),
                                         rectangleToDraw.Y,
                                         thicknessOfBorder,
                                         rectangleToDraw.Height), borderColor);
         // Draw bottom line
         spriteBatch.Draw(pixel, new Rectangle(rectangleToDraw.X,
                                         rectangleToDraw.Y + rectangleToDraw.Height - thicknessOfBorder,
                                         rectangleToDraw.Width,
                                         thicknessOfBorder), borderColor);
      }

   }
}
