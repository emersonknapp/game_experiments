using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Shooter
{
    class Projectile : StaticSprite
    {
        public int damage;
        float speed;

        public override void Initialize(Texture2D texture, Vector2 position)
        {
            damage = 4;
            speed = 480f;
            base.Initialize(texture, position);
        }

        public override void Update(GameTime gt)
        {
            float elapsedTime = (float)gt.ElapsedGameTime.TotalMilliseconds / 1000f;
            pos.X += speed*elapsedTime;
        }

    }
}
