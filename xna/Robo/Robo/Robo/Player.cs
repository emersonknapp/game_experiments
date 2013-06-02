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

      public override void Initialize(Animation animation, Vector2 startPos)
      {
         health = 10;
         speed = 8.0f;
         base.Initialize(animation, startPos);
      }
      public override void Update(GameTime gameTime)
      {
         base.Update(gameTime);
      }

   }
}
