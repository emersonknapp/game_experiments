using System;

namespace Robo
{
#if WINDOWS || XBOX
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            using (RoboGame game = new RoboGame())
            {
                game.Run();
            }
        }
    }
#endif
}

