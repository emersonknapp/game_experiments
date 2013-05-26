using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Shooter
{
    class Animation
    {
        Texture2D spriteStrip;
        float scale;
        int elapsedTime;
        int frameTime;
        int frameCount;
        int currentFrame;
        Color color;
        Rectangle sourceRect = new Rectangle();
        Rectangle destinationRect = new Rectangle();
        public int FrameWidth;
        public int FrameHeight;
        public bool Active;
        public bool Looping;
        public Vector2 Position;

        public void Initialize(Texture2D texture, Vector2 position,
            int frameWidth, int frameHeight, int frameCount, 
            int frametime, Color color, float scale, bool looping)
        {
            this.color = color;
            this.FrameWidth = frameWidth;
            this.FrameHeight = frameHeight;
            this.frameCount = frameCount;
            this.frameTime = frametime;
            this.scale = scale;

            Looping = looping;
            Position = position;
            spriteStrip = texture;

            elapsedTime = 0;
            currentFrame = 0;

            Active = true;
        }
        public void Update(GameTime gameTime)
        {
            if (!Active) return;

            elapsedTime += (int)gameTime.ElapsedGameTime.TotalMilliseconds;

            if (elapsedTime > frameTime)
            {
                currentFrame++;
                if (currentFrame >= frameCount && !Looping)
                {
                    Active = false;
                    return;
                }
                currentFrame %= frameCount;
                elapsedTime -= frameTime;
            }

            sourceRect = new Rectangle(currentFrame * FrameWidth, 0, FrameWidth, FrameHeight);
            
            int topleftx = (int)Position.X - (int)(FrameWidth*scale) / 2;
            int toplefty = (int)Position.Y-(int)(FrameHeight*scale)/2;
            int width = (int)(FrameWidth*scale);
            int height = (int)(FrameHeight*scale);
            destinationRect = new Rectangle(topleftx, toplefty, width, height);
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            if (Active)
                spriteBatch.Draw(this.spriteStrip, this.destinationRect, this.sourceRect, this.color);
        }
    }
}
