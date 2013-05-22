using System;
using Microsoft.Xna.Framework;

using Microsoft.Xna.Framework.Graphics;


namespace Shooter
{
	class Player
	{
        public Texture2D texture;
        public Vector2 pos;
        public Animation anim;
        public bool active;
        public int health;
        public int width 
        {
            get { return anim.FrameWidth; }
        }
        public int height
        {
            get { return anim.FrameHeight;  }
        }

        public void Initialize(Animation animation, Vector2 aposition)
        {
            anim = animation;
            pos = aposition;
            active = true;
            health = 100;
        }
        public void Update(GameTime cgameTime)
        {
            anim.Position = pos;
            anim.Update(cgameTime);
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            this.anim.Draw(spriteBatch);
        }
	}
}
