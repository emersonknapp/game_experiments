using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;


namespace Robo
{
   class Player : AnimatedSprite
   {
      public int health;
      public float speed;
      public Box collision;
      public bool grounded;
      public Vector2 previousPos;

      public override void Initialize(Animation animation, Vector2 startPos)
      {
         health = 10;
         speed = 8.0f;
         grounded = false;
         collision = new Box(pos.X, pos.Y, animation.FrameWidth, animation.FrameHeight);
         base.Initialize(animation, startPos);
      }
      public override void Update(GameTime gameTime)
      {

         base.Update(gameTime);
      }

      public void Move(Vector2 delta)
      {
         pos += delta;
         collision.pos = pos;
         animation.Position = pos;
      }

   }
}
