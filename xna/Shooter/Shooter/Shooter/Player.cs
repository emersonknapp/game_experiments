using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;


namespace Shooter
{
	class Player : AnimatedSprite
	{
        public int health;
        public float speed;

        public override void Initialize(Animation animation, Vector2 position)
        {
            speed = 8.0f;
            health = 100;
            base.Initialize(animation, position);
        }
        public override void Update(GameTime cgameTime)
        {
            animation.Position = pos;
            animation.Update(cgameTime);
        }
	}
}
