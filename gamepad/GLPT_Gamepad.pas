{ GLPT :: OpenGL Pascal Toolkit

  Copyright (c) 2020 Ryan Joseph

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
}
unit GLPT_Gamepad;

{$mode objfpc}

{$IFDEF DARWIN}
  {$define COCOA}
{$ENDIF}

{$IF defined(CPUARM) or defined(CPUAARCH64)}
  {$define IPHONE}
  {$undef COCOA}
{$ENDIF}

{$IFDEF IPHONESIM}
  {$define IPHONE}
  {$undef COCOA}
{$ENDIF}

{$IFDEF COCOA}
  {$modeswitch advancedrecords}
  {$modeswitch objectivec2}
  {$linkframework CoreVideo}
{$ENDIF}

{$IFDEF IPHONE}
  {$modeswitch advancedrecords}
  {$modeswitch objectivec2}
{$ENDIF}

interface

uses
  Classes, CTypes, GLPT,
{$IFDEF MSWINDOWS}
  Windows;
{$ENDIF}
{$IFDEF LINUX}
  Linux;
{$ENDIF}
{$IFDEF COCOA}
  FGL, SysUtils, IOKit, MacOSAll, CocoaAll;
{$ENDIF}

const
  GLPT_HAT_CENTERED = $00;
  GLPT_HAT_UP = $01;
  GLPT_HAT_RIGHT = $02;
  GLPT_HAT_DOWN = $04;
  GLPT_HAT_LEFT = $08;
  GLPT_HAT_RIGHTUP = GLPT_HAT_RIGHT or GLPT_HAT_UP;
  GLPT_HAT_RIGHTDOWN = GLPT_HAT_RIGHT or GLPT_HAT_DOWN;
  GLPT_HAT_LEFTUP = GLPT_HAT_LEFT or GLPT_HAT_UP;
  GLPT_HAT_LEFTDOWN = GLPT_HAT_LEFT or GLPT_HAT_DOWN;

const
  GLPT_CONTROLLER_AXIS_INVALID = -1;
  GLPT_CONTROLLER_AXIS_LEFTX = GLPT_CONTROLLER_AXIS_INVALID + 1;
  GLPT_CONTROLLER_AXIS_LEFTY = GLPT_CONTROLLER_AXIS_LEFTX + 1;
  GLPT_CONTROLLER_AXIS_RIGHTX = GLPT_CONTROLLER_AXIS_LEFTY + 1;
  GLPT_CONTROLLER_AXIS_RIGHTY = GLPT_CONTROLLER_AXIS_RIGHTX + 1;
  GLPT_CONTROLLER_AXIS_TRIGGERLEFT = GLPT_CONTROLLER_AXIS_RIGHTY + 1;
  GLPT_CONTROLLER_AXIS_TRIGGERRIGHT = GLPT_CONTROLLER_AXIS_TRIGGERLEFT + 1;
  GLPT_CONTROLLER_AXIS_MAX = GLPT_CONTROLLER_AXIS_TRIGGERRIGHT + 1;

const
  GLPT_CONTROLLER_BUTTON_INVALID = -1;
  GLPT_CONTROLLER_BUTTON_A = 1;
  GLPT_CONTROLLER_BUTTON_B = 2;
  GLPT_CONTROLLER_BUTTON_X = 3;
  GLPT_CONTROLLER_BUTTON_Y = 4;
  GLPT_CONTROLLER_BUTTON_BACK = 5;
  GLPT_CONTROLLER_BUTTON_GUIDE = 6;
  GLPT_CONTROLLER_BUTTON_START = 7;
  GLPT_CONTROLLER_BUTTON_LEFTSTICK = 8;
  GLPT_CONTROLLER_BUTTON_RIGHTSTICK = 9;
  GLPT_CONTROLLER_BUTTON_LEFTSHOULDER = 10;
  GLPT_CONTROLLER_BUTTON_RIGHTSHOULDER = 11;
  GLPT_CONTROLLER_BUTTON_DPAD_UP = 12;
  GLPT_CONTROLLER_BUTTON_DPAD_DOWN = 13;
  GLPT_CONTROLLER_BUTTON_DPAD_LEFT = 14;
  GLPT_CONTROLLER_BUTTON_DPAD_RIGHT = 15;
  GLPT_CONTROLLER_BUTTON_MAX = 16;

{
   Initializes the GLPT gamepad
   @return True if successfull otherwise False
}
function GLPT_GamepadInit: boolean;
procedure GLPT_PollDevices;

implementation

{$IFDEF MSWINDOWS}
  {$INCLUDE GLPT_gdi.inc}
{$ENDIF}
{$IFDEF LINUX}
  {$INCLUDE include/GLPT_X11.inc}
{$ENDIF}
{$IFDEF COCOA}
  {$INCLUDE include/GLPT_Cocoa.inc}
{$ENDIF}
{$IFDEF IPHONE}
  {$INCLUDE include/GLPT_IPhone.inc}
{$ENDIF}

function GLPT_GamepadInit: boolean;
begin
{$IFDEF MSWINDOWS}
  //exit(gdi_Gamepad_Init(flags));
{$ENDIF}
{$IFDEF LINUX}
  //exit(X11_Gamepad_Init(flags));
{$ENDIF}
{$IFDEF COCOA}
  exit(Cocoa_Gamepad_Init);
{$ENDIF}
end;

procedure GLPT_PollDevices;
begin
{$IFDEF MSWINDOWS}
  //gdi_PollDevices;
{$ENDIF}
{$IFDEF LINUX}
  //X11_PollDevices;
{$ENDIF}
{$IFDEF COCOA}
  Cocoa_PollDevices;
{$ENDIF}
end;

end.
