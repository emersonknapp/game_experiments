using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Media;


namespace Robo
{
   /// <summary>
   /// This is a game component that implements IUpdateable.
   /// </summary>
   public class Level : Microsoft.Xna.Framework.DrawableGameComponent
   {
      public Level(Game game)
         : base(game)
      {
         // TODO: Construct any child components here
      }

      /// <summary>
      /// Allows the game component to perform any initialization it needs to before starting
      /// to run.  This is where it can query for any required services and load content.
      /// </summary>
      public override void Initialize()
      {
         // TODO: Add your initialization code here

         base.Initialize();
      }

      /// <summary>
      /// Allows the game component to update itself.
      /// </summary>
      /// <param name="gameTime">Provides a snapshot of timing values.</param>
      public override void Update(GameTime gameTime)
      {
         // TODO: Add your update code here

         base.Update(gameTime);
      }

      public override void Draw(GameTime gameTime)
      {
         //TODO: Add drawing code here
         base.Draw(gameTime);
      }
   }
}
