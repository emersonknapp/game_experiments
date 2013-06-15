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
      Physics physics;

      Player player;
      Animation playerAnim;

      KeyboardState currentKeyboardState;
      KeyboardState previousKeyboardState;

      Level currentLevel;
      ParallaxBackground background;



      public RoboGame()
      {
         graphics = new GraphicsDeviceManager(this);
         graphics.PreferredBackBufferHeight = (int)Constants.windowSize.Y;
         graphics.PreferredBackBufferWidth = (int)Constants.windowSize.X;
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
         physics = new Physics();
         player = new Player();

         currentKeyboardState = new KeyboardState();
         previousKeyboardState = new KeyboardState();

         camera = new Camera2D(player);
         camera.pos = new Vector2(500f, 200f);
         camera.zoom = 1f;
         camera.fixY(450f);

         background = new ParallaxBackground();
         currentLevel = new Level(this);

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

         Util.pixel = new Texture2D(graphics.GraphicsDevice, 1, 1, false, SurfaceFormat.Color);
         Util.pixel.SetData(new[] { Color.White });

         currentLevel.Initialize(graphics.GraphicsDevice.Viewport.Bounds, Content.Load<Map>(Constants.startMapName));
         background.Initialize(Content, Constants.staticBackgroundName, new Dictionary<string, int>(), currentLevel.map.Width);
         Animation playerAnim = new Animation();
         Texture2D playerTex = Content.Load<Texture2D>("square");
         playerAnim.Initialize(playerTex, Vector2.Zero, 58, 60, 1, 30, Color.White, 1f, true);

         player.Initialize(playerAnim, Constants.playerStartPos);
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
         currentKeyboardState = Keyboard.GetState();
         // Allows the game to exit
         if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed
             || currentKeyboardState.IsKeyDown(Keys.Escape))
            this.Exit();

         List<Keys> keyDowns = new List<Keys>();
         List<Keys> keyUps = new List<Keys>();

         foreach (var k in currentKeyboardState.GetPressedKeys())
         {
            if (!previousKeyboardState.IsKeyDown(k))
               keyDowns.Add(k); 
         }
         foreach (var k in previousKeyboardState.GetPressedKeys())
         {
            if (!currentKeyboardState.IsKeyDown(k))
               keyUps.Add(k);
         }

         foreach (Keys k in keyDowns)
         {
            switch (k)
            {
               case Keys.Left:
                  player.velocity.X -= Constants.playerSpeed;
                  break;
               case Keys.Right:
                  player.velocity.X += Constants.playerSpeed;
                  break;
               case Keys.Up:
                  //if (player.grounded)
                  //{
                     player.velocity.Y -= Constants.playerJumpSpeed;
                     player.grounded = false;
                  //}
                  break;
               //case Keys.Down:
               //   player.velocity.Y += Constants.playerSpeed;
               //   break;
               default:
                  break;
            }
         }
         foreach (Keys k in keyUps)
         {
            switch (k)
            {
               case Keys.Left:
                  player.velocity.X += Constants.playerSpeed;
                  break;
               case Keys.Right:
                  player.velocity.X -= Constants.playerSpeed;
                  break;
               //case Keys.Up:
               //   player.velocity.Y += Constants.playerSpeed;
               //   break;
               //case Keys.Down:
               //   player.velocity.Y -= Constants.playerSpeed;
               //   break;
               default:
                  break;
            }
         }

         background.Update();

         player.Update(gameTime);
         physics.Apply(gameTime, player, currentLevel);

         camera.Update(gameTime, GraphicsDevice, currentLevel.map);

         previousKeyboardState = currentKeyboardState;
         base.Update(gameTime);
         Constants.totalUpdates++;
      }


      /// <summary>
      /// This is called when the game should draw itself.
      /// </summary>
      /// <param name="gameTime">Provides a snapshot of timing values.</param>
      protected override void Draw(GameTime gameTime)
      {
         GraphicsDevice.Clear(Color.DarkOliveGreen);

         spriteBatch.Begin(SpriteSortMode.Deferred,
            BlendState.AlphaBlend,
            null,
            null,
            null,
            null,
            camera.get_transformation(graphics.GraphicsDevice));
         //Start Drawing Code
         background.Draw(spriteBatch, camera.getTopLeft(graphics.GraphicsDevice.Viewport)+new Vector2(0f, -300f));
         currentLevel.Draw(gameTime, spriteBatch, player);
         player.Draw(spriteBatch);
         Util.DrawHollowRect(player.collision.rect, 5, Color.Red, spriteBatch);
         
         //End Drawing Code
         spriteBatch.End();

         base.Draw(gameTime);
      }
   }
}
