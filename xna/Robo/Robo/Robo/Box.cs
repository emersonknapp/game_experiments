using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Robo
{
   class Box
   {
      public Vector2 pos;
      public Vector2 size;

      public Box(float x, float y, float dx, float dy)
      {
         pos = new Vector2(x, y);
         size = new Vector2(dx, dy);
      }
      public Box(Rectangle r)
      {
         pos = new Vector2(r.Left, r.Top);
         size = new Vector2(r.Width, r.Height);
      }

      public float Left
      {
         get { return pos.X; }
         set { pos.X = value; }
      }
      public float Top
      {
         get { return pos.Y; }
         set { pos.Y = value; }
      }
      public float Right
      {
         get { return pos.X + size.X; }
         set { pos.X = value - size.X; }
      }
      public float Bottom
      {
         get { return pos.Y + size.Y; }
         set { pos.Y = value - size.Y; }
      }
      public float Width
      {
         get { return size.X; }
         set { size.X = value; }
      }
      public float Height
      {
         get { return size.Y; }
         set { size.Y = value; }
      }

      public Rectangle rect
      {
         get { return new Rectangle(Util.round(pos.X), Util.round(pos.Y), Util.round(size.X), Util.round(size.Y)); }
      }
   }
}
