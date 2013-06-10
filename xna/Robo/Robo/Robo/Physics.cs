using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using FuncWorks.XNA.XTiled;

namespace Robo
{
   class Physics
   {
      public void Apply(GameTime gt, Player s)
      {
         float dt = gt.ElapsedGameTime.Milliseconds / 1000f;
         //if (!s.grounded)
            s.velocity.Y += Constants.gravity * dt;

         s.Move( new Vector2(s.velocity.X * dt, s.velocity.Y * dt));

      }
      protected Vector2 adjustPos(ref Box mover, Vector2 velocity, MapObject platform)
      {
         if (platform.Polygon != null)
            return Vector2.Zero;
         //return adjustPos(ref mover, platform.Polygon);
         else
            return adjustPos(ref mover, velocity, platform.Bounds);         
      }

      protected Vector2 adjustPos(ref Box mover, Vector2 velocity, Rectangle platform)
      {
         Box delta = new Box(Rectangle.Intersect(mover.rect, platform));

         delta.Left = delta.Left < mover.Left ? mover.Left : delta.Left;
         delta.Top = delta.Top < mover.Top ? mover.Top : delta.Top;
         if (delta.Right > mover.Right)
            delta.Width = mover.Right - delta.Left;
         if (delta.Bottom > mover.Bottom)
            delta.Height = mover.Bottom - delta.Top;

         float adjustY = delta.Height*-1;// *(delta.Y > mover.Y ? -1 : 1);
         return new Vector2(0, adjustY);
      }

      protected float adjustY(ref Rectangle mover, Polygon platform)
      {
         Rectangle delta = Rectangle.Empty;
         Vector2 inside = Vector2.Zero;
         if (platform.Contains(new Vector2(mover.Left, mover.Bottom)))
            inside = new Vector2(mover.Left, mover.Bottom);
         else if (platform.Contains(new Vector2(mover.Right, mover.Bottom)))
            inside = new Vector2(mover.Right, mover.Bottom);
         else if (platform.Contains(new Vector2(mover.Left, mover.Top)))
            inside = new Vector2(mover.Left, mover.Top);
         else if (platform.Contains(new Vector2(mover.Right, mover.Top)))
            inside = new Vector2(mover.Right, mover.Top);
         else
            return 0;

         Line l = Line.FromPoints(inside, new Vector2(mover.Center.X, mover.Center.Y));
         Vector2 intersection;
         foreach (var line in platform.Lines)
         {
            if (line.Intersects(l, out intersection))
            {
               delta.Width = Convert.ToInt32(Math.Abs(l.Start.X - intersection.X));
               delta.Height = Convert.ToInt32(Math.Abs(l.Start.Y - intersection.Y));
               delta.X = Convert.ToInt32(Math.Min(l.Start.X, intersection.X));
               delta.Y = Convert.ToInt32(Math.Min(l.Start.Y, intersection.Y));
            }
         }
         return delta.Height * (delta.Y > mover.Y ? -1 : 1);
      }
      public void Collide(Player player, Level level)
      {
         Rectangle checkRect = player.collision.rect;
         checkRect.Inflate(1, 1);
         foreach (var obj in level.map.GetObjectsInRegion(level.collisionLayer, checkRect))
         {
            Vector2 delta = adjustPos(ref player.collision, player.velocity, obj);
            if (delta.Y != 0f)
            {
               player.velocity.Y = 0;
               player.grounded = true;
            }
            player.Move(delta);
         }
      }

   }
}
