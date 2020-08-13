{
  requires -dGLPT_GAMEPAD to use GLPT_FlagGamepad
}
program gamepad;

{$mode objfpc}

uses
  SysUtils,
  GL, GLPT, GLPT_Gamepad;

var
  window: pGLPTWindow;
  width: integer = 640;
  height: integer = 480;

  procedure error_callback(error: integer; description: string);
  begin
    writeln(stderr, description);
  end;

  procedure event_callback(event: pGLPT_MessageRec);
  begin
    case event^.mcode of

      GLPT_MESSAGE_CONTROLLER_ADDED:
        begin
          writeln('controller added');
        end;
      GLPT_MESSAGE_CONTROLLER_REMOVED:
        begin
          writeln('controller removed');
        end;
      GLPT_MESSAGE_CONTROLLER_AXIS:
        begin
          writeln('axis:',event^.params.axis.which,' ',event^.params.axis.axis, ' = ', event^.params.axis.value);
        end;

      GLPT_MESSAGE_CONTROLLER_BUTTON:
        begin
          writeln('button:',event^.params.button.which,' ',event^.params.button.button, ' = ', event^.params.button.state);
        end;

      GLPT_MESSAGE_KEYPRESS:
        if event^.params.keyboard.keycode = GLPT_KEY_ESCAPE then
          GLPT_SetWindowShouldClose(event^.win, True);

      GLPT_MESSAGE_MOUSEDOWN:
        writeln('GLPT_MESSAGE_MOUSEDOWN:',event^.params.mouse.buttons);
    end;
  end;

begin
  GLPT_SetErrorCallback(@error_callback);

  if not GLPT_Init or
    not GLPT_GamepadInit then
    halt(-1);

  window := GLPT_CreateWindow(GLPT_WINDOW_POS_CENTER, GLPT_WINDOW_POS_CENTER, width, height, 'Gamepad example', GLPT_GetDefaultContext);
  if window = nil then
  begin
    GLPT_Terminate;
    halt(-1);
  end;

  window^.event_callback := @event_callback;

  writeln('GLPT version: ', GLPT_GetVersionString);
  writeln('OpenGL version: ', glGetString(GL_VERSION));

  while not GLPT_WindowShouldClose(window) do
  begin
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    GLPT_SwapBuffers(window);
    GLPT_PollDevices;
    GLPT_PollEvents;
  end;

  GLPT_DestroyWindow(window);
  GLPT_Terminate;
end.
