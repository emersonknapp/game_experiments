using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using FuncWorks.XNA.XTiled;

namespace Robo
{
   class Camera2D
   {
      protected float _zoom;
      protected Matrix _transform;
      protected Vector2 _pos;

      protected bool fixedX;
      protected bool fixedY;

      protected bool isFollowingSprite;
      protected Sprite sprite;

      public Camera2D()
      {
         _zoom = 1f;
         _pos = Vector2.Zero;
         isFollowingSprite = false;
      }
      public Camera2D(Sprite follow)
      {
         isFollowingSprite = true;
         sprite = follow;
      }

      public float zoom
      {
         get {return _zoom;}
         set {_zoom = value; if (_zoom <0.1f) _zoom = 0.1f; }
      }

      public void Move(Vector2 amount)
      {
         _pos += amount;
      }
      public Vector2 pos
      {
         get { return _pos; }
         set { _pos = value; }
      }

      public void fixX(float x)
      {
         fixedX = true;
         _pos.X = x;
      }
      public void fixY(float y)
      {
         fixedY = true;
         _pos.Y = y;
      }
      public void freeX()
      {
         fixedX = false;
      }
      public void freeY()
      {
         fixedY = false;
      }

      public Matrix get_transformation(GraphicsDevice graphicsDevice)
      {
         Viewport vp = graphicsDevice.Viewport;
         _transform =     
               Matrix.CreateTranslation(new Vector3(-_pos.X, -_pos.Y, 0)) *
               Matrix.CreateScale(new Vector3(zoom, zoom, 1)) *
               Matrix.CreateTranslation(new Vector3(vp.Width * 0.5f, vp.Height * 0.5f, 0));
         return _transform;
      }

      public Vector2 getTopLeft(Viewport vp)
      {
         return new Vector2(pos.X - vp.Width / 2, pos.Y - vp.Height / 2);

      }

      public void Update(GameTime gt, GraphicsDevice graphicsDevice, Map m)
      {
         //Do not display beyond the edge of the map
         Viewport vp = graphicsDevice.Viewport;
         float minX = m.Bounds.X+(vp.Width*0.5f);
         float minY = m.Bounds.Y+(vp.Height*0.5f);
         float maxX = m.Bounds.X+m.Bounds.Width-(vp.Width*0.5f);
         float maxY = m.Bounds.Y+m.Bounds.Height-(vp.Height*0.5f);

         //Following the sprite
         if (isFollowingSprite)
         {
            Vector2 newPos = pos;
            if (!fixedX)
               newPos.X = MathHelper.Clamp(sprite.pos.X, minX, maxX);
            if (!fixedY)
               newPos.Y = MathHelper.Clamp(sprite.pos.Y, minY, maxY);

            pos = newPos;
         }
      }
   }
}
