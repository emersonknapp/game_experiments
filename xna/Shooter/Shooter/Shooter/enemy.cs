using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Shooter
{
    class Enemy : AnimatedSprite
    {

        public int health;
        public int damage;
        public int pointValue;
        float speed;

        public override void Initialize(Animation animation, Vector2 startPos)
        {    
            health = 10;
            damage = 10;
            speed = 120f;
            pointValue = 100;
            base.Initialize(animation, startPos);
        }

        public override void Update(GameTime gt)
        {
            float elapsedTime = (float)gt.ElapsedGameTime.TotalMilliseconds / 1000f;
            pos.X -= speed*elapsedTime;
            animation.Position = pos;
            animation.Update(gt);
            if (health <= 0) isActive = false;
        }

    }
}
