using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Input.Touch;
using Microsoft.Xna.Framework.Media;

namespace Shooter
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Player player;

        KeyboardState currentKeyboardState;
        KeyboardState previousKeyboardState;
        GamePadState currentGamePadState;
        GamePadState previousGamePadState;

        SpriteFont font;

        float playerMoveSpeed;

        Texture2D staticBackground;
        ParallaxBackground bgLayer1;
        ParallaxBackground bgLayer2;

        public Game1()
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
            playerMoveSpeed = 8.0f;
            TouchPanel.EnabledGestures = GestureType.FreeDrag;

            bgLayer1 = new ParallaxBackground();
            bgLayer2 = new ParallaxBackground();
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

            Animation playerAnim = new Animation();
            Texture2D playerTex = Content.Load<Texture2D>("shipAnimation");
            playerAnim.Initialize(playerTex, Vector2.Zero, 115, 69, 8, 30, Color.White, 1f, true);

            Rectangle tsa = GraphicsDevice.Viewport.TitleSafeArea;
            Vector2 playerPosition = new Vector2(tsa.X, tsa.Y + tsa.Height / 2);

            player.Initialize(playerAnim, playerPosition);

            font = Content.Load<SpriteFont>("font1");

            bgLayer1.Initialize(Content, "bgLayer1", GraphicsDevice.Viewport.Width, -1);
            bgLayer2.Initialize(Content, "bgLayer2", GraphicsDevice.Viewport.Width, -2);
            staticBackground = Content.Load<Texture2D>("mainbackground");
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
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            previousGamePadState = currentGamePadState;
            previousKeyboardState = currentKeyboardState;
            currentGamePadState = GamePad.GetState(PlayerIndex.One);
            currentKeyboardState = Keyboard.GetState();

            if (currentGamePadState.Buttons.Back == ButtonState.Pressed ||
                currentKeyboardState.GetPressedKeys().Contains(Keys.Escape))
                this.Exit();

            UpdatePlayer(gameTime);
            bgLayer1.Update();
            bgLayer2.Update();

            base.Update(gameTime);
        }

        private void UpdatePlayer(GameTime gameTime)
        {
            player.Update(gameTime);
            // Get Thumbstick Controls
            player.pos.X += currentGamePadState.ThumbSticks.Left.X * playerMoveSpeed;
            player.pos.Y -= currentGamePadState.ThumbSticks.Left.Y * playerMoveSpeed;

            // Use the Keyboard / Dpad
            if (currentKeyboardState.IsKeyDown(Keys.Left) ||
            currentGamePadState.DPad.Left == ButtonState.Pressed)
            {
                player.pos.X -= playerMoveSpeed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Right) ||
            currentGamePadState.DPad.Right == ButtonState.Pressed)
            {
                player.pos.X += playerMoveSpeed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Up) ||
            currentGamePadState.DPad.Up == ButtonState.Pressed)
            {
                player.pos.Y -= playerMoveSpeed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Down) ||
            currentGamePadState.DPad.Down == ButtonState.Pressed)
            {
                player.pos.Y += playerMoveSpeed;
            }

            // Make sure that the player does not go out of bounds
            player.pos.X = MathHelper.Clamp(player.pos.X, 0, GraphicsDevice.Viewport.Width - player.width);
            player.pos.Y = MathHelper.Clamp(player.pos.Y, 0, GraphicsDevice.Viewport.Height - player.height);
        }

        private void DrawText(SpriteBatch sb)
        {
            sb.DrawString(font, "This is text.", new Vector2(20, 45), Color.Green);
        }
        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();
            //Drawing code here
            spriteBatch.Draw(staticBackground, Vector2.Zero, Color.White);
            bgLayer1.Draw(spriteBatch);
            bgLayer2.Draw(spriteBatch);
            player.Draw(spriteBatch);
            DrawText(spriteBatch);


            //End Drawing code
            spriteBatch.End();
     
            

            base.Draw(gameTime);
        }


    }
}
