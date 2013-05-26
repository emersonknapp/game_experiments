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

namespace Shooter
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class ShooterGame : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        InputManager inputManager;

        Player player;

        int score;
        SpriteFont font;

        ParallaxBackground background;

        Texture2D enemyTexture;
        List<Enemy> enemies;

        TimeSpan enemySpawnTime;
        TimeSpan previousSpawnTime;

        Random random;

        Texture2D projectileTexture;
        List<Projectile> projectiles;
        TimeSpan fireTime;
        TimeSpan previousFireTime;

        Texture2D explosionTexture;
        List<Animation> explosions;

        SoundEffect laserSound;
        SoundEffect explosionSound;
        Song gameplayMusic;

        public ShooterGame()
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
            inputManager = new InputManager();

            player = new Player();

            score = 0;

            background = new ParallaxBackground();

            enemies = new List<Enemy>();
            previousSpawnTime = TimeSpan.Zero;
            enemySpawnTime = TimeSpan.FromSeconds(1f);

            random = new Random();

            projectiles = new List<Projectile>();
            fireTime = TimeSpan.FromSeconds(.25f);

            explosions = new List<Animation>();

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

            enemyTexture = Content.Load<Texture2D>("mineAnimation");

            projectileTexture = Content.Load<Texture2D>("laser");

            explosionTexture = Content.Load<Texture2D>("explosion");

            font = Content.Load<SpriteFont>("gameFont");

            Dictionary<string, int> movingBackgrounds = new Dictionary<string,int>()
            {
                {"bgLayer1", -1},
                {"bgLayer2", -2}
            };
            background.Initialize(Content, "mainbackground", movingBackgrounds, GraphicsDevice.Viewport.Width);

            gameplayMusic = Content.Load<Song>("sound/gameMusic");
            laserSound = Content.Load<SoundEffect>("sound/laserFire");
            explosionSound = Content.Load<SoundEffect>("sound/explosion");
            PlayMusic(gameplayMusic);
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        private void AddEnemy()
        {
            Animation enemyAnimation = new Animation();
            enemyAnimation.Initialize(enemyTexture, Vector2.Zero, 47, 61, 8, 30, Color.White, 1f, true);
            Vector2 position = new Vector2(GraphicsDevice.Viewport.Width + enemyTexture.Width / 2, random.Next(100, GraphicsDevice.Viewport.Height - 100));
            Enemy enemy = new Enemy();
            enemy.Initialize(enemyAnimation, position);
            enemies.Add(enemy);
        }

        private void AddProjectile(Vector2 position)
        {
            Projectile pro = new Projectile();
            pro.Initialize(projectileTexture, position);
            projectiles.Add(pro);
            laserSound.Play();
        }

        private void AddExplosion(Vector2 position)
        {
            Animation explosion = new Animation();
            explosion.Initialize(explosionTexture, position, 134, 134, 12, 45, Color.White, 1f, false);
            explosions.Add(explosion);
            explosionSound.Play(0.1f, 0.0f, 0.0f);
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {

            inputManager.Update(player);
            if (inputManager.QuitRequested())
            {
                this.Exit();
            }

            background.Update();

            UpdatePlayer(gameTime);
            UpdateEnemies(gameTime);
            UpdateProjectiles(gameTime);
            UpdateExplosions(gameTime);

            UpdateCollision();

            base.Update(gameTime);
        }

        private void UpdatePlayer(GameTime gameTime)
        {
            player.Update(gameTime);

            if (gameTime.TotalGameTime - previousFireTime > fireTime)
            {
                previousFireTime = gameTime.TotalGameTime;

                AddProjectile(player.pos + new Vector2(player.width / 2, 0));
            }

            if (player.health <= 0)
            {
                player.health = 100;
                score = 0;
            }
        }

        private void UpdateEnemies(GameTime gameTime)
        {
            if (gameTime.TotalGameTime - previousSpawnTime > enemySpawnTime)
            {
                previousSpawnTime = gameTime.TotalGameTime;
                AddEnemy();
            }
            for (int i = enemies.Count-1; i >= 0; i--)
            {
                enemies[i].Update(gameTime);
                if (!enemies[i].isActive)
                {
                    if (enemies[i].health <= 0)
                    {
                        AddExplosion(enemies[i].pos);
                        score += enemies[i].pointValue;
                    }
                    enemies.RemoveAt(i);
                }
            }
        }

        private void UpdateProjectiles(GameTime gt)
        {
            for (int i = projectiles.Count-1; i >= 0; i--)
            {
                projectiles[i].Update(gt);
                if (!projectiles[i].isActive) projectiles.RemoveAt(i);
            }
        }

        private void UpdateExplosions(GameTime gt)
        {
            for (int i = explosions.Count - 1; i >= 0; i--)
            {
                explosions[i].Update(gt);
                if (!explosions[i].Active)
                {
                    explosions.RemoveAt(i);
                }
            }
        }

        private void UpdateCollision()
        {
            //Bounds-checking
            // Make sure that the player does not go out of bounds
            player.pos.X = MathHelper.Clamp(player.pos.X, 0, GraphicsDevice.Viewport.Width - player.width);
            player.pos.Y = MathHelper.Clamp(player.pos.Y, 0, GraphicsDevice.Viewport.Height - player.height);


            //Collision testing
            Rectangle rect1;
            Rectangle rect2;

            rect1 = new Rectangle((int)player.pos.X, (int)player.pos.Y, player.width, player.height);

            foreach (Enemy e in enemies)
            {
                rect2 = new Rectangle((int)e.pos.X, (int)e.pos.Y, e.width, e.height);
                if (rect1.Intersects(rect2))
                {
                    player.health -= e.damage;
                    e.health = 0;
                    if (player.health <= 0) player.isActive = false;
                }
                if (e.pos.X < -e.width)
                {
                    e.isActive = false;
                    score -= e.pointValue;
                }
            }
            foreach (Projectile p in projectiles)
            {
                if (p.pos.X + p.texture.Width / 2 > GraphicsDevice.Viewport.Width) p.isActive = false;
                foreach (Enemy e in enemies)
                {
                    rect1 = new Rectangle((int)p.pos.X - p.width / 2, (int)p.pos.Y - p.height / 2, p.width, p.height);
                    rect2 = new Rectangle((int)e.pos.X - e.width / 2, (int)e.pos.Y - e.height / 2, e.width, e.height);
                    if (rect1.Intersects(rect2))
                    {
                        e.health -= p.damage;
                        p.isActive = false;
                    }
                    
                }
            }
        }
        private void DrawText(SpriteBatch sb, String text, Vector2 pos, Color color)
        {
            Vector2 actualPos = new Vector2(GraphicsDevice.Viewport.TitleSafeArea.X, GraphicsDevice.Viewport.TitleSafeArea.Y) + pos;
            sb.DrawString(font, text, actualPos, color);
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

            background.Draw(spriteBatch);

            foreach (Enemy e in enemies)
            {
                e.Draw(spriteBatch);
            }
            foreach (Projectile p in projectiles)
            {
                p.Draw(spriteBatch);
            }

            player.Draw(spriteBatch);

            foreach (Animation e in explosions)
            {
                e.Draw(spriteBatch);
            }

            DrawText(spriteBatch, "Score: " + score, new Vector2(0,0), Color.White);
            DrawText(spriteBatch, "Health: " + player.health, new Vector2(0, 30), Color.White);

            //End Drawing code
            spriteBatch.End();
     
            base.Draw(gameTime);
        }

        private void PlayMusic(Song song)
        {
            try
            {
                MediaPlayer.Play(song);
                MediaPlayer.IsRepeating = true;
            }
            catch { }
        }



    }
}
