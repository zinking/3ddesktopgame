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
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace _3DGame
{
  
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        #region Fields

        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        KeyboardState currentKeyboardState = new KeyboardState();
        GamePadState currentGamePadState = new GamePadState();

        Vector3 cameraPosition = new Vector3(1000, 1000, 1000);
        Vector3 cameraFront = new Vector3(-1, -1, -1);

        Model tableModel;
        Model groundModel;
        Model[] balls ;
        
        #endregion

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            graphics.PreferredBackBufferWidth = 800;
            graphics.PreferredBackBufferHeight = 600;
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here

            base.Initialize();
        }

        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            tableModel = Content.Load<Model>("models/table");
            //groundModel = Content.Load<Model>("models/Ground");
            this.balls = new Model[10];
            for (int i = 0; i < balls.Length; ++i)
            {
                balls[i] = Content.Load<Model>("models/ball"+i);
            }
        }

        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

    
        protected override void Update(GameTime gameTime)
        {
            this.HandleInput();
            this.checkReset();
            this.UpdateCamera(gameTime);
            
            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            // TODO: Add your drawing code here
            Matrix view = Matrix.CreateLookAt(cameraPosition,
                                             cameraPosition + cameraFront,
                                             Vector3.Up);

            float aspectRatio = GraphicsDevice.Viewport.AspectRatio;

            Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4,
                                                                    aspectRatio,
                                                                    0.1f, 10000);

            DrawModel(tableModel, Matrix.Identity, view, projection);

            for (int i = 0; i < balls.Length; ++i)
            {
                Matrix m = Matrix.Identity;
               // m.Translation = new Vector3(0,55,0);
                m.Translation = this.getTranslationVector(i);
                DrawModel(balls[i], m, view, projection);
            }

            base.Draw(gameTime);
        }

        private Vector3 getTranslationVector(int ballNum)
        {
            int height = 55, diameter = 30;
            float sqrttwo = (float)System.Math.Sqrt(2);

            if (ballNum >= balls.Length)
                return new Vector3(0,height,0);

            switch (ballNum)
            {
                case 0:
                    return new Vector3(-300, height, 0);
                    break;
                case 1:
                    return new Vector3(200, height, 0);
                    break;
                case 2:
                    return new Vector3(200 + diameter /sqrttwo , height, -diameter / sqrttwo );
                    break;
                case 3:
                    return new Vector3(200 + diameter /sqrttwo , height, diameter / sqrttwo );
                    break;
                case 4:
                    return new Vector3(200 + diameter / sqrttwo*2, height, -diameter / sqrttwo*2);
                    break;
                case 5:
                    return new Vector3(200 + diameter / sqrttwo*2, height, diameter / sqrttwo*2);
                    break;
                case 6:
                    return new Vector3(200 + diameter / sqrttwo * 3, height, -diameter / sqrttwo );
                    break;
                case 7:
                    return new Vector3(200 + diameter / sqrttwo * 3, height, diameter / sqrttwo );
                    break;
                case 8:
                    return new Vector3(200 + diameter / sqrttwo * 4, height, 0);
                    break;
                case 9:
                    return new Vector3(200 + diameter/sqrttwo*2, height, 0);
                    break;
                default:
                    return new Vector3(0, height, 0);
            }

        }

        private void HandleInput()
        {
            currentKeyboardState = Keyboard.GetState();
            //currentGamePadState = GamePad.GetState(PlayerIndex.One);


            if (currentKeyboardState.IsKeyDown(Keys.Escape))
            {
                Exit();
            }
        }

        private void UpdateCamera(GameTime gameTime)
        {
            float time = (float)gameTime.ElapsedGameTime.TotalMilliseconds;

            float pitch = 0, turn = 0;

            if (currentKeyboardState.IsKeyDown(Keys.Up))
                pitch += time * 0.001f;
            if (currentKeyboardState.IsKeyDown(Keys.Down))
                pitch -= time * 0.001f;
            if (currentKeyboardState.IsKeyDown(Keys.Left))
                turn += time * 0.001f;
            if (currentKeyboardState.IsKeyDown(Keys.Right))
                turn -= time * 0.001f;

            Vector3 cameraRight = Vector3.Cross(Vector3.Up, cameraFront);
            Vector3 flatFront = Vector3.Cross(cameraRight, Vector3.Up);

            Matrix pitchMatrix = Matrix.CreateFromAxisAngle(cameraRight, pitch);
            Matrix turnMatrix = Matrix.CreateFromAxisAngle(Vector3.Up, turn);

            Vector3 tiltedFront = Vector3.TransformNormal(cameraFront, pitchMatrix *
                                                          turnMatrix);

            // Check angle so we can't flip over.
            if (Vector3.Dot(tiltedFront, flatFront) > 0.001f)
            {
                cameraFront = Vector3.Normalize(tiltedFront);
            }

            // Check for input to move the camera around.
            if (currentKeyboardState.IsKeyDown(Keys.W))
                cameraPosition += cameraFront * time * 0.1f;

            if (currentKeyboardState.IsKeyDown(Keys.S))
                cameraPosition -= cameraFront * time * 0.1f;

            if (currentKeyboardState.IsKeyDown(Keys.A))
                cameraPosition += cameraRight * time * 0.1f;

            if (currentKeyboardState.IsKeyDown(Keys.D))
                cameraPosition -= cameraRight * time * 0.1f;
        }

        private void checkReset()
        {
            if (this.currentKeyboardState.IsKeyDown(Keys.R))
            {
                Vector3 cameraPosition = new Vector3(500, 500, 500);
                Vector3 cameraFront = new Vector3(1, -1, 0);
            }
        }

        private void DrawModel(Model model, Matrix world, Matrix view, Matrix projection)
        {
            Matrix[] transforms = new Matrix[model.Bones.Count];
            model.CopyAbsoluteBoneTransformsTo(transforms);

            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = true;
                    effect.World = transforms[mesh.ParentBone.Index] * world;

                    // Use the matrices provided by the chase camera
                    effect.View = view;
                    effect.Projection = projection;
                }
                mesh.Draw();
            }
        }
    }
}
