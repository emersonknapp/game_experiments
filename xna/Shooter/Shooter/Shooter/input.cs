using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Shooter
{
    class InputManager
    {
        KeyboardState currentKeyboardState;
        KeyboardState previousKeyboardState;
        GamePadState currentGamePadState;
        GamePadState previousGamePadState;

        private bool quitRequested;

        public InputManager()
        {
            quitRequested = false;
        }

        public void Update(Player player)
        {
            previousGamePadState = currentGamePadState;
            previousKeyboardState = currentKeyboardState;
            currentGamePadState = GamePad.GetState(PlayerIndex.One);
            currentKeyboardState = Keyboard.GetState();

            if (currentGamePadState.Buttons.Back == ButtonState.Pressed ||
                currentKeyboardState.IsKeyDown(Keys.Escape))
            {
                quitRequested = true;
                return;
            }

            ///For now, the inputmanager can know about and directly update the player, considering the simplicity of this game.
            // Get Thumbstick Controls
            player.pos.X += currentGamePadState.ThumbSticks.Left.X * player.speed;
            player.pos.Y -= currentGamePadState.ThumbSticks.Left.Y * player.speed;

            // Use the Keyboard / Dpad
            if (currentKeyboardState.IsKeyDown(Keys.Left) ||
            currentGamePadState.DPad.Left == ButtonState.Pressed)
            {
                player.pos.X -= player.speed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Right) ||
            currentGamePadState.DPad.Right == ButtonState.Pressed)
            {
                player.pos.X += player.speed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Up) ||
            currentGamePadState.DPad.Up == ButtonState.Pressed)
            {
                player.pos.Y -= player.speed;
            }
            if (currentKeyboardState.IsKeyDown(Keys.Down) ||
            currentGamePadState.DPad.Down == ButtonState.Pressed)
            {
                player.pos.Y += player.speed;
            }
        }

        public bool QuitRequested()
        {
            return quitRequested;
        }
    }
}
