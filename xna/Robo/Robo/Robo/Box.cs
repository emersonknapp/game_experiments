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
      public Box(Box b)
      {
         pos = b.pos;
         size = b.size;
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

      public Box shrinkWrap(Rectangle r)
      {
         if (r.Width == 0 || r.Height == 0)
            return new Box(r);
         //Box b = new Box(r);

         float newLeft = Math.Max(r.Left, Left);
         float newTop = Math.Max(r.Top, Top);
         float newRight = Math.Min(r.Right, Right);
         float newBottom = Math.Min(r.Bottom, Bottom);

         return new Box(newLeft, newTop, newRight - newLeft, newBottom - newTop);
      }

      public bool Equals(Box b)
      {
         return (b.pos == pos && b.size == size);
      }



      public Rectangle rect
      {
         get { return new Rectangle(Util.round(pos.X), Util.round(pos.Y), Util.round(size.X), Util.round(size.Y)); }
      }
   }
}
