using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Robo
{
   class Constants
   {
      public static int totalUpdates = 0;
      public static float eps = 0.001f;
      public static String windowTitle = "Jumper.";
      public static Vector2 windowSize = new Vector2(1150f, 860f);

      public static float gravity = 1000f;
      
      public static string staticBackgroundName = "ocean-wallpaper";
      public static String startMapName = "cuteplat";

      public static float playerSpeed = 400f;
      public static float playerJumpSpeed = 500f;
      public static Vector2 playerStartPos = new Vector2(400f, 500f);

   }
}
