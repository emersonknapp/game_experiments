using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Shooter
{
    class MovingBackground
    {
        Texture2D texture;
        Vector2[] positions;
        int speed;

        public MovingBackground(Texture2D texture, int screenWidth, int speed)
        {
            this.texture = texture;
            this.speed = speed;
            positions = new Vector2[screenWidth / texture.Width + 1];
            for (int i = 0; i < positions.Length; i++)
            {
                positions[i] = new Vector2(i * texture.Width, 0);
            }
        }

        public void Update()
        {
            for (int i = 0; i < positions.Length; i++)
            {
                positions[i].X += speed;
                if (speed <= 0)
                {
                    if (positions[i].X <= -texture.Width)
                    {
                        positions[i].X = texture.Width * (positions.Length - 1);
                    }
                }
                else
                {
                    if (positions[i].X >= texture.Width * (positions.Length - 1))
                    {
                        positions[i].X = -texture.Width;
                    }
                }
            }

        }
        public void Draw(SpriteBatch sb)
        {
            for (int i = 0; i < positions.Length; i++)
            {
                sb.Draw(texture, positions[i], Color.White);
            }
        }
    }

    class ParallaxBackground
    {
        Texture2D staticLayer;
        List<MovingBackground> movingLayers;
        public void Initialize(ContentManager content, String staticTexturePath, Dictionary<String, int> movingTextures, int screenWidth)
        {
            staticLayer = content.Load<Texture2D>(staticTexturePath);
            movingLayers = new List<MovingBackground>();
            foreach (KeyValuePair<string, int> kvp in movingTextures)
            {
                movingLayers.Add(new MovingBackground(content.Load<Texture2D>(kvp.Key), screenWidth, kvp.Value));
            }

        }

        public void Update()
        {
            foreach (MovingBackground bglayer in movingLayers)
            {
                bglayer.Update();
            }
        }

        public void Draw(SpriteBatch sb)
        {
            sb.Draw(staticLayer, Vector2.Zero, Color.White);
            foreach (MovingBackground bglayer in movingLayers)
            {
                bglayer.Draw(sb);
            }
        }

    }
}
