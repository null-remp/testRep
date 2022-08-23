{$reference FreeGlut.dll}
{$reference OpenGl.dll}

uses
  System, System.Collections.Generic, System.Linq, System.Text,
  OpenGl, FreeGlut;
  
const 
  width = 680;
  height = 480;
  
  key_w = 119;
  key_s = 115;
  key_a = 97;
  key_d = 100;
  key_esc = 127;
  
  step: integer = 20;
  
  _TEMP: Integer = 3;
  
type
  Direction = (UP, DOWN, LEFT, RIGHT); 

  Snake = record 
    posX: integer;
    posY: integer;
  end;  
  
  Apple = record 
    posX: integer;
    posY: integer;
    
    color: string;
    visible: boolean;
  end;
  
var
  points: integer := 0;
  _TIME_GAME_: integer := 250;
  vectorSnake: Direction := UP;
  countSnake: integer := 3;
  elementOfSnake: array[1..100] of Snake;
  app: Apple;
  
procedure StartGame();
begin
  points := 0;
  _TIME_GAME_ := 250;
  countSnake := 3;
  elementOfSnake[1].posX := 2 * step;
  elementOfSnake[1].posY := 2 * step;
  
  elementOfSnake[2].posX := 2 * step;
  elementOfSnake[2].posY := 1 * step;
  
  elementOfSnake[3].posX := 2 * step;
  elementOfSnake[3].posY := 0 * step;
end;
  
  
procedure CreateApple(value: integer);
var
  x, y: integer;
  rnd: Random;
begin
  rnd := new Random();
  x := rnd.Next(0, Width div step);
  y := rnd.Next(0, Height div step);
  
  app.color := 'red';
  app.posX := x * step;
  app.posY := y * step;
  app.visible := true;
  
  if (_TEMP = (rnd.Next(0, 6))) then
  begin
    app.color := 'green';
  end;
end;  
  
procedure DrawQuad(mode: integer);
begin
  GL.glPushMatrix();
    GL.glBegin(mode);
      GL.glVertex2f(0, 0);
      GL.glVertex2f(step, 0);
      GL.glVertex2f(step, step);
      GL.glVertex2f(0, step);
    GL.glEnd();
  GL.glPopMatrix();
end;  
  
procedure DrawGrind();
begin
  GL.glPushMatrix();
    GL.glColor3f(0.0, 0.0, 0.0);
    GL.glBegin(GL.GL_LINES);
      for var i := 1 to (height div step) do
      begin
        gl.glVertex2f(0, i * step);
        gl.glVertex2f(width, i * step);
      end;
      
      for var j := 1 to (width div step) do
      begin
        gl.glVertex2f(j * step, 0);
        gl.glVertex2f(j * step, height);
      end;
    GL.glEnd();
  GL.glPopMatrix();
end;  

procedure RenderSnake();
begin
  for var i := 1 to countSnake do
  begin
    gl.glPushMatrix();
      GL.glColor3f(1.0, 1.0, 1.0);
      GL.glTranslatef(elementOfSnake[i].posX, elementOfSnake[i].posY, 0.0);
      DrawQuad(GL.GL_QUADS);
    gl.glPopMatrix();
    
    gl.glPushMatrix();
      GL.glColor3f(0.0, 0.0, 0.0);
      GL.glTranslatef(elementOfSnake[i].posX, elementOfSnake[i].posY, 1.0);
      DrawQuad(GL.GL_LINE_LOOP);
    gl.glPopMatrix();
  end;
end;

procedure pressKey(key: byte; x, y: integer);
begin
  case key of 
    key_w:
    begin
      //writeln('w');
      if (not (vectorSnake = DOWN)) then 
        vectorSnake := UP;
    end;
    key_s:
    begin
      //writeln('s');
      if (not (vectorSnake = UP)) then 
        vectorSnake := DOWN;
    end;
    key_a:
    begin
      //writeln('a');
     if (not (vectorSnake = RIGHT)) then 
        vectorSnake := LEFT;
    end;
    key_d:
    begin
     //writeln('d');
     if (not (vectorSnake = LEFT)) then 
        vectorSnake := RIGHT;
    end;
    key_esc:
    begin
       //writeln('del');
       glut.glutLeaveMainLoop();
    end;
  end; 
end;

function isCollisionApple() : boolean;
begin
  if((elementOfSnake[1].posX = app.posX) and (elementOfSnake[1].posY = app.posY)) then
    isCollisionApple := true
  else
    isCollisionApple := false;
end;

procedure Update(value: integer);
begin
  for var i := 2 to countSnake do
  begin
    if((elementOfSnake[1].posX = elementOfSnake[i].posX) and (elementOfSnake[1].posY = elementOfSnake[i].posY)) then
    begin
      writeln('Total points: ', points);
      StartGame();
    end;
  end;
  
  if(isCollisionApple() and (app.visible)) then
  begin
    app.visible := false;
    if(app.color = 'red') then
    begin
      countSnake := countSnake + 1;
      writeln('Plus one point!');
      points := points + 1;
      if(_TIME_GAME_ > 50) then
        _TIME_GAME_ := _TIME_GAME_ - 30;
    end
    else
    begin
      if(_TIME_GAME_ < 300) then
        _TIME_GAME_ := _TIME_GAME_ + 50;
    end;
    writeln('Game speed: ', _TIME_GAME_);
    GLUT.glutTimerFunc(1000, CreateApple, 0);
  end;
  
  for var i := countSnake downto 2 do
  begin
    elementOfSnake[i].posY := elementOfSnake[i - 1].posY;
    elementOfSnake[i].posX := elementOfSnake[i - 1].posX;
  end;
  
  case (vectorSnake) of 
    UP:
    begin
      elementOfSnake[1].posY += step;
    end;
    DOWN:
    begin
      elementOfSnake[1].posY -= step;
    end;
    RIGHT:
    begin
      elementOfSnake[1].posX += step;
    end;
    LEFT:
    begin
      elementOfSnake[1].posX -= step;
    end;
  end;
  
  if(elementOfSnake[1].posX > Width) then
    elementOfSnake[1].posX := 0;
  
  if(elementOfSnake[1].posX < 0) then
    elementOfSnake[1].posX := Width;
  
  if(elementOfSnake[1].posY > Height) then
    elementOfSnake[1].posY := 0;
  
  if(elementOfSnake[1].posY < 0) then
    elementOfSnake[1].posY := Height;
  
  Glut.glutTimerFunc(_TIME_GAME_, Update, 0);
end;


procedure InitScene();
begin
  GL.glClearCOlor(0.3, 0.7, 0.9, 0.0);
  GL.glEnable(GL.GL_DEPTH_TEST);
  StartGame();
end;

procedure RenderScene();
begin
  GL.glLoadIdentity();
  GL.glClear(GL.GL_COLOR_BUFFER_BIT or GL.GL_DEPTH_BUFFER_BIT);
  
  DrawGrind();
  RenderSnake();
  
  if(app.visible) then
  begin
    gl.glPushMatrix();
      if(app.color = 'red') then
         GL.glColor3f(1.0, 0.0, 0.0)
      else
         GL.glColor3f(0.0, 1.0, 0.0);
      
      GL.glTranslatef(app.posX, app.posY, 0.0);
      DrawQuad(GL.GL_QUADS);
    gl.glPopMatrix();
  end;


  Glut.glutSwapBuffers;
  Glut.glutPostRedisplay();
end;

procedure Reshape(w, h: integer);
begin
  gl.glViewport(0, 0, w, h);
  gl.glMatrixMode(gl.GL_PROJECTION);
  gl.glLoadIdentity();

  GLU.gluOrtho2d(0, w, 0, h);
 
  gl.glMatrixMode(gl.GL_MODELVIEW);
  gl.glLoadIdentity();
end;

begin
  Glut.glutInit(); 
  Glut.glutInitWindowSize(width, height); 

  Glut.glutInitWindowPosition((Glut.glutGet(glut.GLUT_SCREEN_WIDTH) - Width) div 2,
                             (Glut.glutGet(glut.GLUT_SCREEN_HEIGHT) - Height) div 2); 
  Glut.glutInitDisplayMode(GLUT.GLUT_RGBA or Glut.GLUT_DOUBLE or GLUT.GLUT_DEPTH);
  Glut.glutCreateWindow('Snake2.0');
  {Glut.glutGameModeString('1920x1080:32');
  if(Glut.glutGameModeGet(Glut.GLUT_GAME_MODE_POSSIBLE) <> 0) then
    Glut.glutEnterGameMode()
  else
    Glut.glutLeaveGameMode();}
  
  
  Glut.glutDisplayFunc(RenderScene);
  Glut.glutReshapeFunc(Reshape);
  
  Glut.glutTimerFunc(1, Update, 0);
  Glut.glutTimerFunc(1, CreateApple, 0);
  
  glut.glutKeyboardFunc(pressKey);
  
  InitScene();
  Glut.glutMainLoop();
end.