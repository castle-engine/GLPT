{ GLPT :: OpenGL Pascal Toolkit

  Copyright (c) 2018 Ryan Joseph

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

const
  GLPT_KEY_UNKNOWN = 0;
var 
  darwin_scancode_table: array[0..127] of GLPT_Scancode = (
    {   0 }   GLPT_SCANCODE_A,
    {   1 }   GLPT_SCANCODE_S,
    {   2 }   GLPT_SCANCODE_D,
    {   3 }   GLPT_SCANCODE_F,
    {   4 }   GLPT_SCANCODE_H,
    {   5 }   GLPT_SCANCODE_G,
    {   6 }   GLPT_SCANCODE_Z,
    {   7 }   GLPT_SCANCODE_X,
    {   8 }   GLPT_SCANCODE_C,
    {   9 }   GLPT_SCANCODE_V,
    {  10 }   GLPT_SCANCODE_NONUSBACKSLASH, { GLPT_SCANCODE_NONUSBACKSLASH on ANSI and JIS keyboards (if this key would exist there), GLPT_SCANCODE_GRAVE on ISO. (The USB keyboard driver actually translates these usage codes to different virtual key codes depending on whether the keyboard is ISO/ANSI/JIS. That's why you have to help it identify the keyboard type when you plug in a PC USB keyboard. It's a historical thing - ADB keyboards are wired this way.) }
    {  11 }   GLPT_SCANCODE_B,
    {  12 }   GLPT_SCANCODE_Q,
    {  13 }   GLPT_SCANCODE_W,
    {  14 }   GLPT_SCANCODE_E,
    {  15 }   GLPT_SCANCODE_R,
    {  16 }   GLPT_SCANCODE_Y,
    {  17 }   GLPT_SCANCODE_T,
    {  18 }   GLPT_SCANCODE_1,
    {  19 }   GLPT_SCANCODE_2,
    {  20 }   GLPT_SCANCODE_3,
    {  21 }   GLPT_SCANCODE_4,
    {  22 }   GLPT_SCANCODE_6,
    {  23 }   GLPT_SCANCODE_5,
    {  24 }   GLPT_SCANCODE_EQUALS,
    {  25 }   GLPT_SCANCODE_9,
    {  26 }   GLPT_SCANCODE_7,
    {  27 }   GLPT_SCANCODE_MINUS,
    {  28 }   GLPT_SCANCODE_8,
    {  29 }   GLPT_SCANCODE_0,
    {  30 }   GLPT_SCANCODE_RIGHTBRACKET,
    {  31 }   GLPT_SCANCODE_O,
    {  32 }   GLPT_SCANCODE_U,
    {  33 }   GLPT_SCANCODE_LEFTBRACKET,
    {  34 }   GLPT_SCANCODE_I,
    {  35 }   GLPT_SCANCODE_P,
    {  36 }   GLPT_SCANCODE_RETURN,
    {  37 }   GLPT_SCANCODE_L,
    {  38 }   GLPT_SCANCODE_J,
    {  39 }   GLPT_SCANCODE_APOSTROPHE,
    {  40 }   GLPT_SCANCODE_K,
    {  41 }   GLPT_SCANCODE_SEMICOLON,
    {  42 }   GLPT_SCANCODE_BACKSLASH,
    {  43 }   GLPT_SCANCODE_COMMA,
    {  44 }   GLPT_SCANCODE_SLASH,
    {  45 }   GLPT_SCANCODE_N,
    {  46 }   GLPT_SCANCODE_M,
    {  47 }   GLPT_SCANCODE_PERIOD,
    {  48 }   GLPT_SCANCODE_TAB,
    {  49 }   GLPT_SCANCODE_SPACE,
    {  50 }   GLPT_SCANCODE_GRAVE, { GLPT_SCANCODE_GRAVE on ANSI and JIS keyboards, GLPT_SCANCODE_NONUSBACKSLASH on ISO (see comment about virtual key code 10 above) }
    {  51 }   GLPT_SCANCODE_BACKSPACE,
    {  52 }   GLPT_SCANCODE_KP_ENTER, { keyboard enter on portables }
    {  53 }   GLPT_SCANCODE_ESCAPE,
    {  54 }   GLPT_SCANCODE_RGUI,
    {  55 }   GLPT_SCANCODE_LGUI,
    {  56 }   GLPT_SCANCODE_LSHIFT,
    {  57 }   GLPT_SCANCODE_CAPSLOCK,
    {  58 }   GLPT_SCANCODE_LALT,
    {  59 }   GLPT_SCANCODE_LCTRL,
    {  60 }   GLPT_SCANCODE_RSHIFT,
    {  61 }   GLPT_SCANCODE_RALT,
    {  62 }   GLPT_SCANCODE_RCTRL,
    {  63 }   GLPT_SCANCODE_RGUI, { fn on portables, acts as a hardware-level modifier already, so we don't generate events for it, also XK_Meta_R }
    {  64 }   GLPT_SCANCODE_F17,
    {  65 }   GLPT_SCANCODE_KP_PERIOD,
    {  66 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    {  67 }   GLPT_SCANCODE_KP_MULTIPLY,
    {  68 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    {  69 }   GLPT_SCANCODE_KP_PLUS,
    {  70 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    {  71 }   GLPT_SCANCODE_NUMLOCKCLEAR,
    {  72 }   GLPT_SCANCODE_VOLUMEUP,
    {  73 }   GLPT_SCANCODE_VOLUMEDOWN,
    {  74 }   GLPT_SCANCODE_MUTE,
    {  75 }   GLPT_SCANCODE_KP_DIVIDE,
    {  76 }   GLPT_SCANCODE_KP_ENTER, { keypad enter on external keyboards, fn-return on portables }
    {  77 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    {  78 }   GLPT_SCANCODE_KP_MINUS,
    {  79 }   GLPT_SCANCODE_F18,
    {  80 }   GLPT_SCANCODE_F19,
    {  81 }   GLPT_SCANCODE_KP_EQUALS,
    {  82 }   GLPT_SCANCODE_KP_0,
    {  83 }   GLPT_SCANCODE_KP_1,
    {  84 }   GLPT_SCANCODE_KP_2,
    {  85 }   GLPT_SCANCODE_KP_3,
    {  86 }   GLPT_SCANCODE_KP_4,
    {  87 }   GLPT_SCANCODE_KP_5,
    {  88 }   GLPT_SCANCODE_KP_6,
    {  89 }   GLPT_SCANCODE_KP_7,
    {  90 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    {  91 }   GLPT_SCANCODE_KP_8,
    {  92 }   GLPT_SCANCODE_KP_9,
    {  93 }   GLPT_SCANCODE_INTERNATIONAL3, { Cosmo_USB2ADB.c says "Yen (JIS)" }
    {  94 }   GLPT_SCANCODE_INTERNATIONAL1, { Cosmo_USB2ADB.c says "Ro (JIS)" }
    {  95 }   GLPT_SCANCODE_KP_COMMA, { Cosmo_USB2ADB.c says ", JIS only" }
    {  96 }   GLPT_SCANCODE_F5,
    {  97 }   GLPT_SCANCODE_F6,
    {  98 }   GLPT_SCANCODE_F7,
    {  99 }   GLPT_SCANCODE_F3,
    { 100 }   GLPT_SCANCODE_F8,
    { 101 }   GLPT_SCANCODE_F9,
    { 102 }   GLPT_SCANCODE_LANG2, { Cosmo_USB2ADB.c says "Eisu" }
    { 103 }   GLPT_SCANCODE_F11,
    { 104 }   GLPT_SCANCODE_LANG1, { Cosmo_USB2ADB.c says "Kana" }
    { 105 }   GLPT_SCANCODE_PRINTSCREEN, { On ADB keyboards, this key is labeled "F13/print screen". Problem: USB has different usage codes for these two functions. On Apple USB keyboards, the key is labeled "F13" and sends the F13 usage code (GLPT_SCANCODE_F13). I decided to use GLPT_SCANCODE_PRINTSCREEN here nevertheless since SDL applications are more likely to assume the presence of a print screen key than an F13 key. }
    { 106 }   GLPT_SCANCODE_F16,
    { 107 }   GLPT_SCANCODE_SCROLLLOCK, { F14/scroll lock, see comment about F13/print screen above }
    { 108 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    { 109 }   GLPT_SCANCODE_F10,
    { 110 }   GLPT_SCANCODE_APPLICATION, { windows contextual menu key, fn-enter on portables }
    { 111 }   GLPT_SCANCODE_F12,
    { 112 }   GLPT_SCANCODE_UNKNOWN, { unknown (unused?) }
    { 113 }   GLPT_SCANCODE_PAUSE, { F15/pause, see comment about F13/print screen above }
    { 114 }   GLPT_SCANCODE_INSERT, { the key is actually labeled "help" on Apple keyboards, and works as such in Mac OS, but it sends the "insert" usage code even on Apple USB keyboards }
    { 115 }   GLPT_SCANCODE_HOME,
    { 116 }   GLPT_SCANCODE_PAGEUP,
    { 117 }   GLPT_SCANCODE_DELETE,
    { 118 }   GLPT_SCANCODE_F4,
    { 119 }   GLPT_SCANCODE_END,
    { 120 }   GLPT_SCANCODE_F2,
    { 121 }   GLPT_SCANCODE_PAGEDOWN,
    { 122 }   GLPT_SCANCODE_F1,
    { 123 }   GLPT_SCANCODE_LEFT,
    { 124 }   GLPT_SCANCODE_RIGHT,
    { 125 }   GLPT_SCANCODE_DOWN,
    { 126 }   GLPT_SCANCODE_UP,
    { 127 }   GLPT_SCANCODE_POWER
);

// SDL_cocoakeyboard.m 

(*

static void
UpdateKeymap(SDL_VideoData *data, SDL_bool send_event)
{
    TISInputSourceRef key_layout;
    const void *chr_data;
    int i;
    SDL_Scancode scancode;
    SDL_Keycode keymap[SDL_NUM_SCANCODES];

    /* See if the keymap needs to be updated */
    key_layout = TISCopyCurrentKeyboardLayoutInputSource();
    if (key_layout == data->key_layout) {
        return;
    }
    data->key_layout = key_layout;

    SDL_GetDefaultKeymap(keymap);

    /* Try Unicode data first */
    CFDataRef uchrDataRef = TISGetInputSourceProperty(key_layout, kTISPropertyUnicodeKeyLayoutData);
    if (uchrDataRef) {
        chr_data = CFDataGetBytePtr(uchrDataRef);
    } else {
        goto cleanup;
    }

    if (chr_data) {
        UInt32 keyboard_type = LMGetKbdType();
        OSStatus err;

        for (i = 0; i < SDL_arraysize(darwin_scancode_table); i++) {
            UniChar s[8];
            UniCharCount len;
            UInt32 dead_key_state;

            /* Make sure this scancode is a valid character scancode */
            scancode = darwin_scancode_table[i];
            if (scancode == SDL_SCANCODE_UNKNOWN ||
                (keymap[scancode] & SDLK_SCANCODE_MASK)) {
                continue;
            }

            dead_key_state = 0;
            err = UCKeyTranslate ((UCKeyboardLayout ) chr_data,
                                  i, kUCKeyActionDown,
                                  0, keyboard_type,
                                  kUCKeyTranslateNoDeadKeysMask,
                                  &dead_key_state, 8, &len, s);
            if (err != noErr) {
                continue;
            }

            if (len > 0 && s[0] != 0x10) {
                keymap[scancode] = s[0];
            }
        }
        SDL_SetKeymap(0, keymap, SDL_NUM_SCANCODES);
        if (send_event) {
            SDL_SendKeymapChangedEvent();
        }
        return;
    }

cleanup:
    CFRelease(key_layout);
}

*)

//#########################################################
// COCOA UTILS
//#########################################################

{$if FPC_FULLVERSION <= 30004}
type
  objcbool = bool;
{$endif}
  
type
  NSFileManager_Additions = objccategory external (NSFileManager)
    function createDirectoryAtURL_withIntermediateDirectories_attributes_error (url: NSURL; createIntermediates: boolean; attributes: NSDictionary; error: NSErrorPtr): boolean; message 'createDirectoryAtURL:withIntermediateDirectories:attributes:error:'; { available in 10_7, 5_0 }
  end;

function NSSTR(str: string): NSString; overload;
begin
  result := NSString.stringWithCString_length(@str[1], length(str));
end;

type
  TCocoaWindowHelper = objccategory (NSWindow)
    function openGLView: NSView; message 'openGLView';
  end;

function TCocoaWindowHelper.openGLView: NSView;
begin
  result := contentView.subviews.objectAtIndex(0);
end;

//#########################################################
// COCOA WINDOWS
//#########################################################

type
  TBorderlessWindow = objcclass (NSWindow)
    public
      function initWithContentRect_styleMask_backing_defer (contentRect: NSRect; aStyle: NSUInteger; bufferingType: NSBackingStoreType; flag: objcbool): id; override;
      function initWithContentRect(contentRect: NSRect): id; message 'initWithContentRect:';
      function canBecomeKeyWindow: objcbool; override;
      function canBecomeMainWindow: objcbool; override;
      procedure setKeepFullScreenAlways (newValue: boolean); message 'setKeepFullScreenAlways:';
      procedure dealloc; override;
      procedure toggleFullScreen(sender: id); override;
    private
      keepFullScreenAlways: boolean;
      previousStyleMask: NSUInteger;
      previousFrame: NSRect;
      function fullScreenFrame: NSRect; message 'fullScreenFrame';
      function isFullScreen: boolean; message 'isFullScreen';
      procedure screenParametersChanged (notification: NSNotification); message 'screenParametersChanged:';
  end;

const
  NSWindowCollectionBehaviorFullScreenPrimary = 1 shl 7 { available in 10_7 };
  NSWindowCollectionBehaviorFullScreenAuxiliary = 1 shl 8 { available in 10_7 };
  NSWindowCollectionBehaviorFullScreenNone = 1 shl 9 { available in 10_7 };

procedure TBorderlessWindow.toggleFullScreen(sender: id);
begin
  inherited toggleFullScreen(sender);
  NSMenu.setMenuBarVisible(not isFullScreen);

  //if isFullScreen then
  //  begin
  //    setKeepFullScreenAlways(false);
  //    NSMenu.setMenuBarVisible(true);
  //    setFrame_display(previousFrame, true);
  //  end
  //else
  //  begin
  //    previousStyleMask := styleMask;
  //    previousFrame := frame;
  //    setKeepFullScreenAlways(true);
  //    NSMenu.setMenuBarVisible(false);
  //    // TODO: this gives a strange opengl error
  //    // glUseProgram 9 GL_INVALID_FRAMEBUFFER_OPERATION ($0506) (GLUtils.pas, line 641)
  //    //setStyleMask(NSBorderlessWindowMask);
  //  end;
end;

function TBorderlessWindow.canBecomeKeyWindow: objcbool;
begin
  result := true;
end;

function TBorderlessWindow.canBecomeMainWindow: objcbool;
begin
  result := true;
end;

function TBorderlessWindow.fullScreenFrame: NSRect;
begin
  result := screen.frame;
end;

function TBorderlessWindow.isFullScreen: boolean;
begin
  result := styleMask = (styleMask or NSFullScreenWindowMask)

end;

procedure TBorderlessWindow.setKeepFullScreenAlways (newValue: boolean);
begin
  orderFrontRegardless;
  keepFullScreenAlways := newValue;
  if keepFullScreenAlways then
    begin
      setFrame_display(fullScreenFrame, true);
      setLevel(CGWindowLevelForKey(kCGFloatingWindowLevelKey));
    end
  else
    setLevel(CGWindowLevelForKey(kCGNormalWindowLevelKey));
end;

procedure TBorderlessWindow.screenParametersChanged (notification: NSNotification);
begin 
  if keepFullScreenAlways then
    setFrame_display(fullScreenFrame, true);
end;

procedure TBorderlessWindow.dealloc;
begin
  NSNotificationCenter.defaultCenter.removeObserver(self);
  inherited dealloc;
end;

function TBorderlessWindow.initWithContentRect_styleMask_backing_defer (contentRect: NSRect; aStyle: NSUInteger; bufferingType: NSBackingStoreType; flag: objcbool): id;
begin
  result := inherited initWithContentRect_styleMask_backing_defer(contentRect, aStyle, bufferingType, flag);
  if result <> nil then
    NSNotificationCenter(NSNotificationCenter.defaultCenter).addObserver_selector_name_object(result, objcselector('screenParametersChanged:'), NSApplicationDidChangeScreenParametersNotification, nil);
end;

function TBorderlessWindow.initWithContentRect(contentRect: NSRect): id;
begin
  result := initWithContentRect_styleMask_backing_defer(contentRect, NSBorderlessWindowMask, NSBackingStoreBuffered, false);
  if result <> nil then
    begin 
      result.setMovableByWindowBackground(false);
      //result.setBackgroundColor(NSColor.clearColor);
      //result.setOpaque(false);
      result.setHasShadow(false);
      result.setExcludedFromWindowsMenu(true);
      self := result;
    end;
end;

type
  TCocoaWindow = objcclass (TBorderlessWindow)
    private
      ref: pGLPTwindow;
    public
      procedure close; override;
      procedure becomeKeyWindow; override;
      procedure resignKeyWindow; override;
      procedure doCommandBySelector(aSelector: SEL); override;
      procedure bringToFront(sender: id); message 'bringToFront:';
      procedure toggleFullScreen(sender: id); override;
      function glptWindowRef: pGLPTwindow; message 'glptWindowRef';
  end;

// this method is provided for extensions outside of the main unit
function TCocoaWindow.glptWindowRef: pGLPTwindow;
begin
  result := ref;
end;

procedure TCocoaWindow.toggleFullScreen(sender: id);
begin
  inherited toggleFullScreen(sender);
  ref^.fscreen := isFullScreen;
end;

procedure TCocoaWindow.bringToFront(sender: id);
begin
  NSApp.activateIgnoringOtherApps(true);
  orderFrontRegardless;
end;

procedure TCocoaWindow.close;
begin
  ref^.shouldClose := true;
  inherited;
end;

procedure TCocoaWindow.doCommandBySelector(aSelector: SEL);
begin
  // do nothing to prevent beeping
end;

procedure TCocoaWindow.becomeKeyWindow;
var
  params: GLPT_MessageParams;
begin
  inherited;
  FillChar(params, sizeof(params), 0);
  glptPostMessage(ref, GLPT_MESSAGE_ACTIVATE, params);      
end;

procedure TCocoaWindow.resignKeyWindow;
var
  params: GLPT_MessageParams;
begin
  inherited;
  FillChar(params, sizeof(params), 0);
  glptPostMessage(ref, GLPT_MESSAGE_DEACTIVATE, params);
end;

//#########################################################
// COCOA APP
//#########################################################

type
  TCocoaApp = objcclass (NSApplication)
    procedure poll; message 'poll';
  end;

type
  TCocoaAppDelegate = objcclass (NSObject, NSApplicationDelegateProtocol)
  end;

function Cocoa_GetKeyboardShiftState: TShiftState; forward;
function Cocoa_GetTime: double; forward;

//#########################################################
// COCOA OPENGL VIEW
//#########################################################

type
  TOpenGLView = objcclass (NSView)
    public
      function initWithFrame(frameRect: NSRect): id; override;
      function isOpaque: objcbool; override;
      function isFlipped: objcbool; override;
      procedure viewDidMoveToWindow; override;
      procedure mouseEntered(theEvent: NSEvent); override;
      procedure mouseExited(theEvent: NSEvent); override;
      procedure doCommandBySelector(aSelector: SEL); override;
      procedure keyDown(theEvent: NSEvent); override;
      procedure drawRect(dirtyRect: NSRect); override;
      procedure dealloc; override;
      procedure updateTrackingAreas; override;
      function acceptsFirstMouse (theEvent: NSEvent): objcbool; override;
    private
      openGLContext: NSOpenGLContext;
      trackingArea: NSTrackingArea;
      displayLink: CVDisplayLinkRef;
      displayLinkSemaphore: NSCondition;
      isLiveResizing: boolean;
      nativeSize: CGSize;

      function defaultPixelFormat: NSOpenGLPixelFormat; message 'defaultPixelFormat';
      function windowRef: pGLPTwindow; message 'windowRef';
      function glptContext: GLPT_Context; message 'glptContext';

      procedure setupContext; message 'setupContext';

      { Notifications }
      procedure frameDidChange (sender: NSNotification); message 'frameDidChange:';
      procedure windowDidResize (sender: NSNotification); message 'windowDidResize:';
      procedure windowWillStartLiveResize (sender: NSNotification); message 'windowWillStartLiveResize:';
      procedure windowDidEndLiveResize (sender: NSNotification); message 'windowDidEndLiveResize:';
      procedure reshape; message 'reshape';
  end;


function HandleMouseEvent(event: NSEvent; var params: GLPT_MessageParams): boolean;
begin
  FillChar(params, sizeof(params), 0);
  result := event.window <> nil;

  // point is outside of content view
  if result and (CGRectContainsPoint(event.window.openGLView.frame, event.locationInWindow) <> 1) then
    exit(false);

  if result then
    begin
      //writeln(event.window.description.utf8string, ' -> ', Trunc(event.locationInWindow.x),'x',Trunc(event.locationInWindow.y));
      params.mouse.x := Trunc(event.locationInWindow.x);
      params.mouse.y := Trunc(event.window.openGLView.frame.size.height - event.locationInWindow.y);
      params.mouse.shiftstate := Cocoa_GetKeyboardShiftState;
      params.mouse.timestamp := Cocoa_GetTime;
    end;
end;

procedure TCocoaApp.poll;
var
  event: NSEvent;
  params: GLPT_MessageParams;
  win: pGLPTwindow = nil;
  pool: NSAutoreleasePool;
  keymap: GLPTKeymapArrayPtr;
label
  IgnoreEvent;
begin
  pool := NSAutoreleasePool.alloc.init;
  event := nextEventMatchingMask_untilDate_inMode_dequeue(NSAnyEventMask, nil, NSDefaultRunLoopMode, true);
  if event <> nil then
    begin
      //writeln(event.description.utf8string);

      if event.window <> nil then
        win := TCocoaWindow(event.window).ref;
     
      case event.type_ of
        NSScrollWheel:
          begin
            if not HandleMouseEvent(event, params) then
              goto IgnoreEvent;

            // ignore movement outside of content view, which is probably the title bar
            if (params.mouse.x > 0) and (params.mouse.y > 0) then
              begin
                params.mouse.deltaX := event.deltaX;
                params.mouse.deltaY := event.deltaY;
                glptPostMessage(win, GLPT_MESSAGE_SCROLL, params);
              end;
          end;
        NSLeftMouseDragged, NSRightMouseDragged:
          begin
            if not HandleMouseEvent(event, params) then
              goto IgnoreEvent;
            glptPostMessage(win, GLPT_MESSAGE_MOUSEMOVE, params);
          end;
        NSMouseMoved:
          begin
            if not HandleMouseEvent(event, params) then
              goto IgnoreEvent;
            glptPostMessage(win, GLPT_MESSAGE_MOUSEMOVE, params);
          end;
        NSLeftMouseDown, NSRightMouseDown:
          begin
            if not HandleMouseEvent(event, params) then
              goto IgnoreEvent;

            params.mouse.clicks := event.clickCount;

            // ignore clicks outside content view, which is probably the title bar
            if (params.mouse.x > 0) and (params.mouse.y > 0) then
              begin
                case event.type_ of
                  NSLeftMouseDown:
                    params.mouse.buttons := GLPT_MOUSE_BUTTON_LEFT;
                  NSRightMouseDown:
                    params.mouse.buttons := GLPT_MOUSE_BUTTON_RIGHT;
                end;
                glptPostMessage(win, GLPT_MESSAGE_MOUSEDOWN, params);
              end;
          end;
        NSLeftMouseUp, NSRightMouseUp:
          begin
            if not HandleMouseEvent(event, params) then
              goto IgnoreEvent;

            // ignore clicks outside of content view, which is probably the title bar
            if (params.mouse.x > 0) and (params.mouse.y > 0) then
              begin
                case event.type_ of
                  NSLeftMouseUp:
                    params.mouse.buttons := GLPT_MOUSE_BUTTON_LEFT;
                  NSRightMouseUp:
                    params.mouse.buttons := GLPT_MOUSE_BUTTON_RIGHT;
                end;
                glptPostMessage(win, GLPT_MESSAGE_MOUSEUP, params);
              end;
          end;
        NSKeyDown, NSKeyUp:
          begin
            // todo: implement UpdateKeymap
            keymap := @GLPT_default_keymap;

            params.keyboard.scancode := darwin_scancode_table[event.keycode];
            params.keyboard.keycode := keymap^[params.keyboard.scancode];
            params.keyboard.shiftstate := Cocoa_GetKeyboardShiftState;
            
            //writeln('scancode:',params.keyboard.scancode);
            //writeln('keycode:',params.keyboard.keycode);
            //writeln('keychar:',chr(params.keyboard.keycode));
            //writeln('name:',GLPT_GetScancodeName(params.keyboard.scancode));

            case event.type_ of
              NSKeyDown:
                glptPostMessage(win, GLPT_MESSAGE_KEYPRESS, params);
              NSKeyUp:
                glptPostMessage(win, GLPT_MESSAGE_KEYRELEASE, params);
            end;
          end;
        otherwise
          ;
      end;

      IgnoreEvent:
      sendEvent(event);
      updateWindows;
    end;
  pool.release;
end;


// note: setValues_forParameter in RTL headers is parsed wrong
type
  NSOpenGLContext_Fixed = objccategory external (NSOpenGLContext)
    procedure setValues_forParameter_fixed (vals: pointer; param: NSOpenGLContextParameter); overload; message 'setValues:forParameter:';
  end;

function TOpenGLView.windowRef: pGLPTwindow;
begin
  result := TCocoaWindow(window).ref;
end;

function TOpenGLView.acceptsFirstMouse (theEvent: NSEvent): objcbool;
begin
  // accepts first mouse is supposed to ignore the click
  // the activates the window but for some reason it's
  // not working, so we simply discard the mouse down
  // message which is sent *before* this method is called.
  // also to make matters worse acceptsFirstMouse is called
  // for *every* mouse down when the window is fullscreen
  // so we need to omit this check entirely in that case
  if not TCocoaWindow(window).isFullScreen then
    glptDiscardMessages(GLPT_MESSAGE_MOUSEDOWN);
  result := true;
end;

procedure TOpenGLView.updateTrackingAreas;
begin 
  if trackingArea <> nil then
    removeTrackingArea(trackingArea);
  trackingArea := NSTrackingArea.alloc.initWithRect_options_owner_userInfo(bounds, NSTrackingMouseEnteredAndExited + NSTrackingActiveInActiveApp, self, nil).autorelease;
  addTrackingArea(trackingArea);
end;

procedure TOpenGLView.keyDown(theEvent: NSEvent);
begin
  // do nothing to prevent beeping
end;

procedure TOpenGLView.doCommandBySelector(aSelector: SEL);
begin
  // do nothing to prevent beeping
end;

procedure TOpenGLView.mouseEntered(theEvent: NSEvent);
var
   params: GLPT_MessageParams;
begin
  FillChar(params, sizeof(params), 0);
  HandleMouseEvent(theEvent, params);
  glptPostMessage(windowRef, GLPT_MESSAGE_MOUSEENTER, params);      
end;

procedure TOpenGLView.mouseExited(theEvent: NSEvent);
var
   params: GLPT_MessageParams;
begin
  FillChar(params, sizeof(params), 0);
  glptPostMessage(windowRef, GLPT_MESSAGE_MOUSEEXIT, params);   
end;

function DisplayLinkOutputCallback (displayLink: CVDisplayLinkRef; inNow: CVTimeStampPtr; inOutputTime: CVTimeStampPtr; flagsIn: CVOptionFlags; var flagsOut: CVOptionFlags; displayLinkContext: pointer): CVReturn; cdecl;
begin 
  TOpenGLView(displayLinkContext).displayLinkSemaphore.signal;
  result := 0;
end;

function TOpenGLView.glptContext: GLPT_Context;
begin
  result := TCocoaWindow(window).ref^.context;
end;

procedure TOpenGLView.setupContext;
var
  opacity: integer = 0;
  pixelFormat: NSOpenGLPixelFormat;
begin
  pixelFormat := defaultPixelFormat;
  openGLContext := NSOpenGLContext.alloc.initWithFormat_shareContext(pixelFormat, nil);
  if openGLContext = nil then
    GLPTError(GLPT_ERROR_PLATFORM, 'invalid NSOpenGLContext');
  openGLContext.makeCurrentContext;
  openGLContext.setView(self);

  {$if FPC_FULLVERSION > 30004}
  setWantsBestResolutionOpenGLSurface(glptContext.bestResolution);
  {$endif}

  nativeSize := frame.size;

  // enable vsync
  if glptContext.vsync then
    begin
      displayLinkSemaphore := NSCondition.alloc.init;
      CVDisplayLinkCreateWithActiveCGDisplays(displayLink);
      CVDisplayLinkSetOutputCallback(displayLink, CVDisplayLinkOutputCallback(@DisplayLinkOutputCallback), self);
      CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, openGLContext.CGLContextObj, pixelFormat.CGLPixelFormatObj);
      CVDisplayLinkStart(displayLink);
    end;

  if not isOpaque then
    openGLContext.setValues_forParameter_fixed(@opacity, NSOpenGLCPSurfaceOpacity);
end;

procedure TOpenGLView.viewDidMoveToWindow;
begin
  inherited viewDidMoveToWindow;
  if openGLContext = nil then
    setupContext;
  if window = nil then
    openGLContext.clearDrawable;
end;

procedure TOpenGLView.windowDidResize (sender: NSNotification);

  function ScaleToFit(source, dest: CGSize): CGRect;
  var
    aspectRatio: CGFloat;
    newSize: CGSize;
    newOrigin: CGPoint;
  begin
    aspectRatio := Min(dest.width, dest.height) / Min(source.width, source.height);
    newOrigin := CGPointMake(0, 0);
    newSize := CGSizeMake(source.width * aspectRatio, source.height * aspectRatio);
    if dest.width > newSize.width then
      newOrigin.x := (dest.width / 2) - (newSize.width / 2);
    if dest.height > newSize.height then
      newOrigin.y := (dest.height / 2) - (newSize.height / 2);
    result := CGRectMake(newOrigin.x, newOrigin.y, newSize.width, newSize.height);
  end;

var
  newFrame: NSRect;
  bestSize,
  targetSize: NSSize;
begin
  if sender.object_ = window then
    begin

      case glptContext.resizePolicy of
        rpStretchToFill:
          begin
            newFrame.size.width := superview.bounds.size.width;
            newFrame.size.height := superview.bounds.size.height;
            newFrame.origin.x := 0;
            newFrame.origin.y := 0;
            setFrame(newFrame);
          end;
        rpScaleToFit:
          begin
            newFrame := ScaleToFit(frame.size, superview.bounds.size);
            setFrame(newFrame);
          end;
        rpRealNative:
          begin
            newFrame := frame;
            newFrame.origin.x := (superview.bounds.size.width / 2) - (newFrame.size.width / 2);
            newFrame.origin.y := (superview.bounds.size.height / 2) - (newFrame.size.height / 2);
            setFrame(newFrame);
          end;
        rpBestNative:
          begin
            bestSize := nativeSize;
            targetSize := superview.bounds.size;
            while (bestSize.width <= targetSize.width) or (bestSize.height <= targetSize.height) do
              begin
                if (bestSize.width * 2 > targetSize.width) and (bestSize.height * 2 > targetSize.height) then
                  break;
                bestSize.width *= 2;
                bestSize.height *= 2;
              end;
            newFrame.size := bestSize;
            newFrame.origin.x := (superview.bounds.size.width / 2) - (newFrame.size.width / 2);
            newFrame.origin.y := (superview.bounds.size.height / 2) - (newFrame.size.height / 2);
            setFrame(newFrame);
          end;
      end;

    end;
end;


procedure TOpenGLView.frameDidChange (sender: NSNotification);
begin
  if not isLiveResizing and assigned(openGLContext) then
    reshape;
end;

procedure TOpenGLView.windowWillStartLiveResize (sender: NSNotification);
begin
  // if a mouse down was queued before resizing we need to discard it
  // so it doesn't get polled after resizing is complete
  glptDiscardMessages(GLPT_MESSAGE_MOUSEDOWN);
  isLiveResizing := true;
end;

procedure TOpenGLView.windowDidEndLiveResize (sender: NSNotification);
begin
  isLiveResizing := false;
  reshape;
end;

procedure TOpenGLView.drawRect(dirtyRect: NSRect);
begin 
  openGLContext.flushBuffer;
end;

procedure TOpenGLView.reshape;
var
  params: GLPT_MessageParams;
begin
  openGLContext.update;

  if window <> nil then
    begin
      params.rect.top := 0;
      params.rect.left := 0;
      params.rect.width  := Trunc(bounds.size.width);
      params.rect.height := Trunc(bounds.size.height);
      glptPostMessage(windowRef, GLPT_MESSAGE_RESIZE, params);      
    end;
end;

function TOpenGLView.isOpaque: objcbool;
begin
  // return false to make the view transparent
  result := window.backgroundColor.alphaComponent > 0;
end;

function TOpenGLView.isFlipped: objcbool;
begin
  result := true;
end;

function TOpenGLView.defaultPixelFormat: NSOpenGLPixelFormat;

  function Inc (var i: integer): integer;
  begin
    i += 1;
    result := i;
  end;

var
  attributes: array[0..32] of NSOpenGLPixelFormatAttribute;
  i: integer = -1;

  procedure Add(name: NSOpenGLPixelFormatAttribute; value: integer = -1);
  begin
    attributes[Inc(i)] := name;
    if value <> -1 then
      attributes[Inc(i)] := value;
  end;

const
  NSOpenGLPFAOpenGLProfile = 99 { available in 10_7 };
const
  NSOpenGLProfileVersionLegacy = $1000 { available in 10_7 };
  NSOpenGLProfileVersion3_2Core = $3200 { available in 10_7 };
  NSOpenGLProfileVersion4_1Core = $4100 { available in 10_10 };

var
  context: GLPT_Context;
begin
  context := glptContext;

  if context.doubleBuffer then
    Add(NSOpenGLPFADoubleBuffer);

  Add(NSOpenGLPFAColorSize, context.colorSize);
  Add(NSOpenGLPFADepthSize, context.depthSize);
  Add(NSOpenGLPFAStencilSize, context.stencilSize);
  //Add(NSOpenGLPFAOffScreen, 1);

  if context.multiSamples > 0 then
    begin
      Add(NSOpenGLPFAMultisample, 1);
      Add(NSOpenGLPFASampleBuffers, 1);
      Add(NSOpenGLPFASamples, context.multiSamples);
    end;

  // we can only specify "legacy" or "core" on mac and the system will decide what version we actually get
  Add(NSOpenGLPFAOpenGLProfile);
  if context.profile = GLPT_CONTEXT_PROFILE_LEGACY then
    Add(NSOpenGLProfileVersionLegacy)
  else if context.profile = GLPT_CONTEXT_PROFILE_CORE then
    begin
      if context.majorVersion = 3 then
        Add(NSOpenGLProfileVersion3_2Core)
      else if context.majorVersion = 4 then
        Add(NSOpenGLProfileVersion4_1Core)
      else
        glptError(GLPT_ERROR_PLATFORM, 'invalid core profile major version');
    end
  else
    glptError(GLPT_ERROR_PLATFORM, 'invalid context profile');

  // terminate with 0
  Add(0);

  result := NSOpenGLPixelFormat.alloc.initWithAttributes(@attributes).autorelease;
  if result = nil then
    glptError(GLPT_ERROR_PLATFORM, 'invalid NSOpenGLPixelFormat');
end;

procedure TOpenGLView.dealloc;
begin
  if displayLink <> nil then
    CVDisplayLinkRelease(displayLink);
  if displayLinkSemaphore <> nil then
    begin
      displayLinkSemaphore.release;
      displayLinkSemaphore := nil;
    end;

  inherited dealloc;
end;

function TOpenGLView.initWithFrame(frameRect: NSRect): id;
begin
  result := inherited initWithFrame(frameRect);
  if result <> nil then
    begin
      NSNotificationCenter.defaultCenter.addObserver_selector_name_object(result, objcselector('windowDidResize:'), NSWindowDidResizeNotification, nil);
      NSNotificationCenter.defaultCenter.addObserver_selector_name_object(result, objcselector('windowWillStartLiveResize:'), NSWindowWillStartLiveResizeNotification, nil);
      NSNotificationCenter.defaultCenter.addObserver_selector_name_object(result, objcselector('windowDidEndLiveResize:'), NSWindowDidEndLiveResizeNotification, nil);
      NSNotificationCenter.defaultCenter.addObserver_selector_name_object(result, objcselector('frameDidChange:'), NSViewGlobalFrameDidChangeNotification, nil);
    end;
end;

//#########################################################
// GLPT FUNCTIONS
//#########################################################

procedure Cocoa_Delay(ms: longint);
begin
  NSThread.sleepForTimeInterval(ms/1000);
end;

procedure Cocoa_Delay(ms: double);
begin
  NSThread.sleepForTimeInterval(ms);
end;

function Cocoa_GetTime: double;
begin
  result := NSDate.date.timeIntervalSince1970;
end;

function Cocoa_Terminate: boolean;
begin
  NSApp.terminate(nil);
  exit(True);
end;

procedure Cocoa_DestroyWindow(var win: pGLPTwindow);
begin
  win^.ref.close;
  win^.ref := nil;
end;

function TestFlag(const flags: Longint; const bit: Byte): Boolean;
begin
  Result := flags = (flags or bit);
end;

function Cocoa_CreateWindow(win: pGLPTwindow; posx, posy, sizex, sizey: integer; title: PChar): boolean;
var
  window: TCocoaWindow;
  screen: NSScreen;
  windowFlags: NSUInteger = 0;
  openGLView: TOpenGLView;
begin  
  if TestFlag(win^.flags, GLPT_WINDOW_TITLED) then
    windowFlags += NSTitledWindowMask;
  if TestFlag(win^.flags, GLPT_WINDOW_CLOSABLE) then
    windowFlags += NSClosableWindowMask;
  if TestFlag(win^.flags, GLPT_WINDOW_MINIATURIZABLE) then
    windowFlags += NSMiniaturizableWindowMask;
  if TestFlag(win^.flags, GLPT_WINDOW_RESIZABLE) then
    windowFlags += NSResizableWindowMask;

  // if the window is borderless than ignore all other flags
  if TestFlag(win^.flags, GLPT_WINDOW_BORDERLESS) then
    windowFlags := NSBorderlessWindowMask;

  screen := NSScreen.mainScreen;
  if posx = GLPT_WINDOW_POS_CENTER then
    posx := trunc(NSWidth(screen.frame)/2 - sizex/2);
  if posy = GLPT_WINDOW_POS_CENTER then
    posy := trunc(NSHeight(screen.frame)/2 - sizey/2);

  // create cocoa window
  window := TCocoaWindow.alloc.initWithContentRect_styleMask_backing_defer(NSMakeRect(posx, posy, sizex, sizey), windowFlags, NSBackingStoreBuffered, false);
  window.setTitle(NSSTR(title));

  //window.setLevel(CGWindowLevelForKey(kCGMainMenuWindowLevelKey));
  //writeln('level: ', window.level);
  //writeln('cocoa window: ',trunc(window.openGLView.bounds.size.width),'x',trunc(window.openGLView.bounds.size.height));

  // enter fullscreen mode once context is setup
  if TestFlag(win^.flags, GLPT_WINDOW_FULLSCREEN) then
    window.performSelector_withObject_afterDelay(objcselector('toggleFullScreen:'), nil, 0.0);

  window.ref := win;

  // create openGL view
  openGLView := TOpenGLView.alloc.initWithFrame(NSMakeRect(0, 0, sizex, sizey)).autorelease;
  // TODO: include background color in context
  window.contentView.addSubview(openGLView);

  // 
  window.setBackgroundColor(NSColor.blackColor);
  window.makeFirstResponder(openGLView);
  window.setCollectionBehavior(NSWindowCollectionBehaviorFullScreenPrimary);
  window.setAcceptsMouseMovedEvents(true);
  window.makeKeyAndOrderFront(nil);

  win^.glcontext := openGLView.openGLContext;
  win^.ref := window;

  // when running the terminal this helps to make sure
  // window is ordered front after it launches
  //window.performSelector_withObject_afterDelay(objcselector('bringToFront:'), nil, 0.5);

  exit(True);
end;

function Cocoa_MakeCurrent(win: pGLPTwindow): boolean;
begin
  win^.glcontext.makeCurrentContext;

  exit(True);
end;


procedure Cocoa_SwapBuffers(win: pGLPTwindow);
var
  view: TOpenGLView;
begin
  view := TOpenGLView(win^.ref.openGLView);
  if assigned(view.displayLinkSemaphore) then
    view.displayLinkSemaphore.wait;

  // note: on 10.14 NSView.display was giving a black screen
  // https://stackoverflow.com/questions/52938516/opengl-not-rendering-on-macos-mojave
  win^.ref.openGLView.setNeedsDisplay_(true);
end;

procedure Cocoa_GetFrameBufferSize(win: pGLPTwindow; out width, height: integer);
begin
  width := Trunc(win^.ref.openGLView.bounds.size.width);
  height := Trunc(win^.ref.openGLView.bounds.size.height);
end;

procedure Cocoa_PollEvents;
begin
  //NSApp.performSelectorOnMainThread_withObject_waitUntilDone(objcselector('poll'), nil, true);
  NSApp.poll;
end;

procedure Cocoa_GetDisplayCoords(var dr: GLPTRect);
var
  screenFrame: NSRect;
begin
  screenFrame := NSScreen.mainScreen.frame;

  dr.top := Trunc(NSMinY(screenFrame));
  dr.left := Trunc(NSMinX(screenFrame));
  dr.bottom := Trunc(NSMaxY(screenFrame));
  dr.right := Trunc(NSMaxX(screenFrame));
end;

function Cocoa_GetBasePath: string;
begin
  result := NSBundle.mainBundle.resourcePath.UTF8String+'/';
end;

function Cocoa_GetPrefPath (org: string; app: string): string;
var
  applicationSupport: NSURL;
  folder: NSURL;
begin
  applicationSupport := NSFileManager.defaultManager.URLForDirectory_inDomain_appropriateForURL_create_error(NSApplicationSupportDirectory, NSUserDomainMask, nil, false, nil);
  result := applicationSupport.path.UTF8String+'/'+org+'/'+app+'/';
  folder := NSURL.fileURLWithPath(NSSTR(result));
  NSFileManager.defaultManager.createDirectoryAtURL_withIntermediateDirectories_attributes_error(folder, true, nil, nil);
end;

function Cocoa_GetKeyboardShiftState: TShiftState;
var
  modifierFlags: NSUInteger;
begin
  modifierFlags := NSApp.currentEvent.modifierFlags;
  Result := [];

  if modifierFlags = (modifierFlags or NSShiftKeyMask) then
    Include(Result, ssShift);

  if modifierFlags = (modifierFlags or NSControlKeyMask) then
    Include(Result, ssCtrl);

  if modifierFlags = (modifierFlags or NSAlternateKeyMask) then
    Include(Result, ssAlt);

  if modifierFlags = (modifierFlags or NSCommandKeyMask) then
    Include(Result, ssSuper);
end;


procedure SetupMainMenu;

  procedure AddMenu (menu: NSMenu);
  var
    menuItem: NSMenuItem;
  begin
    menuItem := NSMenuItem.alloc.initWithTitle_action_keyEquivalent(menu.title, nil, NSSTR('')).autorelease;
    menuItem.setSubmenu(menu);
    NSApp.mainMenu.addItem(menuItem);
  end;

var
  mainMenu: NSMenu;
  appleMenu: NSMenu;
  windowMenu: NSMenu;
begin

  // main menu
  mainMenu := NSMenu.alloc.init.autorelease;
  NSApp.setMainMenu(mainMenu);

  // apple menu
  appleMenu := NSMenu.alloc.initWithTitle(NSSTR('')).autorelease;
  appleMenu.addItemWithTitle_action_keyEquivalent(NSSTR('Quit '+NSProcessInfo.processInfo.processName.UTF8String), objcselector('terminate:'), NSSTR('q'));

  AddMenu(appleMenu);

  // window menu
  windowMenu := NSMenu.alloc.initWithTitle(NSSTR('Window')).autorelease;
  windowMenu.addItemWithTitle_action_keyEquivalent(NSSTR('Minimize'), objcselector('performMiniaturize:'), NSSTR('m'));
  windowMenu.addItemWithTitle_action_keyEquivalent(NSSTR('Zoom'), objcselector('performZoom:'), NSSTR(''));
  windowMenu.addItemWithTitle_action_keyEquivalent(NSSTR('Enter Full Screen'), objcselector('toggleFullScreen:'), NSSTR('F'));

  AddMenu(windowMenu);
end;

procedure HandleSignal_EINTR(sig: cint); cdecl;
begin
   writeln('***** Receiving signal: ', sig);
end;

function Cocoa_Init(flags: GLPT_InitFlags): boolean;
var
  pool: NSAutoreleasePool;
  app: TCocoaApp;
  delegate: TCocoaAppDelegate;
begin  

  if fpSignal(ESysEINTR, @HandleSignal_EINTR) = signalhandler(SIG_ERR) then
    writeln('fpSignal error: ',fpGetErrno,'.');

  // set mac specific keynames
  GLPT_scancode_names[GLPT_SCANCODE_LALT] := 'Left Option';
  GLPT_scancode_names[GLPT_SCANCODE_LGUI] := 'Left Command';
  GLPT_scancode_names[GLPT_SCANCODE_RALT] := 'Right Option';
  GLPT_scancode_names[GLPT_SCANCODE_RGUI] := 'Right Command';

  // https://hero.handmade.network/forums/code-discussion/t/1409-main_game_loop_on_os_x

  pool := NSAutoreleasePool.alloc.init;

  app := TCocoaApp(TCocoaApp.sharedApplication);
  
  delegate := TCocoaAppDelegate.alloc.init;
  app.setDelegate(delegate);

  NSApp.setActivationPolicy(NSApplicationActivationPolicyRegular);
  NSApp.activateIgnoringOtherApps(true);

  if NSApp.mainMenu = nil then
    SetupMainMenu;
  app.finishLaunching;

  pool.release;

  exit(True);
end;

procedure Cocoa_SetCursor(cursor: byte);
begin
  case cursor of
    GLPT_ARROW_CURSOR:
      NSCursor.arrowCursor.set_;
    GLPT_IBEAM_CURSOR:
      NSCursor.IBeamCursor.set_;
    GLPT_CROSSHAIR_CURSOR:
      NSCursor.crosshairCursor.set_;
    GLPT_HAND_CURSOR:
      NSCursor.openHandCursor.set_;
    GLPT_HRESIZE_CURSOR:
      NSCursor.resizeLeftRightCursor.set_;
    GLPT_VRESIZE_CURSOR:
      NSCursor.resizeUpDownCursor.set_;
    otherwise
      begin
        NSCursor.arrowCursor.set_;
        glptError(GLPT_ERROR_PLATFORM, 'cursor is not supported, using GLPT_ARROW_CURSOR instead.');
      end;
  end;
end;
