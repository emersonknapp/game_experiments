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
      protected float _rotation;

      protected bool isFollowingSprite;
      protected Sprite sprite;

      public Camera2D()
      {
         _zoom = 1f;
         _rotation = 0f;
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

      public float rotation
      {
         get { return _rotation; }
         set { _rotation = value; }
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

      public Matrix get_transformation(GraphicsDevice graphicsDevice)
      {
         Viewport vp = graphicsDevice.Viewport;
         _transform =     
               Matrix.CreateTranslation(new Vector3(-_pos.X, -_pos.Y, 0)) *
               Matrix.CreateRotationZ(rotation) *
               Matrix.CreateScale(new Vector3(zoom, zoom, 1)) *
               Matrix.CreateTranslation(new Vector3(vp.Width * 0.5f, vp.Height * 0.5f, 0));
         return _transform;
      }

      public void Update(GameTime gt, GraphicsDevice graphicsDevice, Map m)
      {
         //Do not display beyond the edge of the map
         Viewport vp = graphicsDevice.Viewport;
         float minX = m.Bounds.X+(vp.Width*0.5f);
         float minY = m.Bounds.Y+(vp.Height*0.5f);
         float maxX = m.Bounds.X+m.Bounds.Width-(vp.Width*0.5f);
         float maxY = m.Bounds.Y+m.Bounds.Height-(vp.Height*0.5f);

         Vector2 newPos = pos;
         newPos.X = MathHelper.Clamp(sprite.pos.X, minX, maxX);
         newPos.Y = MathHelper.Clamp(sprite.pos.Y, minY, maxY);

         pos = newPos;

      }
   }
}
