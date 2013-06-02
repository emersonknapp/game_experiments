using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using FuncWorks.XNA.XTiled;

namespace Robo
{
   /// <summary>
   /// This is the main type for your game
   /// </summary>
   public class RoboGame : Microsoft.Xna.Framework.Game
   {
      GraphicsDeviceManager graphics;
      SpriteBatch spriteBatch;
      Camera2D camera;

      int globalScale;

      Player player;
      Animation playerAnim;

      Rectangle mapView;

      //[ContentSerializer(SharedResource = true)]
      Map map;

      public RoboGame()
      {
         graphics = new GraphicsDeviceManager(this);
         Content.RootDirectory = "Content";
      }

      /// <summary>
      /// Allows the game to perform any initialization it needs to before starting to run.
      /// This is where it can query for any required services and load any non-graphic
      /// related content.  Calling base.Initialize will enumerate through any components
      /// and initialize them as well.
      /// </summary>
      protected override void Initialize()
      {
         player = new Player();

         camera = new Camera2D(player);
         camera.pos = new Vector2(500f, 200f);
         camera.zoom = 1f;

         globalScale = 1;
         Rectangle viewBounds = graphics.GraphicsDevice.Viewport.Bounds ;
         mapView = new Rectangle(0, 0, viewBounds.Width / globalScale, viewBounds.Height / globalScale);

         base.Initialize();
      }

      /// <summary>
      /// LoadContent will be called once per game and is the place to load
      /// all of your content.
      /// </summary>
      protected override void LoadContent()
      {
         // Create a new SpriteBatch, which can be used to draw textures.
         spriteBatch = new SpriteBatch(GraphicsDevice);
         map = Content.Load<Map>("planetcute");
         Animation playerAnim = new Animation();
         Texture2D playerTex = Content.Load<Texture2D>("mineAnimation");
         playerAnim.Initialize(playerTex, Vector2.Zero, 47, 61, 8, 30, Color.White, 1f, true);

         player.Initialize(playerAnim, Vector2.Zero);
      }

      /// <summary>
      /// UnloadContent will be called once per game and is the place to unload
      /// all content.
      /// </summary>
      protected override void UnloadContent()
      {
         // TODO: Unload any non ContentManager content here
      }

      /// <summary>
      /// Allows the game to run logic such as updating the world,
      /// checking for collisions, gathering input, and playing audio.
      /// </summary>
      /// <param name="gameTime">Provides a snapshot of timing values.</param>
      protected override void Update(GameTime gameTime)
      {
         KeyboardState keys = Keyboard.GetState();
         // Allows the game to exit
         if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed
             || keys.IsKeyDown(Keys.Escape))
            this.Exit();

         
         if (keys.IsKeyDown(Keys.Down))
            player.pos.Y += Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Up))
            player.pos.Y -= Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Right))
            player.pos.X += Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Left))
            player.pos.X -= Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         /*
         //Test camera movement
         Vector2 delta = Vector2.Zero;
         if (keys.IsKeyDown(Keys.Down))
            delta.Y += Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Up))
            delta.Y -= Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Right))
            delta.X += Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         if (keys.IsKeyDown(Keys.Left))
            delta.X -= Convert.ToInt32(gameTime.ElapsedGameTime.TotalMilliseconds / 4);
         camera.Move(delta);

         if (keys.IsKeyDown(Keys.H))
            camera.pos = Vector2.Zero;

         //Test camera rotation
         if (keys.IsKeyDown(Keys.Q))
            camera.rotation += 0.1f;
         if (keys.IsKeyDown(Keys.A))
            camera.rotation -= 0.1f;
         if (keys.IsKeyDown(Keys.Z))
            camera.rotation = 0;

         //Test camera zoom
         if (keys.IsKeyDown(Keys.W))
            camera.zoom += 0.1f;
         if (keys.IsKeyDown(Keys.S))
            camera.zoom -= 0.1f;
         if (keys.IsKeyDown(Keys.X))
            camera .zoom = 1.0f;
         */

         player.Update(gameTime);

         camera.Update(gameTime, GraphicsDevice, map);
         base.Update(gameTime);
      }

      /// <summary>
      /// This is called when the game should draw itself.
      /// </summary>
      /// <param name="gameTime">Provides a snapshot of timing values.</param>
      protected override void Draw(GameTime gameTime)
      {
         GraphicsDevice.Clear(Color.DarkOliveGreen);

         Matrix scaleAll = Matrix.CreateScale(globalScale);
         spriteBatch.Begin(SpriteSortMode.Deferred,
            BlendState.AlphaBlend,
            null,
            null,
            null,
            null,
            camera.get_transformation(graphics.GraphicsDevice));
         //Start Drawing Code
         map.Draw(spriteBatch, map.Bounds);
         player.Draw(spriteBatch);
         //End Drawing Code
         spriteBatch.End();

         base.Draw(gameTime);
      }
   }
}
