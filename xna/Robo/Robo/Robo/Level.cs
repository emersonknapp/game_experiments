using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Media;
using FuncWorks.XNA.XTiled;


namespace Robo
{
   /// <summary>
   /// This is a game component that implements IUpdateable.
   /// </summary>
   class Level
   {
      public Map map;
      public Rectangle mapView;
      public int collisionLayer;
      public int deathLayer;
      public int objectiveLayer;

      public Level(Game game)
      {
         Map.InitObjectDrawing(game.GraphicsDevice);
            
         // TODO: Construct any child components here
      }

      /// <summary>
      /// Allows the game component to perform any initialization it needs to before starting
      /// to run.  This is where it can query for any required services and load content.
      /// </summary>
      public void Initialize(Rectangle viewBounds, Map map)
      {
         this.map = map;
         mapView = new Rectangle(0, 0, viewBounds.Width, viewBounds.Height);

         for (int i = 0; i < map.ObjectLayers.Count; i++)
         {
            switch (map.ObjectLayers[i].Name)
            {
               case "Collision":
                  collisionLayer = i;
                  break;
               case "Death":
                  deathLayer = i;
                  break;
               case "Objective":
                  objectiveLayer = i;
                  break;
               default:
                  break;
            }
         }

      }


      /// <summary>
      /// Allows the game component to update itself.
      /// </summary>
      /// <param name="gameTime">Provides a snapshot of timing values.</param>
      public void Update(GameTime gameTime)
      {

      }

      public void Draw(GameTime gameTime, SpriteBatch sb, Player player)
      {
         Single depth = 0;
         for (int i = 0; i < map.LayerOrder.Length; i++)
         {
            LayerInfo li = map.LayerOrder[i];
            if (li.LayerType == LayerType.TileLayer)
               map.DrawLayer(sb, map.LayerOrder[i].ID, map.Bounds, depth);
            if (li.LayerType == LayerType.ObjectLayer)
               map.DrawObjectLayer(sb, map.LayerOrder[i].ID, map.Bounds, depth);

         }

         //map.DrawObjectLayer(sb, 0, map.Bounds, 0);
      }
   }
}
