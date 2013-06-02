using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Robo
{
    abstract class Sprite
    {
        public bool isAnimated;
        public bool isInitialized;
        public bool isActive;

        public Vector2 pos;

        protected virtual void Initialize(Vector2 startPos)
        {
            if (isInitialized) throw new InvalidOperationException("Sprite has already been initialized!");
            isActive = true;
            isInitialized = true;
            pos = startPos;
        }

        public abstract void Update(GameTime gt);
        public abstract void Draw(SpriteBatch sb);
    }

    abstract class StaticSprite : Sprite
    {
        public Texture2D texture;

        public int width
        {
            get { return texture.Width; }
        }
        public int height
        {
            get { return texture.Height; }
        }
        public virtual void Initialize(Texture2D texture, Vector2 startPos)
        {
            base.Initialize(startPos);
            isAnimated = false;
            this.texture = texture;
        }
        public override void Draw(SpriteBatch sb)
        {
            sb.Draw(texture, pos, null, Color.White, 0f, new Vector2(width / 2, height / 2), 1f, SpriteEffects.None, 0f);
        }
    }

    abstract class AnimatedSprite : Sprite
    {
        public Animation animation;

        public int width
        {
            get { return animation.FrameWidth; }
        }
        public int height
        {
            get { return animation.FrameHeight; }
        }
        public virtual void Initialize(Animation animation, Vector2 startPos)
        {
            base.Initialize(startPos);
            isAnimated = true;
            this.animation = animation;
        }
        public override void Update(GameTime gt)
        {
           animation.Position = pos;
           animation.Update(gt);
        }
        public override void Draw(SpriteBatch sb)
        {
            animation.Draw(sb);
        }
    }
}
