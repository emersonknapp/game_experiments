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
      public enum Axis { X, Y };

      public void Apply(GameTime gt, Player player, Level level)
      {
         float dt = gt.ElapsedGameTime.Milliseconds / 1000f;

         player.velocity.Y += Constants.gravity * dt;

         Box endBox = new Box(player.collision) ;

         float dx = player.velocity.X * dt;
         float dy = player.velocity.Y * dt;

         Rectangle checkRect ;

         IEnumerable<MapObject> collideObjects;

         if (dx != 0)
         {
            endBox.Left += dx;
            checkRect = endBox.rect;
            checkRect.Inflate(1, 1);
            collideObjects = level.map.GetObjectsInRegion(level.collisionLayer, checkRect);

            foreach (var obj in collideObjects)
            {
               Vector2 delta = adjustPos(ref endBox, obj, Axis.X);
               endBox.pos += delta;
            }
         }

         endBox.Top += dy;

         checkRect = endBox.rect;
         checkRect.Inflate(1, 1);
         collideObjects = level.map.GetObjectsInRegion(level.collisionLayer, checkRect);

         foreach (var obj in collideObjects)
         {
            Vector2 delta = adjustPos(ref endBox, obj, Axis.Y);
            endBox.pos -= delta;
            if (delta.Y != 0)
            {
               player.velocity.Y = 0;
               if (delta.Y > 0) player.grounded = true;
            }
         }

         player.pos = endBox.pos;
      }

      protected Vector2 adjustPos(ref Box mover, MapObject platform, Axis axis)
      {
         if (platform.Polygon != null)
            return Vector2.Zero;
         //return adjustPos(ref mover, platform.Polygon);
         else
            return adjustPos(ref mover, platform.Bounds, axis);
      }


      protected Vector2 adjustPos(ref Box mover, Rectangle platform, Axis axis)
      {
         Rectangle checkRect = mover.rect;
         checkRect.Inflate(1, 1);
         Box delta = mover.shrinkWrap(Rectangle.Intersect(checkRect, platform));

         if (axis == Axis.X)
         {
            if (mover.Left >= platform.Left && mover.Right <= platform.Right) return Vector2.Zero;
           
            return new Vector2(delta.Width, 0);
         }
         else
         {
            if (mover.Top >= platform.Top && mover.Bottom <= platform.Bottom) return Vector2.Zero;
            return new Vector2(0, delta.Height);
         }
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


   }
}
